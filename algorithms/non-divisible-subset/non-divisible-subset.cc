#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

constexpr bool debug = false;

using UChar = unsigned char;
using ULInt = unsigned long int;
using UInt = unsigned int;
using ULIntPair = pair<ULInt, ULInt>;

template <typename Container>
void printContainer(const Container& c, const string& name) {
    if (!c.empty()) {
        cout << "Printing container - " << name << " of size = " << c.size() << " : [";
        for (auto i = c.begin(); i != prev(c.end()); ++i) {
            cout << *i << ",";
        }
    	cout << *prev(c.end()) << "]" << endl;
    }
}

template <typename Container>
void printPairsContainer(const Container& c, const string& name) {
    if (!c.empty()) {
        cout << "Printing container - " << name << " of size = " << c.size() << " : [";
        for (auto i = c.begin(); i != prev(c.end()); ++i) {
            cout << "(" << i->first << "," << i->second << ")";
        }
        cout << "(" << prev(c.end())->first << "," << prev(c.end())->second << ")]" << endl;
    }
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

void printDebug(string s) {
    if (debug) {
        cout << s << endl;
    }
}

ULInt findSubsetSize(const vector<ULInt>& s, UInt k) {
    ULInt subsetSize = static_cast<ULInt>(s.size());
    vector<vector<bool>> isDivisible(s.size(), vector<bool>(s.size(), false));
    vector<ULIntPair> divisiblesCount;
    
    ULInt totalHits = static_cast<ULInt>(0);
    
    for (auto i = 0; i < s.size(); ++i) {
        auto hits = static_cast<ULInt>(0);
        for (auto j = 0; j < s.size(); ++j) {
            if (j != i) {
                printDebug("trying s[i] = " + to_string(s[i]) + " + s[j] = " + to_string(s[j]) + " = " + to_string((s[i] + s[j]) % k));
                if ((s[i] + s[j]) % k == 0) {
                    isDivisible[i][j] = true;
                    ++hits;
                    ++totalHits;
                    printDebug("DIVISIBLE!");
                }
            }
        }
        divisiblesCount.emplace_back(i, hits);
    }
    
    if (totalHits == s.size() * (s.size()-1)) {
        return 1;
    }
    
    if (debug) {
        printMatrix(isDivisible, "isDivisible");
        // printPairsContainer(divisiblesCount, "divisiblesCount");
        printDebug("totalHits = " + to_string(totalHits));
    }
    
    auto comp = [](const ULIntPair& a, const ULIntPair&b) { return a.second < b.second; };
    while (totalHits > 0 && !divisiblesCount.empty()) {
        auto divisiblesCountCopy = divisiblesCount;
        sort(divisiblesCountCopy.begin(), divisiblesCountCopy.end(), comp);
        auto topHitter = divisiblesCountCopy.back();
        if (debug) {
            cout << "topHitter is : " << topHitter.first << " with hit count : " << topHitter.second << endl;
            printPairsContainer(divisiblesCount, "divisiblesCount");
        }
        totalHits -= topHitter.second * 2;
        for (auto i = 0; i < s.size(); ++i) {
            if (isDivisible[i][topHitter.first] == true) {
                // printDebug(to_string(i) + " is divisible by " + to_string(topHitter.first));
                --divisiblesCount[i].second;
            }
        }
        printDebug("totalHits = " + to_string(totalHits));
        --subsetSize;
        divisiblesCount[topHitter.first].second = 0;
    }
    
    if (debug) {
        printMatrix(isDivisible, "isDivisible");
        printPairsContainer(divisiblesCount, "divisiblesCount");
    }
    
    return subsetSize;
}

int main() {
    auto n = static_cast<ULInt>(0);
    cin >> n;
    
    auto k = static_cast<UInt>(0);
    cin >> k;
    
	vector<ULInt> set;
    for (auto i = 0; i < n; ++i) {
        auto elem = static_cast<ULInt>(0);
 	   	cin >> elem;
        set.push_back(elem);
	}
	
	if (debug) printContainer(set, "set");
	
	cout << findSubsetSize(set, k) << endl;
	
	return 0;
}