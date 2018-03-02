#pragma once

#include "../../Interface.h"

#include "../Common/Common.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{

			class TWorldChangeListenerArray
			{
				std::vector<TWorldChangeListener*> listeners;
			public:
				void OnObjectCreate(TWorldObjectType type, const std::string& name)
				{
					for (auto v : listeners)
						v->OnObjectCreate(type, name);
				}
				void OnObjectDestroy(TWorldObjectType type, const std::string& name)
				{
					for (auto v : listeners)
						v->OnObjectDestroy(type, name);
				}
				void AddChangesListener(TWorldChangeListener* listener)
				{
					auto it = std::find(listeners.begin(), listeners.end(), listener);
					assert(it == listeners.end());
					listeners.push_back(listener);
				}
				void RemoveChangesListener(TWorldChangeListener* listener)
				{
					auto it = std::find(listeners.begin(), listeners.end(), listener);
					assert(it != listeners.end());
					listeners.erase(it);
				}
			};

			class TWorld : public IWorld
			{
			private:
				class TPrivate;
				TPrivate* p;
			public:

				IEventsEditor * GetEventsEditor();

				void AddChangesListener(TWorldChangeListener* listener);
				void RemoveChangesListener(TWorldChangeListener* listener);

				TWorld();
				~TWorld();

				bool TryFind(const char* name, IWorldObject*& result);

				IWorldObject* GetObjectByName(TWorldObjectType type, const char* name);
				std::vector<IWorldObject*> GetObjects(TWorldObjectType type);
				bool ObjectNameExists(TWorldObjectType type, const char* name);
				TWorldObject* CreateObject(TWorldObjectType type, const char* name);
				void DestroyObject(TWorldObjectType type, const char* name);

				IMaterial* CreateMaterial(const char* name);
				ISprite* CreateSprite(const char* name);
				IClass* CreateClass(const char* name);
				IScene* CreateScene(const char* name);

				IScene* GetScene(const std::string& name);
				IMaterial* GetMaterial(const std::string& name);
				ISprite* GetSprite(const std::string& name);
				IClass* GetClass(const std::string& name);

				void SaveToXML(const std::string& path)const;
				void LoadFromXML(const std::string& path);

				void SaveToXML(pugi::xml_node& parent_node, const int version)const;
				void LoadFromXML(const pugi::xml_node& document_node, const int version);
			};
		}
	}
}
