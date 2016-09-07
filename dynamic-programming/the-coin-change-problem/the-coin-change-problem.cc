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

UInt findChange(UInt change, const vector<UInt>& coins) {
	
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
	
	if (debug) printContainer(coins, "coins");
	
	sort(coins.begin(), coins.end());
	
	auto nChange = findChange(change, coins);
	cout << nChange << endl;
	
	return 0;
}