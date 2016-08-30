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

unsigned long int findMaxPoints(const vector<unsigned long int>& i, unsigned long int& maxPoints) {
    if (debug) printContainer(i, "vector to findMaxPoints");
    
    if (i.size() <= 1) {
        return 0;
    } else if (i.size() == 2) {
        if (i[0] == i[1]) {
            return maxPoints + 1;
        } else {
            return 0;
        }
    } else {
        auto half = i.size() / 2;
        maxPoints += max(findMaxPoints(vector<unsigned long int> (i.begin(), i.begin() + half), maxPoints),
            findMaxPoints(vector<unsigned long int> (i.begin() + half, i.end()), maxPoints));
            
        return maxPoints;
    }
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
        
        auto maxPoints = static_cast<unsigned long int>(0);
        cout << findMaxPoints(integers, maxPoints) << endl;
    }
    
    return 0;
}