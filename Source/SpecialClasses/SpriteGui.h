#pragma once

#include "..\EngineInterfaces\IMaterial.h"
#include "..\EngineInterfaces\ISprite.h"


class TSpriteAdornmentDef
{
private:
	bool visible;
	EngineInterface::IBaluSprite* visual;
public: 
	EngineInterface::IBaluSprite* GetSprite();
};

class TSpriteAdornment : public TSpriteAdornmentDef, public EngineInterface::TSceneObject
{
public:

};