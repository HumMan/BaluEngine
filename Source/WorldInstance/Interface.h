#pragma once

#include "../WorldDef/Interface.h"


namespace BaluEngine
{
	namespace WorldInstance
	{
		class IScene;
		class ISceneContactListener;
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
		class IDirector;
		class IEventsEditorInstance;
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
#include "IEventsEditorInstance.h"

#include "../Common/IResources.h"