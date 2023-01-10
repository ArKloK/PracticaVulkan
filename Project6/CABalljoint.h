#pragma once



#include "CASphere.h"
#include "CACylinder.h"
#include <glm\glm.hpp>

//
// CLASE: Balljoint
//
// DESCRIPCIÓN: Representa una articulación con 3 grados de libertad
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
	int numhijos;
	CABalljoint **hijos;//tiene que ser una lista de hijos
	void ComputeMatrix();
	
public:
	CABalljoint(float length);
	~CABalljoint();
	void createBuffers(CAVulkanState* vulkan);
	void destroyBuffers(CAVulkanState* vulkan);
	void addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index);
	void updateDescriptorSets(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection);

	glm::mat4 getFatherLocationMatrix();
	void setLight(CALight l);
	void setLocation(glm::vec3 loc);
	void setOrientation(glm::vec3 nDir, glm::vec3 nUp);
	void setPose(float xrot, float yrot, float zrot);

	void SetMatrix(glm::mat4 matrix);
	//guardar matriz del padre
	void addChild(CABalljoint *child);
};


