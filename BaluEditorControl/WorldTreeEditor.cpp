#include "WorldTreeEditor.h"

#include <baluLib.h>

#include <Interfaces\BaluEngineInterface.h>

#include "Converters.h"

#include <vcclr.h>
#include <msclr\marshal_cppstd.h>

namespace Editor
{

	class TWorldTreeChangesListener : public TBaluWorldChangeListener
	{
		gcroot<TWorldTreeEditor^> editor;
	public:
		TWorldTreeChangesListener(TWorldTreeEditor^ editor)
		{
			this->editor = editor;
		}
		void OnObjectCreate(TWorldObjectType type, const std::string& name)
		{
			editor->ObjectCreatedHandler(editor, (int)type, Converters::ToClrString(name));
		}
		void OnObjectDestroy(TWorldObjectType type, const std::string& name)
		{
			editor->ObjectDestroyedHandler(editor, (int)type, Converters::ToClrString(name));
		}
	};

	class TWorldTreeEditorPrivate
	{
	public:
		IBaluWorld* world;
		std::unique_ptr<TWorldTreeChangesListener> world_change_listener;
	};

	void TWorldTreeEditor::AfterWorldLoadedHandler()
	{
		p->world = director->GetWorld();
		p->world->AddChangesListener(p->world_change_listener.get());
		GUI_Notify_AfterWorldLoaded();
	}

	std::vector<std::string> TWorldTreeEditor::GetObjectNames(int obj_type)
	{
		return std::vector<std::string>();
	}

	TWorldTreeEditor::TWorldTreeEditor(TWorldDirector^ director)
	{
		WriteInfoToLog("Initializing TWorldTreeEditor");

		this->director = director;
		director->RegisterEditor(this);

		director->Notify_All_AfterWorldLoaded += gcnew TNotify_All_AfterWorldLoaded(this, &TWorldTreeEditor::AfterWorldLoadedHandler);

		p = new TWorldTreeEditorPrivate();

		p->world = director->GetWorld();
		p->world_change_listener.reset(new TWorldTreeChangesListener(this));
		if (p->world != nullptr)
		{
			p->world->AddChangesListener(p->world_change_listener.get());
		}
		WriteInfoToLog("Initializing TWorldTreeEditor success");
	}

	void TWorldTreeEditor::Destroy()
	{
		if (p->world != nullptr)
		{
			p->world->RemoveChangesListener(p->world_change_listener.get());
		}
		delete p;
	}

	int TWorldTreeEditor::GetWorldObjectTypesCount()
	{
		return (int)TWorldObjectType::None;
	}
	String^ TWorldTreeEditor::GetObjectTypeName(int obj_type)
	{
		return gcnew String(TWorldObjectTypeString::Get((TWorldObjectType)obj_type));
	}

	void TWorldTreeEditor::SetEditedObject(int type, String^ name)
	{
		director->Perform_Notify_ObjectEditor_EditedObjectChange(this, type, name);
	}

	int TWorldTreeEditor::GetObjectsCount(int obj_type)
	{
		return p->world->GetObjects((TWorldObjectType)obj_type).size();
	}
	String^ TWorldTreeEditor::GetObjectName(int obj_type, int obj_index)
	{
		return Converters::ToClrString(p->world->GetObjects((TWorldObjectType)obj_type)[obj_index]->GetName());
	}
	void TWorldTreeEditor::SetObjectName(int obj_type, int obj_index, String^ new_name)
	{
		//TODO
	}
	bool TWorldTreeEditor::CanSetObjectName(int obj_type, int obj_index, String^ new_name)
	{
		return p->world->ObjectNameExists((TWorldObjectType)obj_type, Converters::FromClrString(new_name).c_str());
	}
	int TWorldTreeEditor::GetObjectIndex(int obj_type, String^ new_name)
	{
		auto name = Converters::FromClrString(new_name);
		auto arr = p->world->GetObjects((TWorldObjectType)obj_type);
		int index = 0;
		for (auto& v : arr)
		{
			if (v->GetName() == name)
				return index;
			index++;
		}
		return -1;
	}
	void TWorldTreeEditor::CreateObject(int obj_type, String^ name)
	{
		p->world->CreateObject((TWorldObjectType)obj_type, Converters::FromClrString(name).c_str());
	}
	bool TWorldTreeEditor::CanCreateObject(int obj_type, String^ name)
	{
		return !(p->world->ObjectNameExists((TWorldObjectType)obj_type, Converters::FromClrString(name).c_str()));
	}
	void TWorldTreeEditor::DestroyObject(int obj_type, String^ name)
	{
		p->world->DestroyObject((TWorldObjectType)obj_type, Converters::FromClrString(name).c_str());
	}
}