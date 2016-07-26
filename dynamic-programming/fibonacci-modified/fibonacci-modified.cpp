#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <iterator>
#include <cstddef>

using namespace std;

constexpr unsigned outputBase = 10;
constexpr unsigned internalBase = 100;

void printVector(const vector<unsigned long long int>& v);

class BigNumber {

    private:
        vector<unsigned long long int> num;
    
    public:
        BigNumber(unsigned long long int num = 0);
        BigNumber(const BigNumber& a);
        BigNumber(BigNumber&& a);
        BigNumber& operator+=(const BigNumber& a);
        BigNumber& operator=(const BigNumber& a);
    
        friend BigNumber operator*(const BigNumber& a, const BigNumber& b);
        friend BigNumber operator+(const BigNumber& a, const BigNumber& b);
        friend ostream& operator<<(ostream& outstream, const BigNumber& a);
        friend bool operator<(const BigNumber& a, const BigNumber& b);
        
        friend void printNaked(const BigNumber& a);
    
    private:
        void add(const BigNumber& b, int exp);
        
};

BigNumber::BigNumber(unsigned long long int n) {
    for (; n; n /= internalBase) {
        num.push_back(n % internalBase);
    }
    
    if (num.empty()) {
        num.push_back(0);
    }
}

BigNumber::BigNumber(const BigNumber& a) 
    : num(a.num)
{ }

BigNumber::BigNumber(BigNumber&& a)
    : num(std::move(a.num))
{ }

bool operator<(const BigNumber& a, const BigNumber& b) {
    if (a.num.size() != b.num.size()) {
        return a.num.size() < b.num.size();
    } else {
        return a.num.front() < b.num.front();
    }
}

ostream& operator<<(ostream& outstream, const BigNumber& a) {
    vector<unsigned long long int> result(a.num.size() * 2, 0);
    
    for (unsigned long int i = 0; i < a.num.size(); ++i) {
        auto d = a.num[i];
        result[2 * i] = d % outputBase;
        result[2 * i + 1] = d / outputBase;
    }
    
    reverse(result.begin(), result.end());
    if (result.size() > 1) {
        auto it = result.begin();
        while (*it == 0) {
            it++;
        }
        result.erase(result.begin(), it);
    }
    
    for (auto r : result) {
        outstream << r;
    }
    
    return outstream;
}

BigNumber operator+(const BigNumber& a, const BigNumber& b) {
    auto shortest = a.num.size() < b.num.size() ? a.num : b.num;
    auto longest = a.num.size() < b.num.size() ? b.num : a.num;
    
    auto nShortest = shortest.size();
    auto nLongest = longest.size();
    
    BigNumber result;
    auto& r = result.num;
    r.clear();
    unsigned long long int carry = 0;
    
    for (unsigned long int i = 0; i < nShortest; i++) {
        auto toAdd = shortest[i] + longest[i] + carry;
        r.push_back(toAdd % internalBase);
        carry = toAdd / internalBase;
    }
    
    for (unsigned long int j = nShortest; j < nLongest; j++) {
        auto toAdd = longest[j] + carry;
        r.push_back(toAdd % internalBase);
        carry = toAdd / internalBase;
    }
    
    return result;
}

void printVector(const vector<unsigned long long int>& v) {
    cout << endl;
    for (auto n : v) {
        cout << n << ",";
    }
    cout << endl;
}

void printNaked(const BigNumber& a) {
    if (a.num.size() == 0) {
        cout << "" << endl;
        return;
    }
    
    vector<unsigned long long int> copy(a.num);
    reverse(copy.begin(), copy.end());
    
    for (auto n : copy) {
        cout << n << ",";
    }
}

BigNumber operator*(const BigNumber& a, const BigNumber& b) {
    BigNumber aExp(a);
    BigNumber bExp(b);
    
    BigNumber result(0);
    
    return result;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    /*int t1;
    cin >> t1;
    
    int t2;
    cin >> t2;
    
    int n;
    cin >> n;*/
    
    BigNumber a(2500), b(10);
    
//    cout << "Naked print of a : "; printNaked(a); cout << " and of b : "; printNaked(b); cout << endl;
//    cout << a << " < " << b << " ? : " << (a < b) << endl;

    BigNumber c(4896436); 
//    cout << "Naked print of c : "; printNaked(c); cout << endl; cout << "Normal print of c : " << c << endl;
    
    cout << "Addition of a + b + c : " << (a + b + c) << endl;
    
    return 0;
}
