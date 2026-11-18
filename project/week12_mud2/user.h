#ifndef USER_H
#define USER_H

#include <iostream>  // std::ostream을 사용하기 위해 포함한다.

class User {
private:
    int hp;       // 현재 체력
    int itemCnt;  // 획득한 아이템 수

public:
    User();

    void IncreaseHP(int inc_hp);
    void DecreaseHP(int dec_hp);
    void IncreaseItemCnt();

    int GetHP() const;
    int GetItemCnt() const;
};

// cout << user 형태로 User 정보를 출력하는 비멤버 연산자 함수
std::ostream& operator<<(std::ostream& out, const User& user);

#endif
