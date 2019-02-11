#pragma once

#include "../Interfaces/ExportMacro.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		class ICommand
		{
		public:
			virtual void Do() = 0;
			virtual void Undo() = 0;
			virtual ~ICommand() {}
		};
		class ICommandList
		{
		public:
			virtual void Undo() = 0;
			virtual void Redo() = 0;
			virtual void AddCommmand(ICommand*) = 0;
		};

		class IWorld
		{
		public:
			virtual void AddChangesListener(TWorldChangeListener* listener) = 0;
			virtual void RemoveChangesListener(TWorldChangeListener* listener) = 0;

			virtual bool TryFind(const char* name, IWorldObject*& result) = 0;

			virtual IWorldObject* GetObjectByName(TWorldObjectType type, const char* name) = 0;
			virtual std::vector<IWorldObject*> GetObjects(TWorldObjectType type) = 0;
			virtual bool ObjectNameExists(TWorldObjectType type, const char* name) = 0;
			virtual IWorldObject* CreateObject(TWorldObjectType type, const char* name) = 0;
			virtual void DestroyObject(TWorldObjectType type, const char* name) = 0;

			virtual IMaterial* CreateMaterial(const char* name) = 0;
			virtual ISprite* CreateSprite(const char* name) = 0;
			virtual IClass* CreateClass(const char* name) = 0;
			virtual IScene* CreateScene(const char* name) = 0;

			virtual IMaterial* CreateMaterial(const char* name, const std::string& serialized) = 0;
			virtual ISprite* CreateSprite(const char* name, const std::string& serialized) = 0;
			virtual IClass* CreateClass(const char* name, const std::string& serialized) = 0;
			virtual IScene* CreateScene(const char* name, const std::string& serialized) = 0;

			virtual IScene* GetScene(const std::string& name) = 0;
			virtual IMaterial* GetMaterial(const std::string& name) = 0;
			virtual ISprite* GetSprite(const std::string& name) = 0;
			virtual IClass* GetClass(const std::string& name) = 0;

			virtual void SaveToXML(const std::string& path)const = 0;
			virtual void LoadFromXML(const std::string& path) = 0;

			virtual IEventsEditor* GetEventsEditor() = 0;
			virtual ICommandList* GetCommandList() = 0;
		};

		BALUENGINEDLL_API IWorld* CreateWorld();
		BALUENGINEDLL_API void DestroyWorld(IWorld* world);
		BALUENGINEDLL_API void UnregisterAll();
	}
}
