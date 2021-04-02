#include "ge1/memory.h"

#include <stdexcept>

namespace ge1 {

    VkBuffer create_buffer(
        VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage,
        VkSharingMode sharing_mode
    ) {
        VkBuffer buffer;
        VkBufferCreateInfo create_info{
            .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            .size = size,
            .usage = usage,
            .sharingMode = sharing_mode,
        };

        if (
            vkCreateBuffer(device, &create_info, nullptr, &buffer) !=
            VK_SUCCESS
        ) {
            throw std::runtime_error("failed to create buffer");
        }

        return buffer;
    }

    VkDeviceMemory allocate_memory(
        VkDevice device, VkPhysicalDevice physical_device, VkBuffer buffer,
        VkMemoryPropertyFlags memory_property_flags
    ) {
        VkMemoryRequirements memory_requirements;
        vkGetBufferMemoryRequirements(device, buffer, &memory_requirements);

        VkPhysicalDeviceMemoryProperties memory_properties;
        vkGetPhysicalDeviceMemoryProperties(
            physical_device, &memory_properties
        );

        uint32_t memory_type_index = 0;
        for (auto i = 0u; i < memory_properties.memoryTypeCount; i++) {
            if (
                memory_requirements.memoryTypeBits & (1 << i) &&
                (
                    memory_properties.memoryTypes[i].propertyFlags &
                    memory_property_flags
                ) == memory_property_flags
            ) {
                memory_type_index = i;
                break;
            }
        }

        VkDeviceMemory device_memory;
        VkMemoryAllocateInfo allocate_info{
            .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .allocationSize = memory_requirements.size,
            .memoryTypeIndex = memory_type_index,
        };
        if (
            vkAllocateMemory(
                device, &allocate_info, nullptr, &device_memory) != VK_SUCCESS
        ) {
            throw std::runtime_error("failed to allocate vertex buffer memory");
        }

        return device_memory;
    }

}
