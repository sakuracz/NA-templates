#include <catch.hpp>

#include "vector_erase.h"

TEST_CASE("vector erase", "[vector_erase]")
{
    std::vector<int> data{ 1, 2, 3, 1, 3, 1, 2 };

    vector_erase(data, 1);

/*    for(auto i = data.begin(); i != data.end(); i++)
        std::cout << *i << ", ";
    std::cout << std::endl;     */

    CHECK((data == std::vector<int>{ 2, 3, 3, 2 }));

    vector_erase(data, 3);


/*    for(auto i = data.begin(); i != data.end(); i++)
        std::cout << *i << ", ";
    std::cout << std::endl;     */


    REQUIRE((data == std::vector<int>{ 2, 2 }));

    vector_erase(data, 2);
    REQUIRE(data.empty());
}

template<typename T>
class custom_allocator : public std::allocator<T>
{
};

TEST_CASE("vector erase with custom allocator", "[vector_erase]")
{
    using vector_type = std::vector<int, custom_allocator<int>>;
//    using vector_type = std::vector<int>;

    vector_type data{ 1, 2, 3, 1, 3, 1, 2 };

    vector_erase(data, 1);
    REQUIRE((data == vector_type{ 2, 3, 3, 2 }));

    vector_erase(data, 3);
    REQUIRE((data == vector_type{ 2, 2 }));

    vector_erase(data, 2);
    REQUIRE(data.empty());
}

