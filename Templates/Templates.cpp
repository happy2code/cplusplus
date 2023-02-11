#include <iostream>
#include <string>

template<typename T> void Swap(T& first, T& second)
{
    T temp = first;
    first = second;
    second = temp;
}
template<> void Swap(int& first, int& second)
{
    std::cout << "I am specialized!!!\n";
    first = first + second;
    second = first - second;
    first = first - second;
}

template<typename KeyType, typename ValueType>
class Pair
{
private:
    KeyType _key;
    ValueType _value;
public:
    constexpr Pair(KeyType key, ValueType value) : _key(key), _value(value)
    {

    }
    KeyType getKey() const { return _key; }
    ValueType getValue() const { return _value; }
};

template<int N> struct Factorial
{
    static const unsigned long value = N * Factorial<N - 1>::value;
};

template<> struct  Factorial<0>
{
    static const unsigned long value = 1;
};

constexpr unsigned long FactorialExpr(int value)
{
    return (value <= 1) ? 1 : value * FactorialExpr(value - 1);
}

int main()
{
    int a = 1;
    int b = 2;
    std::cout << "Before Swap:\n";
    std::cout << "a = " << a << ", b = " << b << std::endl;
    Swap(a, b);
    std::cout << "After Swap:\n";
    std::cout << "a = " << a << ", b = " << b << std::endl;

    std::string x = "C++";
    std::string y = "Rust";
    std::cout << "Before Swap:\n";
    std::cout << "x = " << x << ", y = " << y << std::endl;
    Swap(x, y);
    std::cout << "After Swap:\n";
    std::cout << "x = " << x << ", y = " << y << std::endl;

    Pair<int, float> p1{ 1,1.0 }; // need to specify the types, automatic detection does not work for classes.

    std::cout << Factorial<5>::value;
    std::cout << FactorialExpr(5);
    return 0;
}

