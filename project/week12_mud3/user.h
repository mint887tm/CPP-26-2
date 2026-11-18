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

    virtual void doAttack() const;
};

// User를 상속받는 마법사 클래스
class Magician : public User {
public:
    void doAttack() const override;
};

// User를 상속받는 전사 클래스
class Warrior : public User {
public:
    void doAttack() const override;
};

// cout << user 형태로 정보를 출력하기 위한 연산자 함수
std::ostream& operator<<(std::ostream& out, const User& user);

#endif
