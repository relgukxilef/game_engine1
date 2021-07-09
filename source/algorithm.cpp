#include "ge1/algorithm.h"

#include <algorithm>
#include <cassert>

namespace ge1 {

    void permutation_swap(
        span<unsigned short> values, span<unsigned short> index,
        unsigned short value_a, unsigned short value_b
    ) {
        std::swap(index[value_a], index[value_b]);
        std::swap(values[index[value_a]], values[index[value_b]]);
        assert(value_a == values[index[value_a]]);
        assert(value_b == values[index[value_b]]);
    }

    void permutation_push_back(
        span<unsigned short> values, span<unsigned short> index, unsigned size
    ) {
        values[size] = size;
        index[size] = size;
    }


}
