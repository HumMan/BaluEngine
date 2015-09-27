#include "Converters.h"

//#include <vcclr.h>
#include <msclr\marshal_cppstd.h>

#include "../Source/EditorUtils/IAbstractEditor.h"

namespace Converters
{

	String^ ToClrString(std::string value)
	{
		return gcnew String(EngineInterface::as_wide(value).c_str());
	}
	std::string FromClrString(String^ value)
	{
		return EngineInterface::as_utf8(msclr::interop::marshal_as<std::wstring>(value));
	}
}