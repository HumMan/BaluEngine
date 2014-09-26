#pragma once

#include <vector>
#include <memory>

class TPhysBodyEditorScene
{
public:
	TBaluPhysBodyDef* phys_body;

	void Initialize(TBaluPhysBodyDef* phys_body)
	{
		this->phys_body = phys_body;
	}
	std::vector<std::unique_ptr<TBoundaryBoxAdornment>> boundaries;
	std::vector<std::unique_ptr<TJointAdornment>> joints;
};