
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BALU_ENGINE_SCRIPT_CLASSES) && !defined(BALU_ENGINE_DLL_INTERFACES) && !defined(BALU_ENGINE_DISABLE_PRAGMA_ONCE)
#include <World\IResources.h>
#include <baluLib.h>
#include <World/ICommon.h>
#endif

using namespace BaluLib;

namespace EngineInterface
{
	class TBaluSceneInstance;
	class TBaluSpritePolygonInstance;

#ifndef BALU_ENGINE_SCRIPT_CLASSES
#ifndef BALU_ENGINE_DLL_INTERFACES
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
		virtual void OnMouseUp(TMouseEventArgs e, TVec2 scene_cursor_location){};
		virtual void OnMouseDown(TMouseEventArgs e, TVec2 scene_cursor_location){};
		virtual void OnMouseMove(TMouseEventArgs e, TVec2 scene_cursor_location){};
		virtual ~TSceneObjectInstance(){}
	};

	typedef TSceneObjectInstance*(*SceneObjectInstanceClone)(TSceneObject* source_def, TBaluSceneInstance* scene);
	class SceneObjectInstanceFactory
	{
	public:
		static bool Register(const char* name, SceneObjectInstanceClone clone);
		static TSceneObjectInstance* Create(const char* name, TSceneObject* param, TBaluSceneInstance* scene);
	};
#endif
	class IBaluMaterialInstance
	{
	public:
	};
#ifndef BALU_ENGINE_DLL_INTERFACES
	class TBaluMaterial;
	class TMaterialInstance
	{
		TBaluTexture texture;
		TBaluMaterial* source;
	public:
		TMaterialInstance(TBaluMaterial* source, TResources* resources);
		TBaluTexture GetTexture();
	};
#endif
#endif

}