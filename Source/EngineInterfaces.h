#pragma once

#include "exportMacro.h"

#include "EngineInterfaces\IAnimationFrames.h"
#include "EngineInterfaces\IMaterial.h"
#include "EngineInterfaces\ISpritePolygon.h"
#include "EngineInterfaces\IPhysShape.h"
#include "EngineInterfaces\ISprite.h"
#include "EngineInterfaces\IClass.h"
#include "EngineInterfaces\IScene.h"
#include "EngineInterfaces\IWorld.h"

BALUENGINEDLL_API EngineInterface::IBaluWorld* CreateWorld();
BALUENGINEDLL_API void DestroyWorld(EngineInterface::IBaluWorld* world);

#include "EngineInterfaces\IMaterialInstance.h"
#include "EngineInterfaces\ISpritePolygonInstance.h"
#include "EngineInterfaces\IPhysShapeInstance.h"
#include "EngineInterfaces\ISpriteInstance.h"
#include "EngineInterfaces\IClassInstance.h"
#include "EngineInterfaces\ISceneInstance.h"
#include "EngineInterfaces\IWorldInstance.h"

#include "EngineInterfaces\IResources.h"

BALUENGINEDLL_API EngineInterface::IBaluWorldInstance* CreateWorldInstance(EngineInterface::IBaluWorld* source, EngineInterface::IResources* resources);
BALUENGINEDLL_API void DestroyWorldInstance(EngineInterface::IBaluWorldInstance* world);

#include "EngineInterfaces\IDirector.h"

BALUENGINEDLL_API EngineInterface::IDirector* CreateDirector();
BALUENGINEDLL_API void DestroyDirector(EngineInterface::IDirector* director);

