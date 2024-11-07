#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

// Remove the even integers from v.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original vector.
void removeEven(vector<int>& v)
{	
	for (vector<int>::iterator p = v.begin(); p != v.end();) {
		if (*p % 2 == 0) 
			p = v.erase(p);
		else
			p++; 
	}
}

//void test()
//{
//	int a[9] = { 4, 1, 7, 6, 5, 8, 0, 3, 2 };
//	vector<int> x(a, a + 9);  // construct x from the array
//	assert(x.size() == 9 && x.front() == 4 && x.back() == 2);
//	removeEven(x);
//	assert(x.size() == 4);
//	sort(x.begin(), x.end());
//	int expect[4] = { 1, 3, 5, 7 };
//	for (int k = 0; k < 4; k++)
//		assert(x[k] == expect[k]);
//}
//
//int main()
//{
//	test();
//	cout << "Passed" << endl;
//}