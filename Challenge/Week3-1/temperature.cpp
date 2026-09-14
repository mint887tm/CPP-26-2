#include <iostream>
#include <string>
using namespace std;

int main() {
    double fahrenheit;
    cout << "화씨온도: ";
    cin >> fahrenheit;

    double celsius;
    celsius = (5.0 / 9.0) * (fahrenheit - 32);

    cout << celsius << endl;

    return 0;
}