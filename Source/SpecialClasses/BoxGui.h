#pragma once

#include "..\EngineInterfaces\IMaterial.h"

class TBoxGuiDef
{
public:
	TOBB2 boundary;
};

class TBoxGui : public EngineInterface::TGui, public TBoxGuiDef
{
public:

};
