#include <iostream>
#include <utility>

struct empty
{
};

struct some_metafunction
{
	using type = int;
};

struct some_object_type
{
	int member;
};

template<typename...>
struct voider
{
	using type = void;
};
template<typename... Args>
using void_t = typename voider<Args...>::type;

template<typename T, typename = void>
struct has_type_typedef : std::false_type {};

template<typename T>
struct has_type_typedef<T, void_t<typename T::type>> : std::true_type{};


template<typename T, typename = void>
struct has_member_variable : std::false_type {};

template<typename T>
struct has_member_variable<T, void_t<
	typename std::enable_if<
	std::is_same<
	int,
	decltype(std::declval<T>().member)
	>::value
	>::type
	>> : std::true_type{};

int main()
{
	if (has_type_typedef<empty>()){
		std::cout << "has typedef" << std::endl;
	}
	else{
		std::cout << "no typedef for you, empty" << std::endl;
	}
	if (has_member_variable<some_object_type>()){
		std::cout << "has a member named member" << std::endl;
	}
	else{
		std::cout << "No member called member" << std::endl;
	}
}