#include "CAFigure.h"
#include "CAVertex.h"
#include "CATransform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

//
// FUNCIÓN: CAFigure::createBuffers(CAVulkanState* vulkan)
//
// PROPÓSITO: Crea el Vertex Buffer
//
void CAFigure::createBuffers(CAVulkanState* vulkan)
{
	size_t vertexSize = sizeof(CAVertex) * vertices.size();
	vulkan->createBuffer(&vertexBuffer, &vertexBufferMemory, vertexSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);

	void* data;
	vkMapMemory(vulkan->device, vertexBufferMemory, 0, vertexSize, 0, &data);
	memcpy(data, vertices.data(), vertexSize);
	vkUnmapMemory(vulkan->device, vertexBufferMemory);

	size_t indexSize = sizeof(indices[0])* indices.size();
	vulkan->createBuffer(&indexBuffer, &indexBufferMemory, indexSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT);

	void* indexData;
	vkMapMemory(vulkan->device, indexBufferMemory, 0, indexSize, 0, &indexData);
	memcpy(indexData, indices.data(), indexSize);
	vkUnmapMemory(vulkan->device, indexBufferMemory);

	size_t transformBufferSize = sizeof(CATransform);
	transformBuffers.resize(vulkan->imageCount);
	transformBuffersMemory.resize(vulkan->imageCount);

	size_t lightBufferSize = sizeof(CALight);
	lightBuffers.resize(vulkan->imageCount);
	lightBuffersMemory.resize(vulkan->imageCount);

	size_t materialBufferSize = sizeof(CAMaterial);
	materialBuffers.resize(vulkan->imageCount);
	materialBuffersMemory.resize(vulkan->imageCount);

	for (size_t i = 0; i < vulkan->imageCount; i++)
	{
		vulkan->createBuffer(&transformBuffers[i], &transformBuffersMemory[i], transformBufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
		vulkan->createBuffer(&lightBuffers[i], &lightBuffersMemory[i], lightBufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
		vulkan->createBuffer(&materialBuffers[i], &materialBuffersMemory[i], materialBufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
	}

	VkBuffer* buffers[] = { transformBuffers.data(), lightBuffers.data(), materialBuffers.data() };
	size_t sizes[] = { transformBufferSize, lightBufferSize, materialBufferSize };

	descriptorSets.resize(vulkan->imageCount);
	vulkan->createDescriptorSets(&descriptorPool, &descriptorSets, buffers, sizes, 3);
}

//
// FUNCIÓN: CAFigure::destroyBuffers(VkDevice device)
//
// PROPÓSITO: Libera los buffers de la figura
//
void CAFigure::destroyBuffers(CAVulkanState* vulkan)
{
	vkDestroyBuffer(vulkan->device, vertexBuffer, nullptr);
	vkFreeMemory(vulkan->device, vertexBufferMemory, nullptr);

	vkDestroyBuffer(vulkan->device, indexBuffer, nullptr);
	vkFreeMemory(vulkan->device, indexBufferMemory, nullptr);

	for (size_t i = 0; i < vulkan->imageCount; i++)
	{
		vkDestroyBuffer(vulkan->device, transformBuffers[i], nullptr);
		vkFreeMemory(vulkan->device, transformBuffersMemory[i], nullptr);

		vkDestroyBuffer(vulkan->device, lightBuffers[i], nullptr);
		vkFreeMemory(vulkan->device, lightBuffersMemory[i], nullptr);

		vkDestroyBuffer(vulkan->device, materialBuffers[i], nullptr);
		vkFreeMemory(vulkan->device, materialBuffersMemory[i], nullptr);
	}
}

//
// FUNCIÓN: CAFigure::addCommands(VkCommandBuffer commandBuffer, int index)
//
// PROPÓSITO: Añade los comandos de renderizado al command buffer
//
void CAFigure::addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index)
{
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexBuffer, &offset);
	vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT16);
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vulkan->pipelineLayout, 0, 1, &descriptorSets[index], 0, nullptr);
	vkCmdDrawIndexed(commandBuffer, (uint32_t) indices.size(), 1, 0, 0, 0);
}

//
// FUNCIÓN: CAFigure::updateUniformBuffer(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection)
//
// PROPÓSITO: Actualiza las variables uniformes sobre una imagen del swapchain
//
void CAFigure::updateDescriptorSets(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection)
{
	CATransform transform;
	transform.MVP = projection * view * location;
	transform.ModelViewMatrix = view * location;
	transform.ViewMatrix = view;

	void* tData;
	vkMapMemory(vulkan->device, transformBuffersMemory[imageIndex], 0, sizeof(CATransform), 0, &tData);
	memcpy(tData, &transform, sizeof(CATransform));
	vkUnmapMemory(vulkan->device, transformBuffersMemory[imageIndex]);

	void* lData;
	vkMapMemory(vulkan->device, lightBuffersMemory[imageIndex], 0, sizeof(CALight), 0, &lData);
	memcpy(lData, &light, sizeof(CALight));
	vkUnmapMemory(vulkan->device, lightBuffersMemory[imageIndex]);

	void* mData;
	vkMapMemory(vulkan->device, materialBuffersMemory[imageIndex], 0, sizeof(CAMaterial), 0, &mData);
	memcpy(mData, &material, sizeof(CAMaterial));
	vkUnmapMemory(vulkan->device, materialBuffersMemory[imageIndex]);
}

//
// FUNCIÓN: CAFigure::setLight(CALight l)
//
// PROPÓSITO: Asigna las propiedades de la luz que incide en la figura
//
void CAFigure::setLight(CALight l)
{
	this->light = l;
}

//
// FUNCIÓN: CAFigure::setMaterial(CAMaterial m)
//
// PROPÓSITO: Asigna las propiedades del material del que está formada la figura
//
void CAFigure::setMaterial(CAMaterial m)
{
	this->material = m;
}

//
// FUNCIÓN: CAFigure::resetLocation()
//
// PROPÓSITO: Resetea la matriz de localización (Model).
//
void CAFigure::resetLocation()
{
	location = glm::mat4(1.0f);
}

//
// FUNCIÓN: CAFigure::setLocation()
//
// PROPÓSITO: Resetea la matriz de localización (Model).
//
void CAFigure::setLocation(glm::mat4 m)
{
	location = glm::mat4(m);
}


//
// FUNCIÓN: CAFigure::translate(glm::vec3 t)
//
// PROPÓSITO: Añade un desplazamiento la matriz de localización (Model).
//
void CAFigure::translate(glm::vec3 t)
{
	location = glm::translate(location, t);
}

//
// FUNCIÓN: CAFigure::rotate(float angle, glm::vec3 axis)
//
// PROPÓSITO: Añade una rotación la matriz de localización (Model).
//
void CAFigure::rotate(float angle, glm::vec3 axis)
{
	location = glm::rotate(location, glm::radians(angle), axis);
}
