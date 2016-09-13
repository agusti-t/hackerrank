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
    Solution(vector<UInt> s, UInt i, UInt c);
    Solution(const Solution& a);
    Solution(Solution&& a);
    Solution& operator=(const Solution& a);
    Solution& operator=(Solution&& a);
    
    vector<UInt>& getSequence();
    UInt getIndex();
    void setIndex(UInt i);
    UInt getChange();
    void setChange(UInt c);
    
    friend ostream& operator<<(ostream& outstream, const Solution& a);
    friend void printCompleteSolution(const Solution& a);
    
private:
    vector<UInt> sequence;
    UInt index;
    UInt change;
};

Solution::Solution(vector<UInt> s, UInt i, UInt c) 
    : sequence(s), index(i), change(c) 
{}

Solution::Solution(const Solution& a)
    : sequence(a.sequence), index(a.index), change(a.change)
{}

Solution::Solution(Solution&& a) 
    : sequence(move(a.sequence)), index(move(a.index)), change(move(a.change))
{}
    
Solution& Solution::operator=(const Solution& a) {
    sequence = a.sequence;
    index = a.index;
    change = a.change;
    
    return *this;
}

Solution& Solution::operator=(Solution&& a) {
    sequence = move(a.sequence);
    index = move(a.index);
    change = move(a.change);
    
    return *this;
}

vector<UInt>& Solution::getSequence() {
    return sequence;
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
    if (a.sequence.size() > 0) {
        outstream << "[";
        for (auto i = 0; i < a.sequence.size()-1; ++i) {
            outstream << a.sequence[i] << ",";
        }
        outstream << a.sequence[a.sequence.size()-1] << "]" << endl;
    }
    
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
            partialSolutions.emplace_back(vector<UInt>{coin}, i, change - coin);
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
                auto solSequence = partialSolution.getSequence();
                if (debug) {
                    cout << "trying with coin " << coin << endl;
                    printContainer(solSequence, "solSequence iteration " + to_string(i));
                }
                if (solChange > coin) {
                    solSequence.push_back(coin);
                    nextPartialSolutions.emplace_back(solSequence, i, solChange - coin);
                    if (debug) {
                        printContainer(solSequence, "!!!!!!!! partial solution !!!!!!!!!");
                    }
                } else if (solChange == coin) {
                    ++solutions;
                    if (debug) {
                        printContainer(solSequence, "--------- solution ---------");
                    }
                    if (solutions % 10000 == 0) {
                        cout << solutions << endl;
                    }
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