#pragma once

#include "CAFigure.h"
#include <glm/glm.hpp>
#include <iostream>  
#include <windows.h> 

constexpr auto NUM_KF = 4;

class Animation
{
private:
	//No necesario para la animacion
	//int kf_pelvis[NUM_KF];
	//int kf_spine[NUM_KF];
	//int kf_neck[NUM_KF];
	int kf_clavicle_r[NUM_KF];
	int kf_shoulder_r[NUM_KF];
	int kf_elbow_r[NUM_KF];
	int kf_wrist_r[NUM_KF];
	int kf_clavicle_l[NUM_KF];
	int kf_shoulder_l[NUM_KF];
	int kf_elbow_l[NUM_KF];
	int kf_wrist_l[NUM_KF];
	//int kf_hip_l[NUM_KF];
	int kf_leg_l[NUM_KF];
	int kf_knee_l[NUM_KF];
	int kf_ankle_l[NUM_KF];
	//int kf_hip_r[NUM_KF];
	int kf_leg_r[NUM_KF];
	int kf_knee_r[NUM_KF];
	int kf_anckle_r[NUM_KF];

	GLfloat clavicle_r_angles;
	GLfloat shoulder_r_angles;
	GLfloat elbow_r_angles;
	GLfloat clavicle_l_angles;
	GLfloat shoulder_l_angles;
	GLfloat elbow_l_angles;
	GLfloat leg_r_angles;
	GLfloat knee_r_angles;
	GLfloat leg_l_angles;
	GLfloat knee_l_angles;

	bool topeClavicleL;
	bool topeClavicleR;
	bool topeShL;
	bool topeShR;
	bool topeLegL;
	bool topeLegR;
	bool topeKneeL;
	bool topeKneeR;

	bool empiezaContraccion;
	bool empiezaExtension;

public:
	Animation();
	void Animar_clavicle_l(void* skl);
	void Animar_shoulder_l(void* skl);
	void Animar_elbow_l(void* skl, bool tope);
	void Animar_clavicle_r(void* skl);
	void Animar_shoulder_r(void* skl);
	void Animar_elbow_r(void* skl, bool tope);
	void Animar_leg_l(void* skl);
	void Animar_knee_l(void* skl, bool tope);
	void Animar_leg_r(void* skl);
	void Animar_knee_r(void* skl, bool extension, bool contraccion);
};

