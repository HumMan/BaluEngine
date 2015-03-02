#include "World.h"

#include <pugixml.hpp>

using namespace pugi;

TBaluPolygonShape* TBaluPhysShapeFactory::CreatePolygonShape()
{
	return new TBaluPolygonShape();
}

TBaluCircleShape* TBaluPhysShapeFactory::CreateCircleShape(float radius)
{
	return new TBaluCircleShape(radius);
}

TBaluCircleShape* TBaluPhysShapeFactory::CreateCircleShape(float radius, TVec2 pos)
{
	return new TBaluCircleShape(radius,pos);
}

TBaluBoxShape* TBaluPhysShapeFactory::CreateBoxShape(float width, float height)
{
	return new TBaluBoxShape(width, height);
}

//void TScreen::AddView(TView view)
//{
//	views.push_back(view);
//}
//
//int TScreen::GetViewsCount()
//{
//	return views.size();
//}
//
//TView TScreen::GetView(int i)
//{
//	return views[i];
//}
//
//void TScreen::RemoveView(int i)
//{
//	views.erase(views.begin()+i);
//}

TBaluWorld::TBaluWorld()
{
	callback_active_type.active_type = 0;
}

template<class T, class find_array>
bool TryFind(find_array& map, const char* class_name, T*& result)
{
	auto iter = map.find(class_name);
	if (iter == map.end())
		return false;
	else
	{
		result = &iter->second;
		return true;
	}
}

template<class T, class I, class find_array>
bool TryFindI(find_array& map, const char* class_name, I*& result)
{
	T* r;
	auto result0 = TryFind<T>(map, class_name, r);
	result = static_cast<I*>(r);
	return result0;
}

bool TBaluWorld::TryFindClass(const char* class_name, TBaluClass*& result)
{
	return TryFind<TBaluClass>(classes, class_name, result);
}

bool TBaluWorld::TryFindMaterial(const char* material_name, EngineInterface::IBaluMaterial*& result)
{
	return TryFindI<TBaluMaterial, EngineInterface::IBaluMaterial>(materials, material_name, result);
}
bool TBaluWorld::TryFindSprite(const char* sprite_name, EngineInterface::IBaluSprite*& result)
{
	return TryFindI<TBaluSprite, EngineInterface::IBaluSprite>(sprites, sprite_name, result);
}
bool TBaluWorld::TryFindScene(const char* scene_name, EngineInterface::IBaluScene*& result)
{
	return TryFindI<TBaluScene, EngineInterface::IBaluScene>(scenes, scene_name, result);
}

bool TBaluWorld::TryFindClass(const char* class_name, EngineInterface::IBaluClass*& result)
{
	return TryFindI<TBaluClass, EngineInterface::IBaluClass>(classes, class_name, result);
}

TBaluMaterial* TBaluWorld::CreateMaterial(const char* mat_name)
{
	auto iter = materials.find(mat_name);
	if (iter == materials.end())
	{
		materials[mat_name].SetName(mat_name);
		return &materials[mat_name];
	}
	else
	{
		throw std::invalid_argument("Материал с данным имененем уже существует");
	}
}

TBaluSprite* TBaluWorld::CreateSprite(const char* sprite_name)
{
	auto iter = sprites.find(sprite_name);
	if (iter == sprites.end())
	{
		sprites[sprite_name].SetName(sprite_name);
		return &sprites[sprite_name];
	}
	else
	{
		throw std::invalid_argument("Спрайт с данным имененем уже существует");
	}
}
TBaluClass* TBaluWorld::CreateClass(const char* class_name)
{
	auto iter = classes.find(class_name);
	if (iter == classes.end())
	{
		classes[class_name].SetName(class_name);
		return &classes[class_name];
	}
	else
	{
		throw std::invalid_argument("Класс с данным имененем уже существует");
	}
}
TBaluScene* TBaluWorld::CreateScene(const char* scene_name)
{
	auto iter = scenes.find(scene_name);
	if (iter == scenes.end())
	{
		scenes[scene_name].SetName(scene_name);
		return &scenes[scene_name];
	}
	else
	{
		throw std::invalid_argument("Сцена с данным имененем уже существует");
	}
}

TBaluMaterial* TBaluWorld::GetMaterial(const char* scene_name)
{
	auto iter = materials.find(scene_name);
	if (iter != materials.end())
	{
		return &iter->second;
	}
	else
	{
		throw std::invalid_argument("Сцена с данным имененем отсутсвует");
	}
}

