#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

constexpr bool debug = false;

using UChar = unsigned char;
using ULInt = unsigned long int;
using UInt = unsigned int;

template <typename Container>
void printContainer(const Container& c, const string& name) {
    cout << "Printing container - " << name << " of size = " << c.size() << " : [";
    for (auto i = c.begin(); i != c.end(); ++i) {
        cout << *i << ",";
    }
	cout << "]" << endl;
}

class Solution {
public:
    Solution(UInt i, UInt c);
    Solution(const Solution& a);
    Solution(Solution&& a);
    Solution& operator=(const Solution& a);
    Solution& operator=(Solution&& a);
    
    UInt getIndex();
    void setIndex(UInt i);
    UInt getChange();
    void setChange(UInt c);
    
    friend ostream& operator<<(ostream& outstream, const Solution& a);
    friend void printCompleteSolution(const Solution& a);
    
private:
    UInt index;
    UInt change;
};

Solution::Solution(UInt i, UInt c) 
    : index(i), change(c) 
{}

Solution::Solution(const Solution& a)
    : index(a.index), change(a.change)
{}

Solution::Solution(Solution&& a) 
    : index(move(a.index)), change(move(a.change))
{}
    
Solution& Solution::operator=(const Solution& a) {
    index = a.index;
    change = a.change;
    
    return *this;
}

Solution& Solution::operator=(Solution&& a) {
    index = move(a.index);
    change = move(a.change);
    
    return *this;
}

UInt Solution::getIndex() {
    return index;
}

void Solution::setIndex(UInt i) {
    index = i;
}

UInt Solution::getChange() {
    return change;
}

void Solution::setChange(UInt c) {
    change = c;
}

ostream& operator<<(ostream& outstream, const Solution& a) {
    outstream << "Index is " << a.index << "and change is " << a.change << endl;
    
    return outstream;
}

void printCompleteSolution(const Solution& a) {
    cout << "---------------------------------" << endl;
    cout << "Solution index : " << a.index << endl;
    cout << "Solution change : " << a.change << endl;
    cout << "Solution sequence : " << endl << a;
    cout << "---------------------------------" << endl;
}

void initPartialSolutions(UInt change, const vector<UInt>& coins, vector<Solution>& partialSolutions, ULInt& solutions) {
    for (auto i = 0; i < coins.size(); ++i) {
        auto coin = coins[i];
        if (change > coin) {
            partialSolutions.emplace_back(i, change - coin);
        } else if (change == coin) {
            ++solutions;
        }
    }
}

ULInt findChange(UInt change, const vector<UInt>& coins) {
    auto i = 0;
    auto prevIndex = 0;
    ULInt solutions = 0;
    vector<Solution> partialSolutions;
    initPartialSolutions(change, coins, partialSolutions, solutions);
    vector<Solution> nextPartialSolutions;
    while (!partialSolutions.empty()) {
        for (auto partialSolution : partialSolutions) {
            auto solChange = partialSolution.getChange();
            auto solIndex = partialSolution.getIndex();
            if (debug) {
                cout << "current partial solution : " << endl;
                printCompleteSolution(partialSolution);
            }
            for (auto i = solIndex; i < coins.size(); ++i) {
                auto coin = coins[i];
                if (debug) {
                    cout << "trying with coin " << coin << endl;
                }
                if (solChange > coin) {
                    nextPartialSolutions.emplace_back(i, solChange - coin);
                } else if (solChange == coin) {
                    ++solutions;
                    // if (solutions % 100000 == 0) {
//                         cout << solutions << endl;
//                     }
                }
            }
        }
        if (debug) {
            printContainer(nextPartialSolutions, "nextPartialSolutions");
        }
        // partialSolutions.clear();
        partialSolutions = nextPartialSolutions;
        nextPartialSolutions.clear();
    }
    
    return solutions;
}

int main() {
    auto change = static_cast<UInt>(0);
    cin >> change;
	
	auto nCoins = static_cast<UInt>(0);
	cin >> nCoins;
    
	vector<UInt> coins;
    for (auto i = 0; i < nCoins; ++i) {
        auto coin = static_cast<UInt>(0);
 	   	cin >> coin;
        coins.push_back(coin);
	}
	
	sort(coins.begin(), coins.end());
	reverse(coins.begin(), coins.end());
	
	if (debug) printContainer(coins, "coins (sorted)");
	
	cout << findChange(change, coins) << endl;
	
	return 0;
}