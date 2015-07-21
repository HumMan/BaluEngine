#pragma once

#include "..\EngineInterfaces\IMaterial.h"
#include "..\EngineInterfaces\ISprite.h"


class TSimpleSpriteDef
{
protected:
	bool visible;
	EngineInterface::IBaluSprite* visual;
public: 
	EngineInterface::IBaluSprite* GetSprite();
};

class TSimpleSprite : public TSimpleSpriteDef, public EngineInterface::TSceneObject
{
public:
	//TODO abstract methods
};