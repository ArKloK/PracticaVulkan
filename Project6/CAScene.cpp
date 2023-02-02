#include "CAScene.h"
#include "CATransform.h"
#include "CACylinder.h"
#include "CASphere.h"
#include "CAGround.h"
#include "Animation.h"
#include "CABalljoint.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>

//
// FUNCIÓN: CAScene::CAScene(CAVulkanState* vulkan)
//
// PROPÓSITO: Construye el objeto que representa la escena
//
CAScene::CAScene(CAVulkanState* vulkan)
{
	CALight light = {};
	light.Ldir = glm::normalize(glm::vec3(1.0f, -0.8f, -0.7f));
	light.La = glm::vec3(0.2f, 0.2f, 0.2f);
	light.Ld = glm::vec3(0.8f, 0.8f, 0.8f);
	light.Ls = glm::vec3(1.0f, 1.0f, 1.0f);

	CAMaterial groundMat = {};
	groundMat.Ka = glm::vec3(0.0f, 0.3f, 0.0f);
	groundMat.Kd = glm::vec3(0.0f, 0.3f, 0.0f);
	groundMat.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
	groundMat.Shininess = 16.0f;

	ground = new CAGround(5.0f, 5.0f);
	ground->createBuffers(vulkan);
	ground->resetLocation();
	ground->setLight(light);
	ground->setMaterial(groundMat);

	CAMaterial blueMat = {};
	blueMat.Ka = glm::vec3(0.0f, 0.0f, 0.8f);
	blueMat.Kd = glm::vec3(0.0f, 0.0f, 0.8f);
	blueMat.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
	blueMat.Shininess = 16.0f;

	skeleton = new CASkeleton(vulkan);
	skeleton->resetLocation();
	skeleton->translate(glm::vec3(0.0f, 1.05f, 0.0f));

	angle = 0.0;
}

//
// FUNCIÓN: CAScene::~CAScene()
//
// PROPÓSITO: Destruye el objeto que representa la escena
//
CAScene::~CAScene()
{
	delete ground;
	delete skeleton;
}

//
// FUNCIÓN: CAScene::destroyBuffers(CAVulkanState* vulkan)
//
// PROPÓSITO: Destruyelos buffers de las figuras que forman la escena
//
void CAScene::destroyBuffers(CAVulkanState* vulkan)
{
	ground->destroyBuffers(vulkan);
	skeleton->destroyBuffers(vulkan);
}

//
// FUNCIÓN: CAScene::addCommands(VkCommandBuffer commandBuffer, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer
//
void CAScene::addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index)
{
	ground->addCommands(vulkan, commandBuffer, index);
	skeleton->addCommands(vulkan, commandBuffer, index);
}

//
// FUNCIÓN: CAScene::	void update(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection)
// 
// PROPÓSITO: Actualiza los datos para dibujar la escena
//
void CAScene::update(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection)
{
	//Sleep(40);

	ground->updateDescriptorSets(vulkan, imageIndex, view, projection);
	skeleton->updateDescriptorSets(vulkan, imageIndex, view, projection);
}
