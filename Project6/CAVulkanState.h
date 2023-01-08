#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vector>

const int MAX_FRAMES_IN_FLIGHT = 2;

class CAModel;

class CAVulkanState
{
public:
	CAVulkanState(GLFWwindow* window);
	~CAVulkanState();
	void windowResized();
	void setModel(CAModel* model);
	uint32_t waitForNextImage();
	void submitGraphicsCommands();
	void submitPresentCommands();
	void createBuffer(VkBuffer* buffer, VkDeviceMemory* deviceMemory, size_t size, VkBufferUsageFlagBits usage);
	void createDescriptorSets(VkDescriptorPool* descriptorPool, std::vector<VkDescriptorSet>* descriptorSets, VkBuffer** buffers, size_t* size, int bufferCount);

	int wWidth;
	int wHeight;
	uint32_t imageCount;
	VkDevice device;
	VkPipelineLayout pipelineLayout;

private:

	// Campos internos
	CAModel* model;
	GLFWwindow* window;
	VkSurfaceKHR surface;
	VkInstance instance;
	VkPhysicalDevice physicalDevice;
	VkPhysicalDeviceMemoryProperties memProperties;
	uint32_t graphicsQueueFamilyIndex;
	uint32_t presentQueueFamilyIndex;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	VkRenderPass renderPass;
	VkDescriptorSetLayout descriptorSetLayout;
	VkPipeline graphicsPipeline;
	std::vector<VkImage> depthImages;
	std::vector<VkDeviceMemory> depthImageMemories;
	std::vector<VkImageView> depthImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	std::vector<VkFence> imagesInFlight;
	size_t currentFrame = 0;
	uint32_t currentImage = 0;
	bool framebufferResized = false;

	// Métodos de inicialización de Vulkan
	void createInstance();
	void createSurface(GLFWwindow* window);
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createPipelineLayout();
	void createGraphicsPipeline();
	void createDepthBuffers();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffers();
	void createSyncObjects();
	void recreateSwapChain();
	void fillCommandBuffers();

	// Métodos de definición del pipeline de renderizado
	void createVertexShaderStageCreateInfo(VkShaderModule* vertShaderModule, VkPipelineShaderStageCreateInfo* vertShaderStageInfo);
	void createFragmentShaderStageCreateInfo(VkShaderModule* fragShaderModule, VkPipelineShaderStageCreateInfo* fragShaderStageInfo);
	void createPipelineVertexInputStateCreateInfo(VkPipelineVertexInputStateCreateInfo* vertexInputInfo, VkVertexInputBindingDescription* bindingDescriptions, VkVertexInputAttributeDescription* attributeDescriptions);
	void createPipelineInputAssemblyStateCreateInfo(VkPipelineInputAssemblyStateCreateInfo* inputAssembly);
	void createPipelineViewportStateCreateInfo(VkPipelineViewportStateCreateInfo* viewportState, VkViewport* viewport, VkRect2D* scissor);
	void createPipelineRasterizationStateCreateInfo(VkPipelineRasterizationStateCreateInfo* rasterizer);
	void createPipelineMultisampleStateCreateInfo(VkPipelineMultisampleStateCreateInfo* multisampling);
	void createPipelineDepthStencilStateCreateInfo(VkPipelineDepthStencilStateCreateInfo* depthStencil);
	void createPipelineColorBlendStateCreateInfo(VkPipelineColorBlendAttachmentState* colorBlendAttachment, VkPipelineColorBlendStateCreateInfo* colorBlending);

	// Métodos auxiliares
	bool isDeviceSuitable(VkPhysicalDevice pDevice);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	VkShaderModule createShaderModule(const std::vector<char>& code);
	std::vector<char> getFileFromResource(int resource);
	VkFormat findDepthFormat();
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};

