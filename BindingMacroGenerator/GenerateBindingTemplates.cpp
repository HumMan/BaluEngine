

#include <string>
#include <vector>

#include <assert.h>

#include <fstream>
#include <string>
#include <iostream>

struct TParamType
{
	const char* macro_id_letter;
	const char* wrapper;
	const char* interface_wrap;
	TParamType()
	{
		macro_id_letter = nullptr;
		wrapper = nullptr;
	}
	TParamType(const char* _macro_id_letter, const char* _wrapper, const char* _interface_wrap)
		:macro_id_letter(_macro_id_letter), wrapper(_wrapper), interface_wrap(_interface_wrap)
	{
	}
};

const int all_params_count = 2;
TParamType all_params[all_params_count] =
{
	TParamType("p","WrapPointer", "WrapInterface"),
	TParamType("v", "WrapValue", "WrapValue")
};

std::string IntToStr(int i)
{
	char buf[100];
	sprintf_s(buf, "%i", i);
	return buf;
}

std::string GenerateUnpackShortMacro(std::vector<TParamType> params)
{
	std::string result;
	result += "#define MUnpackRp";
	for (auto& v : params)
	{
		result += v.macro_id_letter;
	}
	result+="(ret_type, interface_type, method_name ";
	int i = 0;
	for (auto& v : params)
	{
		result += ", param" + IntToStr(i) +"_type";
		i++;
	}
	result += ")\\\n";

	bool use_macro = true;
	if (use_macro)
	{
		result += "MUnpackRA" + IntToStr(params.size());
		result += "(ret_type, interface_type, method_name ";

		i = 0;
		for (auto& v : params)
		{
			std::string param_type = "param" + IntToStr(i) + "_type";
			result += std::string(", ") + v.wrapper + ", " + param_type;
			i++;
		}
		result += ");\n";
	}
	else
	{
		result += "methods.push_back(SetName(#method_name, new ";
		result += "UnpackRA" + IntToStr(params.size());
		result += "<WrapPointer<ret_type>, ret_type*, WrapInterface<interface_type>\\\n";
		i = 0;
		for (auto& v : params)
		{
			std::string param_type = "param" + IntToStr(i) + "_type";
			result += std::string(", ") + v.wrapper + "<" + param_type + ">, " + param_type + "\\\n";
			i++;
		}
		result += ", &interface_type::method_name>));\n";

	}
	return result;
}

std::string GenerateUnpackConstructorMacro(int params_count)
{
	std::string result;

	result += std::string("#define MUnpackConstr") +
		"A" + IntToStr(params_count);

	result += "(interface_wrapper,  method_name \\\n";

	for (int i = 0; i < params_count; i++)
	{
		result += ", param" + IntToStr(i) + "_wrapper\\\n";
	}
	result += ")\\\n";
	result += "methods.push_back(SetAsConstructor(new ";

	result += std::string("UnpackConstructor") +
		"A" + IntToStr(params_count);


	result += "<interface_wrapper\\\n";

	for (int i = 0; i < params_count; i++)
	{
		std::string param_wrapper = "param" + IntToStr(i) + "_wrapper";
		result += std::string(", ") + param_wrapper + ", " + param_wrapper + "::PassInMethodAs\\\n";
	}
	result += ">));\n";

	return result;
}

std::string GenerateUnpackMacro(int params_count, bool have_result, bool const_method)
{
	std::string result;

	result += std::string("#define MUnpack") +
		(const_method ? "C" : "") +
		(have_result ? "R" : "") +
		"A" + IntToStr(params_count);

	if (have_result)
	{	
		result += "(ret_wrapper, interface_wrapper, method_name \\\n";
	}
	else
	{
		result += "(interface_wrapper,  method_name \\\n";
	}
	
	for (int i = 0; i < params_count;i++)
	{
		result += ", param" + IntToStr(i) + "_wrapper\\\n";
	}
	result += ")\\\n";
	result += "methods.push_back(SetName(#method_name, new ";

	result += std::string("Unpack") +
		(const_method ? "C" : "") +
		(have_result ? "R" : "") +
		"A" + IntToStr(params_count);

	if (have_result)
	{	
		result += "<ret_wrapper, ret_wrapper::PassInMethodAs, interface_wrapper\\\n";
	}
	else
	{
		result += "<interface_wrapper\\\n";
	}
	
	for (int i = 0; i < params_count; i++)
	{
		std::string param_wrapper = "param" + IntToStr(i) + "_wrapper";
		result += std::string(", ") + param_wrapper + ", " + param_wrapper + "::PassInMethodAs\\\n";
	}
	result += ", &interface_wrapper::InterfaceType::method_name>));\n";

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

	result += GenerateUnpackConstructorMacro(params_count);
	result += GenerateUnpackMacro(params_count, true, false);
	result += GenerateUnpackMacro(params_count, false, false);
	result += GenerateUnpackMacro(params_count, true, true);
	result += GenerateUnpackMacro(params_count, false, true);

	result += "\n";

	bool generate_short_macros = false;

	if (generate_short_macros)
	{
		do
		{
			result += GenerateUnpackShortMacro(Convert(param_types_ids));
			result += "\n";
		} while (Increment(param_types_ids) != INCREMENT_OVERFLOW);
	}
	return result;
}

