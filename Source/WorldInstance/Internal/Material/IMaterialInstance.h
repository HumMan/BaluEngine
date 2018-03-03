#pragma once

#include <Common/IResources.h>
#include <baluLib.h>
#include <Common/ICommon.h>

using namespace BaluLib;

namespace EngineInterface
{
	class TSceneInstance;
	class TSpritePolygonInstance;

#ifdef BALUENGINEDLL_EXPORTS
	class TSceneObjectInstance: public ISceneObjectInstance
	{
	private:
		TSceneInstance* scene;
	public:
		TSceneInstance* GetScene();
		TSceneObjectInstance(TSceneInstance* scene);
		virtual void QueryAABB(TAABB2 frustum, std::vector<TSpritePolygonInstance*>& results){}
		virtual TOBB2 GetOBB() = 0;
		virtual void SetTransform(TBaluTransform transform){}
		virtual TSceneObject* GetSource(){ return nullptr; };
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

	typedef TSceneObjectInstance*(*SceneObjectInstanceClone)(TSceneObject* source_def, TSceneInstance* scene);
	class SceneObjectInstanceFactory
	{
	public:
		static bool Register(const char* name, SceneObjectInstanceClone clone);
		static void UnregisterAll();
		static TSceneObjectInstance* Create(const char* name, TSceneObject* param, TSceneInstance* scene);
	};
#endif

	class IBaluMaterialInstance
	{
	public:
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TMaterial;
	class TMaterialInstance: public IChangeListener
	{
		TBaluTexture texture;
		TMaterial* source;
		TResources* resources;

		virtual void SourceChanged();
	public:
		TMaterialInstance(TMaterial* source, TResources* resources);
		~TMaterialInstance();
		TBaluTexture GetTexture();
	};
#endif

}