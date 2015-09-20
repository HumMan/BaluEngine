#include "WorldDirector.h"

#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

using namespace EngineInterface;

#include "../Example/DemoWorld.h"

#include "Converters.h"

namespace Editor
{
	class TWorldDirectorPrivate
	{
	public:
		std::string assets_dir;
		IBaluWorld* world;

		IBaluWorldObject* selected_object;

		TWorldDirectorPrivate()
		{
			world = nullptr;
			selected_object = nullptr;
		}
		~TWorldDirectorPrivate()
		{
			DestroyWorld(world);
		}
	};


	TWorldDirector::TWorldDirector(String^ assets_dir)
	{
		p = new TWorldDirectorPrivate();

		p->assets_dir = Converters::FromClrString(assets_dir);

		editors = gcnew List<TEditor^>();
	}
	void TWorldDirector::Destroy()
	{
		for each (auto ed in editors)
		{
			ed->Destroy();
		}
		editors = nullptr;
		delete p;
	}
	void TWorldDirector::RegisterEditor(TEditor^ editor)
	{
		editors->Add(editor);
	}
	void TWorldDirector::UnregisterEditor(TEditor^ editor)
	{
		editors->Remove(editor);
	}

	//void TWorldDirector::OnSelectWorldNode(TEditor^ sender, IBaluWorldObject* new_selection)
	//{
	//	if (p->selected_object != new_selection)
	//	{
	//		for each (auto ed in editors)
	//		{
	//			ed->OnSelectWorldNode(sender, p->selected_object, new_selection);
	//		}
	//		p->selected_object = new_selection;
	//	}
	//}
	/*void TWorldDirector::OnClassInstanceSelectionChange(TEditor^ sender, TSceneObject* new_selection)
	{
		for each (auto ed in editors)
		{
			ed->OnClassInstanceSelectionChange(sender, new_selection);
		}
	//}*/
	//void TWorldDirector::OnBeforeWorldLoad()
	//{
	//	for each (auto ed in editors)
	//	{
	//		ed->OnBeforeWorldLoad();
	//	}
	//}
	//void TWorldDirector::OnAfterWorldLoad()
	//{
	//	for each (auto ed in editors)
	//	{
	//		ed->OnAfterWorldLoad();
	//	}
	//}

	//void TWorldDirector::OnObjectCreate(TEditor^ sender, int type, int index)
	//{
	//	for each (auto ed in editors)
	//	{
	//		ed->OnObjectCreate(sender, type, index);
	//	}
	//}

	//void TWorldDirector::OnObjectDestroy(TEditor^ sender, int type, int index)
	//{
	//	for each (auto ed in editors)
	//	{
	//		ed->OnObjectDestroy(sender, type, index);
	//	}
	//}
/*
	void TWorldDirector::LayersManagerSceneChange(TEditor^ sender, IBaluSceneInstance* scene_instance)
	{
		for each (auto ed in editors)
		{
			ed->OnLayersManagerSceneChange(sender, scene_instance);
		}
	}

	void TWorldDirector::EditedObjectChange(TEditor^ sender, int type, String^ name)
	{
		for each (auto ed in editors)
		{
			ed->OnEditedObjectChange(sender, type, Converters::FromClrString(name));
		}
	}

	void TWorldDirector::OnSelectObjectsTypeChange(TEditor^ sender, int type)
	{
		for each (auto ed in editors)
		{
			ed->OnSelectObjectsTypeChange(sender, type);
		}
	}

	void TWorldDirector::OnObjectListSelectionChange(TEditor^ sender, int type, String^ name)
	{
		for each (auto ed in editors)
		{
			ed->OnObjectListSelectionChange(sender, type, Converters::FromClrString(name));
		}
	}
*/
	String^ TWorldDirector::GetAssetsDir()
	{
		return Converters::ToClrString(p->assets_dir);
	}

	void TWorldDirector::SaveWorldTo(String^ path)
	{
		p->world->SaveToXML(Converters::FromClrString(path));
	}
	void TWorldDirector::LoadWorldFrom(String^ path)
	{
		Perform_Notify_All_BeforeWorldLoaded();
		if (p->world != nullptr)
		{
			DestroyWorld(p->world);
			p->world = nullptr;
		}
		p->world = CreateWorld();
		p->world->LoadFromXML(Converters::FromClrString(path));
		p->world->GetCallbacksActiveType() = TScriptActiveType::EDITOR;
		Perform_Notify_All_AfterWorldLoaded();
	}
	void TWorldDirector::LoadDemoWorld()
	{
		Perform_Notify_All_BeforeWorldLoaded();
		if (p->world != nullptr)
		{
			DestroyWorld(p->world);
			p->world = nullptr;
		}
		p->world = CreateDemoWorld(p->assets_dir);
		p->world->GetCallbacksActiveType() = TScriptActiveType::EDITOR;
		Perform_Notify_All_AfterWorldLoaded();
	}

	void TWorldDirector::LoadNewWorld()
	{
		Perform_Notify_All_BeforeWorldLoaded();
		if (p->world != nullptr)
		{
			DestroyWorld(p->world);
			p->world = nullptr;
		}
		p->world = CreateWorld();
		p->world->GetCallbacksActiveType() = TScriptActiveType::EDITOR;
		Perform_Notify_All_AfterWorldLoaded();
	}

	EngineInterface::IBaluWorld* TWorldDirector::GetWorld()
	{
		return p->world;
	}

	void TWorldDirector::DetectMemLeaks()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

	void TWorldDirector::ConfigureLogging()
	{
		EngineInterface::ConfigureLogging();
	}
}