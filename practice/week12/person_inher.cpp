#include <iostream>
#include <string>
using namespace std;

class Person
{
protected:
    string name;     // protected: 파생 클래스 Student에서 접근 가능
    string address;  // 파생 클래스에서 사용할 주소
};

class Student : public Person
{
public:
    void SetName(string name)
    {
        this->name = name;  // this->name은 Person에서 물려받은 멤버 변수
    }
    string GetName() const
    {
        return name;
    }
    void SetAddress(string add)
    {
        address = add;
    }
    string GetAddress() const
    {
        return address;
    }
};
int main()
{
    Student obj;

    obj.SetName("미수");
    obj.SetAddress("서울시 종로구 1번지");

    cout << "이름: " << obj.GetName() << endl;
    cout << "주소: " << obj.GetAddress() << endl;

    return 0;
}