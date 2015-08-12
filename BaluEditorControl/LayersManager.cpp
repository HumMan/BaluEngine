
#include "LayersManager.h"

#include <baluLib.h>
#include <assert.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

#include "Converters.h"

namespace Editor
{

	class TLayersManagerPrivate
	{
	public:
		//source edited world
		IBaluWorld* world;

		//local objects
		IDirector* director;
		IBaluWorldInstance* world_instance;
		IBaluSceneInstance* scene_instance;
		
		TLayersManagerPrivate()
		{
			world = nullptr;

			director = nullptr;
			world_instance = nullptr;
			scene_instance = nullptr;
		}
	};

	TLayersManager::TLayersManager(TWorldDirector^ world_director)
	{
		WriteInfoToLog("Initializing TLayersManager");

		this->director = world_director;
		world_director->RegisterEditor(this);

		p = new TLayersManagerPrivate();
		
		p->world = world_director->GetWorld();

		WriteInfoToLog("Initializing TLayersManager success");
	}

	void TLayersManager::Destroy()
	{
		//delete p->screen;
		//OnEditedObjectChange(this, (int)TWorldObjectType::None, -1);
		//IDirector::DestroyDirector(p->director);
		//p->director = nullptr;
		//p->world = nullptr;
		//director = nullptr;
		delete p;
	}

	void TLayersManager::OnBeforeWorldLoad()
	{
		//p->world = director->GetWorld();
		if (p->world != nullptr)
		{
			OnEditedObjectChange(this, (int)TWorldObjectType::None, -1);
			p->director->SetWorldInstance(nullptr);
		}
	}
	void TLayersManager::OnAfterWorldLoad()
	{
		p->world = director->GetWorld();
		OnEditedObjectChange(this, (int)TWorldObjectType::None, -1);
	}

	void TLayersManager::OnEditedObjectChange(TEditor^ sender, int _type, int index)
	{
		
	}
}