#pragma once

#include "MaterialInstance.h"

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