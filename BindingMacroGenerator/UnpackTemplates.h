#pragma once

#define MUnpackRA0(ret_wrapper, ret_type, interface_type, method_name \
)\
methods.push_back(SetName(#method_name, new UnpackRA0<ret_wrapper<ret_type>, ret_type*, WrapPointer<interface_type>\
, &interface_type::method_name>));
#define MUnpackA0(interface_type, method_name \
)\
methods.push_back(SetName(#method_name, new UnpackA0<WrapPointer<interface_type>\
, &interface_type::method_name>));


template<class Tresult_type, class TCppResult, class Tobject_type
 , TCppResult(Tobject_type::Arg::*CppMethod)()>
class UnpackRA0 : public Unpacker
{
public:
	std::string GetSyntax()
	{
		char buf[255];
			sprintf_s(buf, "func %s:%s;", func_name
			, CppTypeToScript<Tresult_type::Arg>::Get()
		);
		return buf;
	}
	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		result.get_as<Tresult_type>() = Tresult_type(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)
		(
		));
	}
	TExternalSMethod GetUnpackMethod()
	{		return Run;
	}
};

template<class Tobject_type
 , void(Tobject_type::Arg::*CppMethod)()>
class UnpackA0 : public Unpacker
{
public:
	std::string GetSyntax()
	{
		char buf[255];
			sprintf_s(buf, "func %s;", func_name
		);
		return buf;
	}
	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)
		(
		));
	}
	TExternalSMethod GetUnpackMethod()
	{		return Run;
	}
};


#define MUnpackRA1(ret_wrapper, ret_type, interface_type, method_name \
, param0_wrapper, param0_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA1<ret_wrapper<ret_type>, ret_type*, WrapPointer<interface_type>\
, param0_wrapper<param0_type>, param0_type\
, &interface_type::method_name>));
#define MUnpackA1(interface_type, method_name \
, param0_wrapper, param0_type\
)\
methods.push_back(SetName(#method_name, new UnpackA1<WrapPointer<interface_type>\
, param0_wrapper<param0_type>, param0_type\
, &interface_type::method_name>));


template<class Tresult_type, class TCppResult, class Tobject_type
, class Ta0, class Ta0_cpp
 , TCppResult(Tobject_type::Arg::*CppMethod)(Ta0_cpp)>
class UnpackRA1 : public Unpacker
{
public:
	std::string GetSyntax()
	{
		char buf[255];
			sprintf_s(buf, "func %s(%s a0):%s;", func_name
			, CppTypeToScript<Ta0::Arg>::Get()
			, CppTypeToScript<Tresult_type::Arg>::Get()
		);
		return buf;
	}
	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		result.get_as<Tresult_type>() = Tresult_type(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)
		(
			formal_params[0].get_as<Ta0>().GetCppValue()
		));
	}
	TExternalSMethod GetUnpackMethod()
	{		return Run;
	}
};

template<class Tobject_type
, class Ta0, class Ta0_cpp
 , void(Tobject_type::Arg::*CppMethod)(Ta0_cpp)>
class UnpackA1 : public Unpacker
{
public:
	std::string GetSyntax()
	{
		char buf[255];
			sprintf_s(buf, "func %s(%s a0);", func_name
			, CppTypeToScript<Ta0::Arg>::Get()
		);
		return buf;
	}
	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)
		(
			formal_params[0].get_as<Ta0>().GetCppValue()
		));
	}
	TExternalSMethod GetUnpackMethod()
	{		return Run;
	}
};


#define MUnpackRA2(ret_wrapper, ret_type, interface_type, method_name \
, param0_wrapper, param0_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA2<ret_wrapper<ret_type>, ret_type*, WrapPointer<interface_type>\
, param0_wrapper<param0_type>, param0_type\
, &interface_type::method_name>));
#define MUnpackA2(interface_type, method_name \
, param0_wrapper, param0_type\
)\
methods.push_back(SetName(#method_name, new UnpackA2<WrapPointer<interface_type>\
, param0_wrapper<param0_type>, param0_type\
, &interface_type::method_name>));


