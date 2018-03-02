#pragma once

#include <string.h>
#include <vector>
#include <map>
#include <set>
#include <memory>>

#include <baluLib.h>

namespace pugi
{
	class xml_node;
}

//#include <Interfaces/ExportMacro.h>


namespace BaluEngine
{
	namespace WorldDef
	{
		class IProperties;
		class IFrame;
		class IWorld;
		class IPhysShape;
		class ISprite;
		class ISpritePolygon;
		class IAnimationFrames;
		class IAnimDesc;

		class IWorldObject;
		class IEventsEditor;

		class IMaterial;
		class IClass;
		class IScene;
		class ITransformedSprite;
		class ISkeletonAnimation;
		class IClassPhysBody;

		class ISkeleton;

	}
}

#include "ICommon.h"
#include "ICallbacks.h"
#include "IWorld.h"
#include "ISprite.h"
#include "ISpritePolygon.h"
#include "IAnimationFrames.h"
#include "IPhysShape.h"
#include "IEventsEditor.h"
#include "IMaterial.h"
#include "IProperties.h"
#include "ICommon.h"
#include "IClass.h"
#include "ISkeleton.h"
#include "ISkeletonAnimation.h"
#include "IScene.h"
#include "ILayers.h"