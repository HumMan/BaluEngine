#pragma once

#include <string>

namespace EngineInterface
{
	class IProperties;
	class IBaluSceneClassInstance;

	class IBaluWorldObject
	{
	public:
		virtual IProperties* GetProperties() = 0;
		virtual std::string GetName() = 0;
	};

	enum class PropertyType
	{
		Bool,
		Int,
		Float,
		String,
		SceneClassInstance,
	};


#ifdef BALU_ENGINE_SCRIPT_CLASSES

	void PropertyType_register(TClassRegistryParams& params)
	{
		auto& syntax = params.syntax;
		TClass* cl = new TClass(syntax->base_class.get());
		syntax->base_class->AddNested(cl);
		syntax->lexer.ParseSource(
			"enum PropertyType\n"
			"{\n"
			"Bool,\n"
			"Int,\n"
			"Float,\n"
			"String,\n"
			"SceneClassInstance\n"
			"}\n"
			);
		cl->AnalyzeSyntax(syntax->lexer);
		syntax->lexer.GetToken(TTokenType::Done);

		TSClass* scl = new TSClass(syntax->sem_base_class.get(), cl);
		syntax->sem_base_class->AddClass(scl);
		scl->Build();
	}
	static bool PropertyType_registered = TScriptClassesRegistry::Register("PropertyType", PropertyType_register);
#endif

	class IProperties
	{
	public:
		virtual bool HasProperty(const std::string& name, PropertyType& type) = 0;
		virtual void SetBool(const std::string& name, bool value) = 0;
		virtual bool GetBool(const std::string& name) = 0;
		virtual void SetSceneClassInstance(const std::string& name, IBaluSceneClassInstance* value) = 0;
		virtual IBaluSceneClassInstance* GetSceneClassInstance(const std::string& name) = 0;
	};


#ifdef BALU_ENGINE_SCRIPT_CLASSES

	void IProperties_HasProperty(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
	}

	void IProperties_register(TClassRegistryParams& params)
	{
		auto& syntax = params.syntax;
		TClass* cl = new TClass(syntax->base_class.get());
		syntax->base_class->AddNested(cl);
		syntax->lexer.ParseSource(
			"class extern IProperties\n"
			"{\n"
			"func HasProperty(string name, PropertyType type):bool;\n"
			"}\n"
			);
		cl->AnalyzeSyntax(syntax->lexer);
		syntax->lexer.GetToken(TTokenType::Done);

		TSClass* scl = new TSClass(syntax->sem_base_class.get(), cl);
		syntax->sem_base_class->AddClass(scl);
		scl->Build();

		scl->SetSize(IntSizeOf(sizeof(TFrame)) / sizeof(int));
		scl->SetAutoMethodsInitialized();

		std::vector<TSMethod*> m;

		m.clear();
		scl->GetMethods(m, syntax->lexer.GetIdFromName("HasProperty"));
		m[0]->SetAsExternal(TFrame_GetLeftBottom);
	}
	static bool IProperties_registered = TScriptClassesRegistry::Register("IProperties", IProperties_register);
#endif

}