TBaluSprite* TBaluWorld::GetSprite(const char* scene_name)
{
	auto iter = sprites.find(scene_name);
	if (iter != sprites.end())
	{
		return &iter->second;
	}
	else
	{
		throw std::invalid_argument("Сцена с данным имененем отсутсвует");
	}
}

TBaluClass* TBaluWorld::GetClass(const char* scene_name)
{
	auto iter = classes.find(scene_name);
	if (iter != classes.end())
	{
		return &iter->second;
	}
	else
	{
		throw std::invalid_argument("Сцена с данным имененем отсутсвует");
	}
}

TBaluScene* TBaluWorld::GetScene(const char* scene_name)
{
	auto iter = scenes.find(scene_name);
	if (iter != scenes.end())
	{
		return &iter->second;
	}
	else
	{
		throw std::invalid_argument("Сцена с данным имененем отсутсвует");
	}
}

TBaluPhysShapeFactory* TBaluWorld::GetPhysShapeFactory()
{
	return &shape_factory;
}

void TBaluWorld::OnMouseDown(CallbackWithData<MouseUpDownCallback> callback)
{
	mouse_down_callbacks.push_back(callback);
}

void TBaluWorld::OnMouseUp(CallbackWithData<MouseUpDownCallback> callback)
{
	mouse_up_callbacks.push_back(callback);
}

void TBaluWorld::OnMouseMove(CallbackWithData<MouseMoveCallback> callback)
{
	mouse_move_callbacks.push_back(callback);
}

void TBaluWorld::SaveToXML(std::string path)
{
	xml_document doc;
	auto doc_el = doc.append_child("BaluEditorWorldFile");
	SaveToXML(doc_el, 1);
	doc.save_file(path.c_str());
}

void TBaluWorld::LoadFromXML(std::string path)
{
	xml_document doc;
	doc.load_file(path.c_str());
	LoadFromXML(doc.child("BaluEditorWorldFile"), 1);
}




void SaveColor(pugi::xml_node& parent_node, std::string name, TVec4 color)
{
	xml_node new_node = parent_node.append_child(name.c_str());
	new_node.append_attribute("r").set_value(color[0]);
	new_node.append_attribute("g").set_value(color[1]);
	new_node.append_attribute("b").set_value(color[2]);
	new_node.append_attribute("a").set_value(color[3]);
}

TVec4 LoadColor(pugi::xml_node& node)
{
	TVec4 color;
	color[0] = node.attribute("r").as_float();
	color[1] = node.attribute("g").as_float();
	color[2] = node.attribute("b").as_float();
	color[3] = node.attribute("a").as_float();
	return color;
}

void SaveCoord(pugi::xml_node& parent_node, std::string name, TVec2 coord)
{
	xml_node new_node = parent_node.append_child(name.c_str());
	new_node.append_attribute("x").set_value(coord[0]);
	new_node.append_attribute("y").set_value(coord[1]);
}

TVec2 LoadCoord(pugi::xml_node& node)
{
	TVec2 coord;
	coord[0] = node.attribute("x").as_float();
	coord[1] = node.attribute("y").as_float();
	return coord;
}

void SaveTransform(pugi::xml_node& parent_node, std::string name, TBaluTransform transform)
{
	xml_node new_node = parent_node.append_child(name.c_str());
	SaveCoord(new_node, "Offset", transform.position);
	new_node.append_attribute("rotation").set_value(transform.angle.GetAngle());
}

TBaluTransform LoadTransform(pugi::xml_node& node)
{
	TBaluTransform transform;
	transform.position = LoadCoord(node.child("Offset"));
	transform.angle.Set(node.attribute("rotation").as_float());
	return transform;
}

void TBaluMaterial::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Material");
	new_node.append_attribute("name").set_value(material_name.c_str());
	new_node.append_attribute("image_path").set_value(image_path.c_str());
	SaveColor(new_node, "color", color);
}

void TBaluMaterial::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	material_name = node.attribute("name").as_string();
	image_path = node.attribute("image_path").as_string();
	color = LoadColor(node.child("color"));
}

void TBaluBoxShape::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("CircleShape");
	{
		new_node.append_attribute("radius").set_value(b2shape.m_radius);
		SaveTransform(new_node, "Transform", local);
	}
}

void TBaluBoxShape::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	float radius = node.attribute("radius").as_float();
	TVec2 pos = LoadCoord(node.child("position"));
	local = LoadTransform(node.child("Transform"));
	b2shape.m_radius = radius;
}


