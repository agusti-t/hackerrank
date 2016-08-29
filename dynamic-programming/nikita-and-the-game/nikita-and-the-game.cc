#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

constexpr bool debug = true;

template <typename Container>
void printContainer(const Container& c, const string& name) {
    cout << "Printing container - " << name << " of size = " << c.size() << " : [";
    for (auto i = 0; i < c.size()-1; ++i) {
        cout << c[i] << ",";
    }
    cout << c[c.size()-1] << "]" << endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    auto cases = static_cast<unsigned int>(0);
    cin >> cases;
    
    while (cases-- > 0) {
        auto size = static_cast<unsigned int>(0);
        cin >> size;
        
        vector<unsigned long int> integers;
        while (size-- > 0) {
            auto integer = static_cast<unsigned long int>(0);
            cin >> integer;
            integers.push_back(integer);
        }
        
        if (debug) printContainer(integers, "integers - " + to_string(cases));
    }
    
    return 0;
}