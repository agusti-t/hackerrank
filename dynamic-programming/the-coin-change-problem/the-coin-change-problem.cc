#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

constexpr bool debug = false;

using ULInt = unsigned long int;
using UInt = unsigned int;

template <typename Container>
void printContainer(const Container& c, const string& name) {
    cout << "Printing container - " << name << " of size = " << c.size() << " : [";
    for (auto i = 0; i < c.size()-1; ++i) {
        cout << c[i] << ",";
    }
	cout << c[c.size()-1] << "]" << endl;
}

template <typename Matrix>
void printMatrix(const Matrix& m, const string& name) {
    auto mSize = m.size() > 0 ? m.size() * m[0].size() : 0;
    cout << "Printing matrix - " << name << " of size = " 
        << mSize << " : {" << endl;
    for (auto i = 0; i < m.size(); ++i) {
        cout << "[";
        for (auto j = 0; j < m[i].size()-1; ++j) {
            cout << m[i][j] << ",";
        }
        cout << m[i][m[i].size()-1] << "]," << endl;
    }
	cout << "}" << endl;
}

ULInt findChange(UInt change, vector<UInt> coins) {
    
    vector<vector<ULInt>> dpCache(change+1, vector<ULInt>(coins.size(), 1));
    
    if (debug) {
         printMatrix(dpCache, "dpCache");
    }
    
    for (auto i = 1; i < change+1; ++i) {
        for (auto j = 0; j < coins.size(); ++j) {
            auto x = (i >= coins[j]) ? dpCache[i-coins[j]][j] : 0;
            
            auto y = (j >= 1) ? dpCache[i][j-1] : 0;
            
            dpCache[i][j] = x + y;
        }
        
        if (debug) {
            printMatrix(dpCache, "dpCache");
        }
    }
    
    if (debug) {
         printMatrix(dpCache, "dpCache");
    }
    
    return dpCache[change][coins.size()-1];
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
	
    if (debug) printContainer(coins, "coins (sorted)");
	
    cout << findChange(change, coins) << endl;
	
	return 0;
}