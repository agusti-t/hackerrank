#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

constexpr bool debug = false;

using UChar = unsigned char;
using ULInt = unsigned long int;
using UInt = unsigned int;

template <typename Container>
void printContainer(const Container& c, const string& name) {
    cout << "Printing container - " << name << " of size = " << c.size() << " : [";
    for (auto i = c.begin(); i != prev(c.end()); ++i) {
        cout << *i << ",";
    }
	cout << *prev(c.end()) << "]" << endl;
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

ULInt findLIS(const vector<ULInt>& s, vector<ULInt>& subLIS, ULInt i) {
	vector<ULInt> lises(s.size(), 0);
	auto lis = static_cast<ULInt>(1);
	auto tempLis = static_cast<ULInt>(1);
	auto tempMin = static_cast<ULInt>(0);
    lises[0] = 1;
    
	if (debug) printContainer(lises, "lises " + to_string(i));
    if (debug) printContainer(s, "sequence");
    if (debug) cout << endl << endl;
    
    for (auto i = 1; i < s.size(); ++i) {
        if (debug) cout << "i is : " << i << " and s[i] : " << s[i] << endl;
        
        tempMin = s[0];
        tempLis = 1;
        for (auto k = 0; k < i; ++k) {
            if (lises[k] >= tempLis && s[k] < s[i]) {
                tempLis = lises[k];
                tempMin = s[k];
                if (debug) cout << "found a better lis at index k = " << k << " number is s[k] = " << tempMin << " and with lenght " << tempLis << endl;
            }
        }
        
		if (s[i] > tempMin) {
			++tempLis;
			tempMin = s[i];
		} else if (s[i] == tempMin) {
		    tempLis = 1;
		} else {
		    tempMin = s[i];
            tempLis = 1; 
		}
        
        lises[i] = tempLis;
		lis = max(lis, lises[i]);
        
        if (debug) cout << s[i] << " "; 
		if (debug) cout << "tempLis " << tempLis << endl;
		if (debug) printContainer(lises, "lises " + to_string(i));
        if (debug) printContainer(s, "sequence");
        if (debug) cout << endl;
	}
	
	return lis;
}

int main() {
    auto n = static_cast<ULInt>(0);
    cin >> n;
    
	vector<ULInt> sequence;
    for (auto i = 0; i < n; ++i) {
        auto elem = static_cast<ULInt>(0);
 	   	cin >> elem;
        sequence.push_back(elem);
	}
	
	if (debug) printContainer(sequence, "sequence");
	
	vector<ULInt> subLIS(sequence.size());
	cout << findLIS(sequence, subLIS, 0) << endl;
	
	return 0;
}