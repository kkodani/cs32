// Dictionary.cpp

// This is a correct but horribly efficient implementation of Dictionary
// functionality.


//  /Users/kkodani/Desktop/Kyle/Sophomore Q3/CS32/Project 4/words.txt

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <algorithm>  // for swap
#include <vector>
using namespace std;

//					a  b  c  d  e   f   g   h   i   j   k   l   m   n
const int primes[]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
//					o   p   q   r   s   t   u   v   w   x   y   z
				    47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
const int SIZE=49999;


void removeNonLetters(string& s);
//string sorta(const string& word);
//string merge(string& word1, string& word2);

  // This class does the real work of the implementation.

class DictionaryImpl
{
  public:
    DictionaryImpl() {}
    ~DictionaryImpl() {}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
	int hashFunction(const string& word) const;
  private:
     vector<string> m_words[SIZE];
};

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    int pos=hashFunction(word);
	m_words[pos].push_back(word);
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == NULL)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;
	string sorted=letters;
	sort(sorted.begin(), sorted.end());

	string current;
    int pos=hashFunction(letters);
	for(int i=0; i<m_words[pos].size(); i++)
	{
		current=m_words[pos][i];
		sort(current.begin(), current.end());

		if(current==sorted)
		{
			callback(m_words[pos][i]);
		}
	}

}


int DictionaryImpl::hashFunction(const string& word) const
{
	unsigned long hashNum=1;
	//int temp;
	//int t;
	//string sorted=sort(word);
	for(int i=0; i<word.length(); i++)
	{
		//t=word[i]-'a';
		//temp=primes[(word[i]-'a')];
		hashNum*=primes[(word[i]-'a')];
	}
	
	
	return hashNum%SIZE;
}


/* This is my beautiful mergesort algorithm that I wrote myself.
   It works, but it is slow.  I still love it however, since I created it.
   It is like my child, my baby.  However, it was brought to my attention
   that we are allowed to used the STL sort algorithm, which is much faster.
   Of course, this is the algorithm I ultimately used.
   I feel guilty for throwing my child to the wolves in order to shave off
   a few extra milliseconds and to get a precious higher score on my project.
   Look at what this class has reduced me to.  I have become a monster.



string merge(string& word1, string& word2)
{
	string result="";
	while(word1.size()>0 || word2.size()>0)
	{
        if(word1.size()>0 && word2.size()>0)
		{
            if(word1[0]<=word2[0])
			{
                result+=word1[0];
				word1=word1.substr(1, word1.size()-1);
			}
			else
			{
				result+=word2[0];
				word2=word2.substr(1, word2.size()-1);
			}
		}
		else if(word1.size()>0)
		{
			result+=word1[0];
			word1=word1.substr(1, word1.size()-1);
			
		}
		else if(word2.size()>0)
		{
			result+=word2[0];
			word2=word2.substr(1, word2.size()-1);
		}
	}
	return result;
}

string sorta(const string& word)
{
	if(word.size()<=1)
	{
		return word;
	}
	int length=word.size();
	string w1=word.substr(0,length/2);
	string w2=word.substr(length/2, length-1);
	w1=sorta(w1);
	w2=sorta(w2);
	return merge(w1, w2);
}
*/


void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop off everything from "to" to end.
} 






//******************** Dictionary functions **********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code.

Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters, callback);
}
