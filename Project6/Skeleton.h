#pragma once

#include "CAVulkanState.h"
#include "CAFigure.h";
#include "CABalljoint.h";
#include <glm/glm.hpp>
#include <iostream>  
#include <windows.h> 


class Skeleton
{
private:
	glm::mat4 location;
	CABalljoint* pelvis;
	CABalljoint* spine;
	CABalljoint* neck;
	CABalljoint* clavicle_l;
	CABalljoint* shoulder_l;
	CABalljoint* elbow_l;
	CABalljoint* wrist_l;
	CABalljoint* clavicle_r;
	CABalljoint* shoulder_r;
	CABalljoint* elbow_r;
	CABalljoint* wrist_r;
	CABalljoint* hip_l;
	CABalljoint* leg_l;
	CABalljoint* knee_l;
	CABalljoint* ankle_l;
	CABalljoint* hip_r;
	CABalljoint* leg_r;
	CABalljoint* knee_r;
	CABalljoint* ankle_r;
	float angle;
public:
	Skeleton(CAVulkanState* vulkan);
	~Skeleton();
	void resetLocation();
	void setLocation(glm::mat4 m);
	void translate(glm::vec3 t);
	void rotate(float angle, glm::vec3 axis);
	void destroyBuffers(CAVulkanState* vulkan);
	void addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index);
	void updateDescriptorSets(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection);
};

