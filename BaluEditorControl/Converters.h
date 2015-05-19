#pragma once

#include <string>

namespace Converters
{
	using namespace System;

	String^ ToClrString(std::string value);
	std::string FromClrString(String^ value);
}