#include "implementation.h"

#include <algorithm>
#include <numeric>
#include <functional>

/*
type * find_return_type(const std::vector<function> & overload_set, std::vector<type *> argument_types)
{
    for (std::vector<function>::const_iterator it = overload_set.begin(); it != overload_set.end(); ++it)
    {
        bool mismatch = false;

        std::vector<type *>::iterator arg_type_it = argument_types.begin();
        std::vector<variable>::const_iterator arg_var_it = it->arguments.begin();
        for (; arg_var_it != it->arguments.end() && arg_type_it != argument_types.end();
            ++arg_var_it, ++arg_type_it)
        {
            if (arg_var_it->type != *arg_type_it)
            {
                mismatch = true;
                break;
            }


        }

        if (mismatch)
        {
            continue;
        }

        if (arg_var_it == it->arguments.end() && arg_type_it == argument_types.end())
        {
            return it->return_type;
        }
    }

    return nullptr;
}	*/

type * find_return_type(const std::vector<function> & overload_set, std::vector<type *> argument_types)
{
	auto overload = std::find_if(overload_set.begin(), overload_set.end(), [&](auto && overload) {
        if (argument_types.size() != overload.arguments.size())
        {
            return false;
        }

        return std::inner_product(argument_types.begin(), argument_types.end(), overload.arguments.begin(), true,
            std::logical_and<>(),
            [](auto && type, auto && variable){ return type == variable.type; });
    });

    if (overload == overload_set.end())
    {
        return nullptr;
    }

    return overload->return_type;
}
