#pragma once

#include <vector>

#include "WorldDirector.h"

namespace EngineInterface
{
	class IBaluWorldObject;
	class IBaluWorld;
	class IAbstractEditor;
}

namespace Editor
{
	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::Collections::Generic;

	using namespace EngineInterface;

	ref class TWorldDirector;

	class TWorldTreeEditorPrivate;

	public delegate void OnAfterWorldLoad();
	public delegate void OnObjectCreateDelegate(TEditor^ sender, int type, String^ name);
	public delegate void OnObjectChangeDelegate(TEditor^ sender, int type, String^ name);
	public delegate void OnObjectDestroyDelegate(TEditor^ sender, int type, String^ name);
	public delegate void TAfterWorldLoaded();

	public ref class TWorldTreeEditor: public TEditor
	{
	internal:
		TWorldTreeEditorPrivate* p;
		TWorldDirector^ director;

		std::vector<std::string> GetObjectNames(int obj_type);

		void AfterWorldLoadedHandler();
		void ObjectCreatedHandler(TEditor^ sender, int type, String^ name)
		{
			ObjectCreate(sender, type, name);
		}
		void ObjectDestroyedHandler(TEditor^ sender, int type, String^ name)
		{
			ObjectDestroy(sender, type, name);
		}
	public:

		event OnObjectCreateDelegate^ ObjectCreate;
		event OnObjectChangeDelegate^ ObjectChange;
		event OnObjectDestroyDelegate^ ObjectDestroy;
		event TAfterWorldLoaded^ AfterWorldLoaded;

		TWorldTreeEditor(TWorldDirector^ director);

		void Destroy() override;

		static int GetWorldObjectTypesCount();
		static String^ GetObjectTypeName(int obj_type);

		int GetObjectsCount(int obj_type);
		String^ GetObjectName(int obj_type, int obj_index);
		void SetObjectName(int obj_type, int obj_index, String^ new_name);
		bool CanSetObjectName(int obj_type, int obj_index, String^ new_name);
		int GetObjectIndex(int obj_type, String^ new_name);

		void CreateObject(int obj_type, String^ name);
		bool CanCreateObject(int obj_type, String^ name);
		void DestroyObject(int obj_type, String^ name);
	};
}