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

unsigned long int findMaxExperienceDP(const vector<unsigned long int>& h, unsigned int i, unsigned int s, unsigned int p, 
		vector<unsigned long int>& withS, vector<unsigned long int>& withP, vector<bool>& calculated) {
	if (i == h.size()-1) {
		withS[i] = (p + s * h[i]);
		withP[i] = (p + s * h[i]);
		calculated[i] = true;
	} else if (i == 0) {
		withS[i] = findMaxExperienceDP(h, i+1, s+1, p, withS, withP, calculated);
		withP[i] = findMaxExperienceDP(h, i+1, s, p + s * h[i], withS, withP, calculated);
	} else if (!calculated[i]) {
		if (debug) {
			printVector(withS, "withS iteration (before recursion) : " + to_string(i));
			printVector(withP, "withP iteration (before recursion) : " + to_string(i));
		}
		withS[i] = findMaxExperienceDP(h, i+1, s+1, p, withS, withP, calculated);
		withP[i] = findMaxExperienceDP(h, i+1, s, p + s * h[i], withS, withP, calculated);
		calculated[i] = true;
		if (debug) {
			printVector(withS, "withS iteration : " + to_string(i));
			printVector(withP, "withP iteration : " + to_string(i));
		}
	} else if (calculated[i]) {
		if (debug) {
			cout << "Already calculated : " << i << endl;
		}
	}
	return max(withS[i], withP[i]);
}

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
		// reverse(healthPoints.begin(), healthPoints.end());
		
		if (debug) {
			printVector(healthPoints, "healthPoints for case " + to_string(i) + " sorted");
		}
        
		vector<unsigned long int> withS(healthPoints.size(), 0);
		vector<unsigned long int> withP(healthPoints.size(), 0);
		vector<bool> calculated(healthPoints.size(), false);
		auto maxExperience = findMaxExperienceDP(healthPoints, 0, 1, 0, withS, withP, calculated);
		cout << maxExperience << endl;
    }
    
    return 0;
}
