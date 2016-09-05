#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

constexpr bool debug = false;

using ULongInt = unsigned long int;
using constIter = vector<ULongInt>::const_iterator;

template <typename Container>
void printContainer(const Container& c, const string& name) {
    cout << "Printing container - " << name << " of size = " << c.size() << " : [";
    for (auto i = 0; i < c.size()-1; ++i) {
        cout << c[i] << ",";
    }
    cout << c[c.size()-1] << "]" << endl;
}

template <typename Container>
void printContainerRange(const Container& c, const string& name, typename Container::const_iterator start, typename Container::const_iterator end) {
    cout << "Printing container range - " << name << " of size = " << c.size() << " and range from " << start - c.begin() << " to " << end-1 - c.begin() << " : [";
    for (auto i = start; i < end-1; ++i) {
        cout << *i << ",";
    }
    cout << *(end-1) << "]" << endl;
}

void findMaxPoints(const vector<ULongInt>& c, ULongInt& maxPoints, constIter rangeStart, constIter rangeEnd) {
    if (debug) printContainerRange(c, " to findMaxPoints", rangeStart, rangeEnd);
    
    auto range = distance(rangeStart, rangeEnd);
    // if (debug) cout << "range is rangeEnd (" << rangeEnd << ") - rangeStart (" << rangeStart << ") : " << range << endl;
    if (range == 2) {
        auto firstNumber = *rangeStart;
        auto secondNumber = *(rangeEnd-1) - *rangeStart;
        if (rangeStart > c.begin()) {
            firstNumber -= *(rangeStart-1);
        }
        if (debug) {
            cout << "range is 2 and we compare firstNumber " << firstNumber << " with secondNumber " << secondNumber << endl;
        }
        if (firstNumber == secondNumber) {
            ++maxPoints;
            // if (debug) {
 //                cout << "range is 2 and we compare firstNumber = " << firstNumber << " with secondNumber " << secondNumber << endl;
 //            }
        }
    } else if (range > 2) {
        for (auto p = 1; p < range; ++p) {
			auto firstHalfSum = *(rangeStart+p-1);
			auto secondHalfSum = *(rangeEnd-1) - firstHalfSum;
            if (rangeStart > c.begin()) {
                firstHalfSum -= *(rangeStart-1);
            }
            if (debug) {
				cout << "firstHalfSum = " << firstHalfSum << " | secondHalfSum = " << secondHalfSum << endl;
			}
			if (firstHalfSum == secondHalfSum) {
				auto maxFirstHalf = static_cast<ULongInt>(0);
				auto maxSecondHalf = static_cast<ULongInt>(0);
                findMaxPoints(c, maxFirstHalf, rangeStart, rangeStart + p);
				findMaxPoints(c, maxSecondHalf, rangeStart + p, rangeEnd);
                maxPoints += 1 + max(maxFirstHalf, maxSecondHalf);
				if (debug) {
                    cout << "maxPoints after recursion : " << maxPoints << endl;
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
        
		auto sum = static_cast<ULongInt>(0);
		vector<ULongInt> cumulative;
		while (size-- > 0) {
            auto integer = static_cast<ULongInt>(0);
            cin >> integer;
            sum += integer;
            cumulative.push_back(sum);
        }
        
        if (debug) printContainer(cumulative, "cumulative - " + to_string(cases));
		
        auto maxPoints = static_cast<ULongInt>(0);
        
		findMaxPoints(cumulative, maxPoints, cumulative.cbegin(), cumulative.cend());
		cout << maxPoints << endl;
    }
    
    return 0;
}