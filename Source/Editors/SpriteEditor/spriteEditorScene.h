#pragma once

#include <vector>
#include <memory>

class TSpriteEditorScene
{
public:
	TBaluSpriteDef* sprite;

	void Initialize(TBaluSpriteDef* sprite)
	{
		this->sprite = sprite;
	}
	std::vector<std::unique_ptr<TBoundaryBoxAdornment>> boundaries;
};