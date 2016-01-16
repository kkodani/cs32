// linear.cpp



// Return true if any of the strings in the array is empty, false
// otherwise.
bool anyEmpty(const string a[], int n)
{
	if(n<=0)
		return false;
	if(a[0].empty())
		return true;
	return anyEmpty((a+1), n-1);
}

// Return the number of empty strings in the array.
int countEmpties(const string a[], int n)
{
	if(n<=0)
		return 0;
	if(a[0].empty())
		return 1+countEmpties((a+1), n-1);
	return countEmpties((a+1), n-1);
}

// Return the subscript of the first empty string in the array.
// If no element is empty, return -1.
int firstEmpty(const string a[], int n)
{
	if(n<=0)
		return -1;
	if(a[0].empty())
		return 0;
	int i=firstEmpty((a+1), n-1);
	if(i==-1)
		return -1;
	else
		return i+1;
}

// Return the subscript of the least string in the array (i.e.,
// the smallest subscript m such that there is no k for which
// a[k] < a[m].  If the array has no elements to examine, return -1.
int indexOfLeast(const string a[], int n)
{
	int pos = 0;
	if(n<=1)
		return 0;
	pos=indexOfLeast(a+1, n-1);
	if (a[0]<=a[pos+1])
		return 0;
	else
		return pos+1;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
	if(n2<=0)
		return true;
	if(n1<=0 && n2>0)
		return false;
	if(n2>n1)
		return false;
	if(a1[0]==a2[0])
		return includes((a1+1), n1-1, (a2+1), n2-1);
	return includes((a1+1), n1-1, a2, n2);
}


