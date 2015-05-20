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
	public delegate void OnObjectCreateDelegate(TEditor^ sender, int type, int index);
	public delegate void OnObjectRemoveDelegate(TEditor^ sender, int type, int index);

	public ref class TEditor
	{
	internal:
		virtual void Destroy() = 0;
		virtual void OnSelectWorldNode(TEditor^ sender, IBaluWorldObject* old_selection, IBaluWorldObject* new_selection){};
		virtual void OnBeforeWorldLoad(){}
		virtual void OnAfterWorldLoad(){}
		virtual void OnObjectCreate(TEditor^ sender, int type, int index){}
		virtual void OnObjectRemove(TEditor^ sender, int type, int index){}
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
		void OnObjectRemove(TEditor^ sender, int type, int index);

		TWorldDirector(String^ assets_dir);
		void Destroy();

		String^ GetAssetsDir();

		void SaveWorldTo(String^ path);
		void LoadWorldFrom(String^ path);
		void LoadDemoWorld();

		static void DetectMemLeaks();
	};


	
}
