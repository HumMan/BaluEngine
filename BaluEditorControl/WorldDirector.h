#pragma once

#include <vector>

#include "Delegate.h"
#include "Converters.h"

namespace EngineInterface
{
	class IBaluWorld;
	class IBaluWorldObject;
	class TSceneObject;
	class IProperties;
}

namespace Editor
{
	using namespace System;
	using namespace System::Collections::Generic;

	using namespace EngineInterface;

	class TWorldDirectorPrivate;
	ref class TEditor;

	public delegate void OnPropertiesEditorTargetChangeDelegate(TEditor^ sender, EngineInterface::IProperties* target);
	//public delegate void OnClassInstanceSelectionChangeDelegate(TEditor^ sender, TSceneObject* new_selection);

	public delegate void OnAfterWorldLoadDelegate();
	public delegate void OnBeforeWorldLoadDelegate();

	public delegate void OnObjectCreateDelegate(TEditor^ sender, int type, String^ name);
	public delegate void OnObjectChangeDelegate(TEditor^ sender, int type, String^ name);
	public delegate void OnObjectDestroyDelegate(TEditor^ sender, int type, String^ name);

	public delegate void OnSubObjectCreateDelegate(TEditor^ sender, int obj_type, String^ name, int sub_obj_type, int sub_obj_index);
	public delegate void OnSubObjectChangeDelegate(TEditor^ sender, int obj_type, String^ name, int sub_obj_type, int sub_obj_index);
	public delegate void OnSubObjectDestroyDelegate(TEditor^ sender, int obj_type, String^ name, int sub_obj_type, int sub_obj_index);

	public delegate void OnEditedObjectChangeDelegate(TEditor^ sender, int type, String^ name);
	public delegate void OnSelectObjectsTypeChangeDelegate(TEditor^ sender, int type);
	public delegate void OnObjectListSelectionChangeDelegate(TEditor^ sender, int type, String^ name);

	public ref  class TEditor abstract
	{
	internal:
		virtual void Destroy() = 0;
		//virtual void OnSelectWorldNode(TEditor^ sender, IBaluWorldObject* old_selection, IBaluWorldObject* new_selection){};


		virtual void OnPropertiesEditorTargetChange(TEditor^ sender, EngineInterface::IProperties* target)
		{
			PropertiesEditorTargetChange(sender, target);
		}
		//virtual void OnClassInstanceSelectionChange(TEditor^ sender, TSceneObject* new_selection)
		//{
		//	ClassInstanceSelectionChange(sender, new_selection);
		//}
		virtual void OnBeforeWorldLoad()
		{
			BeforeWorldLoad();
		}
		virtual void OnAfterWorldLoad()
		{
			AfterWorldLoad();
		}
		virtual void OnObjectCreate(TEditor^ sender, int type, std::string name)
		{
			ObjectCreate(sender, type, Converters::ToClrString(name));
		}
		virtual void OnObjectDestroy(TEditor^ sender, int type, std::string name)
		{
			ObjectDestroy(sender, type, Converters::ToClrString(name));
		}
		virtual void OnObjectChange(TEditor^ sender, int type, std::string name)
		{
			ObjectChange(sender, type, Converters::ToClrString(name));
		}
		virtual void OnSubObjectCreate(TEditor^ sender, int obj_type, std::string name, int sub_obj_type, int sub_obj_index)
		{
			SubObjectCreate(sender, obj_type, Converters::ToClrString(name), sub_obj_type, sub_obj_index);
		}
		virtual void OnSubObjectRemove(TEditor^ sender, int obj_type, std::string name, int sub_obj_type, int sub_obj_index)
		{
			SubObjectChange(sender, obj_type, Converters::ToClrString(name), sub_obj_type, sub_obj_index);
		}
		virtual void OnSubObjectChange(TEditor^ sender, int obj_type, std::string name, int sub_obj_type, int sub_obj_index)
		{
			SubObjectDestroy(sender, obj_type, Converters::ToClrString(name), sub_obj_type, sub_obj_index);
		}
		virtual void OnEditedObjectChange(TEditor^ sender, int type, std::string name)
		{
			EditedObjectChange(sender, type, Converters::ToClrString(name));
		}
		virtual void OnSelectObjectsTypeChange(TEditor^ sender, int type)
		{
			SelectObjectsTypeChange(sender, type);
		}
		virtual void OnObjectListSelectionChange(TEditor^ sender, int type, std::string name)
		{
			ObjectListSelectionChange(sender, type, Converters::ToClrString(name));
		}
	public:
		event OnPropertiesEditorTargetChangeDelegate^ PropertiesEditorTargetChange;
		//event OnClassInstanceSelectionChangeDelegate^ ClassInstanceSelectionChange;
		event OnAfterWorldLoadDelegate^ AfterWorldLoad;
		event OnBeforeWorldLoadDelegate^ BeforeWorldLoad;
		event OnObjectCreateDelegate^ ObjectCreate;
		event OnObjectChangeDelegate^ ObjectChange;
		event OnObjectDestroyDelegate^ ObjectDestroy;
		event OnSubObjectCreateDelegate^ SubObjectCreate;
		event OnSubObjectChangeDelegate^ SubObjectChange;
		event OnSubObjectDestroyDelegate^ SubObjectDestroy;
		event OnEditedObjectChangeDelegate^ EditedObjectChange;
		event OnSelectObjectsTypeChangeDelegate^ SelectObjectsTypeChange;
		event OnObjectListSelectionChangeDelegate^ ObjectListSelectionChange;
	};	

	public ref class TWorldDirector
	{
	private:
		TWorldDirectorPrivate* p;

		List<TEditor^>^ editors;

		void OnBeforeWorldLoad();
		void OnAfterWorldLoad();

	internal:
		EngineInterface::IBaluWorld* GetWorld();
		void RegisterEditor(TEditor^ editor);
		void UnregisterEditor(TEditor^ editor);

	public:

		//void OnSelectWorldNode(TEditor^ sender, IBaluWorldObject* new_selection);
		//void OnClassInstanceSelectionChange(TEditor^ sender, TSceneObject* new_selection);
		
		//void OnObjectCreate(TEditor^ sender, int type, int index);
		//void OnObjectDestroy(TEditor^ sender, int type, int index);
		
		//только для изменения редактируемого объекта в окне редактора
		void EditedObjectChange(TEditor^ sender, int type, String^ name);
		//void OnSelectObjectsTypeChange(TEditor^ sender, int type);
		//void OnObjectListSelectionChange(TEditor^ sender, int type, int index);

		TWorldDirector(String^ assets_dir);
		void Destroy();

		String^ GetAssetsDir();

		void SaveWorldTo(String^ path);
		void LoadWorldFrom(String^ path);
		void LoadDemoWorld();
		void LoadNewWorld();

		static void DetectMemLeaks();
		static void ConfigureLogging();
	};


	
}
