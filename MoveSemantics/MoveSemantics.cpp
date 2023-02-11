// MoveSemantics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

struct Person
{
	char* _name;
	unsigned int _age;

	Person(const char* name, unsigned int age)
	{
		std::cout << "Constructor at work\n";
		const auto bufferSize = strnlen_s(name, 20) + 1;
		_name = new char[bufferSize];
		strncpy_s(_name, bufferSize, name, 20);
		_age = age;
	}

	Person(const Person& other)
	{
		std::cout << "Copy Constructor at work\n";
		const auto bufferSize = strnlen_s(other._name, 20) + 1;
		_name = new char[bufferSize];
		strncpy_s(_name, bufferSize, other._name, 20);
		_age = other._age;
	}

	Person& operator = (const Person& other)
	{
		std::cout << "Copy assignment at work\n";
		if (this != &other)
		{
			Person temp(other);
			std::swap(*this, temp);
		}
		return *this;
	}

	Person(Person&& other) noexcept
	{
		std::cout << "Move Constructor at work\n";
		_name = other._name;
		_age = other._age;

		other._name = nullptr;
		other._age = 0;
	}

	Person& operator = (Person&& other) noexcept
	{
		if (this != &other)
		{
			delete[] _name;
			_name = other._name;
			_age = other._age;

			other._name = nullptr;
			other._age = 0;
		}

		return *this;
	}
	~Person()
	{
		std::cout << "Destructor at work\n";
		delete[] _name;
	}
};



int main()
{
	std::vector<Person> family;
	family.push_back({ "Senthil", 43 });
}

