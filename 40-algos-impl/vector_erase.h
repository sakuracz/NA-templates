#pragma once
#include <algorithm>

// define vector_erase here
/*std::vector<int> data{ 1, 2, 3, 1, 3, 1, 2 };

vector_erase(data, 1);
REQUIRE((data == std::vector<int>{ 2, 3, 3, 2 })); */

template<typename C, typename T>
void vector_erase(C& cont, T toDrop){
    int dropCount = 0;
 //   std::cout << cont.size() << "\t" << dropCount << std::endl;
    std::remove_if(cont.begin(), cont.begin()+cont.size(), [toDrop, &dropCount](const T& val){if(val == toDrop){++dropCount;}; return val == toDrop;});
//    std::cout << cont.size() << "\t" << dropCount << std::endl;
    for(int i = 0; i < dropCount; ++i)
        cont.pop_back();
}