void TBaluCircleShape::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("CircleShape");
	{
		new_node.append_attribute("radius").set_value(b2shape.m_radius);
		SaveTransform(new_node, "Transform", local);
	}
}

void TBaluCircleShape::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	float radius = node.attribute("radius").as_float();
	TVec2 pos = LoadCoord(node.child("position"));
	local = LoadTransform(node.child("Transform"));
	b2shape.m_radius = radius;
}


void TBaluPolygonShape::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("PolygoneShape");
	{
		xml_node polygons_node = new_node.append_child("polygon_vertex");
		for (int i = 0; i < b2shape.GetVertexCount(); i++)
		{
			SaveCoord(polygons_node, "vertex", *(TVec2*)(&b2shape.GetVertex(i)));
		}
		SaveTransform(new_node, "Transform", local);
	}
}

void TBaluPolygonShape::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	xml_node polygons_node = node.child("polygon_vertex");
	std::vector<TVec2> vertices;
	for (pugi::xml_node polygon_node = polygons_node.first_child(); polygon_node; polygon_node = polygon_node.next_sibling())
	{
		vertices.push_back(LoadCoord(polygon_node));
	}
	b2shape.Set((b2Vec2*)&vertices[0], vertices.size());
	local = LoadTransform(node.child("Transform"));
}

void TBaluSpritePolygon::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("SpritePolygon");
	if (material != nullptr)
		new_node.append_attribute("material_name").set_value(material->GetName().c_str());

	SaveTransform(new_node, "Transform", local);

	{
		xml_node polygons_node = new_node.append_child("polygon_vertices");
		for (const TVec2& v : polygon_vertices)
		{
			SaveCoord(polygons_node, "vertex", v);
		}
	}
	{
		xml_node polygons_node = new_node.append_child("tex_coordinates");
		for (const TVec2& v : tex_coordinates)
		{
			SaveCoord(polygons_node, "vertex", v);
		}
	}
}

void TBaluSpritePolygon::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	material = world->GetMaterial(node.attribute("material_name").as_string());

	local = LoadTransform(node.child("Transform"));

	{
		xml_node polygons_node = node.child("polygon_vertices");
		for (pugi::xml_node polygon = polygons_node.first_child(); polygon; polygon = polygon.next_sibling())
		{
			polygon_vertices.push_back(LoadCoord(polygon));
		}
	}
	{
		xml_node polygons_node = node.child("tex_coordinates");
		for (pugi::xml_node polygon = polygons_node.first_child(); polygon; polygon = polygon.next_sibling())
		{
			tex_coordinates.push_back(LoadCoord(polygon));
		}
	}
}

void TBaluSprite::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Sprite");
	new_node.append_attribute("name").set_value(sprite_name.c_str());
	xml_node polygon_node = new_node.append_child("sprite_polygon");
	sprite_polygon.Save(polygon_node, version);
}

void TBaluSprite::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	sprite_name = node.attribute("name").as_string();
	xml_node polygon_node = node.child("sprite_polygon");
	sprite_polygon.Load(polygon_node, version, world);

	xml_node fixture = node.child("phys_shape");
	TBaluPhysShape* new_shape = nullptr;
	if (std::string(fixture.name()) == "PolygoneShape")
		new_shape = new TBaluPolygonShape();
	if (std::string(fixture.name()) == "CircleShape")
		new_shape = new TBaluCircleShape();
	if (std::string(fixture.name()) == "BoxShape")
		new_shape = new TBaluBoxShape();
	new_shape->Load(fixture, version, world);
	phys_shape.reset(new_shape);
}

void TBaluClass::TBaluSpriteInstance::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node sprite_node = parent_node.append_child("sprite");
	sprite_node.append_attribute("sprite_name").set_value(sprite->GetName().c_str());
	sprite_node.append_attribute("sprite_tag").set_value(tag.c_str());
	SaveTransform(sprite_node, "Transform", local);
}

void TBaluClass::TBaluSpriteInstance::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	sprite = world->GetSprite(node.attribute("sprite_name").as_string());
	tag = node.attribute("sprite_tag").as_string();
	local = LoadTransform(node.child("Transform"));
}

void TBaluClass::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Class");
	new_node.append_attribute("class_name").set_value(class_name.c_str());
	{
		xml_node sprites_node = new_node.append_child("sprites");
		for (int i = 0; i < sprites.size(); i++)
		{
			sprites[i]->Save(sprites_node, version);
		}
	}
}