template<class Tresult_type, class TCppResult, class Tobject_type
, class Ta0, class Ta0_cpp
, class Ta1, class Ta1_cpp
 , TCppResult(Tobject_type::Arg::*CppMethod)(Ta0_cpp, Ta1_cpp)>
class UnpackRA2 : public Unpacker
{
public:
	std::string GetSyntax()
	{
		char buf[255];
			sprintf_s(buf, "func %s(%s a0, %s a1):%s;", func_name
			, CppTypeToScript<Ta0::Arg>::Get()
			, CppTypeToScript<Ta1::Arg>::Get()
			, CppTypeToScript<Tresult_type::Arg>::Get()
		);
		return buf;
	}
	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		result.get_as<Tresult_type>() = Tresult_type(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)
		(
			formal_params[0].get_as<Ta0>().GetCppValue(), 
			formal_params[1].get_as<Ta1>().GetCppValue()
		));
	}
	TExternalSMethod GetUnpackMethod()
	{		return Run;
	}
};

template<class Tobject_type
, class Ta0, class Ta0_cpp
, class Ta1, class Ta1_cpp
 , void(Tobject_type::Arg::*CppMethod)(Ta0_cpp, Ta1_cpp)>
class UnpackA2 : public Unpacker
{
public:
	std::string GetSyntax()
	{
		char buf[255];
			sprintf_s(buf, "func %s(%s a0, %s a1);", func_name
			, CppTypeToScript<Ta0::Arg>::Get()
			, CppTypeToScript<Ta1::Arg>::Get()
		);
		return buf;
	}
	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)
		(
			formal_params[0].get_as<Ta0>().GetCppValue(), 
			formal_params[1].get_as<Ta1>().GetCppValue()
		));
	}
	TExternalSMethod GetUnpackMethod()
	{		return Run;
	}
};


#define MUnpackRA3(ret_wrapper, ret_type, interface_type, method_name \
, param0_wrapper, param0_type\
, param2_wrapper, param2_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA3<ret_wrapper<ret_type>, ret_type*, WrapPointer<interface_type>\
, param0_wrapper<param0_type>, param0_type\
, param2_wrapper<param2_type>, param2_type\
, &interface_type::method_name>));
#define MUnpackA3(interface_type, method_name \
, param0_wrapper, param0_type\
, param2_wrapper, param2_type\
)\
methods.push_back(SetName(#method_name, new UnpackA3<WrapPointer<interface_type>\
, param0_wrapper<param0_type>, param0_type\
, param2_wrapper<param2_type>, param2_type\
, &interface_type::method_name>));


template<class Tresult_type, class TCppResult, class Tobject_type
, class Ta0, class Ta0_cpp
, class Ta1, class Ta1_cpp
, class Ta2, class Ta2_cpp
 , TCppResult(Tobject_type::Arg::*CppMethod)(Ta0_cpp, Ta1_cpp, Ta2_cpp)>
class UnpackRA3 : public Unpacker
{
public:
	std::string GetSyntax()
	{
		char buf[255];
			sprintf_s(buf, "func %s(%s a0, %s a1, %s a2):%s;", func_name
			, CppTypeToScript<Ta0::Arg>::Get()
			, CppTypeToScript<Ta1::Arg>::Get()
			, CppTypeToScript<Ta2::Arg>::Get()
			, CppTypeToScript<Tresult_type::Arg>::Get()
		);
		return buf;
	}
	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		result.get_as<Tresult_type>() = Tresult_type(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)
		(
			formal_params[0].get_as<Ta0>().GetCppValue(), 
			formal_params[1].get_as<Ta1>().GetCppValue(), 
			formal_params[2].get_as<Ta2>().GetCppValue()
		));
	}
	TExternalSMethod GetUnpackMethod()
	{		return Run;
	}
};

template<class Tobject_type
, class Ta0, class Ta0_cpp
, class Ta1, class Ta1_cpp
, class Ta2, class Ta2_cpp
 , void(Tobject_type::Arg::*CppMethod)(Ta0_cpp, Ta1_cpp, Ta2_cpp)>
