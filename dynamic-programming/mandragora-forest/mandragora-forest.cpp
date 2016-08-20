#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr bool debug = false;

void printVector(const vector<unsigned long int>& v, const string& name) {
    cout << "Printing vector - " << name << " of size = " << v.size() << " : [";
    for (unsigned long i = 0; i < v.size()-1; ++i) {
        cout << v[i] << ",";
    }
    cout << v[v.size()-1] << "]";
    cout << endl;
}

unsigned long long int findMaxExperienceIt(const vector<unsigned long int>& h) {
	unsigned long long int max = 0;
	auto hSize = h.size();
	for (auto i = 0; i < h.size(); ++i) {
		unsigned long long int sum = 0;
		for (auto j = 0; j <= i; ++j) {
			sum += h[j] * (hSize - i);
		}
		// cout << "sum is : " << sum << " and max is : " << max << " iteration is : " << i << endl;
		if (sum > max) {
			max = sum;
		} else {
			break;
		}
	}
	return max;
}

// unsigned long int findMaxExperienceDP(const vector<unsigned long int>& h, unsigned int i, unsigned int s, unsigned int p,
// 		vector<unsigned long int>& withS, vector<unsigned long int>& withP, vector<bool>& calculated) {
//
//
//
// 		if (debug) {
// 			printVector(withS, "withS iteration (before recursion) : " + to_string(i));
// 			printVector(withP, "withP iteration (before recursion) : " + to_string(i));
// 		}
//
// 		if (debug) {
// 			printVector(withS, "withS iteration : " + to_string(i));
// 			printVector(withP, "withP iteration : " + to_string(i));
// 		}
// 	} else if (calculated[i]) {
// 		if (debug) {
// 			cout << "Already calculated : " << i << endl;
// 		}
// 	}
// }

// unsigned long int findMaxExperience(const vector<unsigned long int>& h, unsigned int i, unsigned int s, unsigned int p,
// 		vector<unsigned long int>& withS, vector<unsigned long int>& withP, vector<bool>& calculated, vector<unsigned long int>& maxExp) {
// 	if (i == 0) {
// 		return p + h[i] * s;
// 	} else if (calculated[i]) {
// 		if (debug) {
// 			cout << "calculated[" << i << "] = " << maxExp[i] << endl;
// 		}
// 		return maxExp[i];
// 	} else {
// 		findMaxExperienceDP(h, i, s, p, withS, withP, calculated, maxExp);
		// calculated[i] = true;
// 		withS[i] = findMaxExperience(h, i-1, s+1, p, withS, withP, calculated);
// 		withP[i] = findMaxExperience(h, i-1, s, p + s * h[i], withS, withP, calculated);
// 		if (debug) {
// 			cout << "withS[ " << i << "] = " << withS[i] << endl;
// 			cout << "withP[ " << i << "] = " << withP[i] << endl;
// 		}
// 		return max(withS[i], withP[i]);
// 	}
// }

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    unsigned int cases {1};
    cin >> cases;
	
	if (debug) {
		cout << "cases : " << cases << endl;
	}
    
    for (auto i = 0; i < cases; ++i) {
        unsigned int mandragoras {1};
        cin >> mandragoras;
        
        vector<unsigned long int> healthPoints;
        for (int j = 0; j < mandragoras; ++j) {
            unsigned int health {1};
            cin >> health;
            healthPoints.push_back(health);
        }
		
		// if (debug) {
// 			printVector(healthPoints, "healthPoints for case " + to_string(i) + " unsorted");
// 		}
		
		sort(healthPoints.begin(), healthPoints.end());
		reverse(healthPoints.begin(), healthPoints.end());
		
		if (debug) {
			printVector(healthPoints, "healthPoints for case " + to_string(i) + " sorted");
		}
        
		vector<unsigned long int> withS(healthPoints.size(), 0);
		vector<unsigned long int> withP(healthPoints.size(), 0);
		vector<bool> calculated(healthPoints.size(), false);
		auto maxExperience = findMaxExperienceIt(healthPoints);
		// auto maxExperience = findMaxExperienceDP(healthPoints, 0, 1, 0, withS, withP, calculated);
		cout << maxExperience << endl;
    }
    
    return 0;
}
