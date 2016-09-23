#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

constexpr bool debug = false;

using UChar = unsigned char;
using ULInt = unsigned long int;
using UInt = unsigned int;

template <typename Container>
void printContainer(const Container& c, const string& name) {
    cout << "Printing container - " << name << " of size = " << c.size() << " : [";
    for (auto i = c.begin(); i != prev(c.end()); ++i) {
        cout << *i << ",";
    }
	cout << *prev(c.end()) << "]" << endl;
}

template <typename Matrix>
void printMatrix(const Matrix& m, const string& name) {
    auto mSize = m.size() > 0 ? m.size() * m[0].size() : 0;
    cout << "Printing matrix - " << name << " of size = " 
        << mSize << " : {" << endl;
    for (auto i = 0; i < m.size(); ++i) {
        cout << "[";
        for (auto j = 0; j < m[i].size()-1; ++j) {
            cout << m[i][j] << ",";
        }
        cout << m[i][m[i].size()-1] << "]," << endl;
    }
	cout << "}" << endl;
}

ULInt findLISn2(const vector<ULInt>& s) {
	vector<ULInt> lises(s.size(), 0);
	auto lis = static_cast<ULInt>(1);
	auto tempLis = static_cast<ULInt>(1);
	auto tempMin = static_cast<ULInt>(0);
    lises[0] = 1;
    
	if (debug) printContainer(lises, "lises");
    if (debug) printContainer(s, "sequence");
    if (debug) cout << endl << endl;
    
    for (auto i = 1; i < s.size(); ++i) {
        if (debug) cout << "i is : " << i << " and s[i] : " << s[i] << endl;
        
        tempMin = s[0];
        tempLis = 1;
        for (auto k = 0; k < i; ++k) {
            if (lises[k] >= tempLis && s[k] < s[i]) {
                tempLis = lises[k];
                tempMin = s[k];
                if (debug) cout << "found a better lis at index k = " << k << " number is s[k] = " << tempMin << " and with lenght " << tempLis << endl;
            }
        }
        
		if (s[i] > tempMin) {
			++tempLis;
		} else {
            tempLis = 1; 
		}
        
        lises[i] = tempLis;
		lis = max(lis, lises[i]);
        
        if (debug) cout << s[i] << " "; 
		if (debug) cout << "tempLis " << tempLis << endl;
		if (debug) printContainer(lises, "lises " + to_string(i));
        if (debug) printContainer(s, "sequence");
        if (debug) cout << endl;
	}
	
	return lis;
}

//This is a binary search function O(log N).
//We need a sorted vector to perform a binary search and in this case it is
//given by the elements of s indexed with the elements stored in t.
//On each iteration we split the part of the vector where we are looking for our
//value v in 2 and depending on if v is greater or equal or less than the element
//at the middle of the split, we keep looking on one side or the other.
//ref: https://en.wikipedia.org/wiki/Binary_search_algorithm
ULInt findCeiling(const vector<ULInt>& s, const vector<ULInt>& t, ULInt v, ULInt end) {
    auto beginning = static_cast<ULInt>(0);
    while (end > beginning + 1) {
        auto p = beginning + (end - beginning) / 2;
        if (s[t[p]] >= v) {
            end = p;
        } else {
            beginning = p;
        }
    }
    
    return end;
}

