#pragma once

#include <vector>
#include <memory>

class TSpriteEditorScene : public TBoundaryBoxScene
{
public:
	TBaluSpriteDef* sprite;

	void Initialize(TBaluSpriteDef* sprite)
	{
		this->sprite = sprite;
	}
};