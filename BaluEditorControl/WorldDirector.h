#pragma once

#include <vector>

#include "Converters.h"

namespace EngineInterface
{
	class IBaluWorld;
	class IBaluWorldObject;
	class TSceneObject;
	class IProperties;
	class IBaluSceneInstance;
}

namespace Editor
{
	using namespace System;
	using namespace System::Collections::Generic;

	using namespace EngineInterface;

	class TWorldDirectorPrivate;
	ref class TEditor;


	public ref  class TEditor abstract
	{
	internal:
		virtual void Destroy() = 0;
	public:
	};	

	public delegate void TNotify_LayersManager_SceneChange(TEditor^ sender, IBaluSceneInstance* scene_instance);
	public delegate void TNotify_ObjectEditor_EditedObjectChange(TEditor^ sender, int type, String^ name);
	public delegate void TNotify_ObjectList_TypeChange(TEditor^ sender, int type);
	public delegate void TNotify_ObjectEditor_ObjectListSelectionChange(TEditor^ sender, int type, String^ name);
	public delegate void TNotify_All_AfterWorldLoaded();
	public delegate void TNotify_All_BeforeWorldLoaded();

	public ref class TWorldDirector
	{
	private:
		TWorldDirectorPrivate* p;

		List<TEditor^>^ editors;

	internal:
		EngineInterface::IBaluWorld* GetWorld();
		void RegisterEditor(TEditor^ editor);
		void UnregisterEditor(TEditor^ editor);

		event TNotify_LayersManager_SceneChange^ Notify_LayersManager_SceneChange;
		void Perform_Notify_LayersManager_SceneChange(TEditor^ sender, IBaluSceneInstance* scene_instance)
		{
			Notify_LayersManager_SceneChange(sender, scene_instance);
		}

		event TNotify_ObjectEditor_ObjectListSelectionChange^ Notify_ObjectEditor_ObjectListSelectionChange;
		void Perform_Notify_ObjectEditor_ObjectListSelectionChange(TEditor^ sender, int type, String^ name)
		{
			Notify_ObjectEditor_ObjectListSelectionChange(sender, type, name);
		}

		event TNotify_ObjectList_TypeChange^ Notify_ObjectList_TypeChange;
		void Perform_Notify_ObjectList_TypeChange(TEditor^ sender, int type)
		{
			Notify_ObjectList_TypeChange(sender, type);
		}

		
		event TNotify_ObjectEditor_EditedObjectChange^ Notify_ObjectEditor_EditedObjectChange;
		void Perform_Notify_ObjectEditor_EditedObjectChange(TEditor^ sender, int type, String^ name)
		{
			Notify_ObjectEditor_EditedObjectChange(sender, type, name);
		}
		
		event TNotify_All_AfterWorldLoaded^ Notify_All_AfterWorldLoaded;
		void Perform_Notify_All_AfterWorldLoaded()
		{
			Notify_All_AfterWorldLoaded();
		}

		event TNotify_All_BeforeWorldLoaded^ Notify_All_BeforeWorldLoaded;
		void Perform_Notify_All_BeforeWorldLoaded()
		{
			Notify_All_BeforeWorldLoaded();
		}
	public:
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
