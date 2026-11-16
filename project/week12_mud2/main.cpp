#include <iostream>
#include <string>
#include "user.h"
using namespace std;

const int mapX = 5;  // 맵의 가로 칸 수
const int mapY = 5;  // 맵의 세로 칸 수

// 함수 원형 선언
bool checkXY(int user_x, int width, int user_y, int height);
void displayMap(const int gameMap[][mapX], int user_x, int user_y);
bool checkGoal(const int gameMap[][mapX], int user_x, int user_y);
void checkState(const int gameMap[][mapX], int user_x, int user_y);
bool CheckUser(User user);

int main() {
    // 0: 빈 공간, 1: 아이템, 2: 적, 3: 포션, 4: 목적지
    int gameMap[mapY][mapX] = {
        {0, 1, 2, 0, 4},
        {1, 0, 0, 2, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 3, 0, 0},
        {3, 0, 0, 0, 2}
    };

    // 유저의 현재 위치. x는 열, y는 행을 나타낸다.
    int user_x = 0;
    int user_y = 0;

    // User 객체 하나를 생성한다. 생성자에서 HP가 20으로 설정된다.
    User user;

    while (true) {
        // HP는 private이므로 GetHP()를 통해 읽는다.
        cout << "현재 HP: " << user.GetHP() << endl;
        cout << "명령어를 입력하세요 (상,하,좌,우,지도,종료): ";

        string user_input;
        cin >> user_input;

        // 이동할 위치를 임시로 계산한다.
        // 맵 밖으로 나가면 실제 위치는 바꾸지 않는다.
        int next_x = user_x;
        int next_y = user_y;
        string moveMessage;

        if (user_input == "상") {
            --next_y;
            moveMessage = "위로 한 칸 올라갑니다.";
        } else if (user_input == "하") {
            ++next_y;
            moveMessage = "아래로 한 칸 내려갑니다.";
        } else if (user_input == "좌") {
            --next_x;
            moveMessage = "왼쪽으로 이동합니다.";
        } else if (user_input == "우") {
            ++next_x;
            moveMessage = "오른쪽으로 이동합니다.";
        } else if (user_input == "지도") {
            displayMap(gameMap, user_x, user_y);
            continue;
        } else if (user_input == "종료") {
            cout << "종료합니다." << endl;
            break;
        } else {
            cout << "잘못된 입력입니다." << endl;
            continue;
        }

        // 이동하려는 위치가 맵 안인지 확인한다.
        if (!checkXY(next_x, mapX, next_y, mapY)) {
            cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
            continue;
        }

        // 유효한 위치인 경우에만 실제 좌표를 갱신한다.
        user_x = next_x;
        user_y = next_y;

        cout << moveMessage << endl;
        displayMap(gameMap, user_x, user_y);

        // 한 칸 이동할 때 HP가 1 감소한다.
        user.DecreaseHP(1);

        // 현재 칸에 무엇이 있는지 메시지를 출력한다.
        checkState(gameMap, user_x, user_y);

        // 현재 칸의 상태를 확인해 추가 효과를 적용한다.
        // 아이템·적·포션은 한 번 이용한 뒤 빈칸으로 바꾼다.
        int& currentTile = gameMap[user_y][user_x];

        if (currentTile == 2) {
            user.DecreaseHP(2);
            cout << "적을 만나 HP가 2 감소했습니다." << endl;
            currentTile = 0;
        } else if (currentTile == 3) {
            user.IncreaseHP(2);
            cout << "포션을 만나 HP가 2 증가했습니다." << endl;
            currentTile = 0;
        } else if (currentTile == 1) {
            // 아이템 칸은 방문 후 빈칸으로 처리한다.
            currentTile = 0;
        }

        // HP가 0 이하인지 CheckUser 함수로 확인한다.
        if (!CheckUser(user)) {
            cout << "실패" << endl;
            break;
        }

        // 목적지에 도착했는지 확인한다.
        if (checkGoal(gameMap, user_x, user_y)) {
            cout << "목적지에 도착했습니다! 축하합니다!" << endl;
            cout << "게임을 종료합니다." << endl;
            break;
        }
    }

    return 0;
}

// 좌표가 맵의 범위 안에 있으면 true를 반환한다.
bool checkXY(int user_x, int width, int user_y, int height) {
    return user_x >= 0 && user_x < width &&
           user_y >= 0 && user_y < height;
}

// 현재 위치가 표시된 지도를 출력한다.
void displayMap(const int gameMap[][mapX], int user_x, int user_y) {
    for (int row = 0; row < mapY; ++row) {
        for (int col = 0; col < mapX; ++col) {
            // 유저가 있는 칸에는 맵의 요소 대신 USER를 출력한다.
            if (row == user_y && col == user_x) {
                cout << " USER |";
            } else {
                switch (gameMap[row][col]) {
                case 0:
                    cout << "      |";
                    break;
                case 1:
                    cout << "아이템|";
                    break;
                case 2:
                    cout << "  적  |";
                    break;
                case 3:
                    cout << " 포션 |";
                    break;
                case 4:
                    cout << "목적지|";
                    break;
                }
            }
        }

        cout << endl;
        cout << " -------------------------------- " << endl;
    }
}

// 현재 위치의 맵 값이 4이면 목적지에 도착한 것이다.
bool checkGoal(const int gameMap[][mapX], int user_x, int user_y) {
    return gameMap[user_y][user_x] == 4;
}

// 현재 칸에 있는 아이템·적·포션에 대한 메시지를 출력한다.
void checkState(const int gameMap[][mapX], int user_x, int user_y) {
    switch (gameMap[user_y][user_x]) {
    case 1:
        cout << "무기/갑옷 아이템이 있습니다." << endl;
        break;
    case 2:
        cout << "적을 만났습니다." << endl;
        break;
    case 3:
        cout << "포션이 있습니다." << endl;
        break;
    }
}

// HP가 양수이면 게임을 계속할 수 있으므로 true를 반환한다.
// 0 또는 음수이면 실패 상태이므로 false를 반환한다.
bool CheckUser(User user) {
    return user.GetHP() > 0;
}
