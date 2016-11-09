#pragma once
#include <initializer_list>
#include <utility>

template<typename T>
class container_wrapper
{
public:
//    container_wrapper(std::initializer_list<T> l) : elem_count(l.count())
//    {}

    container_wrapper(T arg) : _value(std::move(arg)){}

    container_wrapper() = default;
    container_wrapper(const container_wrapper &) = default;
    container_wrapper(container_wrapper&&_) = default;

    container_wrapper& operator=(const container_wrapper &) = default;
    container_wrapper& operator=(container_wrapper &&) = default;


    size_t size() const { return _value.size(); }

private:
    T _value;

};

