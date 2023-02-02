#include "CAModel.h"

#include "CATransform.h"
#include "CACylinder.h"
#include "CASphere.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//
// FUNCIÓN: CAModel::CAModel(CAVulkanState* vulkan)
//
// PROPÓSITO: Initializa el modelo 3D
//
CAModel::CAModel(CAVulkanState* vulkan)
{
	this->vulkan = vulkan;

	this->camera2 = new CACamera();
	//Camara de lado
	this->camera2->setPosition(glm::vec3(12.0f, 1.0f, 0.0f));
	this->camera2->setDirection(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	this->camera2->setMoveStep(0.0f);

	//Camara frontal
	this->camera = new CACamera();
	this->camera->setPosition(glm::vec3(0.0f, 1.0f, 10.0f));
	this->camera->setMoveStep(0.0f);

	this->scene = new CAScene(vulkan);
}

//
// FUNCIÓN: CAModel::~CAModel()
//
// PROPÓSITO: Libera los recursos del modelo 3D
//
CAModel::~CAModel()
{
	scene->destroyBuffers(vulkan);
	delete scene;
	delete camera;
	delete camera2;
}

//
// FUNCIÓN: CAModel::addCommands(VkCommandBuffer commandBuffer, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer
//
void CAModel::addCommands(VkCommandBuffer commandBuffer, int index)
{
	scene->addCommands(vulkan, commandBuffer, index);
}

//
// FUNCIÓN: CAModel::aspect_ratio(double)
//
// PROPÓSITO: Modifica la relación anchura/altura del modelo
//
void CAModel::aspect_ratio(double aspect)
{
	double fov = glm::radians(15.0f);
	double sin_fov = sin(fov);
	double cos_fov = cos(fov);
	float wHeight = (float)(sin_fov * 0.2 / cos_fov);
	float wWidth = (float)(wHeight * aspect);

	//projection = glm::frustum(-wWidth, wWidth, -wHeight, wHeight, 0.2f, 400.0f);
	projection = glm::perspective((float)fov, (float)aspect, 0.2f, 400.0f);
	projection[1][1] *= -1.0f;
}

//
// FUNCIÓN: CAModel::update(uint32_t imageIndex)
//
// PROPÓSITO: Actualiza la información para generar la imagen 
//
void CAModel::update(uint32_t imageIndex)
{
	camera->moveFront();
	scene->update(vulkan, imageIndex, camera->getViewMatrix(), projection);
}

//
// FUNCIÓN: CAModel::key_pressed(int)
//
// PROPÓSITO: Respuesta a acciones de teclado
//
void CAModel::key_pressed(int key)
{
	switch (key)
	{
	case GLFW_KEY_UP:
		camera->turnDown();
		break;
	case GLFW_KEY_DOWN:
		camera->turnUp();
		break;
	case GLFW_KEY_LEFT:
		camera->turnCCW();
		break;
	case GLFW_KEY_RIGHT:
		camera->turnCW();
		break;
	case GLFW_KEY_S:
		camera->setMoveStep(0.0f);
		break;
	case GLFW_KEY_KP_ADD:
		camera->setMoveStep(camera->getMoveStep() + 0.1f);
		break;
	case GLFW_KEY_KP_SUBTRACT:
		camera->setMoveStep(camera->getMoveStep() - 0.1f);
		break;
	case GLFW_KEY_Q:
		camera->setMoveStep(0.1f);
		camera->moveUp();
		camera->setMoveStep(0.0f);
		break;
	case GLFW_KEY_A:
		camera->setMoveStep(0.1f);
		camera->moveDown();
		camera->setMoveStep(0.0f);
		break;
	case GLFW_KEY_O:
		camera->setMoveStep(0.1f);
		camera->moveLeft();
		camera->setMoveStep(0.0f);
		break;
	case GLFW_KEY_P:
		camera->setMoveStep(0.1f);
		camera->moveRight();
		camera->setMoveStep(0.0f);
		break;
	case GLFW_KEY_K:
		camera->turnLeft();
		break;
	case GLFW_KEY_L:
		camera->turnRight();
		break;
	//case GLFW_KEY_C:

	}
}

//
//  FUNCIÓN: CAModel:::mouse_button(int button, int action)
//
//  PROPÓSITO: Respuesta del modelo a un click del ratón.
//
void CAModel::mouse_button(int button, int action)
{
//	std::cout << "Model mouse button" << std::endl;
}

//
//  FUNCIÓN: CAModel::mouse_move(double xpos, double ypos)
//
//  PROPÓSITO: Respuesta del modelo a un movimiento del ratón.
//
void CAModel::mouse_move(double xpos, double ypos)
{
//	std::cout << "Model mouse move(" << xpos << "," << ypos << ")" << std::endl;
}
