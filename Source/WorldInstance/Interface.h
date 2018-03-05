#pragma once

#include "../WorldDef/Interface.h"


namespace BaluEngine
{
	namespace WorldInstance
	{
		class IScene;
		class IWorld;
		class IComposer;
		class ISceneObjectInstance;
		class ITransformedSpriteInstance;
		class IPhysShapeInstance;
		class TPhysShapeUserData;
		class ISpritesArray;
		class IClassInstance;
		class ITransformedClassInstance;
		class ISkeletonAnimationInstance;
		class ISpritePolygonInstance;		

		class TResources;
	}
}

#include "ISceneInstance.h"
#include "IWorldInstance.h"
#include "IComposer.h"
#include "ISpritePolygonInstance.h"
#include "IMaterialInstance.h"
#include "IClassInstance.h"
#include "IPhysShapeInstance.h"
#include "ISkeletonAnimationInstance.h"
#include "ISkeletonInstance.h"
#include "ISpriteInstance.h"

#include "../Common/IResources.h"