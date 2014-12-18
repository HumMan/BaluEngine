#pragma once

#include <vector>
#include <memory>

class TBoundaryBoxWithJointsScene : public TBoundaryBoxScene
{
public:
	std::vector<std::unique_ptr<TJointAdornment>> joints;
};

class TPhysBodyEditorScene : public TBoundaryBoxWithJointsScene
{
public:
	TBaluPhysBodyDef* phys_body;

	void Initialize(TBaluPhysBodyDef* phys_body)
	{
		this->phys_body = phys_body;
	}
	
};