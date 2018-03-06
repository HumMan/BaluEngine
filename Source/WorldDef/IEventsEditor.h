#pragma once

namespace BaluEngine
{
	namespace WorldDef
	{
		typedef std::string TScript;

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

		class IEventsEditor
		{
		public:
			virtual int GlobalGetCount(GlobalCallbackType type)=0;
			virtual TScript& GlobalGet(GlobalCallbackType type, int index)=0;
			virtual void GlobalInsert(GlobalCallbackType type, int after_index, TScript script)=0;
			virtual void GlobalRemove(GlobalCallbackType type, int index)=0;

			virtual int GlobalKeyGetCount(GlobalKeyCallbackType type)=0;
			virtual std::tuple<TKey, TScript>& GlobalKeyGet(GlobalKeyCallbackType type, int index)=0;
			virtual void GlobalKeyInsert(GlobalKeyCallbackType type, TKey key, int after_index, TScript script)=0;
			virtual void GlobalKeyRemove(GlobalKeyCallbackType type, int index)=0;

			virtual int ClassGetCount(ClassCallbackType type)=0;
			virtual std::tuple<TScript, std::string>& ClassGet(ClassCallbackType type, int index)=0;
			virtual void ClassInsert(ClassCallbackType type, std::string class_name, int after_index, TScript script)=0;
			virtual void ClassRemove(ClassCallbackType type, int index)=0;

			virtual int ClassKeyGetCount(ClassKeyCallbackType type)=0;
			virtual std::tuple<TKey, TScript, std::string>& ClassKeyGet(ClassKeyCallbackType type, int index)=0;
			virtual void ClassKeyInsert(ClassKeyCallbackType type, TKey key, std::string class_name, int after_index, TScript script)=0;
			virtual void ClassKeyRemove(ClassKeyCallbackType type, int index)=0;

			virtual int OnCollideGetCount()=0;
			virtual TSpriteWithClassCollide& OnCollideGet(int index)=0;
			virtual void OnCollideInsert(int after_index, std::string source_class, int sprite, std::string  obstancle_class, TScript callback)=0;
			virtual void OnCollideRemove(int index)=0;

			virtual void SaveToXML(pugi::xml_node& parent_node, const int version)=0;
			virtual void LoadFromXML(const pugi::xml_node& document_node, const int version)=0;
		};
	}
}
