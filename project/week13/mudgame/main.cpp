#include <iostream>
#include <string>
#include <vector>
#include "user.h"
using namespace std;

bool checkXY(const vector<vector<int>>& gameMap, int x, int y);
void displayMap(const vector<vector<int>>& gameMap, int user_x, int user_y);
bool checkGoal(const vector<vector<int>>& gameMap, int user_x, int user_y);
void checkState(const vector<vector<int>>& gameMap, int user_x, int user_y);
bool attackAdjacentEnemy(vector<vector<int>>& gameMap,
                         int user_x, int user_y, User& user);

int main() {
    // 0: 빈칸, 1: 아이템, 2: 적, 3: 포션, 4: 목적지
    vector<vector<int>> gameMap = {
        {0, 1, 2, 0, 4},
        {1, 0, 0, 2, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 3, 0, 0},
        {3, 0, 0, 0, 2}
    };

    // 게임을 시작하기 전에 직업을 선택하게 함.
    int choice;
    cout << "직업을 선택하세요 (1. Magician, 2. Warrior): ";
    if (!(cin >> choice)) {
        return 0; 
    }

    while (choice != 1 && choice != 2) {
        cout << "잘못된 선택입니다. 1 또는 2를 입력하세요: ";
        if (!(cin >> choice)) {
            return 0;
        }
    }

    User* user = nullptr;
    if (choice == 1) {
        user = new Magician();
    } else {
        user = new Warrior();
    }

    cout << user->GetJobName() << "를 선택했습니다." << endl;

    int user_x = 0;
    int user_y = 0;

    displayMap(gameMap, user_x, user_y);

    while (true) {
        cout << "\n현재 HP: " << user->GetHP() << endl;
        cout << "명령어 (상,하,좌,우,공격,지도,정보/info,종료): ";

        string command;
        if (!(cin >> command)) {
            break;  // 입력이 끝난 경우에도 게임을 마침.
        }

        if (command == "종료") {
            cout << "게임을 종료합니다." << endl;
            break;
        }

        if (command == "지도") {
            displayMap(gameMap, user_x, user_y);
            continue;  // 지도 확인은 이동이 아니므로 HP를 깎지 않음.
        }

        if (command == "정보" || command == "info") {
            cout << user->GetJobName() << " 정보: " << *user << endl;
            continue;  // 정보 확인도 이동이 아니므로 HP를 깎지 않음.
        }

        if (command == "공격") {
            // 인접한 적이 있을 때 직업별 doAttack()이 실행되고 적을 제거함.
            attackAdjacentEnemy(gameMap, user_x, user_y, *user);
            displayMap(gameMap, user_x, user_y);
            continue;  // 공격 자체는 이동 HP를 소모하지 않음.
        }

        // 이동 전 다음 좌표를 계산함. 범위가 유효할 때만 실제 좌표를 갱신함.
        int next_x = user_x;
        int next_y = user_y;
        string moveMessage;

        if (command == "상") {
            --next_y;
            moveMessage = "위로 한 칸 올라갑니다.";
        } else if (command == "하") {
            ++next_y;
            moveMessage = "아래로 한 칸 내려갑니다.";
        } else if (command == "좌") {
            --next_x;
            moveMessage = "왼쪽으로 이동합니다.";
        } else if (command == "우") {
            ++next_x;
            moveMessage = "오른쪽으로 이동합니다.";
        } else {
            cout << "잘못된 입력입니다." << endl;
            continue;
        }

        // 맵 밖 이동은 좌표와 HP를 바꾸지 않음.
        if (!checkXY(gameMap, next_x, next_y)) {
            cout << "맵을 벗어났습니다. 다시 입력하세요." << endl;
            continue;
        }

        // 유효한 한 칸 이동을 적용하고 기본 이동 HP 1을 감소시킴.
        user_x = next_x;
        user_y = next_y;
        user->DecreaseHP(1);
        cout << moveMessage << endl;
        displayMap(gameMap, user_x, user_y);

        // 도착한 칸 종류에 따라 아이템, 적, 포션을 처리함.
        checkState(gameMap, user_x, user_y);
        int& currentTile = gameMap[user_y][user_x];

        if (currentTile == 1) {
            user->IncreaseItemCnt();
            cout << "아이템을 획득했습니다. 획득 수가 1 증가했습니다." << endl;
            currentTile = 0;  // 아이템은 한 번만 획득하도록 빈칸으로 바꿈.
        } else if (currentTile == 2) {
            user->doAttack();
            user->DecreaseHP(2);
            cout << "적과 싸워 HP가 추가로 2 감소했습니다." << endl;
            currentTile = 0;  // 적은 처리된 뒤 빈칸으로 바꿈.
        } else if (currentTile == 3) {
            user->IncreaseHP(2);
            cout << "포션을 마셔 HP가 2 회복됐습니다." << endl;
            currentTile = 0;  // 포션은 한 번만 사용하도록 빈칸으로 바꿈.
        }

        // HP가 0 이하이면 목적지 검사보다 먼저 실패 처리함.
        if (user->GetHP() <= 0) {
            cout << "실패: HP가 0 이하입니다." << endl;
            break;
        }

        if (checkGoal(gameMap, user_x, user_y)) {
            cout << "목적지에 도착했습니다! 축하합니다!" << endl;
            cout << "게임을 종료합니다." << endl;
            break;
        }
    }

    // new로 만든 객체를 해제함. User의 가상 소멸자로 파생 객체도 안전하게 삭제됨.
    delete user;
    return 0;
}

