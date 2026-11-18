#include <iostream>
#include <string>
#include <vector>  
#include "user.h"
using namespace std;

bool checkXY(const vector<vector<int>>& gameMap, int user_x, int user_y);
void displayMap(const vector<vector<int>>& gameMap, int user_x, int user_y);
bool checkGoal(const vector<vector<int>>& gameMap, int user_x, int user_y);
void checkState(const vector<vector<int>>& gameMap, int user_x, int user_y);

int main() {
    // 0: 빈칸, 1: 아이템, 2: 적, 3: 포션, 4: 목적지
    vector<vector<int>> gameMap = {
        {0, 1, 2, 0, 4},
        {1, 0, 0, 2, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 3, 0, 0},
        {3, 0, 0, 0, 2}
    };

    int user_x = 0;
    int user_y = 0;

    // 생성자에서 HP는 20, itemCnt는 0으로 초기화된다.
    User user;

    while (true) {
        cout << "현재 HP: " << user.GetHP() << endl;
        cout << "명령어를 입력하세요 (상,하,좌,우,지도,정보/info,종료): ";

        string user_input;
        if (!(cin >> user_input)) {
            break;
        }

        // 우선 현재 위치를 복사해 다음 이동 위치를 계산한다.
        // 맵 밖으로 나가려는 경우 실제 위치는 바꾸지 않는다.
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
            // 지도 보기만 하므로 이동하거나 HP를 소모하지 않는다.
            displayMap(gameMap, user_x, user_y);
            continue;
        } else if (user_input == "정보" || user_input == "info") {
            // User의 << 연산자를 호출해 HP와 획득 아이템 수를 출력한다.
            cout << user << endl;
            continue;
        } else if (user_input == "종료") {
            cout << "종료합니다." << endl;
            break;
        } else {
            cout << "잘못된 입력입니다." << endl;
            continue;
        }

        // 다음 위치가 맵 범위 밖이면 이동하지 않고 HP도 감소시키지 않는다.
        if (!checkXY(gameMap, next_x, next_y)) {
            cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
            continue;
        }

        // 유효한 이동이므로 실제 위치를 갱신한다.
        user_x = next_x;
        user_y = next_y;
        cout << moveMessage << endl;
        displayMap(gameMap, user_x, user_y);

        // 맵 안에서 한 칸 이동할 때 기본 HP 1을 감소시킨다.
        user.DecreaseHP(1);

        // 현재 칸의 종류에 맞는 안내 메시지를 출력한다.
        checkState(gameMap, user_x, user_y);

        // int&는 현재 칸 자체를 가리킨다.
        // currentTile을 바꾸면 vector 안의 해당 칸도 함께 바뀐다.
        int& currentTile = gameMap[user_y][user_x];

        if (currentTile == 1) {
            // 아이템 칸에 도착하면 획득 횟수를 1 증가시킨다.
            user.IncreaseItemCnt();
            cout << "아이템을 획득했습니다. 획득한 아이템 수가 1 증가했습니다." << endl;
            currentTile = 0;  // 다시 방문해도 같은 아이템을 중복 획득하지 않도록 빈칸 처리
        } else if (currentTile == 2) {
            // 적을 만나면 이동 비용 외에 HP 2를 추가로 잃는다.
            user.DecreaseHP(2);
            cout << "적을 만나 HP가 2 감소했습니다." << endl;
            currentTile = 0;  // 적을 한 번 만난 뒤에는 해당 칸을 빈칸으로 처리
        } else if (currentTile == 3) {
            // 포션을 마시면 HP 2를 회복한다. 포션은 itemCnt에 포함하지 않는다.
            user.IncreaseHP(2);
            cout << "포션을 만나 HP가 2 증가했습니다." << endl;
            currentTile = 0;  // 다시 방문해도 포션을 중복 사용하지 않도록 빈칸 처리
        }

        // HP가 0 이하이면 실패하고 게임을 끝낸다.
        if (user.GetHP() <= 0) {
            cout << "실패" << endl;
            break;
        }

        // 현재 칸이 목적지인지 확인한다.
        if (checkGoal(gameMap, user_x, user_y)) {
            cout << "목적지에 도착했습니다! 축하합니다!" << endl;
            cout << "게임을 종료합니다." << endl;
            break;
        }
    }

    return 0;
}

// 좌표가 실제 vector 맵 안에 있는지 확인한다.
bool checkXY(const vector<vector<int>>& gameMap, int user_x, int user_y) {
    if (user_y < 0 || user_y >= static_cast<int>(gameMap.size())) {
        return false;
    }

    if (user_x < 0 || user_x >= static_cast<int>(gameMap[user_y].size())) {
        return false;
    }

    return true;
}

// 현재 위치가 표시된 맵을 출력한다.
void displayMap(const vector<vector<int>>& gameMap, int user_x, int user_y) {
    for (int row = 0; row < static_cast<int>(gameMap.size()); ++row) {
        for (int col = 0; col < static_cast<int>(gameMap[row].size()); ++col) {
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

// 현재 위치의 칸이 목적지인지 확인한다.
bool checkGoal(const vector<vector<int>>& gameMap, int user_x, int user_y) {
    return gameMap[user_y][user_x] == 4;
}

// 현재 칸의 아이템·적·포션 종류를 메시지로 알려준다.
void checkState(const vector<vector<int>>& gameMap, int user_x, int user_y) {
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
