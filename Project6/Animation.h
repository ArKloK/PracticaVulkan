#pragma once

#include "CAFigure.h"
#include "CASkeleton.h"
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
	//int kf_clavicle_r[NUM_KF];
	int kf_shoulder_r[NUM_KF];
	int kf_elbow_r[NUM_KF];
	int kf_wrist_r[NUM_KF];
	//int kf_clavicle_l[NUM_KF];
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

	GLfloat shoulder_r_angles[3];
	GLfloat elbow_r_angles[3];
	GLfloat wrist_r_angles[3];
	GLfloat shoulder_l_angles[3];
	GLfloat elbow_l_angles[3];
	GLfloat wrist_l_angles[3];
	GLfloat leg_r_angles[3];
	GLfloat knee_r_angles[3];
	GLfloat ankle_r_angles[3];
	GLfloat leg_l_angles[3];
	GLfloat knee_l_angles[3];
	GLfloat ankle_l_angles[3];
	//Skeleton* skl;

public:
	Animation();
	void Animar(void * skl);
};