std::string GetScriptConstrFunc(int params_count)
{
	std::string result;
	if (params_count > 0)
	{
		result += "copy(";
		for (int i = 0; i < params_count; i++)
		{
			result += "%s a" + IntToStr(i) + ((i < params_count - 1) ? ", " : "");
		}
		result += ");";
	}
	else
	{
		result += "default;";
	}
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
			result += ");";
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


std::string GenerateTemplateConstructorClass(int params_count)
{
	std::string result;

	result += "template<class Tobject_type\n";
	for (int i = 0; i < params_count; i++)
	{
		result += ", class Ta" + IntToStr(i) + ", class Ta" + IntToStr(i) + "_cpp\n";
	}
	
	result += ">\n";

	result += std::string("class UnpackConstructorA") +	IntToStr(params_count) + " : public Unpacker\n{\n";

	result +=
		"public:\n"
		"	std::string GetSyntax()\n"
		"	{\n"
		"		char buf[255];\n";
	result += "			sprintf_s(buf, \"" + GetScriptConstrFunc(params_count) + "\"\n";
	for (int i = 0; i < params_count; i++)
	{
		result += "			, EngineInterface::CppTypeToScript<Ta" + IntToStr(i) + "::TypeForGetName>::Get()\n";
	}
	result +=
		"		);\n"
		"		return buf;\n"
		"	}\n"
		"	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)\n"
		"	{\n";

		result +=
			"		(new (&object.get_as<Tobject_type>().GetCppValue())Tobject_type::InterfaceType\n"
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

std::string GenerateTemplateClass(int params_count, bool have_return, bool const_method)
{
	std::string result;
	if (have_return)
		result += "template<class Tresult_type, class TCppResult, class Tobject_type\n";
	else
		result += "template<class Tobject_type\n";
	for (int i = 0; i < params_count;i++)
	{
		result += ", class Ta" + IntToStr(i) + ", class Ta" + IntToStr(i) + "_cpp\n";
	}
	if (have_return)
		result += " , TCppResult(Tobject_type::InterfaceType::*CppMethod)(";
	else
		result += " , void(Tobject_type::InterfaceType::*CppMethod)(";
	for (int i = 0; i < params_count; i++)
	{
		result += "Ta" + IntToStr(i) + "_cpp" + ((i < params_count - 1) ? ", " : "");
	}
	if (const_method)
		result += ")const>\n";
	else
		result+= ")>\n";

	result += std::string("class Unpack")+
		(const_method?"C":"")+
		(have_return ? "R" : "") +
		"A" + IntToStr(params_count) + " : public Unpacker\n{\n";

	result +=
		"public:\n"
		"	std::string GetSyntax()\n"
		"	{\n"
		"		char buf[255];\n";
	result += "			sprintf_s(buf, \"" + GetScriptFunc(params_count, have_return) + "\", func_name\n";
	for (int i = 0; i < params_count; i++)
	{
		result += "			, EngineInterface::CppTypeToScript<Ta" + IntToStr(i) + "::TypeForGetName>::Get()\n";
	}
	if (have_return)
		result +=
			"			, EngineInterface::CppTypeToScript<Tresult_type::TypeForGetName>::Get()\n";
	result+=
		"		);\n"
		"		return buf;\n"
		"	}\n"
		"	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)\n"
		"	{\n";
	if (have_return)
	{
		result +=
			"		result.get_as<Tresult_type>() = Tresult_type(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)\n"
			"		(\n";
	}
	else
	{
		result +=
			"		(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)\n"
			"		(\n";
	}
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
		result += GenerateTemplateConstructorClass(i);
		result += GenerateTemplateClass(i, true, false);
		result += GenerateTemplateClass(i, false, false);
		result += GenerateTemplateClass(i, true, true);
		result += GenerateTemplateClass(i, false, true);
		result += "\n";
	}

	std::ofstream out("UnpackTemplates.h");
	out << result;
	out.close();

	return 0;
}