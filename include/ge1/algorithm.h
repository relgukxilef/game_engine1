#pragma once

#include "span.h"

namespace ge1 {

    void permutation_swap(
        span<unsigned short> values, span<unsigned short> index,
        unsigned short value_a, unsigned short value_b
    );

    void permutation_push_back(
        span<unsigned short> values, span<unsigned short> index, unsigned size
    );
}
