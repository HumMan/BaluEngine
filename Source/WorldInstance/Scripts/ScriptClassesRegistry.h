#pragma once

#include <baluScript.h>
#include <baluLib.h>

class Unpacker
{
protected:
	const char* func_name;
	bool is_constructor;
public:
	Unpacker()
	{
		func_name = nullptr;
		is_constructor = false;
	}
	//virtual TExternalSMethod GetUnpackMethod() = 0;
	virtual std::string GetSyntax() = 0;
	const char* GetFuncName()
	{
		return func_name;
	}
	void SetFuncName(const char* func_name)
	{
		this->func_name = func_name;
	}
	void SetAsConstructor()
	{
		is_constructor = true;
	}
	bool IsConstructor()
	{
		return is_constructor;
	}
	virtual ~Unpacker()
	{
	}
};

class TClassBinding
{
public:
	const char* class_name;
	int size;
	std::vector<std::unique_ptr<Unpacker>> methods;
	TSClass* compiled;
	TClassBinding()
	{
		class_name = nullptr;
		size = 0;
		compiled = nullptr;
	}

	void SetMethods(std::vector<Unpacker*> methods)
	{
		for (auto v : methods)
			this->methods.push_back(std::unique_ptr<Unpacker>(v));
	}
};

class TClassRegistryParams
{
public:
	TSyntaxAnalyzer* syntax;
	std::vector<TStaticValue> *static_objects;
	//std::vector < std::unique_ptr<TSMethod>> *smethods;
};

typedef void(*RegisterScriptClass)(TClassRegistryParams& params);

TSClass* RegisterEnum(TClassRegistryParams& params, const char* source);

Unpacker* SetName(const char* name, Unpacker* method);
Unpacker* SetAsConstructor(Unpacker* method);

class TScriptClassesRegistry
{
public:
	static bool RegisterEnum(const char* name, RegisterScriptClass reg);
	static void RegisterClassBinding(TClassBinding* binding);
	static void RegisterClassesInScript(TClassRegistryParams& params);
};