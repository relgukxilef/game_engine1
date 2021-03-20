#pragma once

#include <initializer_list>

#include <vulkan/vulkan.h>

#include "ge1/span.h"

namespace ge1 {
    VkShaderModule create_shader_module(
        VkDevice device, span<const char> source
    );
}
