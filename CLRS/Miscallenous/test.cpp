#include <iostream>
using namespace std;

constexpr uint8_t NUM = 5;

int main()
{
    int p[NUM];
    int a;
    cout << " p= " << hex << p << endl;
    auto endptr = &p[NUM-1];
    cout << " endptr= " << hex << endptr << endl;
    auto endptr2 = &p[NUM];
    cout << " endptr= " << hex << endptr2 << endl;
    auto a_addr = &a;
    cout << " a address = " << hex << a_addr << endl;
}