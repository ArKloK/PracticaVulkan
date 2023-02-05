#pragma once

#include "CAVulkanState.h"
#include "CAFigure.h"
#include "CABalljoint.h"
#include "Animation.h"
#include <glm/glm.hpp>
#include <iostream>  
#include <windows.h> 


class CASkeleton{
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
	Animation* anim;
public:
	CASkeleton(CAVulkanState* vulkan);
	~CASkeleton();

	CABalljoint* getclavicle_l() { return clavicle_l; };
	CABalljoint* getshoulder_l() { return shoulder_l; };
	CABalljoint* getelbow_l() { return elbow_l; };
	CABalljoint* getclavicle_r() { return clavicle_r; };
	CABalljoint* getshoulder_r() { return shoulder_r; };
	CABalljoint* getelbow_r() { return elbow_r; }; 
	CABalljoint* getleg_l() { return leg_l; };
	CABalljoint* getknee_l() { return knee_l; };
	CABalljoint* getleg_r() { return leg_r; };
	CABalljoint* getknee_r() { return knee_r; };

	void resetLocation();
	void setLocation(glm::mat4 m);
	void translate(glm::vec3 t);
	void rotate(float angle, glm::vec3 axis);
	void destroyBuffers(CAVulkanState* vulkan);
	void addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index);
	void updateDescriptorSets(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection);
};

