#pragma once
#include <initializer_list>

template<typename T>
class container_wrapper
{
public:
//    container_wrapper(std::initializer_list<T> l) : elem_count(l.count())
//    {}

    container_wrapper(T arg) : elem_count(0), _value(arg){}
    container_wrapper() = default;


    size_t size() const { return _value.size(); }

private:
    std::size_t elem_count;
    T _value;

};

