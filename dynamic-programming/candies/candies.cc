#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void printVector(const vector<unsigned long int>& v, const string& name) {
    cout << "Printing vector - " << name << " of size = " << v.size() << " : [";
    for (unsigned long i = 0; i < v.size()-1; ++i) {
        cout << v[i] << ",";
    }
    cout << v[v.size()-1] << "]";
    cout << endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    auto children = static_cast<unsigned int>(0);
    cin >> children;
    
	vector<unsigned int> ratings (children, 0);
    for (auto i = 0; i < children; ++i) {
        auto rating = static_cast<unsigned int>(0);
 	   	cin >> rating;
        ratings.push_back(rating);
	}
	
	return 0;
}