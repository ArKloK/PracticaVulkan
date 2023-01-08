#pragma once

#include "CASphere.h"
#include "CACylinder.h"
#include <glm\glm.hpp>

//
// CLASE: Balljoint
//
// DESCRIPCI�N: Representa una articulaci�n con 3 grados de libertad
// 
class CABalljoint {
private:
	GLfloat length;
	glm::vec3 location;
	glm::vec3 dir;
	glm::vec3 up;
	glm::vec3 right;
	glm::mat4 matrizpadre;
	GLfloat angles[3];
	CASphere* joint;
	CACylinder* bone;
	void ComputeMatrix();
	void SetMatrix(glm::mat4 matrix);
	CABalljoint *hijo;
	//guardar matriz del padre
public:
	CABalljoint(float length);
	~CABalljoint();
	void createBuffers(CAVulkanState* vulkan);
	void destroyBuffers(CAVulkanState* vulkan);
	void addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index);
	void updateDescriptorSets(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection);

	void setLight(CALight l);
	void setLocation(glm::vec3 loc);
	void setOrientation(glm::vec3 nDir, glm::vec3 nUp);
	void setPose(float xrot, float yrot, float zrot);

	void addChild(CABalljoint *child);
};