//So this is the O(N*log N) in time complexity solution and the one 
//required to pass the hackerrank test cases.
//Let's abbreviate Longest Increasing Subsequence as LIS.
//
//Let's explain it with an example. Consider the sequence:
//                    s = {5,2,3,6,4,5}
//
//We create two helper vectors called temp and res. temp will keep the
//indexes of the smallest element of the sequence with which a LIS of 
//certain length ends. res will keep indexes pointing at the elements
//that form the final LIS, this is only needed if we are interested in
//printing the LIS.
//We also have a variable len that keeps the length of the longest LIS.
//
//Let's do the iterations in detail. We start by setting the index
//of the LIS of length 0 as 0, i.e. at the beginning we have 1 LIS of
//length 1 formed by the first element in s (s[0]=5). We start with the 1st
//iteration (note there will be s.size()-1 iterations since we have a base
//case when s.size() == 1):
//  1- temp : [1,0,0,0,0,0]
//      res : [0,0,0,0,0,0]
//      len : 0
//     in this iteration we have s[1] = 2 smaller than the minimum number
//     we had stored for a LIS of length one s[temp[0]] = s[0] = 5 and
//     2 < 5 so our new minimum for a LIS of length 1 is 2 and temp[0] = 1.
//
//  2- temp : [1,2,0,0,0,0]
//      res : [0,0,1,0,0,0]
//      len : 1
//     now s[2] = 3 and since it is greater than the maximum number of the
//     current longest LIS, i.e. 2, the current maximum LIS length is
//     increased by 1, we also store the index of the previous element for
//     the LIS of which this element is part of in res[2] = 1. Finally we set
//     the current element as the minimum number that needs to be surpassed in
//     order to get a longer LIS.
//
//  3- temp : [1,2,3,0,0,0]
//      res : [0,0,1,2,0,0]
//      len : 2
//     this iteration has s[3] = 3 and is exactly like iteration 2.
//
//  4- temp : [1,2,4,0,0,0]
//      res : [0,0,1,2,2,0]
//      len : 2
//     for this iteration we have s[4] = 4 and since it is neither greater than
//     the current minimum number for the longest LIS (i.e 6) nor smaller than
//     the minimum number for a LIS of length 1 (i.e. 2), this is a candidate to
//     replace the minimum number for a LIS of length inferior to the current max.
//     The res vector from iteration 3 tells us the maximum LIS is {2,3,6}, this is
//     a sorted sequence and so we can perform a binary search to find the ceiling
//     of 4, i.e. the element of temp that is greater than 4. This number is 6 and
//     so we can change the minimum number that needs to be surpassed to create
//     a LIS of length > 3 from 6 to 4 and so the res vector after this iteration
//     will represent the sequence {2,3,4}.
//
//  5- temp : [1,2,4,5,0,0]
//      res : [0,0,1,2,2,4]
//      len : 3
//     the final iteration is a repetition of iteration 3 and 2.       
ULInt findLISnlogn(const vector<ULInt>& s) {
    vector<ULInt> temp(s.size(), 0);
    vector<ULInt> res(s.size(), 0);
    auto len = static_cast<ULInt>(0);
    
    temp[0] = 0;
    
    for (auto i = 1; i < s.size(); ++i) {
        if (s[i] > s[temp[len]]) {
            res[i] = temp[len];
            ++len;
            temp[len] = i;
        } else if (s[i] <= s[temp[0]]) {
            temp[0] = i;
        } else {
            auto c = findCeiling(s, temp, s[i], len);
            temp[c] = i;
            res[i] = temp[c-1];
        }
        
        if (debug) {
            printContainer(temp, "temp");
            printContainer(res, "res");
            cout << "len : " << len << endl;
        }
    }
    
    if (debug) {
        vector<ULInt> lis;
        auto nextIndex = temp[len];
        for (auto i = 0; i < len+1; ++i) {
            lis.push_back(s[nextIndex]);
            nextIndex = res[nextIndex];    
        }
        reverse(lis.begin(), lis.end());
        printContainer(lis, "lis");
    }
    
    return len+1;
}

int main() {
    auto n = static_cast<ULInt>(0);
    cin >> n;
    
	vector<ULInt> sequence;
    for (auto i = 0; i < n; ++i) {
        auto elem = static_cast<ULInt>(0);
 	   	cin >> elem;
        sequence.push_back(elem);
	}
	
	if (debug) printContainer(sequence, "sequence");
	
	cout << findLISnlogn(sequence) << endl;
	
	return 0;
}