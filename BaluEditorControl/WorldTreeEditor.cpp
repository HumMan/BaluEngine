#include "WorldTreeEditor.h"

#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

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
		void OnObjectCreate(TWorldObjectType type,std::string name)
		{
			editor->ObjectCreatedHandler(editor, (int)type, Converters::ToClrString(name));
		}
		void OnObjectDestroy(TWorldObjectType type, std::string name)
		{
			editor->ObjectDestroyedHandler(editor, (int)type, Converters::ToClrString(name));
		}
		void OnObjectChange(TWorldObjectType type, std::string name){}
		void OnSubObjectCreate(TWorldObjectType obj_type, std::string name, TWorldObjectSubType sub_obj_type, int sub_obj_index){}
		void OnSubObjectDestroy(TWorldObjectType obj_type, std::string name, TWorldObjectSubType sub_obj_type, int sub_obj_index){}
		void OnSubObjectChange(TWorldObjectType obj_type, std::string name, TWorldObjectSubType sub_obj_type, int sub_obj_index){}
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
		AfterWorldLoaded();
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

		director->Notify_All_AfterWorldLoaded += AfterWorldLoadedHandler();

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