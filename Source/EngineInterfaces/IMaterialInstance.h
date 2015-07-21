
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "IMaterial.h"
#endif

class TBaluSceneInstance;
class TBaluSpritePolygonInstance;

#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES

	class TSceneObjectInstance
	{
	public:
		virtual void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results){}
		virtual TOBB2 GetOBB() = 0;
		virtual void SetTag(void* tag){}
		virtual void* GetTag(){ return nullptr; }
		virtual void SetTransform(TBaluTransform transform){}
		virtual TBaluTransform GetTransform(){ return TBaluTransform(); }
		virtual TVec2 GetScale(){ return TVec2(); }
		virtual void SetScale(TVec2 scale){}
		virtual bool PointCollide(TVec2 scene_space_point) = 0;
		virtual void UpdateTransform(){};
		virtual void OnMouseUp(EngineInterface::TMouseEventArgs e, TVec2 scene_cursor_location){};
		virtual void OnMouseDown(EngineInterface::TMouseEventArgs e, TVec2 scene_cursor_location){};
		virtual void OnMouseMove(EngineInterface::TMouseEventArgs e, TVec2 scene_cursor_location){};
		virtual ~TSceneObjectInstance(){}
	};

	typedef TSceneObjectInstance*(*SceneObjectInstanceClone)(TSceneObject* source_def, TBaluSceneInstance* scene);
	class SceneObjectInstanceFactory
	{
	public:
		static bool Register(const char* name, SceneObjectInstanceClone clone);
		static TSceneObjectInstance* Create(const char* name, TSceneObject* param, TBaluSceneInstance* scene);
	};

	class IBaluMaterialInstance
	{
	public:
	};
#endif

}