#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void printVector(const vector<unsigned long int>& v, const string& name) {
    cout << "Printing vector - " << name << " of size = " << v.size() << " : [";
    for (unsigned long i = 0; i < v.size()-1; ++i) {
        cout << v[i] << ",";
    }
    cout << v[v.size()-1] << "]";
    cout << endl;
}

unsigned long long int findMaxExperienceIt(const vector<unsigned long int>& h) {
	auto hSize = h.size();
	auto max = static_cast<unsigned long long int>(h[0] * hSize);
	auto sum = max;
	auto less = static_cast<unsigned long long int>(0);
	for (auto i = 1; i < hSize; ++i) {
		less += h[i-1];
		sum += h[i] * (hSize - i) - less;
		if (sum > max) {
			max = sum;
		} else {
			break;
		}
	}
	return max;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    unsigned int cases {1};
    cin >> cases;
    
    for (auto i = 0; i < cases; ++i) {
        auto mandragoras = static_cast<unsigned int>(1);
        cin >> mandragoras;
        
        vector<unsigned long int> healthPoints;
        for (auto j = 0; j < mandragoras; ++j) {
			auto health = static_cast<unsigned int>(1);
            cin >> health;
            healthPoints.push_back(health);
        }
		
		sort(healthPoints.begin(), healthPoints.end());
		reverse(healthPoints.begin(), healthPoints.end());
		        
		auto maxExperience = findMaxExperienceIt(healthPoints);
		cout << maxExperience << endl;
    }
    
    return 0;
}
