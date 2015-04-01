#pragma once

#define MUnpackRp(ret_type, interface_type, method_name \
)\
methods.push_back(SetName(#method_name, new UnpackRA0<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
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


#define MUnpackRpp(ret_type, interface_type, method_name \
, param0_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA1<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, &interface_type::method_name>));

#define MUnpackRpv(ret_type, interface_type, method_name \
, param0_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA1<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
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

template<class Tresult_type, class Tobject_type
	, class Ta0 , typename TT>
class _UnpackRA1
{
public:
	typedef typename UnpackRA1<Tresult_type, Tresult_type::Arg, Tobject_type, Ta0, Ta0::Arg, TT> Proxy;
};

#define MUnpackRppp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA2<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, &interface_type::method_name>));

#define MUnpackRpvp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA2<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, &interface_type::method_name>));

#define MUnpackRppv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA2<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, &interface_type::method_name>));

#define MUnpackRpvv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA2<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
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


#define MUnpackRpppp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA3<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, &interface_type::method_name>));

#define MUnpackRpvpp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA3<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, &interface_type::method_name>));

#define MUnpackRppvp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA3<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, &interface_type::method_name>));

#define MUnpackRpvvp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA3<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, &interface_type::method_name>));

#define MUnpackRpppv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA3<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, &interface_type::method_name>));

#define MUnpackRpvpv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA3<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, &interface_type::method_name>));

#define MUnpackRppvv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA3<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, &interface_type::method_name>));

#define MUnpackRpvvv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA3<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
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


#define MUnpackRppppp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, &interface_type::method_name>));

#define MUnpackRpvppp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, &interface_type::method_name>));

#define MUnpackRppvpp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, &interface_type::method_name>));

#define MUnpackRpvvpp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, &interface_type::method_name>));

#define MUnpackRpppvp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, &interface_type::method_name>));

#define MUnpackRpvpvp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, &interface_type::method_name>));

#define MUnpackRppvvp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, &interface_type::method_name>));

#define MUnpackRpvvvp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, &interface_type::method_name>));

#define MUnpackRppppv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, &interface_type::method_name>));

#define MUnpackRpvppv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, &interface_type::method_name>));

#define MUnpackRppvpv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, &interface_type::method_name>));

#define MUnpackRpvvpv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, &interface_type::method_name>));

#define MUnpackRpppvv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, &interface_type::method_name>));

#define MUnpackRpvpvv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, &interface_type::method_name>));

#define MUnpackRppvvv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, &interface_type::method_name>));

#define MUnpackRpvvvv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA4<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
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


#define MUnpackRpppppp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvpppp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRppvppp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvvppp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpppvpp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvpvpp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRppvvpp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvvvpp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRppppvp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvppvp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRppvpvp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvvpvp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpppvvp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvpvvp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRppvvvp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvvvvp(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapPointer<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpppppv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvpppv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRppvppv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvvppv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpppvpv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvpvpv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRppvvpv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvvvpv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapPointer<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRppppvv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvppvv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRppvpvv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvvpvv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapPointer<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpppvvv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvpvvv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapPointer<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRppvvvv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapPointer<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
, &interface_type::method_name>));

#define MUnpackRpvvvvv(ret_type, interface_type, method_name \
, param0_type\
, param1_type\
, param2_type\
, param3_type\
, param4_type\
)\
methods.push_back(SetName(#method_name, new UnpackRA5<WrapPointer<ret_type>, ret_type*, WrapPointer<interface_type>\
, WrapValue<param0_type>, param0_type\
, WrapValue<param1_type>, param1_type\
, WrapValue<param2_type>, param2_type\
, WrapValue<param3_type>, param3_type\
, WrapValue<param4_type>, param4_type\
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