class UnpackA3 : public Unpacker
{
public:
	std::string GetSyntax()
	{
		char buf[255];
			sprintf_s(buf, "func %s(%s a0, %s a1, %s a2);", func_name
			, CppTypeToScript<Ta0::Arg>::Get()
			, CppTypeToScript<Ta1::Arg>::Get()
			, CppTypeToScript<Ta2::Arg>::Get()
		);
		return buf;
	}
	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)
		(
			formal_params[0].get_as<Ta0>().GetCppValue(), 
			formal_params[1].get_as<Ta1>().GetCppValue(), 
			formal_params[2].get_as<Ta2>().GetCppValue()
		));
	}
	TExternalSMethod GetUnpackMethod()
	{		return Run;
	}
};


#define MUnpackRA4(ret_wrapper, ret_type, interface_type, method_name \
, param0_wrapper, param0_type\
, param2_wrapper, param2_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<ret_wrapper<ret_type>, ret_type*, WrapPointer<interface_type>\
, param0_wrapper<param0_type>, param0_type\
, param2_wrapper<param2_type>, param2_type\
, &interface_type::method_name>));
#define MUnpackA4(interface_type, method_name \
, param0_wrapper, param0_type\
, param2_wrapper, param2_type\
)\
methods.push_back(SetName(#method_name, new UnpackA4<WrapPointer<interface_type>\
, param0_wrapper<param0_type>, param0_type\
, param2_wrapper<param2_type>, param2_type\
, &interface_type::method_name>));


template<class Tresult_type, class TCppResult, class Tobject_type
, class Ta0, class Ta0_cpp
, class Ta1, class Ta1_cpp
, class Ta2, class Ta2_cpp
, class Ta3, class Ta3_cpp
 , TCppResult(Tobject_type::Arg::*CppMethod)(Ta0_cpp, Ta1_cpp, Ta2_cpp, Ta3_cpp)>
class UnpackRA4 : public Unpacker
{
public:
	std::string GetSyntax()
	{
		char buf[255];
			sprintf_s(buf, "func %s(%s a0, %s a1, %s a2, %s a3):%s;", func_name
			, CppTypeToScript<Ta0::Arg>::Get()
			, CppTypeToScript<Ta1::Arg>::Get()
			, CppTypeToScript<Ta2::Arg>::Get()
			, CppTypeToScript<Ta3::Arg>::Get()
			, CppTypeToScript<Tresult_type::Arg>::Get()
		);
		return buf;
	}
	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		result.get_as<Tresult_type>() = Tresult_type(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)
		(
			formal_params[0].get_as<Ta0>().GetCppValue(), 
			formal_params[1].get_as<Ta1>().GetCppValue(), 
			formal_params[2].get_as<Ta2>().GetCppValue(), 
			formal_params[3].get_as<Ta3>().GetCppValue()
		));
	}
	TExternalSMethod GetUnpackMethod()
	{		return Run;
	}
};

template<class Tobject_type
, class Ta0, class Ta0_cpp
, class Ta1, class Ta1_cpp
, class Ta2, class Ta2_cpp
, class Ta3, class Ta3_cpp
 , void(Tobject_type::Arg::*CppMethod)(Ta0_cpp, Ta1_cpp, Ta2_cpp, Ta3_cpp)>
class UnpackA4 : public Unpacker
{
public:
	std::string GetSyntax()
	{
		char buf[255];
			sprintf_s(buf, "func %s(%s a0, %s a1, %s a2, %s a3);", func_name
			, CppTypeToScript<Ta0::Arg>::Get()
			, CppTypeToScript<Ta1::Arg>::Get()
			, CppTypeToScript<Ta2::Arg>::Get()
			, CppTypeToScript<Ta3::Arg>::Get()
		);
		return buf;
	}
	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)
		(
			formal_params[0].get_as<Ta0>().GetCppValue(), 
			formal_params[1].get_as<Ta1>().GetCppValue(), 
			formal_params[2].get_as<Ta2>().GetCppValue(), 
			formal_params[3].get_as<Ta3>().GetCppValue()
		));
	}
	TExternalSMethod GetUnpackMethod()
	{		return Run;
	}
};


