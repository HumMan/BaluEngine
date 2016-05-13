#pragma once

#include "../Material/IMaterial.h"

class TBoxGuiDef
{
public:
	TOBB2 boundary;
};

class TBoxGui : public EngineInterface::TGui, public TBoxGuiDef, public EngineInterface::TSceneObject
{
public:

};
