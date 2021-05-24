#pragma once

#include <vulkan/vulkan.h>

namespace ge1 {
    VkBuffer create_buffer(
        VkDevice device,
        VkDeviceSize size, VkBufferUsageFlags usage, VkSharingMode sharing_mode
    );

    VkDeviceMemory allocate_memory(
        VkDevice device, VkPhysicalDevice physical_device,
        VkMemoryRequirements memory_requirements,
        VkMemoryPropertyFlags memory_property_flags
    );

    VkDeviceMemory allocate_memory(
        VkDevice device, VkPhysicalDevice physical_device, VkBuffer buffer,
        VkMemoryPropertyFlags memory_property_flags
    );
}
