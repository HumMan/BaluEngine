#pragma once

namespace BaluEngine
{
	namespace WorldDef
	{
		class IFrame
		{

		};

		class IAnimDesc : public ISerializable
		{
		public:
			virtual IFrame* GetFrame(int index) = 0;
		};

	}
}
