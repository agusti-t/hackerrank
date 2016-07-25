#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <iterator>
#include <cstddef>

using namespace std;

void formatLongNumber(vector<unsigned int>& v, int number) {
    v.push_back(number % 10);
    
    if (number / 10 != 0) {
        formatLongNumber(v, number / 10);
    }
}

void printLongNumber(const vector <unsigned int>& number) {
    std::copy(number.rbegin(), number.rend(), std::ostream_iterator<unsigned int>(std::cout, ""));
    cout << endl;
}

void doPartialLongNumbersSum(vector<unsigned int>& result, unsigned int partialDigitsSum, int i) {
    vector<unsigned int> temp;
    
    formatLongNumber(temp, partialDigitsSum);
    
    for (auto j = 0; j < temp.size(); j++) {
        result[i+j] = temp[j]; 
    }
}

vector<unsigned int> addLongNumbers(const vector<unsigned int>& a, const vector<unsigned int>& b) {
    const auto longestVec = a.size() >= b.size() ? a : b;
    const auto shortestVec = a.size() >= b.size() ? b : a;
    auto longest = max(a.size(), b.size());
    auto shortest = min(a.size(), b.size());
    
    vector<unsigned int> result(longest+1);
    
    for (auto i = 0; i < shortest; i++) {
        doPartialLongNumbersSum(result, a[i] + b[i] + result[i], i);
    }
    
    if (longest > shortest) {
        int possibleCarryIndex = shortest;
        while (result[possibleCarryIndex] != 0) {
            doPartialLongNumbersSum(result, longestVec[possibleCarryIndex] + result[possibleCarryIndex], possibleCarryIndex);
            possibleCarryIndex++;
        }
        
        for (int k = possibleCarryIndex; k < longest; k++) {
            result[k] = longestVec[k];
        }
    }
    
    return result;
}

vector<unsigned int> multiplyLongNumbers(const vector<unsigned int>& a, const vector<unsigned int>& b) {
    const auto longestVec = a.size() >= b.size() ? a : b;
    const auto shortestVec = a.size() >= b.size() ? b : a;
    auto longest = max(a.size(), b.size());
    auto shortest = min(a.size(), b.size());
    
    return {};
}

vector<unsigned int> findFibonacciModified(vector<vector <unsigned int>>& terms, vector<bool>& calculated, int n) {
    
//    cout << endl << "n = " << n << " - calculated[n] = " << calculated[n] << " - terms[n] = "; printLongNumber(terms[n]); cout << endl;
    
    if (calculated[n]) {
        return terms[n];
    }
    
    terms[n] = addLongNumbers(findFibonacciModified(terms, calculated, n-2), findFibonacciModified(terms, calculated, n-1));
    calculated[n] = true;
    
    return terms[n];
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t1;
    cin >> t1;
    
    int t2;
    cin >> t2;
    
    int n;
    cin >> n;
    
    vector<vector<unsigned int>> terms(n);
    vector<bool> calculated(n, false);
    
    formatLongNumber(terms[0], t1);
    formatLongNumber(terms[1], t2);
    
    /*formatLongNumber(terms[3], 40);
    printLongNumber(terms[3]);
    
    formatLongNumber(terms[4], 10);
    printLongNumber(terms[4]);*/
    
    //printLongNumber(multiplyLongNumbers(terms[3], terms[4]));
    
    calculated[0] = true;
    calculated[1] = true;
    
    vector<unsigned int> searchedTerm = findFibonacciModified(terms, calculated, n-1);
    /*reverse(searchedTerm.begin(), searchedTerm.end());
    searchedTerm.resize(searchedTerm.size());*/
    printLongNumber(searchedTerm);
    
    return 0;
}
