#include <iostream>
#include <string>
#include <vector>
#include "user.h"
using namespace std;

// 플레이어마다 캐릭터 이름, 지도 기호, 좌표, User 객체 주소를 보관함
struct Player {
    string name;
    char symbol;
    int x;
    int y;
    User* user;
};

bool checkXY(const vector<vector<int>>& gameMap, int x, int y);
void displayMap(const vector<vector<int>>& gameMap, const Player players[]);
bool checkGoal(const vector<vector<int>>& gameMap, int x, int y);
bool attackAdjacentEnemy(vector<vector<int>>& gameMap, const Player& player);

int main() {
    // 0: 빈칸, 1: 아이템, 2: 적, 3: 포션, 4: 목적지
    vector<vector<int>> gameMap = {
        {0, 1, 2, 0, 4},
        {1, 0, 0, 2, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 3, 0, 0},
        {3, 0, 0, 0, 2}
    };

    // 각 객체가 독립된 HP와 아이템 수를 가짐
    Magician magician;
    Warrior warrior;

    // 두 플레이어는 같은 시작 좌표 (0, 0)에서 시작함
    Player players[2] = {
        {"Magician", 'M', 0, 0, &magician},
        {"Warrior",  'W', 0, 0, &warrior}
    };

    int turn = 0;  // 유효한 행동이 끝날 때마다 증가시킴

    while (true) {
        // 짝수 턴은 Magician, 홀수 턴은 Warrior
        int currentIndex = turn % 2;
        Player& current = players[currentIndex];

        cout << "\n" << current.name << " 차례 (HP: "
             << current.user->GetHP() << ")" << endl;
        cout << "명령어 (상,하,좌,우,공격,지도,정보/info,종료): ";

        string command;
        if (!(cin >> command)) {
            // 입력 스트림이 끝나도 프로그램을 안전하게 끝냄
            break;
        }

        if (command == "종료") {
            cout << "게임을 종료합니다." << endl;
            break;
        }

        if (command == "지도") {
            // 지도 확인은 행동이 아니므로 턴을 소비하지 않음
            displayMap(gameMap, players);
            continue;
        }

        if (command == "정보" || command == "info") {
            // 현재 차례 캐릭터의 정보만 출력함
            cout << current.name << ": " << *current.user << endl;
            continue;
        }

        if (command == "공격") {
            // User 포인터가 가리키는 실제 객체에 따라
            // Magician 또는 Warrior의 재정의 함수가 실행됨
            current.user->doAttack();

            // 상하좌우 인접 칸 중 적이 있으면 한 마리를 처치함
            attackAdjacentEnemy(gameMap, current);
            displayMap(gameMap, players);

            // 공격 명령은 한 번의 턴을 사용함
            ++turn;
            continue;
        }

        // 먼저 다음 좌표를 계산하고, 범위 확인 후 실제 위치를 바꿈
        int nextX = current.x;
        int nextY = current.y;

        if (command == "상") {
            --nextY;
        } else if (command == "하") {
            ++nextY;
        } else if (command == "좌") {
            --nextX;
        } else if (command == "우") {
            ++nextX;
        } else {
            cout << "잘못된 입력입니다." << endl;
            continue;
        }

        // 맵 밖으로 나가려는 입력은 위치와 턴을 바꾸지 않음
        if (!checkXY(gameMap, nextX, nextY)) {
            cout << "맵을 벗어났습니다. 다시 입력하세요." << endl;
            continue;
        }

        // 좌표가 유효할 때만 실제 위치를 갱신함
        current.x = nextX;
        current.y = nextY;

        // 맵 안에서 이동하면 기본 HP 1을 잃음
        current.user->DecreaseHP(1);
        displayMap(gameMap, players);

        // 현재 도착한 칸의 아이템·적·포션 처리
        int& currentTile = gameMap[current.y][current.x];

        if (currentTile == 1) {
            current.user->IncreaseItemCnt();
            cout << "아이템을 획득했습니다." << endl;
            currentTile = 0;  // 다시 획득하지 못하도록 빈칸 처리
        } else if (currentTile == 2) {
            current.user->doAttack();
            current.user->DecreaseHP(2);
            cout << "적과 싸워 HP가 추가로 2 감소했습니다." << endl;
            currentTile = 0;  // 한 번 만난 적은 처치된 것으로 처리
        } else if (currentTile == 3) {
            current.user->IncreaseHP(2);
            cout << "포션을 마셔 HP가 2 회복됐습니다." << endl;
            currentTile = 0;  // 포션은 한 번만 사용할 수 있음
        }

        // HP가 0 이하인 캐릭터가 나오면 게임을 종료함
        if (current.user->GetHP() <= 0) {
            cout << current.name << "의 HP가 0 이하가 되어 실패했습니다." << endl;
            break;
        }

        // 목적지에 먼저 도착한 캐릭터가 승리함
        if (checkGoal(gameMap, current.x, current.y)) {
            cout << current.name << "가 목적지에 도착했습니다! 승리!" << endl;
            break;
        }

        ++turn;
    }

    return 0;
}

// 좌표가 실제 2차원 vector 맵 안에 있는지 확인함
bool checkXY(const vector<vector<int>>& gameMap, int x, int y) {
    if (y < 0 || y >= static_cast<int>(gameMap.size())) {
        return false;
    }

    if (x < 0 || x >= static_cast<int>(gameMap[y].size())) {
        return false;
    }

    return true;
}

// 두 플레이어의 위치를 기호로 표시하고 나머지는 칸 종류로 표시함
void displayMap(const vector<vector<int>>& gameMap, const Player players[]) {
    for (int row = 0; row < static_cast<int>(gameMap.size()); ++row) {
        for (int col = 0; col < static_cast<int>(gameMap[row].size()); ++col) {
            bool magicianHere =
                (players[0].x == col && players[0].y == row);
            bool warriorHere =
                (players[1].x == col && players[1].y == row);

            if (magicianHere && warriorHere) {
                cout << " M/W  |";
            } else if (magicianHere) {
                cout << "  M   |";
            } else if (warriorHere) {
                cout << "  W   |";
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

// 현재 좌표의 맵 값이 목적지(4)인지 확인함
bool checkGoal(const vector<vector<int>>& gameMap, int x, int y) {
    return gameMap[y][x] == 4;
}

// 상하좌우 인접 칸에서 적을 찾아 한 마리를 제거함
bool attackAdjacentEnemy(vector<vector<int>>& gameMap, const Player& player) {
    const int dx[4] = {0, 0, -1, 1};  
    const int dy[4] = {-1, 1, 0, 0};  

    for (int i = 0; i < 4; ++i) {
        int enemyX = player.x + dx[i];
        int enemyY = player.y + dy[i];

        if (checkXY(gameMap, enemyX, enemyY) && gameMap[enemyY][enemyX] == 2) {
            gameMap[enemyY][enemyX] = 0;
            cout << "인접한 적을 처치했습니다." << endl;
            return true;
        }
    }

    cout << "주변에 공격할 적이 없습니다." << endl;
    return false;
}
