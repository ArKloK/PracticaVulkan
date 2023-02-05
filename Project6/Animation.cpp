#include "Animation.h"
#include "CASkeleton.h"
using namespace std;

Animation::Animation() {

	kf_clavicle_l[0] = 15;
	kf_clavicle_l[1] = -15;

	kf_clavicle_r[0] = 15;
	kf_clavicle_r[1] = -15;

	kf_shoulder_l[0] = 60;
	kf_shoulder_l[1] = 0;
	kf_shoulder_l[2] = -60;

	kf_shoulder_r[0] = 60;
	kf_shoulder_r[1] = 0;
	kf_shoulder_r[2] = -60;

	kf_leg_l[0] = 60;
	kf_leg_l[1] = 0;
	kf_leg_l[2] = -60;

	kf_leg_r[0] = 60;
	kf_leg_r[1] = 0;
	kf_leg_r[2] = -60;

	clavicle_l_angles = 0.0f;
	clavicle_r_angles = 0.0f;
	shoulder_r_angles = 0.0f;
	shoulder_l_angles = 0.0f;
	elbow_r_angles = 0.0f;
	elbow_l_angles = 0.0f;
	leg_r_angles = 0.0f;
	leg_l_angles = 0.0f;
	knee_r_angles = 0.0f;
	knee_l_angles = 10.0f;

	topeClavicleL = false;
	topeClavicleR = false;
	topeLegL = false;
	topeLegR = false;
	empiezaExtension = false;
}

void Animation::Animar(void* skl)
{
	Animar_clavicle_l(skl);
	Animar_clavicle_r(skl);
	Animar_shoulder_l(skl);
	Animar_shoulder_r(skl);
	Animar_leg_l(skl);
	Animar_leg_r(skl);
}

void Animation::Animar_clavicle_l(void* skl) {
	if (topeClavicleL==false)
	{//Rota hacia delante
		clavicle_l_angles -= 0.25;
		//cout << clavicle_l_angles;
		if (clavicle_l_angles==kf_clavicle_l[1])
		{
			topeClavicleL = true;
		}
	}
	else if (topeClavicleL==true) {//Rota hacia detras
		clavicle_l_angles += 0.25;
		if (clavicle_l_angles == kf_clavicle_l[0])
		{
			topeClavicleL = false;
		}
	}
	CASkeleton* sk = (CASkeleton*)skl;
	sk->getclavicle_l()->setPose(clavicle_l_angles, 0, 0);
}

//Animacion hacia delante
void Animation::Animar_shoulder_l(void *skl)
{
	CASkeleton* sk = (CASkeleton*)skl;
	if (!topeShL)//hombro se mueve hacia delante
	{
		shoulder_l_angles++;
		
		if (shoulder_l_angles == kf_shoulder_l[0])
		{
			topeShL = true;
		}
	}
	else {//hombro se mueve hacia atras
		shoulder_l_angles--;
		
		if (shoulder_l_angles == kf_shoulder_l[2])
		{
			topeShL = false;
		}
	}
	//Si esta en el rango de movimiento entre el neutro y el maximo de movimiento hacia atras, se mueve el codo
	if (shoulder_l_angles > kf_shoulder_l[1] && shoulder_l_angles < kf_shoulder_l[0])
	{
		Animar_elbow_l(sk, topeShL);
	}
	
	sk->getshoulder_l()->setPose(shoulder_l_angles, 0, 0);
}

void Animation::Animar_elbow_l(void* skl, bool tope)
{
	//Estirar codo
	if (tope && shoulder_l_angles > 0)
	{
		elbow_l_angles--;
	}
	//Contraer codo
	else if (!tope && shoulder_l_angles > 0) {
		elbow_l_angles++;
	}
	
	CASkeleton* sk = (CASkeleton*)skl;
	sk->getelbow_l()->setPose(0, elbow_l_angles, 0);
}

void Animation::Animar_clavicle_r(void* skl) {
	if (topeClavicleR == false)
	{//Rota hacia atras
		clavicle_r_angles += 0.25;
		//cout << clavicle_r_angles;
		if (clavicle_r_angles == kf_clavicle_r[0])
		{
			topeClavicleR = true;
		}
	}
	else if (topeClavicleR == true) {//Rota hacia delante
		clavicle_r_angles -= 0.25;
		if (clavicle_r_angles == kf_clavicle_r[1])
		{
			topeClavicleR = false;
		}
	}
	CASkeleton* sk = (CASkeleton*)skl;
	sk->getclavicle_r()->setPose(clavicle_r_angles, 0, 0);
}