void TBaluClass::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	class_name = node.attribute("class_name").as_string();
	{
		xml_node sprites_node = node.child("sprites");
		for (pugi::xml_node sprite_node = sprites_node.first_child(); sprite_node; sprite_node = sprite_node.next_sibling())
		{
			TBaluSpriteInstance* new_sprite_instance = new TBaluSpriteInstance();
			new_sprite_instance->Load(sprite_node, version, world);
			sprites.push_back(std::unique_ptr<TBaluSpriteInstance>(new_sprite_instance));
		}
	}
}

void TBaluScene::TClassInstance::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Instance");
	//new_node.append_attribute("name").set_value(name.c_str());
	new_node.append_attribute("class_name").set_value(balu_class->GetName().c_str());
	SaveTransform(new_node, "Transform", transform);
}

void TBaluScene::TClassInstance::Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)
{
	//name = instance_node.attribute("name").as_string();
	balu_class = world->GetClass(instance_node.attribute("class_name").as_string());
	transform = LoadTransform(instance_node.child("Transform"));
}

void TBaluScene::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Scene");
	new_node.append_attribute("name").set_value(scene_name.c_str());
	{
		xml_node instances_node = new_node.append_child("instances");
		for (int i = 0; i < instances.size(); i++)
		{
			instances[i]->Save(instances_node, version);
		}
	}
}

void TBaluScene::Load(const pugi::xml_node& scene_node, const int version, TBaluWorld* world)
{
	scene_name = scene_node.attribute("name").as_string();
	{
		xml_node instances_node = scene_node.child("instances");
		for (pugi::xml_node instance_node = instances_node.first_child(); instance_node; instance_node = instance_node.next_sibling())
		{
			TBaluScene::TClassInstance* new_instance = new TBaluScene::TClassInstance();
			new_instance->Load(instance_node, version, world);
			instances.push_back(std::unique_ptr<TBaluScene::TClassInstance>(new_instance));
		}
	}
}

void TBaluWorld::SaveToXML(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("World");
	{
		xml_node materials_node = new_node.append_child("Materials");
		for (auto i = materials.begin(); i != materials.end(); i++)
		{
			i->second.Save(materials_node, version);
		}
	}
	{
		xml_node sprites_node = new_node.append_child("Sprites");
		for (auto i = sprites.begin(); i != sprites.end(); i++)
		{
			i->second.Save(sprites_node, version);
		}
	}
	{
		xml_node classes_node = new_node.append_child("Classes");
		for (auto i = classes.begin(); i != classes.end(); i++)
		{
			i->second.Save(classes_node, version);
		}
	}
	{
		xml_node scenes_node = new_node.append_child("Scenes");
		for (auto i = scenes.begin(); i != scenes.end(); i++)
		{
			i->second.Save(scenes_node, version);
		}
	}
}

void TBaluWorld::LoadFromXML(const pugi::xml_node& document_node, const int version)
{
	//TODO добавить во все классы недостающие свойства
	xml_node world_node = document_node.child("World");
	{
		xml_node materials_node = world_node.child("Materials");
		for (pugi::xml_node material = materials_node.first_child(); material; material = material.next_sibling())
		{
			TBaluMaterial new_material;
			new_material.Load(material, version, this);
			materials[new_material.GetName()] = new_material;
		}
	}
	{
		xml_node sprites_node = world_node.child("Sprites");
		for (pugi::xml_node sprite_node = sprites_node.first_child(); sprite_node; sprite_node = sprite_node.next_sibling())
		{
			TBaluSprite new_sprite;
			new_sprite.Load(sprite_node, version, this);
			//sprites.insert(std::make_pair(new_sprite.GetName(), std::move(new_sprite)));
		}
	}
	{
		xml_node classes_node = world_node.child("Classes");
		for (pugi::xml_node class_node = classes_node.first_child(); class_node; class_node = class_node.next_sibling())
		{
			TBaluClass new_class;
			new_class.Load(class_node, version, this);
			classes.insert(std::make_pair(new_class.GetName(), std::move(new_class)));
		}
	}
	{
		xml_node scenes_node = world_node.child("Scenes");
		for (pugi::xml_node scene_node = scenes_node.first_child(); scene_node; scene_node = scene_node.next_sibling())
		{
			TBaluScene new_scene;
			new_scene.Load(scene_node, version, this);
			//scenes.insert(std::make_pair(new_scene.GetName(), std::move(new_scene)));
		}
	}
}