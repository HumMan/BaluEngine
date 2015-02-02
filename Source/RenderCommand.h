#pragma once

#include "../../BaluLib/Source/Math/vec.h"

class TMaterialInstance;

struct TRenderCommand
{
public:
	TMaterialInstance* material_id;
	
	int vertices_count;
	TVec2* vertices;
	TVec2* tex_coords;
	TVec4* colors;
	//int indices_count;
	//int* indices;

	TRenderCommand(){}

	TRenderCommand(TMaterialInstance* material_id, int vertices_count, TVec2* vertices, TVec2* tex_coords, TVec4* colors)//, int indices_count, int* indices)
	{
		this->material_id = material_id;
		this->vertices_count = vertices_count;
		this->vertices = vertices;
		this->tex_coords = tex_coords;
		this->colors = colors;
		//this->indices_count = indices_count;
		//this->indices = indices;
	}
};

class NVGcontext;

namespace EngineInterface
{
	class IBaluSpritePolygonInstance;
}

typedef void(*TCustomDrawCallback)(EngineInterface::IBaluSpritePolygonInstance* instance, NVGcontext* vg, void* user_data);

template<class T>
class CallbackWithData
{
public:
	T callback;
	void* user_data;
	CallbackWithData(){}
	CallbackWithData(T callback, void* user_data)
	{
		this->callback = callback;
		this->user_data = user_data;
	}
	CallbackWithData(T callback)
	{
		this->callback = callback;
		this->user_data = nullptr;
	}
};

//TODO в дальнейшем вся информация для рендера должна находиться полностью здесь, для возможности параллельной отрисовки

struct TCustomDrawCommand
{
public:
	EngineInterface::IBaluSpritePolygonInstance* poly;
	CallbackWithData<TCustomDrawCallback> command;
};