#pragma once

#include "CAVulkanState.h"
#include "CAVertex.h"
#include "CATransform.h"
#include "CALight.h"
#include "CAMaterial.h"
#include <glm/glm.hpp>
#include <vector>

class CASkeleton {
protected:
	std::vector<CAVertex> vertices;
	std::vector<uint16_t> indices;
	glm::mat4 location;
	CALight light;
	CAMaterial material;

public:
	void createBuffers(CAVulkanState* vulkan);
	void destroyBuffers(CAVulkanState* vulkan);
	void addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index);
	void updateDescriptorSets(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection);
	void resetLocation();
	void setLocation(glm::mat4 m);
	void translate(glm::vec3 t);
	void rotate(float angle, glm::vec3 axis);
	void setLight(CALight l);
	void setMaterial(CAMaterial m);

private:
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
	std::vector<VkBuffer> transformBuffers;
	std::vector<VkDeviceMemory> transformBuffersMemory;
	std::vector<VkBuffer> lightBuffers;
	std::vector<VkDeviceMemory> lightBuffersMemory;
	std::vector<VkBuffer> materialBuffers;
	std::vector<VkDeviceMemory> materialBuffersMemory;
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;
};