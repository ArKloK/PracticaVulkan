#pragma once

#include "CAVulkanState.h"
#include "CAScene.h"
#include "CACamera.h"


class CAModel
{
private:
	CAVulkanState* vulkan;
	glm::mat4 projection;
	float aspect;

	CAScene* scene;
	CACamera* camera;
	CACamera* camera2;

public:
	CAModel(CAVulkanState* vulkan);
	~CAModel();

	void addCommands(VkCommandBuffer commandBuffer, int index);
	void update(uint32_t imageIndex);
	void key_pressed(int key);
	void mouse_button(int button, int action);
	void mouse_move(double xpos, double ypos);
	void aspect_ratio(double aspect);
};


