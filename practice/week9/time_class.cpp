#include <iostream>
using namespace std;

class Time{
    public:
    int hour;
    int minute;
    Time() {}
    Time(int h, int m) {
        hour = h;
        minute = m;
    }

    void Print() {
        cout << hour << ":" << minute << endl;
    }
};

int main() {
    Time a;
    Time b(10, 30);
    Time c { 10, 40};
    Time d { 10, 50 };

    a.Print();
    b.Print();
    c.Print();
    d.Print();
    return 0;
}