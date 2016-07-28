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

void printVector(const vector<unsigned long long int>& v, const string& name);

class BigNumber {

public:
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
        
        friend void printNaked(const BigNumber& a);
    
//    private:
        BigNumber singleSlotMultiplication(const BigNumber& a, const BigNumber& b) const;
        BigNumber karatsubaMultiplication(const BigNumber& a, const BigNumber& b) const;
        BigNumber getLowerHalf() const;
        BigNumber getHigherHalf() const;
        BigNumber shiftLeft(unsigned int p) const;
        
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
    cout << "Multiplying by single slot : a = " << a << " * b = " << b << endl;
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
            cout << result << ",";
        }
        cout << endl;
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
        cout << "Going into single slot." << endl;
        return singleSlotMultiplication(a, b);
    } else {
        unsigned int m = static_cast<unsigned int>(max(ceil(a.num.size() / 2), ceil(b.num.size() / 2))) * 2;
        
        BigNumber lowA = a.getLowerHalf();
        BigNumber highA = a.getHigherHalf();
        BigNumber lowB = b.getLowerHalf();
        BigNumber highB = b.getHigherHalf();
        
        printVector(highA.num, "highA");
        printVector(lowA.num, "lowA");
        printVector(highB.num, "highB");
        printVector(lowB.num, "lowB");
        
        BigNumber z0 = karatsubaMultiplication(lowA, lowB);
        cout << "z0 = " << z0 << endl;
        printVector(z0.num, "z0");
        BigNumber z1 = karatsubaMultiplication((lowA+highA), (lowB+highB));
        cout << "z1 = " << z1 << endl;
        printVector(z1.num, "z1");
        BigNumber z2 = karatsubaMultiplication(highA, highB);
        cout << "z2 = " << z2 << endl;
        printVector(z2.num, "z2");
        
        BigNumber firstPart = z2.shiftLeft(m);
        printVector(firstPart.num, "firstPart");
        cout << "z2 = " << z2 << endl;
        printVector(z2.num, "z2");
        BigNumber secondPart11 = z1 - z2;
        printVector(secondPart11.num, "secondPart11");
        BigNumber secondPart1 = secondPart11 - z0;
        printVector(secondPart1.num, "secondPart1");
        BigNumber secondPart2 = secondPart1.shiftLeft(m/2);
        printVector(secondPart2.num, "secondPart2");
                        
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
        cout << "right place, wrong time" << endl;
        auto aIt = a.num.end() - 1;
        auto bIt = b.num.end() - 1;
        cout << "now examining : aIt = " << *aIt << " - bIt = " << *bIt << endl;
        
        while ((*aIt == *bIt) && (aIt >= a.num.begin())) {
            cout << "now examining : aIt = " << *aIt << " - bIt = " << *bIt << endl;
            aIt--;
            bIt--;
        }
        
        if (aIt < a.num.begin()) {
            return false;
        } else {
            return *aIt < *bIt;
        }
    }
}

bool operator==(const BigNumber& a, const BigNumber& b) {
    return a.num == b.num;
}

ostream& operator<<(ostream& outstream, const BigNumber& a) {
    vector<unsigned long long int> result(a.num.size() * 2, 0);
    
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
        
        printVector(a.num, "a");
        printVector(b.num, "b");
        
        for (unsigned long int i = 0; i < nB; i++) {
            cout << "a.num[" << i << "] = " << a.num[i];
            cout << " / b.num[" << i << "] = " << b.num[i] << endl;;
            if (a.num[i] < b.num[i] + carry) {
                cout << "with carry" << endl;
                r.push_back((a.num[i] + internalBase) - (b.num[i] + carry));
                carry = 1;
                printVector(r, "result vector with carry");
            } else {
                cout << "without carry" << endl;
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

void printVector(const vector<unsigned long long int>& v, const string& name) {
    cout << endl << "Printing vector - " << name << " of size = " << v.size() << " : [";
    for (unsigned long int i = 0; i < v.size()-1; i++) {
        cout << v[i] << ",";
    }
    cout << v[v.size()-1] << "]";
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

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    /*int t1;
    cin >> t1;
    
    int t2;
    cin >> t2;
    
    int n;
    cin >> n;*/
    
    BigNumber a(4224), b(4096);
    
//    cout << "Naked print of a : "; printNaked(a); cout << " and of b : "; printNaked(b); cout << endl;
//    cout << a << " < " << b << " ? : " << (a < b) << endl;

    BigNumber c(10000); 
//    cout << "Naked print of c : "; printNaked(c); cout << endl; cout << "Normal print of c : " << c << endl;
    
    cout << "a = " << a << " - b = " << b << " - c = " << c << endl;
//    cout << "Addition of a + b : " << (a + b) << endl;
//    cout << "Addition of a + b + c : " << (a + b + c) << endl;
//    cout << "Substraction a - b : " << (a - b) << endl;
//    printVector(c.num, "c");
//    printVector(a.num, "a");
//    printVector(b.num, "b");
//    cout << "Substraction c - a - b : " << (c - b - a) << endl;
//    cout << "Multiplication a * b : " << (a * b) << endl;
    
    BigNumber d(199), e(199), f(948683), g(948683);
    
    cout << "d = " << d << " - e = " << e << " - f = " << f << " - g = " << g << endl;
    cout << "KaratsubaMultiplication d * e : " << d.karatsubaMultiplication(d, e) << endl;
    cout << "KaratsubaMultiplication f * g : " << d.karatsubaMultiplication(f, g) << endl;
    cout << "KaratsubaMultiplication f * g : " << f * g << endl;
//    cout << "SingleSlotMultiplication d * e : " << d.singleSlotMultiplication(d, e) << endl;
//    cout << "Addition d + e : " << d + e << endl;
        
    return 0;
}
