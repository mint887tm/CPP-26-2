#include "user.h"

// 두 직업 모두 HP 20, 아이템 수 0으로 시작함.
Magician::Magician() : hp{20}, itemCnt{0} {}
Warrior::Warrior() : hp{20}, itemCnt{0} {}

void Magician::IncreaseHP(int inc_hp) {
    hp += inc_hp;
}

void Magician::DecreaseHP(int dec_hp) {
    hp -= dec_hp;
}

void Magician::IncreaseItemCnt() {
    ++itemCnt;
}

int Magician::GetHP() const {
    return hp;
}

int Magician::GetItemCnt() const {
    return itemCnt;
}

std::string Magician::GetJobName() const {
    return "Magician";
}

// Magician의 공격 동작
void Magician::doAttack() const {
    std::cout << "마법 사용!" << std::endl;
}

void Warrior::IncreaseHP(int inc_hp) {
    hp += inc_hp;
}

void Warrior::DecreaseHP(int dec_hp) {
    hp -= dec_hp;
}

void Warrior::IncreaseItemCnt() {
    ++itemCnt;
}

int Warrior::GetHP() const {
    return hp;
}

int Warrior::GetItemCnt() const {
    return itemCnt;
}

std::string Warrior::GetJobName() const {
    return "Warrior";
}

// Warrior의 공격 동작
void Warrior::doAttack() const {
    std::cout << "베기 사용!" << std::endl;
}

// User 인터페이스의 getter를 통해 정보를 출력함.
std::ostream& operator<<(std::ostream& out, const User& user) {
    out << "현재 HP는 " << user.GetHP()
        << "이고, 먹은 아이템은 총 "
        << user.GetItemCnt() << "개입니다.";
    return out;
}
