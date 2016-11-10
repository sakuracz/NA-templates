#pragma once
#include <algorithm>

// define vector_erase here
/*std::vector<int> data{ 1, 2, 3, 1, 3, 1, 2 };

vector_erase(data, 1);
REQUIRE((data == std::vector<int>{ 2, 3, 3, 2 })); */

template<typename C>
void vector_erase(C& cont, const typename C::value_type& toDrop){

        cont.erase(std::remove(cont.begin(), cont.end(), toDrop ), cont.end());

}
