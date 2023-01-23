#include "Skeleton.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Skeleton::Skeleton(CAVulkanState* vulkan) {

	CALight light = {};
	light.Ldir = glm::normalize(glm::vec3(1.0f, -0.8f, -0.7f));
	light.La = glm::vec3(0.2f, 0.2f, 0.2f);
	light.Ld = glm::vec3(0.8f, 0.8f, 0.8f);
	light.Ls = glm::vec3(1.0f, 1.0f, 1.0f);

	pelvis = new CABalljoint(0.4f);
	pelvis->createBuffers(vulkan);
	pelvis->setOrientation(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	pelvis->setLight(light);

		spine = new CABalljoint(0.5f);
		spine->createBuffers(vulkan);
		pelvis->addChild(spine);
		spine->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		spine->setLight(light);

			neck = new CABalljoint(0.35f);
			neck->createBuffers(vulkan);
			spine->addChild(neck);
			neck->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			neck->setLight(light);

			clavicle_l = new CABalljoint(0.25f);
			clavicle_l->createBuffers(vulkan);
			spine->addChild(clavicle_l);
			clavicle_l->setLocation((clavicle_l->getLocation()+glm::vec3(-0.05f, 0.0f, -0.05f)));//translado location acorde al offset dado
			clavicle_l->setOrientation(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			clavicle_l->setLight(light);

				shoulder_l = new CABalljoint(0.35f);
				shoulder_l->createBuffers(vulkan);
				clavicle_l->addChild(shoulder_l);
				shoulder_l->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				shoulder_l->setPose(45, 0, 0);
				shoulder_l->setLight(light);

					elbow_l = new CABalljoint(0.3f);
					elbow_l->createBuffers(vulkan);
					shoulder_l->addChild(elbow_l);
					elbow_l->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					elbow_l->setLight(light);

						wrist_l = new CABalljoint(0.2f);
						wrist_l->createBuffers(vulkan);
						elbow_l->addChild(wrist_l);
						wrist_l->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
						wrist_l->setLight(light);

			clavicle_r = new CABalljoint(0.25f);
			clavicle_r->createBuffers(vulkan);
			spine->addChild(clavicle_r);
			clavicle_r->setLocation((clavicle_r->getLocation() + glm::vec3(0.05f, 0.0f, -0.05f)));//translado location acorde al offset dado
			clavicle_r->setOrientation(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			clavicle_r->setLight(light);

				shoulder_r = new CABalljoint(0.35f);
				shoulder_r->createBuffers(vulkan);
				clavicle_r->addChild(shoulder_r);
				shoulder_r->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
				shoulder_r->setPose(45, 0, 0);
				shoulder_r->setLight(light);

					elbow_r = new CABalljoint(0.3f);
					elbow_r->createBuffers(vulkan);
					shoulder_r->addChild(elbow_r);
					elbow_r->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					elbow_r->setLight(light);

						wrist_r = new CABalljoint(0.2f);
						wrist_r->createBuffers(vulkan);
						elbow_r->addChild(wrist_r);
						wrist_r->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
						wrist_r->setLight(light);

	hip_l = new CABalljoint(0.2f);
	hip_l->createBuffers(vulkan);
	hip_l->setLocation(glm::vec3(0.05f, -0.05f, 0.0f));
	hip_l->setOrientation(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	hip_l->setLight(light);

		leg_l = new CABalljoint(0.5f);
		leg_l->createBuffers(vulkan);
		hip_l->addChild(leg_l);
		leg_l->setOrientation(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		leg_l->setLight(light);

			knee_l = new CABalljoint(0.4f);
			knee_l->createBuffers(vulkan);
			leg_l->addChild(knee_l);
			knee_l->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			knee_l->setLight(light);

				ankle_l = new CABalljoint(0.25f);
				ankle_l->createBuffers(vulkan);
				knee_l->addChild(ankle_l);
				ankle_l->setOrientation(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
				ankle_l->setLight(light);

	hip_r = new CABalljoint(0.2f);
	hip_r->createBuffers(vulkan);
	hip_r->setLocation(glm::vec3(-0.05f, -0.05f, 0.0f));
	hip_r->setOrientation(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	hip_r->setLight(light);

		leg_r = new CABalljoint(0.5f);
		leg_r->createBuffers(vulkan);
		hip_r->addChild(leg_r);
		leg_r->setOrientation(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		leg_r->setLight(light);

			knee_r = new CABalljoint(0.4f);
			knee_r->createBuffers(vulkan);
			leg_r->addChild(knee_r);
			knee_r->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			knee_r->setLight(light);

				ankle_r = new CABalljoint(0.25f);
				ankle_r->createBuffers(vulkan);
				knee_r->addChild(ankle_r);
				ankle_r->setOrientation(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
				ankle_r->setLight(light);

	angle = 0;
}

Skeleton::~Skeleton()
{
	delete pelvis;
	delete spine;
	delete neck;
	delete hip_l;
	delete leg_l;
	delete knee_l;
	delete ankle_l;
	delete hip_r;
	delete leg_r;
	delete knee_r;
	delete ankle_r;
	delete clavicle_l;
	delete shoulder_l;
	delete elbow_l;
	delete wrist_l;
	delete clavicle_r;
	delete shoulder_r;
	delete elbow_r;
	delete wrist_r;

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
	leg_l->destroyBuffers(vulkan);
	knee_l->destroyBuffers(vulkan);
	ankle_l->destroyBuffers(vulkan);
	hip_r->destroyBuffers(vulkan);
	leg_r->destroyBuffers(vulkan);
	knee_r->destroyBuffers(vulkan);
	ankle_r->destroyBuffers(vulkan);
	clavicle_l->destroyBuffers(vulkan);
	shoulder_l->destroyBuffers(vulkan);
	elbow_l->destroyBuffers(vulkan);
	wrist_l->destroyBuffers(vulkan);
	clavicle_r->destroyBuffers(vulkan);
	shoulder_r->destroyBuffers(vulkan);
	elbow_r->destroyBuffers(vulkan);
	wrist_r->destroyBuffers(vulkan);
}

void Skeleton::addCommands(CAVulkanState* vulkan, VkCommandBuffer commandBuffer, int index)
{
	pelvis->addCommands(vulkan, commandBuffer, index);
	spine->addCommands(vulkan, commandBuffer, index);
	neck->addCommands(vulkan, commandBuffer, index);
	hip_l->addCommands(vulkan, commandBuffer, index);
	leg_l->addCommands(vulkan, commandBuffer, index);
	knee_l->addCommands(vulkan, commandBuffer, index);
	ankle_l->addCommands(vulkan, commandBuffer, index);
	hip_r->addCommands(vulkan, commandBuffer, index);
	leg_r->addCommands(vulkan, commandBuffer, index);
	knee_r->addCommands(vulkan, commandBuffer, index);
	ankle_r->addCommands(vulkan, commandBuffer, index);
	clavicle_l->addCommands(vulkan, commandBuffer, index);
	shoulder_l->addCommands(vulkan, commandBuffer, index);
	elbow_l->addCommands(vulkan, commandBuffer, index);
	wrist_l->addCommands(vulkan, commandBuffer, index);
	clavicle_r->addCommands(vulkan, commandBuffer, index);
	shoulder_r->addCommands(vulkan, commandBuffer, index);
	elbow_r->addCommands(vulkan, commandBuffer, index);
	wrist_r->addCommands(vulkan, commandBuffer, index);
}

void Skeleton::updateDescriptorSets(CAVulkanState* vulkan, uint32_t imageIndex, glm::mat4 view, glm::mat4 projection)
{
	pelvis->updateDescriptorSets(vulkan, imageIndex, view, projection);
	spine->updateDescriptorSets(vulkan, imageIndex, view, projection);
	neck->updateDescriptorSets(vulkan, imageIndex, view, projection);
	hip_l->updateDescriptorSets(vulkan, imageIndex, view, projection);
	leg_l->updateDescriptorSets(vulkan, imageIndex, view, projection);
	knee_l->updateDescriptorSets(vulkan, imageIndex, view, projection);
	ankle_l->updateDescriptorSets(vulkan, imageIndex, view, projection);
	hip_r->updateDescriptorSets(vulkan, imageIndex, view, projection);
	leg_r->updateDescriptorSets(vulkan, imageIndex, view, projection);
	knee_r->updateDescriptorSets(vulkan, imageIndex, view, projection);
	ankle_r->updateDescriptorSets(vulkan, imageIndex, view, projection);
	clavicle_l->updateDescriptorSets(vulkan, imageIndex, view, projection);
	shoulder_l->updateDescriptorSets(vulkan, imageIndex, view, projection);
	elbow_l->updateDescriptorSets(vulkan, imageIndex, view, projection);
	wrist_l->updateDescriptorSets(vulkan, imageIndex, view, projection);
	clavicle_r->updateDescriptorSets(vulkan, imageIndex, view, projection);
	shoulder_r->updateDescriptorSets(vulkan, imageIndex, view, projection);
	elbow_r->updateDescriptorSets(vulkan, imageIndex, view, projection);
	wrist_r->updateDescriptorSets(vulkan, imageIndex, view, projection);
}
