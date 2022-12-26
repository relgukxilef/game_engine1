#pragma once

#include "introspection.h"
#include <glm/glm.hpp>

namespace ge1 {

    template<typename T, glm::qualifier Q>
    constexpr const auto accessor<glm::vec<2, T, Q>> = make_struct_accessor(
        member<&glm::vec<2, T, Q>::x>("x"),
        member<&glm::vec<2, T, Q>::y>("y")
    );

    template<typename T, glm::qualifier Q>
    constexpr const auto accessor<glm::vec<3, T, Q>> = make_struct_accessor(
        member<&glm::vec<3, T, Q>::x>("x"),
        member<&glm::vec<3, T, Q>::y>("y"),
        member<&glm::vec<3, T, Q>::z>("z")
    );

    template<typename T, glm::qualifier Q>
    constexpr const auto accessor<glm::vec<4, T, Q>> = make_struct_accessor(
        member<&glm::vec<4, T, Q>::x>("x"),
        member<&glm::vec<4, T, Q>::y>("y"),
        member<&glm::vec<3, T, Q>::z>("z"),
        member<&glm::vec<3, T, Q>::w>("w")
    );

}