#define MUnpackRA5(ret_wrapper, ret_type, interface_type, method_name \
, param0_wrapper, param0_type\
, param2_wrapper, param2_type\
, param4_wrapper, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<ret_wrapper<ret_type>, ret_type*, WrapPointer<interface_type>\
, param0_wrapper<param0_type>, param0_type\
, param2_wrapper<param2_type>, param2_type\
, param4_wrapper<param4_type>, param4_type\
, &interface_type::method_name>));
#define MUnpackA5(interface_type, method_name \
, param0_wrapper, param0_type\
, param2_wrapper, param2_type\
, param4_wrapper, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackA5<WrapPointer<interface_type>\
, param0_wrapper<param0_type>, param0_type\
, param2_wrapper<param2_type>, param2_type\
, param4_wrapper<param4_type>, param4_type\
, &interface_type::method_name>));


template<class Tresult_type, class TCppResult, class Tobject_type
, class Ta0, class Ta0_cpp
, class Ta1, class Ta1_cpp
, class Ta2, class Ta2_cpp
, class Ta3, class Ta3_cpp
, class Ta4, class Ta4_cpp
 , TCppResult(Tobject_type::Arg::*CppMethod)(Ta0_cpp, Ta1_cpp, Ta2_cpp, Ta3_cpp, Ta4_cpp)>
class UnpackRA5 : public Unpacker
{
public:
	std::string GetSyntax()
	{
		char buf[255];
			sprintf_s(buf, "func %s(%s a0, %s a1, %s a2, %s a3, %s a4):%s;", func_name
			, CppTypeToScript<Ta0::Arg>::Get()
			, CppTypeToScript<Ta1::Arg>::Get()
			, CppTypeToScript<Ta2::Arg>::Get()
			, CppTypeToScript<Ta3::Arg>::Get()
			, CppTypeToScript<Ta4::Arg>::Get()
			, CppTypeToScript<Tresult_type::Arg>::Get()
		);
		return buf;
	}
	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		result.get_as<Tresult_type>() = Tresult_type(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)
		(
			formal_params[0].get_as<Ta0>().GetCppValue(), 
			formal_params[1].get_as<Ta1>().GetCppValue(), 
			formal_params[2].get_as<Ta2>().GetCppValue(), 
			formal_params[3].get_as<Ta3>().GetCppValue(), 
			formal_params[4].get_as<Ta4>().GetCppValue()
		));
	}
	TExternalSMethod GetUnpackMethod()
	{		return Run;
	}
};

template<class Tobject_type
, class Ta0, class Ta0_cpp
, class Ta1, class Ta1_cpp
, class Ta2, class Ta2_cpp
, class Ta3, class Ta3_cpp
, class Ta4, class Ta4_cpp
 , void(Tobject_type::Arg::*CppMethod)(Ta0_cpp, Ta1_cpp, Ta2_cpp, Ta3_cpp, Ta4_cpp)>
class UnpackA5 : public Unpacker
{
public:
	std::string GetSyntax()
	{
		char buf[255];
			sprintf_s(buf, "func %s(%s a0, %s a1, %s a2, %s a3, %s a4);", func_name
			, CppTypeToScript<Ta0::Arg>::Get()
			, CppTypeToScript<Ta1::Arg>::Get()
			, CppTypeToScript<Ta2::Arg>::Get()
			, CppTypeToScript<Ta3::Arg>::Get()
			, CppTypeToScript<Ta4::Arg>::Get()
		);
		return buf;
	}
	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		(((object.get_as<Tobject_type>().GetCppValue()).*CppMethod)
		(
			formal_params[0].get_as<Ta0>().GetCppValue(), 
			formal_params[1].get_as<Ta1>().GetCppValue(), 
			formal_params[2].get_as<Ta2>().GetCppValue(), 
			formal_params[3].get_as<Ta3>().GetCppValue(), 
			formal_params[4].get_as<Ta4>().GetCppValue()
		));
	}
	TExternalSMethod GetUnpackMethod()
	{		return Run;
	}
};


