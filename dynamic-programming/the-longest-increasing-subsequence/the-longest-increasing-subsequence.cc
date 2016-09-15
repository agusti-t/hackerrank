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

ULInt findLIS(const vector<ULInt>& s) {
	
	if (s.size() == 0) {
		return 0;
	}
	
	if (s.size() == 1) {
		return 1;
	}

	vector<vector<ULInt>> a(s.size(), vector<ULInt>(s.size()+1, 1));
	auto lisLength = static_cast<ULInt>(1);
	
	for (auto i = 0; i < a.size(); ++i) {
		a[i][i] = s[i];
		auto tempLis = static_cast<ULInt>(1);
		for (auto j = i+1; j < a[i].size()-1; ++j) {
			if (s[j] > a[i][j-1]) {
				++tempLis;
				a[i][j] = s[j];
			} else {
				a[i][j] = a[i][j-1];
			}
		}
		if (debug) cout << tempLis << endl;
		a[i][s.size()] = tempLis;
		lisLength = max(lisLength, tempLis);
	}
	
	if (debug) printMatrix(a, "LISes");
	
	return lisLength;
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
	
	cout << findLIS(sequence) << endl;
	
	return 0;
}