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

	class TLayersManagerPrivate;

	public ref class TLayerDesc
	{
	public:
		String^ name;
		bool visible;
		float alpha;
		bool locked;
		bool visible_in_editor;
	};

	public delegate void OnLayersManagerSceneChangeDelegate(TEditor^ sender, bool active);

	public ref class TLayersManager : public TEditor
	{
	internal:
		void OnLayersManagerSceneChange(TEditor^ sender, IBaluSceneInstance* scene_instance);
		IBaluSceneInstance* GetActiveScene();
	private:
		TLayersManagerPrivate* p;
		TWorldDirector^ director;
	public:

		event OnLayersManagerSceneChangeDelegate^ LayersManagerSceneChange;

		TLayersManager(TWorldDirector^ director);

		void AddLayer();
		void RemoveLayer(int id);
		int GetLayersCount();
		TLayerDesc^ GetLayer(int id);
		void SetLayer(int id, TLayerDesc^ desc);

		void Destroy() override;
	};
}