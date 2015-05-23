#pragma once

#include <vector>

#include "Delegate.h"

namespace EngineInterface
{
	class IBaluWorld;
	class IBaluWorldObject;
}

namespace Editor
{
	using namespace System;
	using namespace System::Collections::Generic;

	using namespace EngineInterface;

	class TWorldDirectorPrivate;
	ref class TEditor;

	public delegate void OnAfterWorldLoadDelegate();
	public delegate void OnBeforeWorldLoadDelegate();

	public delegate void OnObjectCreateDelegate(TEditor^ sender, int type, int index);
	public delegate void OnObjectChangeDelegate(TEditor^ sender, int type, int index);
	public delegate void OnObjectDestroyDelegate(TEditor^ sender, int type, int index);

	public delegate void OnSubObjectCreateDelegate(TEditor^ sender, int obj_type, int obj_index, int sub_obj_type, int sub_obj_index);
	public delegate void OnSubObjectChangeDelegate(TEditor^ sender, int obj_type, int obj_index, int sub_obj_type, int sub_obj_index);
	public delegate void OnSubObjectDestroyDelegate(TEditor^ sender, int obj_type, int obj_index, int sub_obj_type, int sub_obj_index);

	public delegate void OnEditedObjectChangeDelegate(TEditor^ sender, int type, int index);

	public ref class TEditor
	{
	internal:
		virtual void Destroy() = 0;
		virtual void OnSelectWorldNode(TEditor^ sender, IBaluWorldObject* old_selection, IBaluWorldObject* new_selection){};
		virtual void OnBeforeWorldLoad()
		{
			BeforeWorldLoad();
		}
		virtual void OnAfterWorldLoad()
		{
			AfterWorldLoad();
		}
		virtual void OnObjectCreate(TEditor^ sender, int type, int index)
		{
			ObjectCreate(sender, type, index);
		}
		virtual void OnObjectDestroy(TEditor^ sender, int type, int index)
		{
			ObjectDestroy(sender, type, index);
		}
		virtual void OnObjectChange(TEditor^ sender, int type, int index)
		{
			ObjectChange(sender, type, index);
		}
		virtual void OnSubObjectCreate(TEditor^ sender, int obj_type, int obj_index, int sub_obj_type, int sub_obj_index)
		{
			SubObjectCreate(sender, obj_type, obj_index, sub_obj_type, sub_obj_index);
		}
		virtual void OnSubObjectRemove(TEditor^ sender, int obj_type, int obj_index, int sub_obj_type, int sub_obj_index)
		{
			SubObjectChange(sender, obj_type, obj_index, sub_obj_type, sub_obj_index);
		}
		virtual void OnSubObjectChange(TEditor^ sender, int obj_type, int obj_index, int sub_obj_type, int sub_obj_index)
		{
			SubObjectDestroy(sender, obj_type, obj_index, sub_obj_type, sub_obj_index);
		}
		virtual void OnEditedObjectChange(TEditor^ sender, int type, int index)
		{
			EditedObjectChange(sender, type, index);
		}
	public:
		event OnAfterWorldLoadDelegate^ AfterWorldLoad;
		event OnBeforeWorldLoadDelegate^ BeforeWorldLoad;
		event OnObjectCreateDelegate^ ObjectCreate;
		event OnObjectChangeDelegate^ ObjectChange;
		event OnObjectDestroyDelegate^ ObjectDestroy;
		event OnSubObjectCreateDelegate^ SubObjectCreate;
		event OnSubObjectChangeDelegate^ SubObjectChange;
		event OnSubObjectDestroyDelegate^ SubObjectDestroy;
		event OnEditedObjectChangeDelegate^ EditedObjectChange;
	};	

	public ref class TWorldDirector
	{
	private:
		TWorldDirectorPrivate* p;

		List<TEditor^>^ editors;
	internal:
		EngineInterface::IBaluWorld* GetWorld();
		void RegisterEditor(TEditor^ editor);
		void UnregisterEditor(TEditor^ editor);

	public:

		void OnSelectWorldNode(TEditor^ sender, IBaluWorldObject* new_selection);
		void OnBeforeWorldLoad();
		void OnAfterWorldLoad();
		void OnObjectCreate(TEditor^ sender, int type, int index);
		void OnObjectDestroy(TEditor^ sender, int type, int index);
		void OnEditedObjectChange(TEditor^ sender, int type, int index);

		TWorldDirector(String^ assets_dir);
		void Destroy();

		String^ GetAssetsDir();

		void SaveWorldTo(String^ path);
		void LoadWorldFrom(String^ path);
		void LoadDemoWorld();

		static void DetectMemLeaks();
	};


	
}
