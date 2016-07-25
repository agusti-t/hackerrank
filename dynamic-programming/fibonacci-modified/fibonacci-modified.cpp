#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

unsigned long int findFibonacciModified(vector<unsigned long int>& terms, vector<bool>& calculated, int n) {
    if (calculated[n]) {
        return terms[n];
    }
    
    terms[n] = findFibonacciModified(terms, calculated, n-2) 
        + pow(findFibonacciModified(terms, calculated, n-1), 2);
    calculated[n] = true;
    
    return terms[n];
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    cin >> n;
    
    vector<unsigned long int> terms(n+1);
    vector<bool> calculated(n+1, false);
        
    cin >> terms[0];
    cin >> terms[1];
    
    calculated[0] = true;
    calculated[1] = true;
    
    cout << findFibonacciModified(terms, calculated, n) << endl;
    
    return 0;
}
