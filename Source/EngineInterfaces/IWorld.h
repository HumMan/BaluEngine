
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "IMaterial.h"
#include "ISprite.h"
#include "IClass.h"
#include "IScene.h"

#endif

namespace EngineInterface
{
	class IDirector;
	class IBaluWorldInstance;
	class TRender;
	class IComposer;
}
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	enum class TMouseButton
	{
		Left,
		Right,
		Middle
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	struct TMouseEventArgs
	{
		TMouseButton button;
		TVec2i location;
		TMouseEventArgs(){}
		TMouseEventArgs(TMouseButton button, TVec2i location)
		{
			this->button = button;
			this->location = location;
		}
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	typedef void(*MouseUpDownCallback)(TCallbackData* callback, TMouseEventArgs e);
	typedef void(*MouseMoveCallback)(TCallbackData* callback, TMouseEventArgs e);

	//typedef void(*RenderWorldCallback)(TCallbackData* data, EngineInterface::IDirector* director, EngineInterface::IBaluWorldInstance* world, TRender* render);

	typedef void(*OnStartWorldCallback)(TCallbackData* data, EngineInterface::IBaluWorldInstance* world_instance, EngineInterface::IComposer* composer);

	typedef void(*ViewportResizeCallback)(TCallbackData* data, EngineInterface::IDirector* director, TVec2i old_size, TVec2i new_size);
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluWorld
	{
	public:
		virtual TCallbacksActiveType& GetCallbacksActiveType() = 0;

		virtual bool TryFind(const char* material_name, EngineInterface::IBaluMaterial*& result) = 0;
		virtual bool TryFind(const char* sprite_name, EngineInterface::IBaluSprite*& result) = 0;
		virtual bool TryFind(const char* scene_name, EngineInterface::IBaluScene*& result) = 0;
		virtual bool TryFind(const char* class_name, IBaluClass*& result) = 0;

		void Create(const char* name, IBaluMaterial*& item)
		{
			item = CreateMaterial(name);
		}
		void Create(const char* name, IBaluSprite*& item)
		{
			item = CreateSprite(name);
		}
		void Create(const char* name, IBaluClass*& item)
		{
			item = CreateClass(name);
		}
		void Create(const char* name, IBaluScene*& item)
		{
			item = CreateScene(name);
		}

		virtual IBaluMaterial* CreateMaterial(const char* mat_name) = 0;
		virtual IBaluSprite* CreateSprite(const char* sprite_name) = 0;
		virtual IBaluClass* CreateClass(const char* class_name) = 0;
		virtual IBaluScene* CreateScene(const char* scene_name) = 0;

		virtual void DestroySprite(const char* class_name) = 0;
		virtual void DestroyClass(const char* class_name) = 0;
		virtual void DestroyScene(const char* scene_name) = 0;

		//virtual void SetRenderWorldCallback(CallbackWithData<RenderWorldCallback> callback) = 0;

		virtual void AddOnWorldStart(CallbackWithData<OnStartWorldCallback> callback) = 0;

		virtual void SetViewportResizeCallback(CallbackWithData<ViewportResizeCallback> callback) = 0;

		virtual std::vector<std::pair<std::string, EngineInterface::IBaluMaterial*>> GetMaterials() = 0;
		virtual std::vector<std::pair<std::string, EngineInterface::IBaluSprite*>> GetSprites() = 0;
		virtual std::vector<std::pair<std::string, EngineInterface::IBaluClass*>> GetClasses() = 0;
		virtual std::vector<std::pair<std::string, EngineInterface::IBaluScene*>> GetScenes() = 0;

		virtual IBaluScene* GetScene(const char* scene_name) = 0;
		virtual IBaluScene* GetScene(int index) = 0;

		virtual IBaluPhysShapeFactory* GetPhysShapeFactory() = 0;

		//void OnKeyDown(TKey key, KeyDownCallback callback);
		//void OnKeyUp(TKey key, KeyDownCallback callback);

		virtual void AddOnMouseDown(CallbackWithData<MouseUpDownCallback>) = 0;
		virtual void AddOnMouseUp(CallbackWithData<MouseUpDownCallback>) = 0;
		virtual void AddOnMouseMove(CallbackWithData<MouseMoveCallback>) = 0;

		virtual void RemoveOnMouseDown(CallbackWithData<MouseUpDownCallback>) = 0;
		virtual void RemoveOnMouseUp(CallbackWithData<MouseUpDownCallback>) = 0;
		virtual void RemoveOnMouseMove(CallbackWithData<MouseMoveCallback>) = 0;

		virtual void SaveToXML(std::string path) = 0;
		virtual void LoadFromXML(std::string path) = 0;

	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluWorld, "IBaluWorld");
	MUnpackRA1(WrapPointer<IBaluScene>, WrapInterface<IBaluWorld>, GetScene, WrapValue<int>);
	BALU_ENGINE_SCRIPT_END_CLASS(WrapInterface<IBaluWorld>);
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	BALUENGINEDLL_API EngineInterface::IBaluWorld* CreateWorld();
	BALUENGINEDLL_API void DestroyWorld(EngineInterface::IBaluWorld* world);
#endif
}
