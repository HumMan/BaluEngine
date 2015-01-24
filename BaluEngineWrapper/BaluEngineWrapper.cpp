// This is the main DLL file.

#include "stdafx.h"

#include "BaluEngineWrapper.h"

#include "../Source/EngineInterfaces.h"

namespace BaluEngineWrapper
{
	IBaluSprite::IBaluSprite(EngineInterface::IBaluSprite* balu_sprite)
	{
		this->balu_sprite = balu_sprite;
	}
	String^ IBaluSprite::GetName()
	{
		return gcnew String(balu_sprite->GetName().c_str());
	}
	void IBaluSprite::SetName(String^ name)
	{
		balu_sprite->SetName(msclr::interop::marshal_as<std::string>(name));
	}
}

