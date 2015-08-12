
#include "WorldObjectsList.h"

#include <baluLib.h>
#include <assert.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

#include "Converters.h"

namespace Editor
{

	class TWorldObjectsListPrivate
	{
	public:
		TWorldObjectType active_type;
		int active_selection;
		IBaluWorldObject* selected_object;
		IBaluWorld* world;
	};

	void TWorldObjectsList::OnSelectObjectsTypeChange(TEditor^ sender, int type)
	{
		if (p->active_type != (TWorldObjectType)type)
		{
			p->active_type = (TWorldObjectType)type;
			TEditor::OnSelectObjectsTypeChange(sender, type);
		}
	}
	void TWorldObjectsList::OnAfterWorldLoad()
	{
		p->world = director->GetWorld();
		TEditor::OnAfterWorldLoad();
	}
	TWorldObjectsList::TWorldObjectsList(TWorldDirector^ world_director)
	{
		WriteInfoToLog("Initializing TWorldObjectsList");

		director = world_director;
		world_director->RegisterEditor(this);
		p = new TWorldObjectsListPrivate();
		p->active_type = TWorldObjectType::None;

		WriteInfoToLog("Initializing TWorldObjectsList success");
	}
	void TWorldObjectsList::Destroy()
	{
		delete p;
	}
	int TWorldObjectsList::GetObjectsCount()
	{
		if (p->active_type == TWorldObjectType::None)
			return 0;
		return p->world->GetObjects(p->active_type).size();
	}
	String^ TWorldObjectsList::GetObjectName(int index)
	{
		return Converters::ToClrString(p->world->GetObjects(p->active_type)[index]->GetName());
	}
	void TWorldObjectsList::SetSelectedObject(int index)
	{
		p->active_selection = index;
		//director->OnObjectListSelectionChange(this, (int)p->active_type, p->active_selection);
	}
}