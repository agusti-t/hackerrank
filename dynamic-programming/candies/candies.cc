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
	//minimum number of candies
	auto minCandies = static_cast<unsigned long int>(1);
	
	//increase in one the number of candies to assign when the current child
	//has a higher rating than the previous one
	auto candyDiffUp = static_cast<unsigned long int>(1);
	
	//these two are tricky, lastUp keeps track of the maximum number of candies
	//assigned on the last upward progression, i.e. what was the number assigned
	//to the last child that was better rated than the one before him.
	//
	//candyDiffDown then keeps track of the downward progression, childs
	//rated in a descending order and when this descending succession ends,
	//i.e. when we have a greater than or equal rating, we check if to see if
	//the candies we gave to the last higher rated child are less than or equal
	//to the number of candies we had to assign to the lower rated child after
	//him due to the downward succession. If that is the case we need to make
	//sure that the higher rated child has one more candy.
	auto candyDiffDown = static_cast<unsigned long int>(0);
    auto lastUp = static_cast<unsigned long int>(0);
	
	//the two progression counters are both resetted when we have equal ratings
	//or independently when we run into a change of succession.
	for (auto i = 1; i < r.size(); ++i) {
		if (r[i] < r[i-1]) {
			if (debug) cout << "r[i] <  r[i-1]";
            if (candyDiffDown == 0) {
                lastUp = candyDiffUp;
            }
			candyDiffUp = 1;
			++candyDiffDown;
			minCandies += candyDiffDown;
		} else if(r[i] == r[i-1]) {
			if (debug) cout << "r[i] == r[i-1]";
            if ((lastUp > 0) && (lastUp <= candyDiffDown)) {
                if (debug) cout << " (adding lastUp = " << candyDiffDown - lastUp + 1 << ")";
                minCandies += 1 + candyDiffDown - lastUp;
                lastUp = 0;
            }
			candyDiffUp = 1;
			candyDiffDown = 0;
			minCandies += 1;
        } else {
			if (debug) cout << "r[i] >  r[i-1]";
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
    
	//we have to make sure that if we have ended in a downward succession, we
	//still check if the last higher rated child has enough candies
    if ((lastUp > 0) && (lastUp <= candyDiffDown)) {
		if (debug) cout << "(adding LAST lastUp = " << candyDiffDown - lastUp + 1 << ")" << endl;
        minCandies += 1 + candyDiffDown - lastUp;
        lastUp = 0; 
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