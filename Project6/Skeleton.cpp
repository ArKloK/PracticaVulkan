#include "Skeleton.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Skeleton::Skeleton(CAVulkanState* vulkan) {

	CALight light = {};
	light.Ldir = glm::normalize(glm::vec3(1.0f, -0.8f, -0.7f));
	light.La = glm::vec3(0.2f, 0.2f, 0.2f);
	light.Ld = glm::vec3(0.8f, 0.8f, 0.8f);
	light.Ls = glm::vec3(1.0f, 1.0f, 1.0f);

	pelvis = new CABalljoint(0.3f);
	pelvis->createBuffers(vulkan);
	//pelvis->setLocation(glm::vec3(0.0f, 0.0f, 0.0f));
	pelvis->setOrientation(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	pelvis->setLight(light);

	spine = new CABalljoint(0.4f);
	spine->createBuffers(vulkan);
	pelvis->addChild(spine);
	spine->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	spine->setLight(light);

	neck = new CABalljoint(0.35f);
	neck->createBuffers(vulkan);
	spine->addChild(neck);
	neck->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	neck->setLight(light);

	hip_l = new CABalljoint(0.2f);
	hip_l->createBuffers(vulkan);
	hip_l->setLocation(glm::vec3(0.05f, -0.05f, 0.0f));
	hip_l->setOrientation(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	hip_l->setLight(light);

	hip_r = new CABalljoint(0.2f);
	hip_r->createBuffers(vulkan);
	hip_r->setLocation(glm::vec3(-0.05f, -0.05f, 0.0f));
	hip_r->setOrientation(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	hip_r->setLight(light);

	angle = 0;
}

Skeleton::~Skeleton()
{
	delete pelvis;
	delete spine;
	delete neck;
	delete hip_l;
	delete hip_r;
}

void Skeleton::resetLocation()
{
	location = glm::mat4(1.0f);
	pelvis->SetMatrix(location);
	hip_l->SetMatrix(location);
	hip_r->SetMatrix(location);
}

void Skeleton::setLocation(glm::mat4 m)
{
	location = glm::mat4(m);
	pelvis->SetMatrix(location);
	hip_l->SetMatrix(location);
	hip_r->SetMatrix(location);
}

void Skeleton::translate(glm::vec3 t)
{
	location = glm::translate(location, t);
	pelvis->SetMatrix(location);
	hip_l->SetMatrix(location);
	hip_r->SetMatrix(location);
}

void Skeleton::rotate(float angle, glm::vec3 axis)
{
	location = glm::rotate(location, glm::radians(angle), axis);
	pelvis->SetMatrix(location);
	hip_l->SetMatrix(location);
	hip_r->SetMatrix(location);
}

void Skeleton::destroyBuffers(CAVulkanState* vulkan)
{
	pelvis->destroyBuffers(vulkan);
	spine->destroyBuffers(vulkan);
	neck->destroyBuffers(vulkan);
	hip_l->destroyBuffers(vulkan);
	hip_r->destroyBuffers(vulkan);
}

void Skeleton::addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index)
{
	pelvis->addCommands(vulkan, commandBuffer, index);
	spine->addCommands(vulkan, commandBuffer, index);
	neck->addCommands(vulkan, commandBuffer, index);
	hip_l->addCommands(vulkan, commandBuffer, index);
	hip_r->addCommands(vulkan, commandBuffer, index);
}

void Skeleton::updateDescriptorSets(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection)
{

	pelvis->updateDescriptorSets(vulkan, imageIndex, view, projection);
	spine->updateDescriptorSets(vulkan, imageIndex, view, projection);
	neck->updateDescriptorSets(vulkan, imageIndex, view, projection);
	hip_l->updateDescriptorSets(vulkan, imageIndex, view, projection);
	hip_r->updateDescriptorSets(vulkan, imageIndex, view, projection);
}