//Animacion hacia atras
void Animation::Animar_shoulder_r(void* skl)
{
	CASkeleton* sk = (CASkeleton*)skl;
	if (!topeShR)//hombro se mueve hacia atras
	{
		shoulder_r_angles--;

		if (shoulder_r_angles == kf_shoulder_r[2])
		{
			topeShR = true;
		}

		
	}
	else {//hombro se mueve hacia delante
		shoulder_r_angles++;
		
		if (shoulder_r_angles == kf_shoulder_r[0])
		{
			topeShR = false;
		}
	}

	//Si esta en el rango de movimiento entre el neutro y el maximo de movimiento hacia atras, se mueve el codo
	if (shoulder_r_angles > kf_shoulder_r[1] && shoulder_r_angles < kf_shoulder_r[0])
	{
		Animar_elbow_r(sk, topeShR);
	}

	sk->getshoulder_r()->setPose(shoulder_r_angles, 0, 0);
}

void Animation::Animar_elbow_r(void* skl, bool tope)
{
	//Estirar codo
	if (tope && shoulder_r_angles > 0)
	{
		elbow_r_angles++;
	}
	//Contraer codo
	else if (!tope && shoulder_r_angles > 0) {
		elbow_r_angles--;
	}
	//cout << elbow_r_angles << "\n";
	CASkeleton* sk = (CASkeleton*)skl;
	sk->getelbow_r()->setPose(0, elbow_r_angles, 0);
}

//Animacion hacia atras
void Animation::Animar_leg_l(void* skl)
{
	CASkeleton* sk = (CASkeleton*)skl;
	if (!topeLegL)
	{//Pierna hacia atras
		leg_l_angles++;
		if (leg_l_angles == kf_leg_l[0])
		{
			topeLegL = true;
		}
		Animar_knee_l(sk, topeLegL);//Rodilla debe contraerse cuando sube la pierna
	}
	else if (topeLegL) {//Pierna hacia delante
		leg_l_angles--;
		if (leg_l_angles == kf_leg_l[2])
		{
			topeLegL = false;
		}
		Animar_knee_l(sk, topeLegL);//Rodilla debe estirarse cuando baja la pierna
	}

	sk->getleg_l()->setPose(leg_l_angles, 0, 0);
}

void Animation::Animar_knee_l(void* skl, bool tope)
{
	if (tope && leg_l_angles >= kf_leg_l[1] && leg_l_angles <= kf_leg_l[0])
	{
		knee_l_angles++;
	}
	else if (!tope && leg_l_angles <= kf_leg_l[1] && leg_l_angles >= kf_leg_l[2])
	{
		knee_l_angles--;
	}
	
	CASkeleton* sk = (CASkeleton*)skl;
	sk->getknee_l()->setPose(knee_l_angles, 0, 0);
}

//Animacion hacia delante
void Animation::Animar_leg_r(void* skl)
{
	CASkeleton* sk = (CASkeleton*)skl;
	if (!topeLegR)
	{//Pierna hacia delante
		//cout << "PIERNA HACIA DELANTE\n";
		leg_r_angles--;
		if (leg_r_angles == kf_leg_r[2])
		{
			topeLegR = true;
			empiezaExtension = true;
		}
		if (leg_r_angles==kf_leg_r[1])
		{
			empiezaContraccion = false;
		}
		//Animar_knee_r(sk, empiezaExtension, empiezaContraccion);//Rodilla debe contraerse cuando sube la pierna
	}
	else if (topeLegR) {//Pierna hacia atras
		//cout << "PIERNA HACIA ATRAS\n";
		leg_r_angles++;
		if (leg_r_angles==kf_leg_r[1])
		{
			empiezaExtension = false;
		}
		if (leg_r_angles == kf_leg_r[0])
		{
			topeLegR = false;
			empiezaContraccion = true;
		}
	}
	Animar_knee_r(sk, empiezaExtension, empiezaContraccion);
	sk->getleg_r()->setPose(leg_r_angles, 0, 0);
}

void Animation::Animar_knee_r(void* skl, bool extension, bool contraccion)
{
	if (extension==true && contraccion != 205)
	{
		//cout << "\nZONA EXTENSION contraccion:" << contraccion << " extension: " << extension;
		knee_r_angles--;
	}
	else if (contraccion==true)
	{
		//cout << "\nZONA CONTRACCION contraccion:" << contraccion << " extension: " << extension;
		knee_r_angles++;
	}
	CASkeleton* sk = (CASkeleton*)skl;
	sk->getknee_r()->setPose(knee_r_angles, 0, 0);
}