#include "Properties.h"

#include "../Common/SerializeCommon.h"

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;

#include <pugixml.hpp>

using namespace pugi;

TProperties::TProperties()
{
}

bool TProperties::HasProperty(const std::string & name, PropertyType & type)const
{
	auto prop = GetProperty(name);
	if (prop == nullptr)
		return false;
	else
	{
		type = prop->GetType();
		return true;
	}
}

IProperty * TProperties::GetProperty(const std::string & name)const
{
	auto it = properties.find(name);
	if (it == properties.end())
	{
		return nullptr;
	}
	auto ptr = it->second.get();
	if (ptr == nullptr)
		return nullptr;
	else
		return ptr;
}

void TProperties::SaveProperties(pugi::xml_node& parent_node, const int version)const
{
	xml_node props_node = parent_node.append_child("Properties");
	for (auto& v : properties)
	{
		v.second->Save(props_node, version);
		props_node.last_child().append_attribute("name").set_value(v.first.c_str());
	}
}

void TProperties::LoadProperties(const pugi::xml_node& instance_node, const int version)
{
	xml_node props_node = instance_node.child("Properties");
	for (pugi::xml_node prop_node = props_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
	{
		auto name = prop_node.attribute("name").as_string();
		GetProperty(name)->Load(prop_node, version);
	}
}

void TProperty::Save(pugi::xml_node& parent_node, const int version)const
{
	xml_node node = parent_node.append_child("Property");
	auto val = node.append_attribute("value");
	switch (this->type)
	{
	case BaluEngine::WorldDef::PropertyType::Bool:
		val.set_value(*(bool*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::Int:
		val.set_value(*(int*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::Number:
		val.set_value(*(size_t*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::Float:
		val.set_value(*(float*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::String:
	case BaluEngine::WorldDef::PropertyType::ImagePath:
		val.set_value(((std::string*)value)->c_str());
		break;
	case BaluEngine::WorldDef::PropertyType::Color:
		SerializeCommon::SaveColor(node, *(BaluLib::TVec4*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::ColorWithAlpha:
		SerializeCommon::SaveColor(node, *(BaluLib::TVec4*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::TransparentMode:
		val.set_value(*(int*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::AlphaTestFunc:
		val.set_value(*(int*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::BlendFunc:
		val.set_value(*(int*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::BlendEquation:
		val.set_value(*(int*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::TexFilter:
		val.set_value(*(int*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::TexClamp:
		val.set_value(*(int*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::Size:
		SerializeCommon::SaveCoord(node, "Size", *(BaluLib::TVec2*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::TransformWithScale:
		SerializeCommon::SaveTransformWithScale(node, "TransformWithScale", *(TTransformWithScale*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::Transform:
		SerializeCommon::SaveTransform(node, "Transform", *(TTransform*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::Scale:
		SerializeCommon::SaveCoord(node, "Scale", *(BaluLib::TVec2*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::Pos:
		SerializeCommon::SaveCoord(node, "Pos", *(BaluLib::TVec2*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::Rotation:
		SerializeCommon::SaveRotation(node, "Rot", *(TRot*)value);
		break;
	case BaluEngine::WorldDef::PropertyType::PhysBodyType:
		val.set_value(*(int*)value);
		break;
	//case BaluEngine::WorldDef::PropertyType::PhysShapeType:
	//	val.set_value(*(int*)value);
	//	break;
	default:
		assert(false);
		break;
	}
}

void TProperty::Load(const pugi::xml_node& prop_node, const int version)
{
	auto val = prop_node.attribute("value");
	switch (this->type)
	{
	case BaluEngine::WorldDef::PropertyType::Bool:
		*(bool*)value = val.as_bool();
		break;
	case BaluEngine::WorldDef::PropertyType::Int:
		*(int*)value = val.as_int();
		break;
	case BaluEngine::WorldDef::PropertyType::Number:
		*(size_t*)value = val.as_uint();
		break;
	case BaluEngine::WorldDef::PropertyType::Float:
		*(float*)value = val.as_float();
		break;
	case BaluEngine::WorldDef::PropertyType::String:
	case BaluEngine::WorldDef::PropertyType::ImagePath:
		*(std::string*)value = val.as_string();
		break;
	case BaluEngine::WorldDef::PropertyType::Color:
		*(BaluLib::TVec4*)value = SerializeCommon::LoadColor(prop_node);
		break;
	case BaluEngine::WorldDef::PropertyType::ColorWithAlpha:
		*(BaluLib::TVec4*)value = SerializeCommon::LoadColor(prop_node);
		break;
	case BaluEngine::WorldDef::PropertyType::TransparentMode:
		*(int*)value = val.as_int();
		break;
	case BaluEngine::WorldDef::PropertyType::AlphaTestFunc:
		*(int*)value = val.as_int();
		break;
	case BaluEngine::WorldDef::PropertyType::BlendFunc:
		*(int*)value = val.as_int();
		break;
	case BaluEngine::WorldDef::PropertyType::BlendEquation:
		*(int*)value = val.as_int();
		break;
	case BaluEngine::WorldDef::PropertyType::TexFilter:
		*(int*)value = val.as_int();
		break;
	case BaluEngine::WorldDef::PropertyType::TexClamp:
		*(int*)value = val.as_int();
		break;
	case BaluEngine::WorldDef::PropertyType::Size:
		*(BaluLib::TVec2*)value = SerializeCommon::LoadCoord(prop_node.child("Size"));
		break;
	case BaluEngine::WorldDef::PropertyType::TransformWithScale:
		*(TTransformWithScale*)value = SerializeCommon::LoadTransformWithScale(prop_node.child("TransformWithScale"));
		break;
	case BaluEngine::WorldDef::PropertyType::Transform:
		*(TTransform*)value = SerializeCommon::LoadTransform(prop_node.child("Transform"));
		break;
	case BaluEngine::WorldDef::PropertyType::Scale:
		*(BaluLib::TVec2*)value = SerializeCommon::LoadCoord(prop_node.child("Scale"));
		break;
	case BaluEngine::WorldDef::PropertyType::Pos:
		*(BaluLib::TVec2*)value = SerializeCommon::LoadCoord(prop_node.child("Pos"));
		break;
	case BaluEngine::WorldDef::PropertyType::Rotation:
		*(TRot*)value = SerializeCommon::LoadRotation(prop_node.child("Rot"));
		break;
	case BaluEngine::WorldDef::PropertyType::PhysBodyType:
		*(int*)value = val.as_int();
		break;
	//case BaluEngine::WorldDef::PropertyType::PhysShapeType:
	//	*(int*)value = val.as_int();
	//	break;
	default:
		assert(false);
		break;
	}
}

TProperties::~TProperties()
{

}