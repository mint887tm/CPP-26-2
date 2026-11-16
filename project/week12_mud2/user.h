#ifndef USER_H
#define USER_H

class User {
private:
    int hp;  // 체력은 클래스 외부에서 직접 바꾸지 못하게 private으로 둔다.

public:
    User();                   // 체력 20으로 시작하는 생성자
    void IncreaseHP(int inc_hp);
    void DecreaseHP(int dec_hp);
    int GetHP() const;        // 현재 체력을 반환한다.
};

#endif
