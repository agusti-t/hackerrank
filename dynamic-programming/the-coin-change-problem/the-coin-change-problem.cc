#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr bool debug = true;

using UInt = unsigned int;

template <typename Container>
void printContainer(const Container& c, const string& name) {
    cout << "Printing container - " << name << " of size = " << c.size() << " : [";
    for (auto i = 0; i < c.size()-1; ++i) {
        cout << c[i] << ",";
    }
    cout << c[c.size()-1] << "]" << endl;
}

void findChange(UInt change, const vector<UInt>& coins, UInt& solutions) {
	if (change != 0) {
		for (auto coin : coins) {
			if (debug) {
				cout << "found " << solutions << " solutions and remaining change is = " << change << endl;
			}
			if (change > coin) {
				findChange(change - coin, coins, solutions);
			} else if (change - coin == 0) {
				++solutions;
			}
		}
	}
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
	
	if (debug) printContainer(coins, "coins (sorted)");
	
	UInt solutions;
	findChange(change, coins, solutions);
	cout << solutions << endl;
	
	return 0;
}