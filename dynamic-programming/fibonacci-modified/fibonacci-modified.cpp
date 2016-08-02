#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <iterator>
#include <cstddef>
#include <chrono>
#include <map>
#include <type_traits>
#include <iomanip>
#include <functional>

using namespace std;
using namespace std::chrono;
using namespace std::placeholders;

constexpr unsigned outputBase = 10;
constexpr unsigned long long internalBase = 1000000000;
constexpr unsigned baseRatio = 9;

static map<string, nanoseconds> durations;

void printVector(const vector<unsigned long long int>& v, const string& name);
void printAllDurations();

struct Check {
    Check(string k): time1{std::chrono::high_resolution_clock::now()}, key{k} {}

    ~Check() {
        std::chrono::high_resolution_clock::time_point time2 = std::chrono::high_resolution_clock::now();
        auto duration = (time2 - time1);
        durations[key] += duration;
    }

    std::chrono::high_resolution_clock::time_point time1;
    string key;
};


template<typename F, typename... Tail>
typename std::result_of<F(Tail&&...)>::type measureAndExecute(string key, F f, Tail&&... tail) {  
    Check check(key);
    (void)check;
    return f(std::forward<Tail>(tail)...);
}

class BigNumber {

    private:
        vector<unsigned long long int> num;
    
    public:
        BigNumber(unsigned long long int num = 0);
        BigNumber(const BigNumber& a);
        BigNumber(BigNumber&& a);
        BigNumber& operator+=(const BigNumber& a);
        BigNumber& operator=(const BigNumber& a);
        BigNumber& operator=(BigNumber&& a);
    
        friend BigNumber operator*(const BigNumber& a, const BigNumber& b);
        friend BigNumber operator+(const BigNumber& a, const BigNumber& b);
        friend BigNumber operator-(const BigNumber& a, const BigNumber& b);
        friend ostream& operator<<(ostream& outstream, const BigNumber& a);
        friend bool operator<(const BigNumber& a, const BigNumber& b);
        friend bool operator==(const BigNumber& a, const BigNumber& b);
        friend bool operator!=(const BigNumber& a, const BigNumber& b);
        
        friend void printNaked(const BigNumber& a);
        friend void printVector(const vector<unsigned long long int>& v, const string& name);
       
        friend BigNumber singleSlotMultiplication(const BigNumber& a, const BigNumber& b);
        friend BigNumber karatsubaMultiplication(const BigNumber& a, const BigNumber& b);
    
    private:
        BigNumber getLowerHalf() const;
        BigNumber getHigherHalf() const;
        BigNumber& shiftLeft(unsigned long long int p);
};

BigNumber findFibonacciModified(vector<BigNumber>& terms, vector<bool>& calculated, unsigned long n);
void testLessThan();
void testSubstraction();
void testAddition();
void testMultiplication();


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

BigNumber& BigNumber::operator+=(const BigNumber& a) {
    *this = *this + a;
    return *this;
}

BigNumber& BigNumber::operator=(BigNumber&& a) {
    num = std::move(a.num);
    return *this;
}

BigNumber& BigNumber::operator=(const BigNumber& a) {
    num = a.num;
    return *this;
}

BigNumber singleSlotMultiplication(const BigNumber& a, const BigNumber& b) {
    BigNumber result;
    if (a.num.size() == 0 || b.num.size() == 0) {
        result.num.clear();
        result.num.push_back(0);
    } else if (a.num.size() > 1 && b.num.size() > 1) {
        cout << "Trying to multiply : a = " << a << " * b = " << b << 
            ". One of them has more than one digit so it is not possible with this function." << endl;
    } else  if ((a.num.size() == 1 && a.num[0] == 0) || (b.num.size() == 1 && b.num[0] == 0)) {
        result.num.clear();
        result.num.push_back(0);
    } else {
        auto shortest = a.num.size() < b.num.size() ? a : b;
        auto longest = a.num.size() < b.num.size() ? b : a;
    
        auto singleDigitOperand = shortest.num[0];
        for (unsigned long i = 0; i < longest.num.size(); ++i) {
            result = result + (BigNumber(longest.num[i] * singleDigitOperand)).shiftLeft(i);
        }
    }
    
    return result;
}

BigNumber& BigNumber::shiftLeft(unsigned long long int p) {
    num.insert(num.begin(), p, 0);
    return *this;
}

