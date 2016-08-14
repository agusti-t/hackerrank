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

unsigned long int findMaxExperience(const vector<unsigned long int>& h, unsigned int i, unsigned int s, unsigned int p) {
	if (i == h.size()-1) {
		return p + h[i] * s;
	} else {
		auto maxEating = findMaxExperience(h, i+1, s+1, p);
		auto maxBattling = findMaxExperience(h, i+1, s, p + s * h[i]);
		return max(maxEating, maxBattling);
	}
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    unsigned int cases {1};
    cin >> cases;
	
	if (debug) {
		cout << "cases : " << cases << endl;
	}
    
    for (auto i = 0; i < cases; i++) {
        unsigned int mandragoras {1};
        cin >> mandragoras;
        
        vector<unsigned long int> healthPoints;
        for (int j = 0; j < mandragoras; ++j) {
            unsigned int health {1};
            cin >> health;
            healthPoints.push_back(health);
        }
		
		if (debug) {
			printVector(healthPoints, "healthPoints for case " + to_string(i) + " unsorted");
		}
		
		sort(healthPoints.begin(), healthPoints.end());
		
		if (debug) {
			printVector(healthPoints, "healthPoints for case " + to_string(i) + " sorted");
		}
        
        //auto maxExp = findMaxExperience(healthPoints, 0, 1, 0);
		//cout << maxExp << endl;
    }
    
    return 0;
}
