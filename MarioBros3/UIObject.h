#ifndef __UIOBJECT_H__
#define __UIOBJECT_H__

#include <unordered_map>

#include "Sprites.h"
#include "Animations.h"
#include "Textures.h"

class UIObject
{
protected:
	D3DXVECTOR2 Position;

	DWORD dt; 

	unordered_map<std::string, LPANIMATION> animation_set; 

public:
	UIObject(); 
	~UIObject(); 

	void setPosition(D3DXVECTOR2 position);
	D3DXVECTOR2 getPosition();

	void AddAnimation(std::string name, LPANIMATION animation);

	virtual void Update(DWORD dt); 

	virtual void Render(); 
};

typedef UIObject* LPUIOBJECT;
#endif