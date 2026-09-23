#include <iostream>
#include <string>
using namespace std;

int main() {
    int maxPeople;
    cout << "총 고객의 수를 입력하라: ";
    cin >> maxPeople;
    string names[maxPeople];
    int ages[maxPeople];

    for (int i = 0; i < maxPeople; i++) {
        cout << "사람 " << i + 1 << "의 이름: ";
        cin >> names[i];
        cout << "사람 " << i + 1 << "의 나이: ";
        cin >> ages[i];
    }

    int ageThreshold;
    cout << "특정 나이 이상인 사람을 찾으려면 나이를 입력하세요: ";
    cin >> ageThreshold;

    cout << ageThreshold << "세 이상의 고객들:\n";

    bool found = false;

    for (int i = 0; i < maxPeople; i++) {
        if (ages[i] >= ageThreshold) {
            cout << names[i] << " (" << ages[i] << "세)\n";
            found = true;
        }
    }

    if (!found) {
        cout << ageThreshold << "세 이상의 나이를 가진 고객이 없습니다.\n";
    }

    return 0;
}