BigNumber BigNumber::getLowerHalf() const {
    BigNumber result ;
    auto& r = result.num;
    r.assign(num.begin(), num.begin() + num.size() / 2);

    //Now make sure we don't have 0's left in front
    while (!(r.size() == 1) && (r.back() == 0)) {
        r.pop_back();
    }
    
    return result;
}

BigNumber BigNumber::getHigherHalf() const {
    BigNumber result;
    auto& r = result.num;
    r.assign(num.begin() + num.size() / 2, num.end());
    
    //Now make sure we don't have 0's left in front
    while (!(r.size() == 1) && (r.back() == 0)) {
        r.pop_back();
    }
    
    return result;
}

BigNumber karatsubaMultiplication(const BigNumber& a, const BigNumber& b) {
    if (a.num.size() == 1 || b.num.size() == 1) {
        return singleSlotMultiplication(a, b);
    } else {
        auto m = static_cast<unsigned long long int>(max(ceil(a.num.size() / 2), ceil(b.num.size() / 2)));
        
        BigNumber lowA = a.getLowerHalf();
        BigNumber highA = a.getHigherHalf();
        BigNumber lowB = b.getLowerHalf();
        BigNumber highB = b.getHigherHalf();
        
        BigNumber z0, z1, z2;
        z0 = karatsubaMultiplication(lowA, lowB);
        z1 = karatsubaMultiplication((lowA+highA), (lowB+highB));
        z2 = karatsubaMultiplication(highA, highB);
         
        BigNumber resPart2 = (z1 - z2 - z0).shiftLeft(m);
        return (z2.shiftLeft(m << 1) + resPart2 + z0);
    }
}

BigNumber operator*(const BigNumber& a, const BigNumber& b) {
    BigNumber result = karatsubaMultiplication(a, b);
    return result;
}

bool operator<(const BigNumber& a, const BigNumber& b) {
    if (a.num.size() < b.num.size()) {
        return true;
    } else if (a.num.size() > b.num.size()) {
        return false;
    } else {
        bool lessThan = false;
        for (unsigned long i = a.num.size()-1 ; i+1 > 0; --i) {
            if (a.num[i] < b.num[i]) {
                lessThan = true;
                break;
            } else if (a.num[i] > b.num[i]) {
                break;
            }
        }
        return lessThan;
    }
}

bool operator==(const BigNumber& a, const BigNumber& b) {
    return a.num == b.num;
}

bool operator!=(const BigNumber& a, const BigNumber& b) {
    return a.num != b.num;
}

ostream& operator<<(ostream& outstream, const BigNumber& a) {
    vector<unsigned long long int> result(a.num.size() * baseRatio, 0);
    
    for (unsigned long i = 0; i < a.num.size(); ++i) {
        auto d = a.num[i];
        for (unsigned long j = 0; j < baseRatio; ++j) {
            result[baseRatio * i + j] = d % outputBase;
            d /= outputBase;
        }
    }
    
    reverse(result.begin(), result.end());
    
    auto it = result.begin();
    while (*it == 0 && it < result.end()) {
        ++it;
    }
    if (it != result.end()) {
        result.erase(result.begin(), it);
    } else {
        result.clear();
        result.push_back(0);
    }
    
    for (auto r : result) {
        outstream << r;
    }
    
    return outstream;
}

BigNumber operator+(const BigNumber& a, const BigNumber& b) {
    auto& shortest = a.num.size() < b.num.size() ? a.num : b.num;
    auto& longest = a.num.size() < b.num.size() ? b.num : a.num;
    
    auto nShortest = shortest.size();
    auto nLongest = longest.size();
    
    BigNumber result;
    auto& r = result.num;
    r.clear();
    unsigned long long int carry = 0;
    
    for (unsigned long i = 0; i < nShortest; ++i) {
        auto toAdd = shortest[i] + longest[i] + carry;
        r.push_back(toAdd % internalBase);
        carry = toAdd / internalBase;
    }
    
    for (unsigned long j = nShortest; j < nLongest; ++j) {
        auto toAdd = longest[j] + carry;
        r.push_back(toAdd % internalBase);
        carry = toAdd / internalBase;
    }
    
    if (carry) {
        r.push_back(carry);
    }
    
    return result;
}

