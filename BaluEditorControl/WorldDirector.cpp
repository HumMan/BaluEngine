#include "WorldDirector.h"

#include <baluLib.h>

#include <Interfaces\BaluEngineInterface.h>

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