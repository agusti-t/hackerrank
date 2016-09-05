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

template <typename Container>
void printContainerRange(const Container& c, const string& name, size_t start, size_t end) {
    cout << "Printing container range - " << name << " of size = " << c.size() << " and range from " << start << " to " << end-1 << " : [";
    for (auto i = start; i < end-1; ++i) {
        cout << c[i] << ",";
    }
    cout << c[end-1] << "]" << endl;
}

void findMaxPoints(const vector<unsigned long int>& c, unsigned long int& maxPoints, size_t rangeStart, size_t rangeEnd) {
    if (debug) printContainerRange(c, " to findMaxPoints", rangeStart, rangeEnd);
    
    auto range = rangeEnd - rangeStart;
    if (debug) cout << "range is rangeEnd (" << rangeEnd << ") - rangeStart (" << rangeStart << ") : " << range << endl;
    if (range == 2) {
        if (debug) {
            cout << "range is 2 and we compare c[" << rangeStart << "] = " << c[rangeStart] << " with (c[" << rangeEnd-1 << "] - c[" 
                << rangeStart << "]) = " << c[rangeEnd-1] - c[rangeStart] << endl;
        }
        auto firstNumber = c[rangeStart];
        auto secondNumber = c[rangeEnd-1] - c[rangeStart];
        if (rangeStart > 0) {
            firstNumber -= c[rangeStart-1];
        }
        if (firstNumber == secondNumber) {
            ++maxPoints;
            if (debug) {
                cout << "range is 2 and we compare firstNumber = " << firstNumber << " with secondNumber " << secondNumber << endl;
            }
        }
    } else if (range > 2) {
        for (auto p = 1; p < rangeEnd; ++p) {
			auto firstHalfSum = c[rangeStart+p-1];
			auto secondHalfSum = c[rangeEnd-1] - firstHalfSum;
            if (rangeStart > 0) {
                firstHalfSum -= c[rangeStart-1];
            }
            if (debug) {
				cout << "firstHalfSum = " << firstHalfSum << " | secondHalfSum = " << secondHalfSum << endl;
			}
			if (firstHalfSum == secondHalfSum) {
				auto maxFirstHalf = static_cast<unsigned long int>(0);
				auto maxSecondHalf = static_cast<unsigned long int>(0);
				findMaxPoints(c, maxFirstHalf, rangeStart, rangeStart + p);
				findMaxPoints(c, maxSecondHalf, rangeStart + p, rangeEnd);
                maxPoints += 1 + max(maxFirstHalf, maxSecondHalf);
				if (debug) {
                    cout << "maxPoints after recursion : " << maxPoints << endl;
                    // printContainer(c, "cumulative with points (after recursion) " + to_string(maxPoints));
                }
				break;
			} else if (firstHalfSum > secondHalfSum) {
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
        
		auto sum = static_cast<unsigned long int>(0);
		vector<unsigned long int> cumulative;
		while (size-- > 0) {
            auto integer = static_cast<unsigned long int>(0);
            cin >> integer;
            sum += integer;
            cumulative.push_back(sum);
        }
        
        if (debug) printContainer(cumulative, "cumulative - " + to_string(cases));
		
        auto maxPoints = static_cast<unsigned long int>(0);
        
		findMaxPoints(cumulative, maxPoints, 0, cumulative.size());
		cout << maxPoints << endl;
    }
    
    return 0;
}