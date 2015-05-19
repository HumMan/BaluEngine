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

	class TWorldDirectorPrivate;

	public ref class TWorldDirector
	{
	private:
		TWorldDirectorPrivate* p;

		array<TEditor^>^ editors;
	internal:
		EngineInterface::IBaluWorld* GetWorld();
		void RegisterEditor(TEditor^ editor);
		void UnregisterEditor(TEditor^ editor);

		void OnSelectWorldNode(TEditor^ sender, IBaluWorldObject* new_selection);
	public:
		TWorldDirector(String^ assets_dir);
		void Destroy();

		String^ GetAssetsDir();

		void SaveWorldTo(String^ path);
		void LoadWorldFrom(String^ path);
		void LoadDemoWorld();
	};


	ref class TEditor
	{
	public:
		virtual void OnSelectWorldNode(TEditor^ sender, IBaluWorldObject* old_selection, IBaluWorldObject* new_selection){};
		virtual void OnObjectCreate(TEditor^ sender, IObservableCollection* collection, IBaluWorldObject* created_object){}
	};
}
