#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

// User는 캐릭터가 제공해야 할 기능만 약속하는 인터페이스임.
// 순수 가상 함수(= 0)가 있으므로 User 객체를 직접 만들 수 없음.
class User {
public:
    // User 포인터로 파생 객체를 삭제할 때 올바른 소멸자가 실행되게 함.
    virtual ~User() {}

    virtual void IncreaseHP(int inc_hp) = 0;
    virtual void DecreaseHP(int dec_hp) = 0;
    virtual void IncreaseItemCnt() = 0;

    virtual int GetHP() const = 0;
    virtual int GetItemCnt() const = 0;
    virtual std::string GetJobName() const = 0;

    // 직업마다 서로 다른 공격 동작을 구현하도록 약속함.
    virtual void doAttack() const = 0;
};

// User 인터페이스를 구현하는 마법사
class Magician : public User {
private:
    int hp;
    int itemCnt;

public:
    Magician();

    void IncreaseHP(int inc_hp) override;
    void DecreaseHP(int dec_hp) override;
    void IncreaseItemCnt() override;

    int GetHP() const override;
    int GetItemCnt() const override;
    std::string GetJobName() const override;
    void doAttack() const override;
};

// User 인터페이스를 구현하는 전사
class Warrior : public User {
private:
    int hp;
    int itemCnt;

public:
    Warrior();

    void IncreaseHP(int inc_hp) override;
    void DecreaseHP(int dec_hp) override;
    void IncreaseItemCnt() override;

    int GetHP() const override;
    int GetItemCnt() const override;
    std::string GetJobName() const override;
    void doAttack() const override;
};

// User 정보 출력용 비멤버 연산자 함수
std::ostream& operator<<(std::ostream& out, const User& user);

#endif
