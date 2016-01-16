// eval.cpp


#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;


bool validate(const string& infix);
void convert(const string& infix, string& postfix);

int evaluate(const string& infix, string& postfix, bool& result)
{
	// validate infix string
	if(validate(infix))
	{
		convert(infix, postfix);
		/*
		When the loop is finished, the operand stack will contain one item, the result of evaluating the expression
		*/
		
		char current;
		char op1;
		char op2;
		stack<char> operands;
		for(int i=0; i<postfix.length(); i++)
		{
			current=postfix[i];
			if(current=='F' || current=='T')
			{
				operands.push(current);
			}
			
			else if(current=='!')
			{
				op1=operands.top();
				operands.pop();
				if(op1=='T')
				{
					operands.push('F');
				}
				else	// op1=='F'
				{
					operands.push('T');
				}
			}
			
			else		// current=='|' || current=='&'
			{
				op2=operands.top();
				operands.pop();
				op1=operands.top();
				operands.pop();
				
				if(current=='&')
				{
					if(op1=='T' && op2=='T')
					{
						operands.push('T');
					}
					else
					{
						operands.push('F');
					}

				}
				if(current=='|')
				{
					if(op1=='F' && op2=='F')
					{
						operands.push('F');
					}
					else
					{
						operands.push('T');
					}
				}
			}

		}
		
		if(operands.top()=='F')
		{
			result=false;
		}
		else	// operands.top()=='T'
		{
			result=true;
		}
		
		return 0;
	}
	
	else
	{
		return 1;
	}
}


int main()
{
	
}

bool validate(const string& infix)
{
	char current;
	char next;
	string noSpace="";
	
	// create a string with no spaces in it to make validation easier
	for(int i=0; i<infix.length(); i++)
	{
		current=infix[i];
		if(current!=' ')
		{
			noSpace+=current;
		}
	}
	
	char final=noSpace[noSpace.length()-1];
	
	// check last char of string to see if valid
	if(final!='T' && final!='F' && final!=')')
	{
		return false;
	}
	
	// check for empty string
	if(infix.length()==0)
	{
		return false;
	}
	
	// check for string of length 1
	if(infix.length()==1)
	{
		if(infix[0]!='F' && infix[0]!='T')
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
	// check for balance of parantheses
	int openers=0;
	int closers=0;
	for(int i=0; i<noSpace.length(); i++)
	{
		current=noSpace[i];
		if(current=='(')
		{
			openers++;
		}
		if(current==')')
		{
			closers++;
		}
	}
	
	if(closers!=openers)
	{
		return false;
	}
	
	// check each char in the string and its following char
	for(int i=0; i<noSpace.length()-1; i++)
	{
		current=noSpace[i];
		next=noSpace[i+1];
		
		if(current=='T')
		{
			if(next!=')' && next!='|' && next!='&')
			{
				return false;
			}
		}
		
		else if(current=='F')
		{
			if(next!=')' && next!='|' && next!='&')
			{
				return false;
			}
		}
		
		else if(current=='!')
		{
			if(next!='T' && next!='F' && next!='(' && next!='!')
			{
				return false;
			}
		}
		
		else if(current=='&')
		{
			if(next!='T' && next!='F' && next!='(' && next!='!')
			{
				return false;
			}
		}
		
		else if(current=='|')
		{
			if(next!='T' && next!='F' && next!='(' && next!='!')
			{
				return false;
			}
		}
		
		else if(current=='(')
		{
			if(next!='T' && next!='F' && next!='!')
			{
				return false;
			}
		}
		
		else if(current==')')
		{
			if(next!='|' && next!='&')
			{
				return false;
			}
		}
		
		else
		{
			return false;
		}
	}
	
	return true;
}

void convert(const string& infix, string& postfix)
{
	postfix="";
	stack<char> operators;
	char current;
	for(int i=0; i<infix.length(); i++)
	{
		current=infix[i];
		switch(current)
		{
			case 'T':
				postfix+=current;
				break;
				
			case 'F':
				postfix+=current;
				break;
				
			case '(':
				operators.push(current);
				break;
				
			case ')':
				while(operators.top()!='(')
				{
					postfix+=operators.top();
					operators.pop();
				}
				operators.pop();
				break;
				
			case '!':
				while(!operators.empty() && operators.top()!='(' && operators.top()!='&' && operators.top()!='|')
				{
					postfix+=operators.top();
					operators.pop();
				}
				operators.push(current);
				break;
				
			case '&':
				while(!operators.empty() && operators.top()!='(' && operators.top()!='|')
				{
					postfix+=operators.top();
					operators.pop();
				}
				operators.push(current);
				break;
				
			case '|':
				while(!operators.empty() && operators.top()!='(')
				{
					postfix+=operators.top();
					operators.pop();
				}
				operators.push(current);
				break;
				
			default:		// when current==' '
				break;
		}
	}
	while(!operators.empty())
	{
		postfix+=operators.top();
		operators.pop();
	}
}





