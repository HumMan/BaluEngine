#include "WorldTreeEditor.h"

#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

#include "Converters.h"

#include <iostream>
#include <fstream>

namespace Editor
{
	class TWorldTreeEditorPrivate
	{
	public:
		IBaluWorld* world;

	};

	void TWorldTreeEditor::OnAfterWorldLoad()
	{
		p->world = director->GetWorld();
		TEditor::AfterWorldLoad();
	}

	std::vector<std::string> TWorldTreeEditor::GetObjectNames(int obj_type)
	{
		return std::vector<std::string>();
	}

	TWorldTreeEditor::TWorldTreeEditor(TWorldDirector^ director)
	{
		std::ofstream myfile;
		myfile.open("treeeditor.log", std::ios::out | std::ios::trunc);
		myfile << "Initializing TWorldTreeEditor\n";
		myfile.close();

		this->director = director;
		director->RegisterEditor(this);

		p = new TWorldTreeEditorPrivate();

		p->world = director->GetWorld();
	}

	void TWorldTreeEditor::Destroy()
	{
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

	//template<class T>
	//IBaluWorldObject* CreateItem(IBaluWorld* world)
	//{
	//	std::string new_name;
	//	T* existing_material;
	//	do
	//	{
	//		new_name = GetNewDefaultName<T>();
	//	} while (world->TryFind(new_name.c_str(), existing_material));

	//	T* new_mat;
	//	world->Create(new_name.c_str(), new_mat);
	//	return dynamic_cast<IBaluWorldObject*>(new_mat);
	//}

	//void BaluEditorControl::CreateMaterial()
	//{
	//	auto new_item = CreateItem<IBaluMaterial>(p->world);
	//	OnObjectCreatedByEditor(new_item);

	//	//p->editor->Edit(&p->world->materials[new_name]);
	//}
	//void BaluEditorControl::CreateSprite()
	//{
	//	auto new_item = CreateItem<IBaluSprite>(p->world);
	//	OnObjectCreatedByEditor(new_item);
	//}
	//void BaluEditorControl::CreateClass()
	//{
	//	auto new_item = CreateItem<IBaluClass>(p->world);
	//	OnObjectCreatedByEditor(new_item);
	//}
	//void BaluEditorControl::CreateScene()
	//{
	//	auto new_item = CreateItem<IBaluScene>(p->world);
	//	OnObjectCreatedByEditor(new_item);
	//}

	//void BaluEditorControl::CreateWorldTree(TreeView^ WorldTreeView, IBaluWorld* world)
	//{
	//	if (world == nullptr)
	//		return;
	//	auto world_node = gcnew TreeNode("World");
	//	world_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::World);
	//	WorldTreeView->Nodes->Add(world_node);
	//	{
	//		auto Materialst_node = gcnew TreeNode("Materials");
	//		Materialst_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material);
	//		world_node->Nodes->Add(Materialst_node);
	//		auto all_materials = world->GetMaterials();
	//		for (auto i = all_materials.begin(); i != all_materials.end(); i++)
	//		{
	//			auto new_sprite_node = gcnew TreeNode(gcnew String(i->first.c_str()));
	//			new_sprite_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material, dynamic_cast<IBaluWorldObject*>(i->second));
	//			Materialst_node->Nodes->Add(new_sprite_node);
	//		}
	//	}
	//	{
	//		auto Sprites_node = gcnew TreeNode("Sprites");
	//		Sprites_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Sprite);
	//		world_node->Nodes->Add(Sprites_node);
	//		auto all_sprites = world->GetSprites();
	//		for (auto i = all_sprites.begin(); i != all_sprites.end(); i++)
	//		{
	//			auto new_sprite_node = gcnew TreeNode(gcnew String(i->first.c_str()));
	//			new_sprite_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Sprite, dynamic_cast<IBaluWorldObject*>(i->second));
	//			Sprites_node->Nodes->Add(new_sprite_node);
	//		}
	//	}
	//	{
	//		auto Classes_node = gcnew TreeNode("Classes");
	//		Classes_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Class);
	//		world_node->Nodes->Add(Classes_node);
	//		auto all_classes = world->GetClasses();
	//		for (auto i = all_classes.begin(); i != all_classes.end(); i++)
	//		{
	//			auto new_class_node = gcnew TreeNode(gcnew String(i->first.c_str()));
	//			new_class_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Class, dynamic_cast<IBaluWorldObject*>(i->second));
	//			Classes_node->Nodes->Add(new_class_node);
	//		}
	//	}
	//	{
	//		auto Scenes_node = gcnew TreeNode("Scenes");
	//		Scenes_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Scene);
	//		world_node->Nodes->Add(Scenes_node);
	//		auto all_scenes = world->GetScenes();
	//		for (auto i = all_scenes.begin(); i != all_scenes.end(); i++)
	//		{
	//			auto new_scene_node = gcnew TreeNode(gcnew String(i->first.c_str()));
	//			new_scene_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Scene, dynamic_cast<IBaluWorldObject*>(i->second));
	//			Scenes_node->Nodes->Add(new_scene_node);
	//		}
	//	}
	//}
}