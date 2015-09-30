
#include "WorldObjectsList.h"

#include <baluLib.h>
#include <assert.h>


#include <Interfaces\BaluEngineInterface.h>

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
			GUI_Notify_TypeChange(sender, type);
		}
	}
	void TWorldObjectsList::OnAfterWorldLoad()
	{
		p->world = director->GetWorld();
	}
	TWorldObjectsList::TWorldObjectsList(TWorldDirector^ world_director)
	{
		WriteInfoToLog("Initializing TWorldObjectsList");

		director = world_director;
		world_director->RegisterEditor(this);

		director->Notify_ObjectList_TypeChange += gcnew TNotify_ObjectList_TypeChange(this, &TWorldObjectsList::OnSelectObjectsTypeChange);
		director->Notify_All_AfterWorldLoaded += gcnew TNotify_All_AfterWorldLoaded(this, &TWorldObjectsList::OnAfterWorldLoad);

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
		director->Perform_Notify_ObjectEditor_ObjectListSelectionChange(this, (int)p->active_type, GetObjectName(p->active_selection));
	}
}

void Editor::TWorldObjectsList::OnNotify_All_AfterWorldLoaded()
{
	throw gcnew System::NotImplementedException();
}
