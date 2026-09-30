#include <iostream>
using namespace std;

void swap(int x, int& y) {
    int tmp;
    tmp = x;
    x = y;
    y = tmp;
    cout << "a=" << x << " b=" << y << endl;
}

int main() {
    int a = 100, b = 200;
    cout << "a=" << a << " b=" << b << endl;

    swap(a,b);
    //cout << "a=" << a << " b=" << b << endl;
    return 0;
}