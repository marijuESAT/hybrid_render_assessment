#ifndef _RI_MATERIAL_RESOURCE_
#define _RI_MATERIAL_RESOURCE_ 1

#include <string>

#include "../basic_types.h"

#include "../Vulkan/vulkan_impl.h"
#include "../Vulkan/vulkan_state.h"
#include "../Vulkan/vulkan_buffer.h"
#include "../Vulkan/vulkan_texture.h"


namespace Reignite {

  struct MaterialResource {

    void init();
    void destroy();

    std::string name;
    struct PushBlock {
      float r;
      float g; 
      float b;
      float roughness;
      float metallic;
    } params;

    vk::VulkanState* vulkanState;
    vk::Buffer uboBasics;
    vk::Buffer uboLights;
    vk::Buffer uboShadows;
    VkDescriptorSet descriptorSet;

    vk::Texture2D colorMap;
    vk::Texture2D normalMap;
    vk::Texture2D roughness;
    vk::Texture2D metallic;
  };

} // end of Reignite namespace

#endif // _RI_MATERIAL_RESOURCE_

