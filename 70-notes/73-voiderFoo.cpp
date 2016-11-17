#include <iostream>
#include <utility>

template<typename...>
struct voider
{
	using type = void;
};
template<typename... Args>
using void_t = typename voider<Args...>::type;

template<typename T, typename = void>
struct has_foo : std::false_type {};

template<typename T>
struct has_foo<T, void_t<decltype(std::declval<T>().foo())>>
	: std::true_type{};


struct X{
	void foo(){};
};

struct Y{
	void no_foo(){};
};

int main()
{
	X x;
	Y y;

	if (has_foo<X>()){
		std::cout << "X has foo" << std::endl;
	}
	else{
		std::cout << "No foo for you, X" << std::endl;
	}
	if (has_foo<Y>()){
		std::cout << "Y has foo" << std::endl;
	}
	else{
		std::cout << "No foo for you, Y" << std::endl;
	}
	x.foo();
	y.no_foo();
}