#pragma once

template<class T>
class WrapPointer
{
public:
	typedef T Arg;
	T* obj;
	WrapPointer(T* copy_from)
	{
		obj = copy_from;
	}
	T& GetValue()
	{
		return *obj;
	}
};

template<class Tresult_type, class Tobject_type, Tresult_type* (Tobject_type::Arg::*SomeMethod)()>
class UnpackR : public Unpacker
{
public:
	std::string GetSyntax()
	{
		char buf[255];
		sprintf_s(buf, "func %s:%s;", func_name, Tresult_type::GetScriptClassName());
		return buf;
	}
	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		*result.get_as<Tresult_type*>() = ((*object.get_as<Tobject_type::Arg*>())->*SomeMethod)();
	}
	TExternalSMethod GetUnpackMethod()
	{
		return Run;
	}
};

template<class Tobject_type, void (Tobject_type::*SomeMethod)(), class Targ0>
class UnpackA1 : public Unpacker
{
public:
	std::string GetSyntax()
	{
		char buf[255];
		sprintf_s(buf, "func %s(%s);", func_name, Targ0::GetScriptClassName());
		return buf;
	}
	static void Run(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		((*object.get_as<Tobject_type*>())->*SomeMethod)(formal_params[0].get_as<Targ0>());
	}
	TExternalSMethod GetUnpackMethod()
	{
		return Run;
	}
};