#include <iostream>
#include <string>
using namespace std;

const int mapX = 5;
const int mapY = 5;

// 사용자 정의 함수
bool checkXY(int user_x, int mapX, int user_y, int mapY);
void displayMap(int map[][mapX], int user_x, int user_y);
bool checkGoal(int map[][mapX], int user_x, int user_y);
void checkState(int map[][mapX], int user_x, int user_y);

// 메인 함수
int main() {
	// 0은 빈 공간, 1은 아이템, 2는 적, 3은 포션, 4는 목적지
	int map[mapY][mapX] = {
		{0, 1, 2, 0, 4},
		{1, 0, 0, 2, 0},
		{0, 0, 0, 0, 0},
		{0, 2, 3, 0, 0},
		{3, 0, 0, 0, 2}
	};

	// 유저의 위치
	int user_x = 0;
	int user_y = 0;

	// 유저는 체력 20으로 시작
	int user_hp = 20;

	while (1) {
		// 처음 명령문을 입력 받을 때 마다 HP 함께 출력
		cout << "현재 HP: " << user_hp << endl;
		cout << "명령어를 입력하세요 (상,하,좌,우,지도,종료): ";

		string user_input;
		cin >> user_input;

		// 유효한 이동을 했는지 확인
		bool moved = false;

		if (user_input == "상") {
			user_y -= 1;
			if (checkXY(user_x, mapX, user_y, mapY) == false) {
				cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
				user_y += 1;
			}
			else {
				cout << "위로 한 칸 올라갑니다." << endl;
				moved = true;
				displayMap(map, user_x, user_y);
			}
		}
		else if (user_input == "하") {
			user_y += 1;
			if (checkXY(user_x, mapX, user_y, mapY) == false) {
				cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
				user_y -= 1;
			}
			else {
				cout << "아래로 한 칸 내려갑니다." << endl;
				moved = true;
				displayMap(map, user_x, user_y);
			}
		}
		else if (user_input == "좌") {
			user_x -= 1;
			if (checkXY(user_x, mapX, user_y, mapY) == false) {
				cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
				user_x += 1;
			}
			else {
				cout << "왼쪽으로 이동합니다." << endl;
				moved = true;
				displayMap(map, user_x, user_y);
			}
		}
		else if (user_input == "우") {
			user_x += 1;
			if (checkXY(user_x, mapX, user_y, mapY) == false) {
				cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
				user_x -= 1;
			}
			else {
				cout << "오른쪽으로 이동합니다." << endl;
				moved = true;
				displayMap(map, user_x, user_y);
			}
		}
		else if (user_input == "지도") {
			displayMap(map, user_x, user_y);
		}
		else if (user_input == "종료") {
			cout << "종료합니다." << endl;
			break;
		}
		else {
			cout << "잘못된 입력입니다." << endl;
			continue;
		}

		// 지도 안에서 실제로 이동한 경우에만 이동 HP를 감소시키고 칸 상태를 확인
		if (moved) {
			user_hp -= 1;
			checkState(map, user_x, user_y);

			if (map[user_y][user_x] == 2) {
				user_hp -= 2;
				cout << "적을 만나 HP가 2 감소했습니다." << endl;
			}
			else if (map[user_y][user_x] == 3) {
				user_hp += 2;
				cout << "포션을 만나 HP가 2 증가했습니다." << endl;
			}
		}

		// HP가 0 이하가 되면 실패하고 종료
		if (user_hp <= 0) {
			cout << "실패" << endl;
			break;
		}

		// 목적지 도착 여부 확인
		if (checkGoal(map, user_x, user_y)) {
			cout << "목적지에 도착했습니다! 축하합니다!" << endl;
			cout << "게임을 종료합니다." << endl;
			break;
		}
	}

	return 0;
}

// 지도와 사용자 위치 출력하는 함수
void displayMap(int map[][mapX], int user_x, int user_y) {
	for (int i = 0; i < mapY; i++) {
		for (int j = 0; j < mapX; j++) {
			if (i == user_y && j == user_x) {
				cout << " USER |";
			}
			else {
				int posState = map[i][j];
				switch (posState) {
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

// 이동하려는 곳이 유효한 좌표인지 체크하는 함수
bool checkXY(int user_x, int mapX, int user_y, int mapY) {
	return user_x >= 0 && user_x < mapX && user_y >= 0 && user_y < mapY;
}

// 유저의 위치가 목적지인지 체크하는 함수
bool checkGoal(int map[][mapX], int user_x, int user_y) {
	return map[user_y][user_x] == 4;
}

// 현재 칸의 상태에 맞는 메시지를 출력하는 함수
void checkState(int map[][mapX], int user_x, int user_y) {
	switch (map[user_y][user_x]) {
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