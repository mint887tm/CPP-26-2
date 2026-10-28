#include <vector>
#include <iostream>
using namespace std;

int main(void) {
    vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    cout << "현재의 v = ";
    for (auto& e : v) {
        cout << e << " ";
    }
    cout << endl;
    for (auto p = v.begin(); p != v.end(); ++p) {
        cout << *p << endl;
    }
    return 0;
}