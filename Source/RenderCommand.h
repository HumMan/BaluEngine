#pragma once

#include "MaterialId.h"

class TRenderCommand
{
	MaterialId material_id;
	
	TVec2* vertices;
	TVec2* tex_coords;
	TVec4* colors;
	int* indices;
public:
	
}