#pragma once

#include "..\EngineInterfaces\IMaterial.h"

class TOBBGuiDef
{
public:
	TOBB2 boundary;
};

class TOBBGui : public EngineInterface::TGui, public TOBBGuiDef, public EngineInterface::TSceneObject
{
public:
	
};
