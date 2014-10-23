#pragma once

#include <vector>
#include <memory>

class TClassEditorScene : public TBoundaryBoxScene
{
public:
	TBaluClass* balu_class;

	void Initialize(TBaluClass* balu_class)
	{
		this->balu_class = balu_class;
	}
};