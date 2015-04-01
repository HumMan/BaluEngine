
#include <string>
#include <vector>

#include <assert.h>

#include <fstream>
#include <string>
#include <iostream>

struct TParamType
{
	const char* macro_id_letter;
	const char* wrap_class;
	TParamType()
	{
		macro_id_letter = nullptr;
		wrap_class = nullptr;
	}
	TParamType(const char* _macro_id_letter,	const char* _wrap_class)
		:macro_id_letter(_macro_id_letter), wrap_class(_wrap_class)
	{
	}
};

const int all_params_count = 2;
TParamType all_params[all_params_count] =
{
	TParamType("p","WrapPointer"),
	TParamType("v", "WrapValue")
};

std::string IntToStr(int i)
{
	char buf[100];
	sprintf_s(buf, "%i", i);
	return buf;
}

std::string GenerateMacro(std::vector<TParamType> params)
{
	std::string result;
	result += "#define MUnpackRp";
	for (auto& v : params)
	{
		result += v.macro_id_letter;
	}
	result+="(ret_type, interface_type, method_name \\\n";
	int i = 0;
	for (auto& v : params)
	{
		result += ", param" + IntToStr(i) +"_type\\\n";
		i++;
	}
	result += ")\\\n";
	result += "methods.push_back(SetName(#method_name, new ";
	result += "UnpackRA" + IntToStr(params.size());
	result+= "<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\\\n";
	i = 0;
	for (auto& v : params)
	{
		std::string param_type = "param" + IntToStr(i) + "_type";
		result += std::string(", ")+v.wrap_class+"<"+param_type+">, "+param_type + "\\\n";
		i++;
	}
	result += ", &interface_type::method_name>));\n";

	return result;
}

enum TIncrementResult
{
	INCREMENT_OK = 0,
	INCREMENT_OVERFLOW = 1
};

TIncrementResult Increment(std::vector<int>& param_types_ids)
{
	if (param_types_ids.size()==0)
		return INCREMENT_OVERFLOW;
	bool carry = false;
	for (int i = 0; i < param_types_ids.size();i++)
	{
		if (carry)
		{
			
			if (param_types_ids[i] == all_params_count - 1)
			{
				if (i == param_types_ids.size() - 1)
					return INCREMENT_OVERFLOW;
				else
					param_types_ids[i] = 0;
			}
			else
			{
				param_types_ids[i] += 1;
				return INCREMENT_OK;
			}
		}
		else
		{
			if (param_types_ids[i] == all_params_count - 1)
			{
				if (i == param_types_ids.size() - 1)
					return INCREMENT_OVERFLOW;
				else
					param_types_ids[i] = 0;
				carry = true;
			}
			else
			{
				param_types_ids[i] += 1;
				return INCREMENT_OK;
			}
		}
	}
	assert(false);
}

std::vector<TParamType> Convert(std::vector<int> param_types_ids)
{
	std::vector<TParamType> result;
	result.resize(param_types_ids.size());
	for (int i = 0; i < param_types_ids.size(); i++)
	{
		result[i] = all_params[param_types_ids[i]];
	}
	return result;
}

std::string GenerateMacro(int params_count)
{
	std::vector<int> param_types_ids;
	param_types_ids.resize(params_count);
	for (auto& v : param_types_ids)
		v = 0;

	std::string result;
	do
	{
		result += GenerateMacro(Convert(param_types_ids));
		result += "\n";
	} while (Increment(param_types_ids) != INCREMENT_OVERFLOW);

	return result;
}

std::string GetScriptFunc(int params_count, bool have_result)
{
	std::string result;
	if (params_count > 0)
	{
		result += "func %s(";
		for (int i = 0; i < params_count; i++)
		{
			result += "%s a" + IntToStr(i) + ((i < params_count - 1) ? ", " : "");
		}
		if (have_result)
			result += "):%s;";
		else
			result += ";";
	}
	else
	{
		if (have_result)
			result += "func %s:%s;";
		else
			result += "func %s;";
	}
	return result;
}

std::string GenerateTemplateClass(int params_count)
{
	std::string result;
	result += "template<class Tresult_type, class TCppResult, class Tobject_type\n";
	for (int i = 0; i < params_count;i++)
	{
		result += ", class Ta" + IntToStr(i) + ", class Ta" + IntToStr(i) + "_cpp\n";
	}
	result += " , TCppResult(Tobject_type::Arg::*CppMethod)(";
	for (int i = 0; i < params_count; i++)
	{
		result += "Ta" + IntToStr(i) + "_cpp" + ((i < params_count - 1) ? ", " : "");
	}
	result+= ")>\n";
	result += "class UnpackRA" + IntToStr(params_count) + " : public Unpacker\n{\n";
	result +=
		"public:\n"
		"	std::string GetSyntax()\n"
		"	{\n"
		"		char buf[255];\n";
	result += "			sprintf_s(buf, \"" + GetScriptFunc(params_count, true) + "\", func_name\n";
	for (int i = 0; i < params_count; i++)
	{
		result += "			, CppTypeToScript<Ta" + IntToStr(i) + "::Arg>::Get()\n";
	}
	result +=
		"			, CppTypeToScript<Tresult_type::Arg>::Get()\n"
		"		);\n"
		"		return buf;\n"
		"	}\n"
		"	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)\n"
		"	{\n";
	result +=
		"		result.get_as<Tresult_type>() = Tresult_type(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)\n"
		"		(\n";
	for (int i = 0; i < params_count; i++)
	{
		result += "			formal_params[" + IntToStr(i) + "].get_as<Ta" + IntToStr(i) + ">().GetCppValue()"
			+ ((i < params_count - 1) ? ", \n" : "\n");;
	}
	result +=
		"		));\n"
		"	}\n"
		"	TExternalSMethod GetUnpackMethod()\n"
		"	{"
		"		return Run;\n"
		"	}\n"
		"};\n\n";
	return result;
}



int main()
{
	std::string result;
	result += "#pragma once\n\n";
	for (int i = 0; i <= 5; i++)
	{
		result += GenerateMacro(i);
		result += "\n";
		result += GenerateTemplateClass(i);
		result += "\n";
	}

	std::ofstream out("UnpackTemplates.h");
	out << result;
	out.close();

	return 0;
}