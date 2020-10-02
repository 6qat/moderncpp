//
// Created by guiga on 28/09/2020.
//
#include <iostream>
#include <vector>
#include <array>
#include <boost/container/vector.hpp>

using namespace std;

struct Foo {
	int a;
	int b;
	Foo(int a, int b)
			:a(a), b(b)
	{
		cout << "Constructor Foo(int a, int b) called" << endl;
	};

	Foo(const Foo& other)
	{
		this->a = other.a;
		this->b = other.b;
		cout << "Copy Constructor Foo(const Foo& other) called" << endl;
	}

	Foo(Foo&& other) noexcept
	{
		this->a = other.a;
		this->b = other.b;
		other.a = 0;
		other.b = 0;
		cout << "Move Constructor Foo(Foo&& other) called" << endl;
	}

	Foo& operator=(const Foo& other) = default;

	Foo& operator=(Foo&& other) noexcept
	{
		this->a = other.a;
		this->b = other.b;
		other.a = 0;
		other.b = 0;
		return *this;
	}

	virtual ~Foo() = default;
};

auto main() -> int
{
	cout << "Playing with constructors." << endl;

	auto f0 = Foo{ -1, 0 };
	auto f1 = Foo{ 1, 2 };
	auto f2 = Foo{ 3, 4 };
	auto f3 = f2;
	cout << f3.a << endl;
	auto f4 = std::move(f3);
	cout << f4.a << endl;

	cout << "Vector:" << endl;
	auto v = boost::container::vector<Foo>{ f0, f1, f2 };
	v.push_back(f4);
	v.push_back(f4);
//	auto v = vector<Foo>{ std::move(f0), std::move(f1), std::move(f2) };



	cout << "Array:" << endl;
	auto a = std::array<Foo, 3>{ f0, f1, f2 };

	cout << "END" << endl;

}