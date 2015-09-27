#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include <EngineInterfaces/Common.h>
#endif
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluMaterial
	{
	public:
		static std::string GetDefaultName()
		{
			return "material";
		}
		virtual std::string GetName() = 0;
		virtual void SetImagePath(std::string image_path) = 0;
		virtual std::string GetImagePath() = 0;
		virtual void SetColor(TVec4 color) = 0;
	};
#endif

}

