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

//So this function builds the bottom up solution from the base case:
//  - When the change to give back is 0 we have 1 way of giving it (0 of each coin).
//
//The indexes of the memoization matrix rows indicate the change and the column
//indexes indicate the index of the last coin to be considered, from our coins
//vector, to try and give change. For example:
//  If we have to calculate the ways to give change of 4 with coins [1,2,3], the
//  completely computated bottom up solution matrix would look like:
//
//                    [1,2,3] ----> coins vector with indexes below
//                    {0,1,2}   
//                  0 [1,1,1]
//                  1 [1,1,1]
//                  2 [1,2,2]
//                  3 [1,2,3]
//                  4 [1,3,4]
//
//  Here are some examples of what different matrix position mean:
//      1- m[0][0] = 1 -> there is 1 way to give change for 0 using the coin up
//         to index 0 (i.e. 1) and it is by giving 0 coins, base case.
//      2- m[2][1] = 2 -> there are 2 ways to give change for 2 using the coin up
//         to index 1 (i.e. 2) and they are {1,1} and {2}.
//      3- m[4][1] = 3 -> there are 3 ways to give change for 4 using the coin up
//         to index 1 (i.e. 2) and they are {1,1,1,1}, {1,1,2} and {2,2}.
// 
//To compute the ways of giving change for a certain amount using the coins from our
//vector up to a certain index we add:
//  - The ways of giving change for that amount minus at least one use of the coin
//    at the index concerning us. We call this x.
//  - The ways of giving change for that amount using 0 times the coin at the index
//    concerning us. We call this y.
//
//For example, for the examples given above:
//  1- m[0][0]:
//      x = 0 = m[0][0] since there is 1 way of giving 0 change, base case (1 - 1 = 0).
//      y = 0 since there are 0 ways of giving change 0 using 0 coins.
//      x + y = 1 = m[0][0]
//  2- m[2][1]:
//      x = 1 = m[0][1] since there is 1 way of giving 0 change, base case (2 - 2 = 0).
//      y = 1 = m[2][0] since there is 1 way of giving 2 change using coins up to index
//          0 (i.e. coin 1), {1,1}.
//      x + y = 2 = m[2][1]
//  3- m[4][1]:
//      x = 2 = m[2][1] since there are 2 ways (see example 2) of giving (4 - 2 = 2)
//          change using coins up to index 1 (i.e. coin 2), {1,1} and {2}.
//      y = 1 = m[4][0] since there is 1 way of giving 4 change using coins up to index
//          0 (i.e. coin 1), {1,1,1,1}.
//      x + y = 3 = m[4][1]
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