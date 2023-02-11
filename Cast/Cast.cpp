// Cast.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct Base
{
	int x{ 200 };
	virtual void Print() const { std::cout << " From base: " << x << std::endl; }
};

struct Derived : Base
{
	int y{ 400 };
	virtual void Print() const override { std::cout << " From derived1: x,y = " << x << ',' << y << std::endl; }
};

struct Derived2 : Base
{
	int y{ 600 };
	virtual void Print() const override { std::cout << " From derived2: x,y = " << x << ',' << y << std::endl; }
};

void Foo(Base* p)
{
	std::cout << "Inside Foo\n";
	Derived* d = static_cast<Derived*>(p);
	if (d != nullptr) {
		std::cout << "casting to Derived succceeded\n";
		p->Print();
	}
	else
	{
		std::cout << "casting to Derived failed\n";
	}
}

void Bar(Base* p)
{
	std::cout << "Inside Bar\n";
	Derived2* d = static_cast<Derived2*>(p);
	if (d != nullptr) {
		std::cout << "casting to Derived2 succceeded\n";
		p->Print();
	}
	else
	{
		std::cout << "casting to Derived2 failed\n";
	}
}

void Wow(uint64_t address)
{
	std::cout << "Inside Wow\n";
	Base* pB = reinterpret_cast<Base*>(address);
	pB->Print();
}



int main()
{
	// Static and dynamic cast
	__int64 l = 200;
	int a = l; // end up in a warning
	int b = static_cast<int>(l); //I know what, i am doing, so shut up.
	std::cout << a << std::endl;
	std::cout << b <<std::endl;

	Derived d;
	Base* b1 = &d; //implicit conversion and is valid C++ 

	Foo(b1);
	Bar(b1);

	// reinterpret_cast
	uint64_t junk = 0xFFFFFFFFFFFFFFFF;
	Wow(junk);

	Base b2;
	uint64_t address = reinterpret_cast<uint64_t>(&b2);
	Wow(address);


	//const_cast
	const int val = 10;
	int& copy = const_cast<int&>(val);
	std::cout << "Casted the const, copy = " << copy << std::endl;
	copy = 100; //undefined behaviour
}
