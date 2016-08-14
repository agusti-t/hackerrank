#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

constexpr bool debug = true;

void printVector(const vector<unsigned long int>& v, const string& name) {
    cout << "Printing vector - " << name << " of size = " << v.size() << " : [";
    for (unsigned long i = 0; i < v.size()-1; ++i) {
        cout << v[i] << ",";
    }
    cout << v[v.size()-1] << "]";
    cout << endl;
}

unsigned long int findMaxExperienceDP(const vector<unsigned long int>& h, unsigned int i, unsigned int s, unsigned int p, 
		vector<unsigned long int>& withS, vector<unsigned long int>& withP, vector<bool>& calculated, vector<unsigned long int>& maxExp) {
	if (i == h.size()-1) {
		withS[i] = withS[i-1] + (p + s * h[i]);
		withP[i] = withP[i-1] + (p + s * h[i]);
		maxExp[i] = max(withS[i], withP[i]);
		calculated[i] = true;
	} else if (!calculated[i]) {
		withS[i] = maxExp[i-1] + findMaxExperienceDP(h, i+1, s+1, p, withS, withP, calculated, maxExp);
		withP[i] = maxExp[i-1] + findMaxExperienceDP(h, i+1, s, p + s * h[i], withS, withP, calculated, maxExp);
		maxExp[i] = max(withS[i], withP[i]);
		calculated[i] = true;
	}
	return maxExp[i];
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
		
		// if (debug) {
// 			printVector(healthPoints, "healthPoints for case " + to_string(i) + " sorted");
// 		}
        
		vector<unsigned long int> withS(healthPoints.size(), 0);
		vector<unsigned long int> withP(healthPoints.size(), 0);
		vector<unsigned long int> maxExp(healthPoints.size(), 0);
		vector<bool> calculated(healthPoints.size(), false);
		withS[0] = 0;
		withP[0] = maxExp[0] = healthPoints[0];
		calculated[0] = true;
        auto max = findMaxExperienceDP(healthPoints, 0, 1, 0, withS, withP, calculated, maxExp);
		cout << max << endl;
    }
    
    return 0;
}
