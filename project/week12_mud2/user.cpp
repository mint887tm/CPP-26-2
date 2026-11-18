#include "user.h"

// 새 유저는 HP 20, 획득 아이템 수 0으로 시작한다.
User::User() : hp{20}, itemCnt{0} {}

// 전달된 양만큼 HP를 증가시킨다.
void User::IncreaseHP(int inc_hp) {
    hp += inc_hp;
}

// 전달된 양만큼 HP를 감소시킨다.
void User::DecreaseHP(int dec_hp) {
    hp -= dec_hp;
}

// 아이템을 획득할 때마다 수를 1 증가시킨다.
void User::IncreaseItemCnt() {
    ++itemCnt;
}

// 현재 HP를 반환한다. const는 객체의 값을 바꾸지 않는 함수라는 뜻이다.
int User::GetHP() const {
    return hp;
}

// 획득한 아이템 수를 반환한다.
int User::GetItemCnt() const {
    return itemCnt;
}

// << 연산자를 사용해 User 정보를 출력한다.
// 값을 읽기만 하므로 const 참조로 받고, 스트림을 반환해 endl과 이어 쓸 수 있다.
std::ostream& operator<<(std::ostream& out, const User& user) {
    out << "현재 HP는 " << user.GetHP()
        << "이고, 먹은 아이템은 총 " << user.GetItemCnt() << "개입니다.";
    return out;
}
