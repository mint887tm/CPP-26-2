#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> scores;
    int score;

    while(true) {
        cout << "성적을 입력하시오(종료는 -1): ";
        cin >> score;

        if (score == -1) {
            break;
        }
        scores.push_back(score);
    }
    if (scores.empty()) {
        cout << "입력된 성적이 없습니다" << endl;
        return 0;
    }
    int sum = 0;
    for (int value : scores) {
        sum += value;
    }
    double average = static_cast<double>(sum) / scores.size();
    cout << "성적 평균=" << average << endl;

    return 0;
}