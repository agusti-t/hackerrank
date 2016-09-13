#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

constexpr bool debug = true;

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

// void printContainerInsideContainer(const vector<vector<UInt>>& c, const string& name) {
//     cout << "Printing container - " << name << " of size = " << c.size() << " : {" << endl;
//     for (auto i = c.begin(); i != c.end(); ++i) {
//         cout << "[";
//         for (auto j = (*i).cbegin(); j != (*i).cend(); ++j) {
//             cout << *j << ",";
//         }
//         cout << "]," << endl;
//     }
//     cout << endl << "}" << endl;
// }

// void findChange(ULInt change, const vector<ULInt>& coins, string& solution, ULInt& nSolutions,
//         unordered_set<string>& solutions, vector<ULInt>::const_iterator& fromStart, unordered_set<string>& unsortedSolutions) {
//     if (change != 0) {
//         for (auto it = fromStart; it != coins.cend(); ++it) {
//             auto coin = *it;
//             auto coinStr = to_string(coin);
//             if (debug) {
//                 cout << "current coin is : " << coinStr << endl;
//                 cout << "current change is : " << change << endl;
//             }
//             if (change > coin) {
//                 findChange(change - coin, coins, solution.append(coinStr), nSolutions, solutions, fromStart, unsortedSolutions);
//                 solution.pop_back();
//             } else if (change == coin) {
//                 solution.append(coinStr);
//                 auto sortedSolution = solution;
//                 sort(sortedSolution.begin(), sortedSolution.end());
//                 auto checkInsert = solutions.insert(sortedSolution);
//                 unsortedSolutions.insert(solution);
//                 if (checkInsert.second == true) {
//                     ++nSolutions;
//                     cout << "solution found! : " << solution << endl;
//                 }
//                 if (next(it) == coins.cend()) {
//                     ++fromStart;
//                 }
//                 solution.pop_back();
//                 if (debug) printContainer(solutions, "solutions so far");
//                 if (debug) printContainer(unsortedSolutions, "unsortedSolutions so far");
//             } else {
//                 if (debug) {
//                     cout << "overshooting, try with next coin " << coinStr << endl;
//                 }
//                 // ++fromStart;
//             }
//         }
//     }
// }

class Solution {
public:
    Solution(vector<UInt> s, UInt i, UInt c);
    Solution(const Solution& a);
    Solution(Solution&& a);
    Solution& operator=(const Solution& a);
    Solution& operator=(Solution&& a);
    
    vector<UInt>& getSequence();
    UInt getIndex();
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

ULInt findChange(UInt change, const vector<UInt>& coins) {
    auto i = 0;
    auto prevIndex = 0;
    vector<Solution> solutions;
    vector<Solution> partialSolutions;
    Solution solution(vector<UInt>(), i, change);
    auto remainingChange = solution.getChange();
	auto cSize = coins.size();
    while (i < cSize) {
        auto coin = coins[i];
		if (debug) cout << "trying coin : " << coin << endl;
        if (remainingChange >= coin) {
			// solution.getSequence().insert(solution.getSequence().end(), remainingChange / coin, coin);
			// remainingChange %= coin;
			// solution.setChange(remainingChange);
			while (remainingChange >= coin) {
				solution.getSequence().push_back(coin);
				remainingChange -= coin;
	            if (remainingChange > 0 && i < cSize-1) {
	                partialSolutions.push_back(Solution(solution.getSequence(), i+1, remainingChange));
	                if (debug) {
	                    cout << "storing partial solution" << endl;
	                    printCompleteSolution(partialSolutions.back());
	                }
				}
            }
			solution.setChange(remainingChange); 
			if (remainingChange == 0) {	       
	            solutions.push_back(solution);
	            if (debug) {
	                printContainer(solution.getSequence(), "solution found");
	            }
	            if (!partialSolutions.empty() && i < cSize-1) {
	                solution = partialSolutions.back();
	                partialSolutions.pop_back();
	                i = solution.getIndex();
	                remainingChange = solution.getChange();
	                if (debug) {
	                    cout << "loading partial solution" << endl;
	                    printCompleteSolution(solution);
	                }
	            }
	        }
        } 
		if (i == coins.size()-1) {
			if (!partialSolutions.empty()) {
                solution = partialSolutions.back();
                partialSolutions.pop_back();
                i = solution.getIndex();
                remainingChange = solution.getChange();
                if (debug) {
                    cout << "loading partial solution" << endl;
                    printCompleteSolution(solution);
                }
			} else {
	            if (debug) cout << "resetting change" << endl;
	            remainingChange = change;
	            i = prevIndex + 1;
	            ++prevIndex;
	            vector<UInt>& seq = solution.getSequence();
	            solution.getSequence().clear();
				partialSolutions.clear();
	            if (debug) cout << "increasing prevIndex to : " << prevIndex << endl;
			}
        } else {
            ++i;
        }
        if (debug) printContainer(solutions, "solutions so far");
        if (debug) printContainer(partialSolutions, "partial solutions");
    }
    
    return solutions.size();
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