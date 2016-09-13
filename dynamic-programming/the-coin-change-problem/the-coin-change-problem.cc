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
    outstream << "i = " << a.index << " | c = " << a.change << endl;
    
    return outstream;
}

void findPartialSolutions(UInt change, const vector<UInt>& coins, UInt startIndex, vector<Solution>& partialSolutions, ULInt& solutions) {
    for (auto i = startIndex; i < coins.size(); ++i) {
        auto coin = coins[i];
        if (debug) {
            cout << "coin : " << coin << endl;
            cout << "change : " << change << endl;
            cout << "startIndex : " << startIndex << endl;
        }
        if (change % coin == 0) {
            cout << "solution FOUND!" << endl;
            ++solutions;
        } else if (change / coin > 0) {
            cout << "partial solution ADDED! (index " << i+1 << ", change " << change / coin << ")" << endl;
            partialSolutions.emplace_back(i+1, change / coin);
        }
        cout << endl;
    }
}

ULInt findChange(UInt change, const vector<UInt>& coins) {
    auto i = 0;
    auto prevIndex = 0;
    ULInt solutions = 0;
    vector<Solution> partialSolutions;
    vector<Solution> nextPartialSolutions;
    findPartialSolutions(change, coins, 0, partialSolutions, solutions);
    
    for (auto i = 0; i < coins.size(); ++i) {
        while (!partialSolutions.empty()) {
            for (auto partialSolution : partialSolutions) {
                if (debug) {
                    cout << "processing partialSolution : " << partialSolution << endl;
                }
                auto solChange = partialSolution.getChange();
                auto solIndex = partialSolution.getIndex();
                findPartialSolutions(solChange, coins, solIndex, nextPartialSolutions, solutions);
            }
            if (debug) {
                printContainer(nextPartialSolutions, "nextPartialSolutions");
            }
            // partialSolutions.clear();
            partialSolutions = nextPartialSolutions;
            nextPartialSolutions.clear();
        }
        
        //here partialSolutions is empty
        findPartialSolutions(change - coins[i], coins, i+1, partialSolutions, solutions);
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