
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "ICallbacks.h"
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
}
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
enum class TWorldObjectType
{
	Material,
	Sprite,
	Class,
	Scene,
	None
};

enum class TWorldObjectSubType
{
	//SpritePolygon,
	//SpritePhysShape,
	ClassSpriteInstance,
	SceneClassInstance
};

class TWorldObjectTypeString
{
public:
	static inline const char* Get(TWorldObjectType index)
	{
		char* values[] =
		{
			"Material",
			"Sprite",
			"Class",
			"Scene",
			"None",
		};
		return values[(int)index];
	}
};
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class TBaluWorldChangeListener
	{
	public:
		virtual void OnObjectCreate(TWorldObjectType type, std::string name) = 0;
		virtual void OnObjectDestroy(TWorldObjectType type, std::string name){}
		virtual void OnObjectChange(TWorldObjectType type, std::string name){}
		virtual void OnSubObjectCreate(TWorldObjectType obj_type, std::string name, TWorldObjectSubType sub_obj_type, int sub_obj_index){}
		virtual void OnSubObjectDestroy(TWorldObjectType obj_type, std::string name, TWorldObjectSubType sub_obj_type, int sub_obj_index){}
		virtual void OnSubObjectChange(TWorldObjectType obj_type, std::string name, TWorldObjectSubType sub_obj_type, int sub_obj_index){}
	};

	class IBaluWorld
	{
	public:

		virtual void AddChangesListener(TBaluWorldChangeListener* listener) = 0;
		virtual void RemoveChangesListener(TBaluWorldChangeListener* listener) = 0;

		virtual TScriptActiveType& GetCallbacksActiveType() = 0;

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

		virtual IBaluWorldObject* GetObjectByName(TWorldObjectType type, const char* name)=0;
		virtual std::vector<IBaluWorldObject*> GetObjects(TWorldObjectType type)=0;
		virtual bool ObjectNameExists(TWorldObjectType type, const char* name)=0;
		virtual void CreateObject(TWorldObjectType type, const char* name)=0;
		virtual void DestroyObject(TWorldObjectType type, const char* name)=0;

		virtual std::vector<EngineInterface::IBaluMaterial*> GetMaterials() = 0;
		virtual std::vector<EngineInterface::IBaluSprite*> GetSprites() = 0;
		virtual std::vector<EngineInterface::IBaluClass*> GetClasses() = 0;
		virtual std::vector<EngineInterface::IBaluScene*> GetScenes() = 0;

		virtual IBaluScene* GetScene(const char* scene_name) = 0;
		virtual IBaluScene* GetScene(int index) = 0;

		virtual IBaluPhysShapeFactory* GetPhysShapeFactory() = 0;

		virtual void AddOnMouseDown(TScript) = 0;
		virtual void AddOnMouseUp(TScript) = 0;
		virtual void AddOnMouseMove(TScript) = 0;

		virtual std::vector<TScript>& GetOnMouseDown() = 0;
		virtual std::vector<TScript>& GetOnMouseUp() = 0;
		virtual std::vector<TScript>& GetOnMouseMove() = 0;

		virtual void AddOnWorldStart(TScript callback) = 0;
		virtual std::vector<TScript>& GetOnWorldStart() = 0;
		virtual void RemoveOnWorldStart(int index) = 0;

		virtual void AddOnViewportResize(TScript callback) = 0;
		virtual std::vector<TScript>& GetOnViewportResize() = 0;
		virtual void RemoveOnViewportResize(int index) = 0;

		virtual void RemoveOnMouseDown(int index) = 0;
		virtual void RemoveOnMouseUp(int index) = 0;
		virtual void RemoveOnMouseMove(int index) = 0;

		virtual void SaveToXML(std::string path) = 0;
		virtual void LoadFromXML(std::string path) = 0;

		

	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluWorld, "IBaluWorld");
	MUnpackRA1(WrapPointer<IBaluScene>, WrapInterface<IBaluWorld>, GetScene, WrapValue<int>);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	BALUENGINEDLL_API EngineInterface::IBaluWorld* CreateWorld();
	BALUENGINEDLL_API void DestroyWorld(EngineInterface::IBaluWorld* world);
#endif
}
