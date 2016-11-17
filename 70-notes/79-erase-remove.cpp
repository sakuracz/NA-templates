#include <algorithm>
#include <vector>
#include <iostream>

template<typename C>
void vector_erase(C& cont, const typename C::value_type& toDrop){
	cont.erase(std::remove(cont.begin(), cont.end(), toDrop), cont.end());
}

int main(){


	std::vector<int> data{ 1, 2, 3, 1, 3, 1, 2 };
	std::cout << "original vector:" << std::endl;
	for (auto v : data)
		std::cout << v << ", ";
	std::cout << std::endl << "vector_erase(data, 1):" << std::endl;

	vector_erase(data, 1);

	for (auto v : data)
		std::cout << v << ", ";
	std::cout << std::endl << "vector_erase(data, 2):" << std::endl;

	vector_erase(data, 2);

	for (auto v : data)
		std::cout << v << ", ";
	std::cout << std::endl;
}