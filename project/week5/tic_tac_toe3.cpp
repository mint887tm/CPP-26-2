#include <iostream>
using namespace std;

int main() {
    const int numCell = 3;
    char board[numCell][numCell]{};
    int x, y;

    for (x = 0; x < numCell; x++) {
        for (y = 0; y < numCell; y++) {
            board[x][y] = ' ';
        }
    }

    int k = 0;                 
    char currentUser = 'X';    

    while (true) {
        switch (k % 3) {
        case 0:
            cout << k % 3 + 1 << "번 유저(X)의 차례입니다 -> ";
            currentUser = 'X';
            break;
        case 1:
            cout << k % 3 + 1 << "번 유저(O)의 차례입니다 -> ";
            currentUser = 'O';
            break;
        case 2:
            // 3번째 플레이어 # 추가
            cout << k % 3 + 1 << "번 유저(#)의 차례입니다 -> ";
            currentUser = '#';
            break;
        }

        // 2. 좌표 입력 받기
        cout << "(x, y) 좌표를 입력하세요: ";
        cin >> x >> y;

        // 3. 입력받은 좌표의 유효성 체크 (기존과 동일)
        if (x < 0 || y < 0 || x >= numCell || y >= numCell) {
            cout << x << ", " << y << ": ";
            cout << "x 와 y 둘 중 하나가 칸을 벗어납니다." << endl;
            continue;
        }
        if (board[x][y] != ' ') {
            cout << x << ", " << y << ": 이미 돌이 차있습니다." << endl;
            continue;
        }

        // 4. 입력받은 좌표에 현재 유저의 돌 놓기
        board[x][y] = currentUser;

        // 5. 현재 보드 판 출력 (기존과 동일)
        for (int i = 0; i < numCell; i++) {
            cout << "---|---|---" << endl;
            for (int j = 0; j < numCell; j++) {
                cout << board[i][j];
                if (j == numCell - 1) {
                    break;
                }
                cout << " | ";
            }
            cout << endl;
        }
        cout << "---|---|---" << endl;

        // 6. 빙고(승리) 체크 - 가로, 세로, 대각선
        bool win = false;
        string winMsg = "";

        // 가로 체크
        for (int i = 0; i < numCell && !win; i++) {
            bool rowWin = true;
            for (int j = 0; j < numCell; j++) {
                if (board[i][j] != currentUser) {
                    rowWin = false;
                    break;
                }
            }
            if (rowWin) {
                win = true;
                winMsg = "가로에 모두 돌이 놓였습니다!";
            }
        }

        // 세로 체크
        for (int j = 0; j < numCell && !win; j++) {
            bool colWin = true;
            for (int i = 0; i < numCell; i++) {
                if (board[i][j] != currentUser) {
                    colWin = false;
                    break;
                }
            }
            if (colWin) {
                win = true;
                winMsg = "세로에 모두 돌이 놓였습니다!";
            }
        }

        // 대각선 체크
        if (!win) {
            bool diagWin = true;
            for (int i = 0; i < numCell; i++) {
                if (board[i][i] != currentUser) {
                    diagWin = false;
                    break;
                }
            }
            if (diagWin) {
                win = true;
                winMsg = "왼쪽 위에서 오른쪽 아래 대각선으로 모두 돌이 놓였습니다!";
            }
        }

        if (!win) {
            bool antiDiagWin = true;
            for (int i = 0; i < numCell; i++) {
                if (board[i][numCell - 1 - i] != currentUser) {
                    antiDiagWin = false;
                    break;
                }
            }
            if (antiDiagWin) {
                win = true;
                winMsg = "오른쪽 위에서 왼쪽 아래 대각선으로 모두 돌이 놓였습니다!";
            }
        }

        if (win) {
            // k % 2 + 1 이었던 부분을 k % 3 + 1 로 변경
            cout << winMsg << ": " << k % 3 + 1 << "번 유저(" << currentUser
                 << ")의 승리입니다! 종료합니다" << endl;
            break;
        }

        // 7. 모든 칸이 찼는지 체크 (기존과 동일, 인원수와 무관)
        bool full = true;
        for (int i = 0; i < numCell && full; i++) {
            for (int j = 0; j < numCell; j++) {
                if (board[i][j] == ' ') {
                    full = false;
                    break;
                }
            }
        }

        if (full) {
            cout << "모든 칸이 다 찼습니다. 종료합니다" << endl;
            break;
        }
        k++;
    }

    return 0;
}