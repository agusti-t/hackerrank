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

template <typename Map>
void printMap(const Map& m, const string& name) {
    cout << "Printing map - " << name << " of size = " << m.size() << " : [" << endl;
    for (auto kv : m) {
        cout << "[" << kv.first << "," << kv.second << "]" << endl;
    }
	cout << "]" << endl; 
}

class PartialSolution {
public:
    PartialSolution(UInt ci, UInt ch);
    
    UInt getCoin() const;
    void setCoin(UInt ci);
    UInt getChange() const;
    void setChange(UInt ch);
    
    friend ostream& operator<<(ostream& outstream, const PartialSolution& a);
    friend bool operator==(const PartialSolution& a, const PartialSolution& b);
    
private:
    UInt coin;
    UInt change;
};

struct PartialSolutionHasher {
    size_t operator()(const PartialSolution& a) const {
        return ((hash<UInt>()(a.getCoin()))
            ^ (hash<UInt>()(a.getChange())));
    }
};

PartialSolution::PartialSolution(UInt ci, UInt ch) 
    : coin(ci), change(ch) 
{}

UInt PartialSolution::getCoin() const {
    return coin;
}

void PartialSolution::setCoin(UInt ci) {
    coin = ci;
}

UInt PartialSolution::getChange() const {
    return change;
}

void PartialSolution::setChange(UInt ch) {
    change = ch;
}

bool operator==(const PartialSolution& a, const PartialSolution& b) {
    return (a.change == b.change
        && a.coin == b.coin);
}

ostream& operator<<(ostream& outstream, const PartialSolution& a) {
    outstream << "coin = " << a.coin << " | change = " << a.change;
    
    return outstream;
}

using umap = unordered_map<PartialSolution, ULInt, PartialSolutionHasher>;

ULInt findChange(UInt change, vector<UInt> coins, umap& cache) {
    if (change == 0) {
        return 1;
    }
    
    if (coins.size() == 0) {
        return 0;
    }
        
    auto coin = coins.back();
    coins.pop_back();
    
    if (debug) {
        cout << "--------------------- START coin : " << coin << " ---------------------" << endl;
        cout << "trying with coin : " << coin << endl;
    }
    
    auto numCoins = static_cast<UInt>(0);
    auto ways = static_cast<ULInt>(0);
    while (numCoins*coin <= change) {
        auto remainingChange = change - numCoins*coin;
        if (debug) cout << "remainingChange is : " << remainingChange << endl;
        PartialSolution ps = PartialSolution(coin, remainingChange);
        auto waysFound = cache.find(ps);
        if (waysFound != cache.end()) {
            if (debug) {
                cout << "CACHED ways : " << waysFound->second << " for " << ps << endl;
            }
            ways += waysFound->second;
        } else {
            ways += findChange(remainingChange, coins, cache);
            if (debug) {
                cout << "UNCACHED ways : " << ways << " for coin = " << coin << " change = " << change << endl;
            }
        }
        ++numCoins;
    }
    
    auto checkInsert = cache.emplace(PartialSolution(coin, change), ways);
    if (checkInsert.second == true) {
        if (debug) {
            cout << "CACHING ways : " << ways << " for coin = " << coin << " change = " << change << endl;
        }
    } else {
        if (debug) {
            cout << "Already CACHED" << endl;
        }
    }
    
    if (debug) {
        printMap(cache, "cached ways");
        cout << "--------------------- STOP coin : " << coin << " ---------------------" << endl;
    }    
    
    return ways;
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
	
	// sort(coins.begin(), coins.end());
//     reverse(coins.begin(), coins.end());
	
    if (debug) printContainer(coins, "coins (sorted)");
	
    umap cache;
    cout << findChange(change, coins, cache) << endl;
	
	return 0;
}