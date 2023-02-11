// ConstExpr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
template<typename T> constexpr T greater(const T& val1, const T& val2)
{
    return val1 >= val2 ? val1 : val2;
}

constexpr unsigned long long factorial(unsigned int n)
{
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

constexpr unsigned long long factorial_cxx14(int n)
{
    unsigned long long res = 1;
    while (n > 1)
        res *= n--;
    return res;
}


int main(int argc, char** argv)
{
    constexpr int a = 100; //valid
    constexpr int b = 200; //valid

    constexpr int k; //invalid

    constexpr int c = a + argc; //invalid, because argc is not a compile time constant
    constexpr int d = a + b; //


    std::cout << greater(a, b) << " is greater\n"; //may not execute at compile time, as the return value is not used at compile time.
    int x = greater(a, b); // may or may not generate at compile times, as c is not a compile time constant
    const int y = greater(a, b); // may or may not generate at compile times, as c is not a compile time constant. but you can force it with consteval
    constexpr int z = greater(a, b); //z is initialized with 200 at compile time.
}