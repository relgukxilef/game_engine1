#include "ge1/shader_module.h"

#include <stdexcept>

namespace ge1 {

    VkShaderModule create_shader_module(
        VkDevice device, span<const char> source
    ) {
        VkShaderModule shaderModule;
        VkShaderModuleCreateInfo createInfo{
            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .codeSize = source.size(),
            .pCode = reinterpret_cast<const uint32_t*>(source.begin()),
        };
        if (
            vkCreateShaderModule(
                device, &createInfo, nullptr, &shaderModule
            ) != VK_SUCCESS
        ) {
            throw std::runtime_error("failed to create shader module");
        }
        return shaderModule;
    }
}
