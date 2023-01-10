#pragma once

#include "CAVulkanState.h"
#include "CAFigure.h"
#include "CABalljoint.h"

class CAScene {
public:
	CAScene(CAVulkanState* vulkan);
	~CAScene();
	void destroyBuffers(CAVulkanState* vulkan);
	void addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index);
	void update(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection);

private:
	CAFigure* ground;
	CAFigure* column;
	CAFigure* cross;
	CAFigure* pelvis;
	CABalljoint* armL;
	CABalljoint* foreArmL;
	CABalljoint* armR;
	CABalljoint* legL;
	CABalljoint* legR;
	float angle;
};

