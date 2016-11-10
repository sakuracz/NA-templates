#pragma once

namespace training
{
    template<typename InputIt, typename UnaryPredicate>
    InputIt find_if(InputIt begin, InputIt end, UnaryPredicate pred)
    {
        for( auto i = begin; i != end; i++){
            if( pred(*i) )
                return i;
        }
        return end;
    }

}

