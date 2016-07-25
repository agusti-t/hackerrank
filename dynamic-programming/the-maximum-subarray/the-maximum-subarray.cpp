#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

void findMaxes(const vector<int>& v, vector<int>& maxSumContiguous, vector<int>& maxSumNonContiguous, int idx, map<string, int>& maxes) {
    if (idx >= v.size()) {
        return;
    }
    
    //For contiguous max, if what we had until now plus the new value is bigger than the new value by itself,
    //  we adopt it as the new max until now.
    maxSumContiguous[idx] = max(maxSumContiguous[idx-1] + v[idx], v[idx]);
    
    //For non-contiguous, we check first as in the contiguous place, but we are allowed now to keep a non-contiguous
    //  max, that is the second term in the outer max function.
    maxSumNonContiguous[idx] = max(max(maxSumNonContiguous[idx-1] + v[idx], v[idx]), maxSumNonContiguous[idx-1]);
    
    maxes["contiguous"] = max(maxes["contiguous"], maxSumContiguous[idx]);
    maxes["non-contiguous"] = max(maxes["non-contiguous"], maxSumNonContiguous[idx]);
    
    findMaxes(v, maxSumContiguous, maxSumNonContiguous, idx+1, maxes);
}

void findMaxSum(const vector<int>& v) {
    vector<int> maxSumContiguous(v.size());
    vector<int> maxSumNonContiguous(v.size());
    
    if (v.size() > 0) {
        maxSumContiguous[0] = v[0];
        maxSumNonContiguous[0] = v[0];
    } else {
        return;
    }
    
    int idx = 1;
    map <string, int> maxes;
    maxes["contiguous"] = maxSumContiguous[0];
    maxes["non-contiguous"] = maxSumNonContiguous[0];
    findMaxes(v, maxSumContiguous, maxSumNonContiguous, idx, maxes);
        
    cout << maxes["contiguous"] << " " << maxes["non-contiguous"] << endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int cases = -1;
    cin >> cases;
    
    for (int i = 0; i < cases; i++) {
        int size = -1;
        cin >> size;
        
        vector<int> vec;
        for (int j = 0; j < size; j++) {
            int number;
            cin >> number;
            vec.push_back(number);
        }
        
        findMaxSum(vec);
    }
    
    return 0;
}
