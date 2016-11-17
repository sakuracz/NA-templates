#include <type_traits>
#include <iostream>

template<typename T, typename T1, typename T2, typename T3>
struct is_any_of : std::disjunction<std::is_same<T, T1>, std::is_same<T, T2>, std::is_same<T, T3>>
{
};

int main(){

	if (is_any_of<int, bool, int, float>){
		std::cout << "We got lift of" << std::endl;
	}
	else {
		std::cout << "Sort of nope" << std::endl;
	}
}