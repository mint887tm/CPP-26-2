#include <iostream>
#include <string>
using namespace std;

int main() {
    int money;
    cout << "현재 가지고 있는 돈: ";
    cin >> money;
    int price;
    cout << "캔디의 가격: ";
    cin >> price;
    cout << "최대로 살 수 있는 캔디";
    cout << money/price << endl;
    cout << "캔디 구입 후 남은 돈";
    cout << money%price << endl;
    return 0;
}