#include <iostream>
#include <string>
using namespace std;

string toLowerStr(string str) {
    string newStr = str; //원본 문자열 복사하여 새로운 문자열 생성
    for (char & c : newStr) {
        c = tolower(c);//소문자 변환
    }
    return newStr;
}
string toUpperStr(string str) {
    string newStr = str;// 원본 문자열 복사
    for (char & c : newStr) {//문자열 순회
        c = toupper(c);
    }
    return newStr;
}
int calcHammingDist(string s1, string s2) {
    s1 = toLowerStr(s1);
    s2 = toLowerStr(s2);
    int count = 0;
    for (int i = 0; i < s1.length(); i++) { //첫번째 문자열의 길이만큼 반복
            if (s1[i] != s2[i]) //두 문자열에서 같은 위치의 문자가 서로 다르면
                count += 1; //count + 1
    }
    return count;
}

int main() {
    string s1, s2;
    while (1) {
        cout << "DNA1: ";
        cin >> s1;
        cout << "DNA2: ";
        cin >> s2;

        if (s1.length() != s2.length()) {
            cout << "오류: 길이가 다름" << endl;
            continue;
        }
        else {
            int count = calcHammingDist(s1, s2);
            cout << "해밍 거리는 " << count << endl;
            break;
        }
    }
    return 0;
}