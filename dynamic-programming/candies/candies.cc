#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr bool debug = false;

template <typename Container>
void printContainer(const Container& c, const string& name) {
    cout << "Printing container - " << name << " of size = " << c.size() << " : [";
    for (auto i = 0; i < c.size()-1; ++i) {
        cout << c[i] << ",";
    }
    cout << c[c.size()-1] << "]" << endl;
}

unsigned long int findMinCandies(const vector<unsigned long int>& r) {
	auto minCandies = static_cast<unsigned long int>(1);
	auto candyDiffUp = static_cast<unsigned long int>(1);
	auto candyDiffDown = static_cast<unsigned long int>(0);
    auto lastUp = static_cast<unsigned long int>(0);
	
	for (auto i = 1; i < r.size(); ++i) {
		if (r[i] < r[i-1]) {
			if (debug) {
				cout << "r[i] <  r[i-1]";
			}
            if (candyDiffDown == 0) {
                lastUp = candyDiffUp;
            }
			candyDiffUp = 1;
			++candyDiffDown;
			minCandies += candyDiffDown;
		} else if(r[i] == r[i-1]) {
			if (debug) {
				cout << "r[i] == r[i-1]";
			}
			candyDiffUp = 1;
			candyDiffDown = 0;
			minCandies += 1;
        } else {
			if (debug) {
				cout << "r[i] >  r[i-1]";
			}
            if ((lastUp > 0) && (lastUp <= candyDiffDown)) {
                if (debug) cout << " (adding lastUp = " << candyDiffDown - lastUp + 1 << ")";
                minCandies += 1 + candyDiffDown - lastUp;
                lastUp = 0;
            }
			candyDiffDown = 0;
			++candyDiffUp;
            minCandies += candyDiffUp;
		}
		if (debug) {
			cout << " minCandies = " << minCandies << " - candyDiffUp = " << candyDiffUp
				 << " - candyDiffDown = " << candyDiffDown << " - lastUp = " << lastUp
                 << " | r[" << i << "] = " << r[i] << " : r[" << i-1 
                 << "] = " << r[i-1] << endl;
		}
	}
    
    if (lastUp > 0) {
		if (lastUp <= candyDiffDown) {
        	if (debug) cout << "(adding LAST lastUp = " << candyDiffDown - lastUp + 1 << ")" << endl;
        	minCandies += 1 + candyDiffDown - lastUp;
        	lastUp = 0;
		} else {
        	if (debug) cout << "(adding LAST lastUp by ITSELF = " << lastUp << ")" << endl;
        	minCandies += lastUp;
        	lastUp = 0;
		}
    }
	    
	return minCandies;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    auto children = static_cast<unsigned long int>(0);
    cin >> children;
    
	vector<unsigned long int> ratings;
    for (auto i = 0; i < children; ++i) {
        auto rating = static_cast<unsigned long int>(0);
 	   	cin >> rating;
        ratings.push_back(rating);
	}
	
	if (debug) {
		printContainer(ratings, "ratings");
	}
	
	auto minCandies = findMinCandies(ratings);
	cout << minCandies << endl;
	
	return 0;
}