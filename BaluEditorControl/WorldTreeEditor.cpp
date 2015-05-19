#include "WorldTreeEditor.h"

#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

namespace Editor
{
	class TWorldTreeEditorPrivate
	{
	public:

	};

	std::vector<std::string> TWorldTreeEditor::GetObjectNames(int obj_type)
	{
		return std::vector<std::string>();
	}

	TWorldTreeEditor::TWorldTreeEditor(TWorldDirector^ world)
	{
		p = new TWorldTreeEditorPrivate();
	}

	void TWorldTreeEditor::Deinitialize()
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
		return -1;
	}
	String^ TWorldTreeEditor::GetObjectName(int obj_type, int obj_index)
	{
		return nullptr;
	}
	void TWorldTreeEditor::SetObjectName(int obj_type, int obj_index, String^ new_name)
	{

	}
	bool TWorldTreeEditor::CanSetObjectName(int obj_type, int obj_index, String^ new_name)
	{
		return false;
	}

	void TWorldTreeEditor::CreateObject(int obj_type)
	{

	}
	void TWorldTreeEditor::DestroyObject(int obj_type, int obj_index)
	{

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