BigNumber operator-(const BigNumber& a, const BigNumber& b) {
    //I am using the fact that according to the problem, there are no negative terms in the fibonacci series.
    if (a < b) {
        cout << endl << "Trying to substract BigNumbers : a = " << a << " - b = " << b << ". Since a < b, the behaviour is undefined." << endl;
        printVector(a.num, "a");
        printVector(b.num, "b");
        return BigNumber();
    } else if (a == b) {
        return BigNumber();
    } else {
        BigNumber result;
        auto& r = result.num;
        r.clear();
        unsigned long long int carry = 0;
        
        auto nA = a.num.size();
        auto nB = b.num.size();
        
        auto& vecA = a.num;
        auto& vecB = b.num;
        
        for (unsigned long i = 0; i < nB; ++i) {
            if (vecA[i] < vecB[i] + carry) {
                r.push_back((vecA[i] + internalBase) - (vecB[i] + carry));
                carry = 1;
            } else {
                r.push_back(vecA[i] - (vecB[i] + carry));
                carry = 0;
            }
        }
        
        for (unsigned long j = nB; j < nA; ++j) {
            if (vecA[j] < carry) {
                r.push_back((vecA[j] + internalBase) - carry);
                carry = 1;
            } else {
                r.push_back(vecA[j] - carry);
                carry = 0;
            }
        }
        
        //Now make sure we don't have 0's left in front
        while (!(r.size() == 1) && (r.back() == 0)) {
            r.pop_back();
        }
        
        return result;
    }
}

void printVector(const vector<unsigned long long int>& v, const string& name) {
    cout << endl << "Printing vector - " << name << " of size = " << v.size() << " : [";
    for (unsigned long i = 0; i < v.size()-1; ++i) {
        cout << v[i] << ",";
    }
    cout << v[v.size()-1] << "]";
    cout << endl;
}

/*void printNaked(const BigNumber& a) {
    if (a.num.size() == 0) {
        cout << "" << endl;
        return;
    }
    
    vector<unsigned long long int> copy(a.num);
    reverse(copy.begin(), copy.end());
    
    for (auto n : copy) {
        cout << n << ",";
    }
}*/

void testLessThan() {
    BigNumber a, b;
    
    a = 819025;
    b = 797449;
    cout << "a = " << a << " - b = " << b << " a < b ? : " << (a < b) << endl;
}

void testSubstraction() {
    BigNumber a, b;
    
    a = 3854896209;
    b = 2969166187;
    cout << "a = " << a << " - b = " << b << " | a - b = " << (a - b) << endl;
}

void testAddition() {
    BigNumber a, b;
    
    a = 3854896209;
    b = 2969166187;
    cout << "a = " << a << " - b = " << b << " | a + b = " << (a + b) << endl;
    
    auto res = a + b;
    
    for (unsigned long i = 0; i < 2000; ++i) {
        res += res;
        cout << "res + res = " << res << endl;
    }
}

void testMultiplication() {
    BigNumber a, b;
    
    a = 3854896209;
    b = 2969166187;
    cout << "a = " << a << " - b = " << b << " | a * b = " << (a * b) << endl;
}

BigNumber findFibonacciModified(vector<BigNumber>& terms, vector<bool>& calculated, unsigned long n) {
    if (calculated[n]) {
        return terms[n];
    }
    
    BigNumber termToPower = findFibonacciModified(terms, calculated, n-1);
    terms[n] = findFibonacciModified(terms, calculated, n-2) + termToPower*termToPower;
    calculated[n] = true;
    
    return terms[n];
}

void printAllDurations() {
    for (auto mapIt = durations.begin(); mapIt != durations.end(); ++mapIt) {
        auto durationMillis = duration_cast<milliseconds>(mapIt->second).count();
        cout << setw(25) << mapIt->first << " : " << durationMillis << " milliseconds" << endl;
    }
}

int main() {
    //testLessThan();
    //testSubstraction();
    //testAddition();
    //testMultiplication();
    
    unsigned long long int t1, t2;
    cin >> t1;
    cin >> t2;
   
    unsigned long n; 
    cin >> n;
    
    vector<BigNumber> terms(n+1);
    vector<bool> calculated(n+1, false);
    terms[0] = t1;
    terms[1] = t2;

/*    unsigned long n = 15;
    vector<BigNumber> terms(n+1);
    vector<bool> calculated(n+1, false);
    terms[0] = 1;
    terms[1] = 2;*/
    
//    cout << "terms[0] = " << terms[0] << " - terms[1] = " << terms[1] << " - n = " << n << endl;
    
    calculated[0] = true;
    calculated[1] = true;
    
    cout << findFibonacciModified(terms, calculated, n-1) << endl;
        
    return 0;
}
