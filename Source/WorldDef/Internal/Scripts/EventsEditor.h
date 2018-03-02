#pragma once

#include "../../Interface.h"

#include "Callbacks.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			typedef std::string TScript;

			struct TSpriteWithClassCollide
			{
				std::string source_class;
				size_t source_sprite_id;
				std::string with_class;
				TScript script;
				TSpriteWithClassCollide()
				{
					source_sprite_id = -1;
				}
				TSpriteWithClassCollide(std::string source_class, size_t source_sprite_id, std::string with_class, TScript script)
				{
					this->source_class = source_class;
					this->source_sprite_id = source_sprite_id;
					this->with_class = with_class;
					this->script = script;
				}
				void SaveToXML(pugi::xml_node& parent_node, const int version);
				void LoadFromXML(const pugi::xml_node& instance_node, const int version);
			};

			enum class GlobalCallbackType
			{
				MouseUp,
				MouseDown,
				MouseMove,
				WorldStart,
				ViewportResize,
				BeforePhysics,
				KeyDown,
				KeyUp,

				Count
			};

			enum class GlobalKeyCallbackType
			{
				KeyDown,
				KeyUp,

				Count
			};

			enum class ClassCallbackType
			{
				BeforePhysics,

				Count
			};

			enum class ClassKeyCallbackType
			{
				KeyDown,
				KeyUp,

				Count
			};

			class TEventsEditor //: public IEventsEditor
			{
			private:
				std::vector<TScript> global[(int)GlobalCallbackType::Count];

				std::vector<std::tuple<TKey, TScript>> global_key[(int)GlobalKeyCallbackType::Count];

				std::vector<std::tuple<TKey, TScript, std::string>> class_key[(int)ClassKeyCallbackType::Count];
				
				std::vector<std::tuple<TScript, std::string>> class_callbacks[(int)ClassCallbackType::Count];

				std::vector<TSpriteWithClassCollide> on_collide;

			public:

				size_t GlobalGetCount(GlobalCallbackType type);
				TScript& GlobalGet(GlobalCallbackType type, size_t index);
				void GlobalInsert(GlobalCallbackType type, size_t after_index, TScript script);
				void GlobalRemove(GlobalCallbackType type, size_t index);

				size_t GlobalKeyGetCount(GlobalCallbackType type);
				std::tuple<TKey, TScript>& GlobalKeyGet(GlobalCallbackType type, size_t index);
				void GlobalKeyInsert(GlobalCallbackType type, TKey key, size_t after_index, TScript script);
				void GlobalKeyRemove(GlobalCallbackType type, size_t index);

				size_t ClassGetCount(GlobalCallbackType type);
				std::tuple<TScript, std::string>& ClassGet(GlobalCallbackType type, size_t index);
				void ClassInsert(GlobalCallbackType type, std::string class_name, size_t after_index, TScript script);
				void ClassRemove(GlobalCallbackType type, size_t index);

				size_t ClassKeyGetCount(GlobalCallbackType type);
				std::tuple<TKey, TScript, std::string>& ClassKeyGet(GlobalCallbackType type, size_t index);
				void ClassKeyInsert(GlobalCallbackType type, TKey key, std::string class_name, size_t after_index, TScript script);
				void ClassKeyRemove(GlobalCallbackType type, size_t index);

				size_t OnCollideGetCount();
				TSpriteWithClassCollide& OnCollideGet(size_t index);
				void OnCollideInsert(int after_index, std::string source_class, int sprite, std::string  obstancle_class, TScript callback);
				void OnCollideRemove(size_t index);

				void SaveToXML(pugi::xml_node& parent_node, const int version);
				void LoadFromXML(const pugi::xml_node& document_node, const int version);
			};
		}
	}
}
