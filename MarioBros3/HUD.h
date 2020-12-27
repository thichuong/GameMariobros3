#ifndef __HUD_H__
#define __HUD_H__


#include "UIObject.h"
#include "PMetter.h"


class HUD : public UIObject
{
private:
	D3DXVECTOR2 world, life, score, coin, timer;

	PMetter* metter; 

	CAnimations* animations;

public:

	HUD();

	~HUD();

	void Update(DWORD dt); 

	void Render(); 


};

#endif