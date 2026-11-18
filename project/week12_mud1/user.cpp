#include "user.h"

// User 객체가 만들어질 때 체력을 20으로 초기화한다.
User::User() : hp{20} {}

// 전달받은 값만큼 체력을 증가시킨다.
void User::IncreaseHP(int inc_hp) {
    hp += inc_hp;
}

// 전달받은 값만큼 체력을 감소시킨다.
void User::DecreaseHP(int dec_hp) {
    hp -= dec_hp;
}

// 현재 체력을 읽어서 반환한다.
// const는 이 함수가 User 객체의 상태를 바꾸지 않는다는 뜻이다.
int User::GetHP() const {
    return hp;
}
