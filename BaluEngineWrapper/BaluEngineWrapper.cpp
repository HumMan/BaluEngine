// This is the main DLL file.

#include "stdafx.h"

#include "BaluEngineWrapper.h"

namespace BaluEngineWrapper
{
	IBaluSprite::IBaluSprite(EngineInterface::IBaluSprite* balu_sprite)
	{
		this->balu_sprite = balu_sprite;
	}
	String^ IBaluSprite::GetName()
	{
		return gcnew String("test");
	}
	void IBaluSprite::SetName(String^ name)
	{
	}
}

