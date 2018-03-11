#pragma once

#include "../../Interface.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			class TEventsEditor : public IEventsEditor
			{
			private:
				std::vector<TScript> global[(int)GlobalCallbackType::Count];

				std::vector<std::tuple<TKey, TScript>> global_key[(int)GlobalKeyCallbackType::Count];

				std::vector<std::tuple<TKey, TScript, std::string>> class_key[(int)ClassKeyCallbackType::Count];
				
				std::vector<std::tuple<std::string, TScript>> class_callbacks[(int)ClassCallbackType::Count];

				std::vector<TSpriteWithClassCollide> on_collide;

			public:

				int GlobalGetCount(GlobalCallbackType type);
				TScript& GlobalGet(GlobalCallbackType type, int index);
				void GlobalInsert(GlobalCallbackType type, int after_index, TScript script);
				void GlobalRemove(GlobalCallbackType type, int index);

				int GlobalKeyGetCount(GlobalKeyCallbackType type);
				std::tuple<TKey, TScript>& GlobalKeyGet(GlobalKeyCallbackType type, int index);
				void GlobalKeyInsert(GlobalKeyCallbackType type, TKey key, int after_index, TScript script);
				void GlobalKeyRemove(GlobalKeyCallbackType type, int index);

				int ClassGetCount(ClassCallbackType type);
				std::tuple<std::string, TScript>& ClassGet(ClassCallbackType type, int index);
				void ClassInsert(ClassCallbackType type, std::string class_name, int after_index, TScript script);
				void ClassRemove(ClassCallbackType type, int index);

				int ClassKeyGetCount(ClassKeyCallbackType type);
				std::tuple<TKey, TScript, std::string>& ClassKeyGet(ClassKeyCallbackType type, int index);
				void ClassKeyInsert(ClassKeyCallbackType type, TKey key, std::string class_name, int after_index, TScript script);
				void ClassKeyRemove(ClassKeyCallbackType type, int index);

				int OnCollideGetCount();
				TSpriteWithClassCollide& OnCollideGet(int index);
				void OnCollideInsert(int after_index, std::string source_class, int sprite, std::string  obstancle_class, TScript callback);
				void OnCollideRemove(int index);

				void SaveToXML(pugi::xml_node& parent_node, const int version);
				void LoadFromXML(const pugi::xml_node& document_node, const int version);
			};
		}
	}
}
