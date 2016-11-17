#include <vector>
#include <iostream>

namespace training
{
	template<typename InputIt1, typename InputIt2, typename T,
		typename BinaryOperation1, typename BinaryOperation2>
		T inner_product(InputIt1 first1, InputIt1 last1, InputIt2 first2, T temp,
		BinaryOperation1 op1, BinaryOperation2 op2)
	{
		auto i = first1;
		auto j = first2;

		for (; i != last1; i++, j++)
		{
			temp = op1(temp, op2(*i, *j));
		}

		return temp;
	}
}

int main() {
	std::vector<int> data_lhs = { 1, 2, 3, 4 };
	std::vector<int> data_rhs = { 2, 2, 3, 3 };

	if (training::inner_product(data_lhs.begin(), data_lhs.end(), data_rhs.begin(),
		0,
		std::plus<>(),
		std::multiplies<>()
		) == 27) {		
		std::cout << "inner product calculated correctly" << std::endl;
	}
	else {
		std::cout << "inner_product can't into math" << std::endl;
	}
}