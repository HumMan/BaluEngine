#pragma once

#include <vector>
#include <memory>

class TMaterialEditorScene
{
public:
	TBaluMaterialDef* material;

	TOBB<float, 2> preview_boundary;

	void Initialize(TBaluMaterialDef* material)
	{
		this->material = material;
		preview_boundary = TOBB<float, 2>(TVec2(0, 0), TMatrix2::GetIdentity(), TAABB<float,2>(TVec2(0,0),TVec2(1, 1)));
	}
};