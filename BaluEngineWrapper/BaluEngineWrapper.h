// BaluEngineWrapper.h

#pragma once

using namespace System;

namespace EngineInterface
{
	class IBaluSprite;
}

namespace BaluEngineWrapper
{
	public ref class IBaluSprite
	{
	private:
		EngineInterface::IBaluSprite* balu_sprite;
		IBaluSprite(EngineInterface::IBaluSprite* balu_sprite);
	public:
		String^ GetName();
		void SetName(String^ name);
	};
}
