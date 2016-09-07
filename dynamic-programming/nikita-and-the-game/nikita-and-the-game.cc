#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

using ULongInt = unsigned long int;

//Work all the time on the same accumulated sums vector and use a range to determine
//the vector the function findMaxPoints "sees"
void findMaxPoints(const vector<ULongInt>& c, ULongInt& maxPoints, size_t rangeStart, size_t rangeEnd) {
    auto range = rangeEnd - rangeStart;
    
	//If we are only concerned with two numbers, it is enough to compare one with the other
	if (range == 2) {
        auto firstNumber = c[rangeStart];
        auto secondNumber = c[rangeEnd-1] - c[rangeStart];
		
		//If our range start is not the beginning of the vector, substract the accumulated
		//sum until the previous position to be able to compare it with the second number
        if (rangeStart > 0) {
            firstNumber -= c[rangeStart-1];
        }
        if (firstNumber == secondNumber) {
            ++maxPoints;
        }
    } else if (range > 2) {
		//Now if we are dealing with more than 2 positions, start trying to split the vector
		//and checking if the sums of both parts are equal
        for (auto p = 1; p < range; ++p) {
			auto firstHalfSum = c[rangeStart+p-1];
			auto secondHalfSum = c[rangeEnd-1] - firstHalfSum;
            if (rangeStart > 0) {
                firstHalfSum -= c[rangeStart-1];
            }
			//If they are, obtain the score for each of the two halves and keep the
			//highest one
            if (firstHalfSum == secondHalfSum) {
				auto maxFirstHalf = static_cast<ULongInt>(0);
				auto maxSecondHalf = static_cast<ULongInt>(0);
				findMaxPoints(c, maxFirstHalf, rangeStart, rangeStart + p);
				findMaxPoints(c, maxSecondHalf, rangeStart + p, rangeEnd);
                maxPoints += 1 + max(maxFirstHalf, maxSecondHalf);
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
		
		//No need to keep track of the numbers, just the accumulated sum for each
		//position
		vector<ULongInt> cumulative;
		while (size-- > 0) {
            auto integer = static_cast<ULongInt>(0);
            cin >> integer;
            sum += integer;
            cumulative.push_back(sum);
        }
        
        auto maxPoints = static_cast<ULongInt>(0);
        
		findMaxPoints(cumulative, maxPoints, 0, cumulative.size());
		cout << maxPoints << endl;
    }
    
    return 0;
}