#pragma once

#include <vector> // std::vector

#include <vulkan/vulkan.h>

#include "Shader.hpp"
#include "VulkanSetup.hpp"

class Render {
    Window& window;
    VkRenderPass renderPass;
    Shader shader;

  public:
    VulkanSetup vulkanSetup;

    Render(Window& window)
        : window(window), vulkanSetup(window, &renderPass),
          shader(&vulkanSetup.device, &renderPass) {}

    void initVulkan();
    void createCommandPool();
    void createRenderPass();
    void createSyncObjects();
    void createCommandBuffers();

    void drawFrame();
    void cleanup();

  private:
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkFence> inFlightFences;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;

    uint32_t currentFrame = 0;

    void recordCommandBuffer(VkCommandBuffer commandBuffer,
                             uint32_t imageIndex);
};