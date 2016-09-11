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

template <typename Container>
void printContainer(const Container& c, const string& name) {
    cout << "Printing container - " << name << " of size = " << c.size() << " : [";
    for (auto i = c.begin(); i != c.end(); ++i) {
        cout << *i << ",";
    }
	cout << "]" << endl;
}

void findChange(ULInt change, const vector<ULInt>& coins, string& solution, ULInt& nSolutions, unordered_set<string>& solutions, unordered_set<string>& unsortedSolutions) {
	if (change != 0) {
		for (auto coin : coins) {
			auto coinStr = to_string(coin);
			if (change > coin) {
				if (debug) {
					cout << "solution so far " << solution << endl;
				}
				findChange(change - coin, coins, solution.append(coinStr), nSolutions, solutions, unsortedSolutions);
				solution.pop_back();
			} else if (change == coin) {
				solution.append(coinStr);
				auto sortedSolution = solution;
				sort(sortedSolution.begin(), sortedSolution.end());
				auto checkInsert = solutions.insert(sortedSolution);
				// unsortedSolutions.insert(solution);
				if (checkInsert.second == true) ++nSolutions;
				if (debug) printContainer(solutions, "solutions so far");
				if (debug) printContainer(unsortedSolutions, "unsortedSolutions so far");
				solution.pop_back();
				cout << nSolutions << endl;
			} else {
				break;
			}
		}
	}
}

int main() {
    auto change = static_cast<ULInt>(0);
    cin >> change;
	
	auto nCoins = static_cast<ULInt>(0);
	cin >> nCoins;
    
	vector<ULInt> coins;
    for (auto i = 0; i < nCoins; ++i) {
        auto coin = static_cast<ULInt>(0);
 	   	cin >> coin;
        coins.push_back(coin);
	}
	
	sort(coins.begin(), coins.end());
	
	if (debug) printContainer(coins, "coins (sorted)");
	
	ULInt nSolutions = 0;
	unordered_set<string> solutions;
	unordered_set<string> unsortedSolutions;
	// for (auto coin : coins) {
		string solution;
		findChange(change, coins, solution, nSolutions, solutions, unsortedSolutions);
	// }
	
	cout << nSolutions << endl;
	
	return 0;
}