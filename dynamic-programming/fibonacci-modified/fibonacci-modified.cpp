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

void printVector(const vector<unsigned int>& v, const string& name);

class BigNumber {

    private:
        vector<unsigned int> num;
    
    public:
        BigNumber(unsigned int num = 0);
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
        friend void printVector(const vector<unsigned int>& v, const string& name);
        friend void testLessThan();
        friend void testSubstraction();
    
    private:
        BigNumber singleSlotMultiplication(const BigNumber& a, const BigNumber& b) const;
        BigNumber karatsubaMultiplication(const BigNumber& a, const BigNumber& b) const;
        BigNumber getLowerHalf() const;
        BigNumber getHigherHalf() const;
        BigNumber shiftLeft(unsigned int p) const;
        
};

BigNumber findFibonacciModified(vector<BigNumber>& terms, vector<bool>& calculated, unsigned long n);


BigNumber::BigNumber(unsigned int n) {
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

BigNumber BigNumber::singleSlotMultiplication(const BigNumber& a, const BigNumber& b) const {
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
    
        for (unsigned int i = 0; i < shortest.num[0]; i++) {
            result = result + longest;
        }
    }
    
    return result;
}

BigNumber BigNumber::shiftLeft(unsigned int p) const {
    BigNumber result(*this);
    result.num.insert(result.num.begin(), p, 0);
    
    return result;
}

BigNumber BigNumber::getLowerHalf() const {
    BigNumber result;
    result.num.assign(num.begin(), num.begin() + num.size() / 2);
    return result;
}

BigNumber BigNumber::getHigherHalf() const {
    BigNumber result;
    result.num.assign(num.begin() + num.size() / 2, num.end());
    return result;
}

BigNumber BigNumber::karatsubaMultiplication(const BigNumber& a, const BigNumber& b) const {
    if (a.num.size() == 1 || b.num.size() == 1) {
        return singleSlotMultiplication(a, b);
    } else {
        unsigned int m = static_cast<unsigned int>(max(ceil(a.num.size() / 2), ceil(b.num.size() / 2))) * 2;
        
        BigNumber lowA = a.getLowerHalf();
        BigNumber highA = a.getHigherHalf();
        BigNumber lowB = b.getLowerHalf();
        BigNumber highB = b.getHigherHalf();
        
        BigNumber z0 = karatsubaMultiplication(lowA, lowB);
        BigNumber z1 = karatsubaMultiplication((lowA+highA), (lowB+highB));
        BigNumber z2 = karatsubaMultiplication(highA, highB);
        
        BigNumber firstPart = z2.shiftLeft(m);
        BigNumber secondPart11 = z1 - z2;
        BigNumber secondPart1 = secondPart11 - z0;
        BigNumber secondPart2 = secondPart1.shiftLeft(m/2);
                        
        return (firstPart + secondPart2 + z0);
    }
}

BigNumber operator*(const BigNumber& a, const BigNumber& b) {
    BigNumber result = a.karatsubaMultiplication(a, b);
    return result;
}

bool operator<(const BigNumber& a, const BigNumber& b) {
    if (a.num.size() < b.num.size()) {
        return true;
    } else if (a.num.size() > b.num.size()) {
        return false;
    } else {
        bool lessThan = false;
        for (unsigned long i = a.num.size()-1 ; i+1 > 0; i--) {
            //cout << "Examining, a.num[" << i << "] = " << a.num[i] << " | b.num[" << i << "] = " << b.num[i] << endl;
            if (a.num[i] < b.num[i]) {
                lessThan = true;
                break;
            } else if (a.num[i] > b.num[i]) {
                break;
            }
        }
        
        return lessThan;
        /*auto aIt = a.num.rbegin();
        auto bIt = b.num.rbegin();
        
        cout << "Examining, aIt : " << *aIt << " | bIt : " << *bIt << endl;
        
        while ((*aIt == *bIt) && (aIt < a.num.rend())) {
            aIt++;
            bIt++;
                    cout << "Examining, aIt : " << *aIt << " | bIt : " << *bIt << endl;
        }
        
        if (aIt < a.num.rend()) {
            return false;
        } else {
            return *aIt < *bIt;
        }*/
    }
}

bool operator==(const BigNumber& a, const BigNumber& b) {
    return a.num == b.num;
}

bool operator!=(const BigNumber& a, const BigNumber& b) {
    return a.num != b.num;
}

ostream& operator<<(ostream& outstream, const BigNumber& a) {
    vector<unsigned int> result(a.num.size() * 2, 0);
    
    for (unsigned long int i = 0; i < a.num.size(); ++i) {
        auto d = a.num[i];
        result[2 * i] = d % outputBase;
        result[2 * i + 1] = d / outputBase;
    }
    
    reverse(result.begin(), result.end());
    
    auto it = result.begin();
    while (*it == 0 && it < result.end()) {
        it++;
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
    auto shortest = a.num.size() < b.num.size() ? a.num : b.num;
    auto longest = a.num.size() < b.num.size() ? b.num : a.num;
    
    auto nShortest = shortest.size();
    auto nLongest = longest.size();
    
    BigNumber result;
    auto& r = result.num;
    r.clear();
    unsigned int carry = 0;
    
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
        unsigned int carry = 0;
        
        auto nA = a.num.size();
        auto nB = b.num.size();
        
        for (unsigned long int i = 0; i < nB; i++) {
            if (a.num[i] < b.num[i] + carry) {
                r.push_back((a.num[i] + internalBase) - (b.num[i] + carry));
                carry = 1;
            } else {
                r.push_back(a.num[i] - (b.num[i] + carry));
                carry = 0;
            }
        }
        
        for (unsigned long int j = nB; j < nA; j++) {
            if (a.num[j] < carry) {
                r.push_back((a.num[j] + internalBase) - carry);
                carry = 1;
            } else {
                r.push_back(a.num[j] - carry);
                carry = 0;
            }
        }
        
        return result;
    }
}

void printVector(const vector<unsigned int>& v, const string& name) {
    cout << endl << "Printing vector - " << name << " of size = " << v.size() << " : [";
    for (unsigned long int i = 0; i < v.size()-1; i++) {
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
    
    vector<unsigned int> copy(a.num);
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
    
    a = 5929;
    b = 5929;
    cout << "a = " << a << " - b = " << b << " | a - b = " << (a - b) << endl;
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

int main() {
    //testLessThan();
    //testSubstraction();
    
/*    unsigned int t1, t2;
    cin >> t1;
    cin >> t2;
   
    unsigned long n; 
    cin >> n;
    
    vector<BigNumber> terms(n+1);
    vector<bool> calculated(n+1, false);
    terms[0] = t1;
    terms[1] = t2;*/

    unsigned long n = 15;
    vector<BigNumber> terms(n+1);
    vector<bool> calculated(n+1, false);
    terms[0] = 1;
    terms[1] = 2;
    
    cout << "terms[0] = " << terms[0] << " - terms[1] = " << terms[1] << " - n = " << n << endl;
    
    calculated[0] = true;
    calculated[1] = true;
    
    cout << findFibonacciModified(terms, calculated, n-1) << endl;
        
    return 0;
}
