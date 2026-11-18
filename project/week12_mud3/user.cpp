#include "user.h"

// 새 유저는 HP 20, 아이템 수 0으로 시작한다.
User::User() : hp{20}, itemCnt{0} {}

void User::IncreaseHP(int inc_hp) {
    hp += inc_hp;
}

void User::DecreaseHP(int dec_hp) {
    hp -= dec_hp;
}

void User::IncreaseItemCnt() {
    ++itemCnt;
}

int User::GetHP() const {
    return hp;
}

int User::GetItemCnt() const {
    return itemCnt;
}

// 일반 User의 기본 공격 메시지
void User::doAttack() const {
    std::cout << "공격합니다" << std::endl;
}

// Magician은 공격 함수를 재정의해 마법 메시지를 출력한다.
void Magician::doAttack() const {
    std::cout << "마법 사용" << std::endl;
}

// Warrior는 공격 함수를 재정의해 베기 메시지를 출력한다.
void Warrior::doAttack() const {
    std::cout << "베기 사용" << std::endl;
}

// User의 HP와 아이템 수를 출력한다.
std::ostream& operator<<(std::ostream& out, const User& user) {
    out << "현재 HP는 " << user.GetHP()
        << "이고, 먹은 아이템은 총 "
        << user.GetItemCnt() << "개입니다.";
    return out;
}
