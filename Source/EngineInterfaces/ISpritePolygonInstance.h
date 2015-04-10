
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "ISpritePolygon.h"
#endif

#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluSpritePolygonInstance
	{
	public:
		//virtual void SetSpritePolygon(std::string name) = 0;
		virtual IBaluSpritePolygon* GetSpritePolygon() = 0;

		virtual void SetActiveAnimation(std::string) = 0;
		//virtual TBaluTransform GetGlobalTransform() = 0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluSpritePolygonInstance, "ISpritePolygonInstance");
	MUnpackA1(TYPE, SetActiveAnimation, TString);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif
}