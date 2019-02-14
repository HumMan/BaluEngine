#pragma once

#include "../../Interface.h"

#include "../Common/Common.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			class TWorld : public IWorld
			{
			private:
				class TPrivate;
				std::unique_ptr<TPrivate> p;
			public:

				IEventsEditor * GetEventsEditor();

				ICommandList* GetCommandList();

				TWorld();
				~TWorld();

				IWorldObject* GetObjectByName(TWorldObjectType type, const char* name);
				std::vector<IWorldObject*> GetObjects(TWorldObjectType type);
				bool ObjectNameExists(TWorldObjectType type, const char* name);
				TWorldObject* CreateObject(TWorldObjectType type, const char* name);
				IWorldObject* CreateObject(TWorldObjectType type, const char* name, const std::string& serialized);
				void DestroyObject(TWorldObjectType type, const char* name);

				IMaterial* CreateMaterial(const char* name);
				ISprite* CreateSprite(const char* name);
				IClass* CreateClass(const char* name);
				IScene* CreateScene(const char* name);

				IMaterial* CreateMaterial(const char* name, const std::string& serialized);
				ISprite* CreateSprite(const char* name, const std::string& serialized);
				IClass* CreateClass(const char* name, const std::string& serialized);
				IScene* CreateScene(const char* name, const std::string& serialized);

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
