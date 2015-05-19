#include "Converters.h"

//#include <vcclr.h>
#include <msclr\marshal_cppstd.h>

namespace Converters
{

	String^ ToClrString(std::string value)
	{
		return gcnew String(value.c_str());
	}
	std::string FromClrString(String^ value)
	{
		return msclr::interop::marshal_as<std::string>(value);
	}
}