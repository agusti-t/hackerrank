#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr bool debug = false;

template <typename Container>
void printContainer(const Container& c, const string& name) {
    cout << "Printing vector - " << name << " of size = " << c.size() << " : [";
    for (auto i = 0; i < c.size()-1; ++i) {
        cout << c[i] << ",";
    }
    cout << c[c.size()-1] << "]" << endl;
}

unsigned long int findMinCandies(const vector<unsigned long int>& r) {
	auto minCandies = static_cast<unsigned long int>(1);
	auto candyDiffUp = static_cast<unsigned long int>(1);
	auto candyDiffDown = static_cast<unsigned long int>(0);
	
	for (auto i = 1; i < r.size(); ++i) {
		if (r[i] <= r[i-1]) {
			if (debug) {
				cout << "r[i] <= r[i-1]";
			}
			minCandies += 1 + candyDiffDown;
			candyDiffUp = 1;
			++candyDiffDown;
		} else {
			if (debug) {
				cout << "r[i] > r[i-1]";
			}
			minCandies += 1 + candyDiffUp;
			candyDiffDown = 0;
			++candyDiffUp;
		}
		if (debug) {
			cout << " minCandies = " << minCandies << " - candyDiffUp = " << candyDiffUp
				 << " - candyDiffDown = " << candyDiffDown << " r[" << i << "] = " 
				 << r[i] << " : r[" << i-1 << "] = " << r[i-1] << endl;
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