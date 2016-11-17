#include <vector>
#include <iostream>

namespace training
{
	template<typename InputIt, typename UnaryPredicate>
	InputIt find_if(InputIt begin, InputIt end, UnaryPredicate pred)
	{
		for (auto i = begin; i != end; i++){
			if (pred(*i))
				return i;
		}
		return end;
	}
}

int main() {
	std::vector<int> data{ 1, 2, 3, 4 };
	if (training::find_if(data.begin(), data.end(), [](auto && elem){ return elem == 4; }) == data.begin() + 3){
		std::cout << "found what i was looking for" << std::endl;
	}
	else {
		std::cout << "those aren't the droids you're looking for" << std::endl;
	}
}