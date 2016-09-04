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

// unsigned long int findMaxPoints(const vector<unsigned long int>& i, unsigned long int& maxPoints) {
//     if (debug) printContainer(i, "integers to findMaxPoints");
//
//     if (i.size() <= 1) {
//         return 0;
//     } else if (i.size() == 2) {
//         if (i[0] == i[1]) {
//             return maxPoints + 1;
//         } else {
//             return maxPoints;
//         }
//     } else {
// 		auto sum = static_cast<unsigned long int>(0);
// 		vector<unsigned long int> c;
// 		for (auto e : i) {
// 			sum += e;
// 			c.push_back(sum);
// 		}
//         for (auto p = 1; p < i.size(); ++p) {
// 			auto firstHalfSum = c[p-1];
// 			auto secondHalfSum = c[c.size()-1] - firstHalfSum;
// 			if (debug) {
// 				// printContainer(c, "cumulative with points " + to_string(maxPoints));
// 				cout << "firstHalfSum = " << firstHalfSum << " | secondHalfSum = " << secondHalfSum << endl;
// 			}
// 			if (firstHalfSum == secondHalfSum) {
// 				maxPoints += 1 + max(findMaxPoints(vector<unsigned long int> (i.begin(), i.begin() + p), maxPoints),
// 	            	findMaxPoints(vector<unsigned long int> (i.begin() + p, i.end()), maxPoints));
// 				if (debug) printContainer(c, "cumulative with points (after recursion) " + to_string(maxPoints));
// 				break;
// 			}
// 		}
//
//         return maxPoints;
//     }
// }

void findMaxPoints(const vector<unsigned long int>& i, unsigned long int& maxPoints) {
    if (debug) printContainer(i, "integers to findMaxPoints");
    
    if (i.size() <= 1) {
    } else if (i.size() == 2) {
        if (i[0] == i[1]) {
            ++maxPoints;
        } else {
        }
    } else {
		auto sum = static_cast<unsigned long int>(0);
		vector<unsigned long int> c;
		for (auto e : i) {
			sum += e;
			c.push_back(sum);
		}
        for (auto p = 1; p < i.size(); ++p) {
			auto firstHalfSum = c[p-1];
			auto secondHalfSum = c[c.size()-1] - firstHalfSum;
			if (debug) {
				// printContainer(c, "cumulative with points " + to_string(maxPoints));
				cout << "firstHalfSum = " << firstHalfSum << " | secondHalfSum = " << secondHalfSum << endl;
			}
			if (firstHalfSum == secondHalfSum) {
				auto maxFirstHalf = static_cast<unsigned long int>(0);
				auto maxSecondHalf = static_cast<unsigned long int>(0);
				findMaxPoints(vector<unsigned long int> (i.begin(), i.begin() + p), maxFirstHalf);
				findMaxPoints(vector<unsigned long int> (i.begin() + p, i.end()), maxSecondHalf);
				maxPoints += 1 + max(maxFirstHalf, maxSecondHalf);
				if (debug) printContainer(c, "cumulative with points (after recursion) " + to_string(maxPoints));
				break;
			}
		}
    }
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    auto cases = static_cast<unsigned int>(0);
    cin >> cases;
    
    while (cases-- > 0) {
        auto size = static_cast<unsigned int>(0);
        cin >> size;
        
        vector<unsigned long int> integers;
		while (size-- > 0) {
            auto integer = static_cast<unsigned long int>(0);
            cin >> integer;
            integers.push_back(integer);
        }
        
        if (debug) printContainer(integers, "integers - " + to_string(cases));
		
        auto maxPoints = static_cast<unsigned long int>(0);
        // cout << findMaxPoints(integers, maxPoints) << endl;
		
		findMaxPoints(integers, maxPoints);
		cout << maxPoints << endl;
    }
    
    return 0;
}