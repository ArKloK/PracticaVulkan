#include "Animation.h"

Animation::Animation() {
	//this->skl = skl;
}

void Animation::Animar(void *skl)
{
	CASkeleton* sk = (CASkeleton*)skl;
	//skl->getshoulder_l()->setPose(124, 0, 0);
	Sleep(10);
}