// 좌표가 각 행의 범위 안에 있는지 확인함.
bool checkXY(const vector<vector<int>>& gameMap, int x, int y) {
    if (y < 0 || y >= static_cast<int>(gameMap.size())) {
        return false;
    }

    if (x < 0 || x >= static_cast<int>(gameMap[y].size())) {
        return false;
    }

    return true;
}

// 현재 위치를 USER로 표시하고 나머지는 칸의 종류에 맞춰 출력함.
void displayMap(const vector<vector<int>>& gameMap, int user_x, int user_y) {
    for (int row = 0; row < static_cast<int>(gameMap.size()); ++row) {
        for (int col = 0; col < static_cast<int>(gameMap[row].size()); ++col) {
            if (row == user_y && col == user_x) {
                cout << " USER |";
            } else {
                switch (gameMap[row][col]) {
                case 0: cout << "      |"; break;
                case 1: cout << "아이템|"; break;
                case 2: cout << "  적  |"; break;
                case 3: cout << " 포션 |"; break;
                case 4: cout << "목적지|"; break;
                }
            }
        }
        cout << endl << " -------------------------------- " << endl;
    }
}

// 현재 좌표의 칸이 목적지(4)인지 확인함.
bool checkGoal(const vector<vector<int>>& gameMap, int x, int y) {
    return gameMap[y][x] == 4;
}

// 현재 칸의 종류에 맞는 안내 메시지를 출력함.
void checkState(const vector<vector<int>>& gameMap, int x, int y) {
    switch (gameMap[y][x]) {
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

// 상하좌우에 있는 적을 찾아 제거함
// User 참조로 호출해도 실제 직업의 doAttack()이 실행됨.
bool attackAdjacentEnemy(vector<vector<int>>& gameMap,
                         int user_x, int user_y, User& user) {
    const int dx[4] = {0, 0, -1, 1};
    const int dy[4] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; ++i) {
        int enemy_x = user_x + dx[i];
        int enemy_y = user_y + dy[i];

        if (checkXY(gameMap, enemy_x, enemy_y) &&
            gameMap[enemy_y][enemy_x] == 2) {
            user.doAttack();
            gameMap[enemy_y][enemy_x] = 0;
            cout << "인접한 적을 처치했습니다." << endl;
            return true;
        }
    }

    cout << "주변에 공격할 적이 없습니다." << endl;
    return false;
}
