#include <string> 
#include <cassert>
#include <iostream>
using namespace std; 

//bool somePredicate(std::string s)
//{
//    return s.empty();
//}
//// Return false if the somePredicate function returns true for at
//         // least one of the array elements; return true otherwise.
//bool allFalse(const std::string a[], int n)
//{   
//    if (n > 0)
//    {
//        if (somePredicate(a[n - 1]))
//            return false;
//        return allFalse(a, n - 1); 
//    }
//    return true; 
//   /* if (n <= 0)
//        return false;
//    if (somePredicate(a[0]))
//        return false; 
//    if (n == 1 && !somePredicate(a[0]))
//        return true;
//    return allFalse(a + 1, n - 1);*/
//}
//
//
//// Return the number of elements in the array for which the
//// somePredicate function returns false.
//int countFalse(const std::string a[], int n)
//{
//    int p;
//    if (n <= 0)
//        return 0;
//    if (!somePredicate(a[0]))
//        p = 1;
//    else
//        p = 0;
//    p += countFalse(a + 1, n - 1);
//    return p;
//}
//
//// Return the subscript of the first element in the array for which
//// the somePredicate function returns false.  If there is no such
//// element, return -1.
//int firstFalse(const std::string a[], int n)
//{
//    if (n <= 0)
//        return -1;
//    if (!somePredicate(a[0]))
//        return 0;
//    int p = firstFalse(a + 1, n - 1);
//    if (p != -1) return(p + 1);
//    return -1;
//}
//
//// Return the subscript of the greatest std::string in the array (i.e.,
//// return the smallest subscript m such that a[m] >= a[k] for all
//// k from 0 to n-1).  If the function is told that no std::strings are to
//// be considered to be in the array, return -1.
//int indexOfMax(const std::string a[], int n)
//{
//    if (n <= 0)
//        return -1; 
//    if (n == 1)
//        return 0;
//    int p = indexOfMax(a + 1, n - 1);
//    if (a[0] >= a[p + 1])
//        return 0;
//    return p + 1;
//}
//
//// If all n2 elements of a2 appear in the n1 element array a1, in
//// the same order (though not necessarily consecutively), then
//// return true; otherwise (i.e., if the array a1 does not include
//// a2 as a not-necessarily-contiguous subsequence), return false.
//// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
//// For example, if a1 is the 7 element array
////    "john" "amy" "ketanji" "sonia" "amy" "ketanji" "elena"
//// then the function should return true if a2 is
////    "amy" "sonia" "elena"
//// or
////    "amy" "ketanji" "ketanji"
//// and it should return false if a2 is
////    "amy" "elena" "sonia"
//// or
////    "john" "sonia" "sonia"
//bool has(const std::string a1[], int n1, const std::string a2[], int n2)
//{
//    if (n2 == 0)
//        return true;
//    if (n1 == 0)
//        return false;
//    if (a1[0] == a2[0])
//        return has(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
//    return has(a1 + 1, n1 - 1, a2, n2);
//}
//bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
int numberOfTimesHas(const string a1[], int n1, const string a2[], int n2);
void order(string a[], int n);
int main() {
    
    string berg[] = { "john", "amy", "ketanji", "sonia", "amy", "ketanji", "elena" };
    string test1[] = { "john", "sonia", "ketanji" };
    string test2[] = { "john", "ketanji", "elena" };
    string test3[] = { "sonia", "john", "ketanji" };
    string test4[] = { "amy", "ketanji", "elena" };

    assert(numberOfTimesHas(berg, 7, test1, 3) == 1);
    assert(numberOfTimesHas(berg, 7, test2, 3) == 2);
    assert(numberOfTimesHas(berg, 7, test3, 3) == 0);
    assert(numberOfTimesHas(berg, 7, test4, 3) == 3);

    //string a[] = { "c", "e", "a", "b", "g", "f" };
    //string b[] = { "d", "b", "c", "b", "d", "a", "b", "c", "d", "a", "e", "b" };
    //assert(numberOfTimesHas(a, 3, b, 3) == 0);
    //assert(numberOfTimesHas(b, 12, a, 3) == 0);
    //order(a, 6);
    //assert(a[0] == "a" && a[1] == "b" && a[2] == "c" && a[3] == "e" && a[4] == "f" && a[5] == "g");

    //order(b, 12);
    //assert(b[0] == "a" && b[1] == "a" && b[2] == "b" && b[3] == "b" && b[4] == "b" && b[5] == "b" && b[6] == "c" && b[7] == "c" && b[8] == "d" && b[9] == "d" && b[10] == "d" && b[11] == "e");

    //string c[] = { "1", "3", "3", "1", "1", "3", "3", "1", "3", "3", "1" };
    //string d[] = { "1", "3", "3" };
    //string e[1] = {};

    //assert(numberOfTimesHas(b, 12, a, 3) == 16);
    //assert(numberOfTimesHas(c, 3, d, 3) == 1);
    //assert(numberOfTimesHas(c, 2, d, 3) == 0);
    //assert(numberOfTimesHas(c, 3, d, 2) == 2);
    //assert(numberOfTimesHas(d, 3, c, 2) == 2);
    //assert(numberOfTimesHas(d, 3, c, 0) == 1);
    //assert(numberOfTimesHas(c, 7, c, 1) == 3); //aliasing !!!
    //assert(numberOfTimesHas(c, 7, e, 0) == 1);
    //assert(numberOfTimesHas(c, 11, d, 1) == 5);
    //assert(numberOfTimesHas(c, 7, d, 3) == 8);
    //assert(numberOfTimesHas(c, 11, d, 3) == 28);

    //cerr << "passed all tests, maybe...";

    /*
    per the spec, in the numberOfTimesHas function, you cannot check strings more than (n1+1) choose n2 times.
    This means that if n2 = n1+1, then you can only check once, and if n2 > n1+1, you cannot check at all
    If n1 = n2, you can only check strings n1+1 times. Apply these tests and put a cerr statement in the appropriate
    places in your code (after a comparison of two strings). If you exceed the number of comparisons on the right of
    each of the following test cases, then you haven't passed all test cases yet. comment out the test cases on top
    so you don't get swarmed with those messages.
    */

    string spec1[] = { "the", "final", "boss", "!!" };
    string spec2[] = { "the", "final", "boss", };

    //comment out to check each individual test case
    //assert(numberOfTimesHas(spec2, 3, spec1, 3) == 1); //must not make more than 4 comparisons
    //assert(numberOfTimesHas(spec2, 3, spec1, 4) == 0); //must not make more than 1 comparison
    //assert(numberOfTimesHas(spec1, 2, spec2, 4) == 0); //must not make any comparisons

    string spec3[] = { "1", "1", "1", "1", "1" };
    string spec4[] = { "1", "1", "1", "1", "1" };

    //assert(numberOfTimesHas(spec3, 5, spec4, 0) == 1); //must not make more than 1 comparison
    //assert(numberOfTimesHas(spec3, 5, spec4, 1) == 5); //must not make more than 6 comparisons
    //assert(numberOfTimesHas(spec3, 5, spec4, 2) == 10); //must not make more than 15 comparisons
    //assert(numberOfTimesHas(spec3, 5, spec4, 3) == 10); //must not make more than 20 comparisons
    //assert(numberOfTimesHas(spec3, 5, spec4, 4) == 5); //must not make more than 15 comparisons
    //assert(numberOfTimesHas(spec3, 5, spec4, 5) == 1); //must not make more than 6 comparisons

    cerr << "passed all tests, yippee!!";

    return 0;

    
  
}