#include "WorldDirector.h"

#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

using namespace EngineInterface;

#include "../Example/DemoWorld.h"

#include "Converters.h"

#include "Delegate.h"

namespace Editor
{
	class TWorldDirectorPrivate
	{
	public:
		std::string assets_dir;
		IBaluWorld* world;

		IBaluWorldObject* selected_object;
		Delegate<IBaluWorldObject*, IBaluWorldObject*> on_selection_change;

		TWorldDirectorPrivate()
		{
			world = nullptr;
			selected_object = nullptr;
		}
	};


	TWorldDirector::TWorldDirector(String^ assets_dir)
	{
		p = new TWorldDirectorPrivate();

		p->assets_dir = Converters::FromClrString(assets_dir);
	}

	String^ TWorldDirector::GetAssetsDir()
	{
		return Converters::ToClrString(p->assets_dir);
	}

	void TWorldDirector::SaveWorldTo(String^ path)
	{
		p->world->SaveToXML(msclr::interop::marshal_as<std::string>(path));
	}
	void TWorldDirector::LoadWorldFrom(String^ path)
	{
		WorldTreeView->Nodes->Clear();
		if (p->world != nullptr)
		{
			DestroyWorld(p->world);
			p->world = nullptr;
		}
		p->world = CreateWorld();
		p->world->LoadFromXML(msclr::interop::marshal_as<std::string>(path));
		CreateWorldTree(WorldTreeView, p->world);
	}
	void TWorldDirector::LoadDemoWorld()
	{
		WorldTreeView->Nodes->Clear();
		if (p->world != nullptr)
		{
			DestroyWorld(p->world);
			p->world = nullptr;
		}
		p->world = CreateDemoWorld(p->director->GetAssetsDir());
		CreateWorldTree(WorldTreeView, p->world);
	}

	EngineInterface::IBaluWorld* TWorldDirector::GetWorld()
	{

	}
}