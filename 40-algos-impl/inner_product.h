#pragma once

namespace training
{
    template<typename InputIt1, typename InputIt2, typename T,
        typename BinaryOperation1, typename BinaryOperation2>
    T inner_product(InputIt1 first1, InputIt1 last1, InputIt2 first2, T value,
        BinaryOperation1 op1, BinaryOperation2 op2)
    {
        auto i = first1;
        auto j = first2;

        T temp{value};

        for( ; i != last1; i++, j++)
        {
            temp = op1(temp, op2(*i, *j));
        }

        return temp;
    }
}

