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


	public enum class TLayersChangeType
	{
		Reorder,
		Add,
		Remove,
		Change
	};

	public delegate void OnLayersManagerSceneChangeDelegate(TEditor^ sender, bool active);
	public delegate void TLayersChange(TLayersChangeType type, int layer_id, int after_id);

	public ref class TLayersManager : public TEditor
	{
	internal:
		void OnLayersManagerSceneChange(TEditor^ sender, IBaluSceneInstance* scene_instance);
		IBaluSceneInstance* GetActiveScene();

		void Perform_GUI_Notify_LayersChange(TLayersChangeType type, int layer_id, int after_id)
		{
			GUI_Notify_LayersChange(type, layer_id, after_id);
		}
	private:
		TLayersManagerPrivate* p;
		TWorldDirector^ director;
	public:

		event OnLayersManagerSceneChangeDelegate^ GUI_Notify_LayersManagerSceneChange;
		event TLayersChange^ GUI_Notify_LayersChange;

		TLayersManager(TWorldDirector^ director);

		void AddLayer();
		void RemoveLayer(int id);
		int GetLayersCount();
		TLayerDesc^ GetLayer(int id);
		void SetLayer(int id, TLayerDesc^ desc);

		void Destroy() override;
	};
}