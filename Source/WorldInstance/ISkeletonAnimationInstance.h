#pragma once

#include <WorldDef/Objects/Class/IClass.h>
#include "../Sprite/ISpriteInstance.h"

#include "ISkeletonInstance.h"

namespace EngineInterface
{

	class ISkeletonAnimationInstance
	{
	public:
		virtual void Update(float step) = 0;
		virtual void PlayAnimation(const std::string& name, float alpha) = 0;
		virtual void StopAnimation(const std::string& name) = 0;
	};
}