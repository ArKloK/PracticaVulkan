#include "CAScene.h"
#include "CATransform.h"
#include "CACylinder.h"
#include "CASphere.h"
#include "CAGround.h"
#include "CABalljoint.h"
#include <iostream>

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

	column = new CACylinder(2, 10, 0.05f, 0.5f);
	column->createBuffers(vulkan);
	column->translate(glm::vec3(0.0f, 1.5f, 0.0f));
	column->rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	column->setLight(light);
	column->setMaterial(blueMat);

	cross = new CACylinder(2, 10, 0.05f, 0.25f);
	cross->createBuffers(vulkan);
	cross->translate(glm::vec3(0.0f, 1.9f, 0.0f));
	cross->rotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	cross->setLight(light);
	cross->setMaterial(blueMat);

	pelvis = new CACylinder(2, 10, 0.05f, 0.25f);
	pelvis->createBuffers(vulkan);
	pelvis->translate(glm::vec3(0.0f, 1, 0.0f));
	pelvis->rotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	pelvis->setLight(light);
	pelvis->setMaterial(blueMat);

	armL = new CABalljoint(0.4f);
	armL->createBuffers(vulkan);
	armL->setLocation(glm::vec3(0.25f, 1.9f, 0.0f));
	armL->setOrientation(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	armL->setLight(light);

	armR = new CABalljoint(0.4f);
	armR->createBuffers(vulkan);
	armR->setLocation(glm::vec3(-0.25f, 1.9f, 0.0f));
	armR->setOrientation(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	armR->setLight(light);

	legL = new CABalljoint(0.8f);
	legL->createBuffers(vulkan);
	legL->setLocation(glm::vec3(0.25f, 1, 0.0f));
	legL->setOrientation(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	legL->setLight(light);

	legR = new CABalljoint(0.8f);
	legR->createBuffers(vulkan);
	legR->setLocation(glm::vec3(-0.25f, 1, 0.0f));
	legR->setOrientation(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	legR->setLight(light);

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
	delete column;
	delete cross;
	delete armL;
	delete armR;
	delete pelvis;
	delete legL;
	delete legR;
}

//
// FUNCIÓN: CAScene::destroyBuffers(CAVulkanState* vulkan)
//
// PROPÓSITO: Destruyelos buffers de las figuras que forman la escena
//
void CAScene::destroyBuffers(CAVulkanState* vulkan)
{
	ground->destroyBuffers(vulkan);
	column->destroyBuffers(vulkan);
	cross->destroyBuffers(vulkan);
	armL->destroyBuffers(vulkan);
	armR->destroyBuffers(vulkan);
	pelvis->destroyBuffers(vulkan);
	legL->destroyBuffers(vulkan);
	legR->destroyBuffers(vulkan);
}

//
// FUNCIÓN: CAScene::addCommands(VkCommandBuffer commandBuffer, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer
//
void CAScene::addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index)
{
	ground->addCommands(vulkan, commandBuffer, index);
	column->addCommands(vulkan, commandBuffer, index);
	cross->addCommands(vulkan, commandBuffer, index);
	armL->addCommands(vulkan, commandBuffer, index);
	armR->addCommands(vulkan, commandBuffer, index);
	pelvis->addCommands(vulkan, commandBuffer, index);
	legL->addCommands(vulkan, commandBuffer, index);
	legR->addCommands(vulkan, commandBuffer, index);
}

//
// FUNCIÓN: CAScene::	void update(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection)
// 
// PROPÓSITO: Actualiza los datos para dibujar la escena
//
void CAScene::update(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection)
{
	angle += 1.0f;
	if (angle >= 90.0f) angle = -90.0f;
	armL->setPose(0.0f, angle, 0.0f);
	armR->setPose(0.0f, -angle, 0.0f);
	legL->setPose(0.0f, angle, 0.0f);
	legR->setPose(0.0f, -angle, 0.0f);

	ground->updateDescriptorSets(vulkan, imageIndex, view, projection);
	column->updateDescriptorSets(vulkan, imageIndex, view, projection);
	cross->updateDescriptorSets(vulkan, imageIndex, view, projection);
	armL->updateDescriptorSets(vulkan, imageIndex, view, projection);
	armR->updateDescriptorSets(vulkan, imageIndex, view, projection);
	pelvis->updateDescriptorSets(vulkan, imageIndex, view, projection);
	legL->updateDescriptorSets(vulkan, imageIndex, view, projection);
	legR->updateDescriptorSets(vulkan, imageIndex, view, projection);
}
