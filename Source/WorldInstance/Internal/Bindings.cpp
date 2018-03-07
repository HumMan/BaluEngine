#include "Class/Binding.h"

#include "../Interface.h"

#include "Scripts/ScriptClassesRegistry.h"

#include <Windows.h>

#include <fstream>
#include <streambuf>

#include <vector>

#include "../Include/baluScript.h"
#include "../Source/BindingGen.h"

std::map<std::string, std::string> StoC_map = {
	{ "TDynArray","TDynArr" },
	{ "TStaticArray","TStaticArr" },
	{ "string","TString" },
	{ "vec2i", "BaluLib::TVec2i" },
	{ "vec2", "BaluLib::TVec2" },
};

void Bootstrap(TMethodRunContext* run_context)
{

}

#include "../submodules/BaluScript/Source/TreeRunner/TreeRunner.h"

#include "../../Common/IDirector.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;

//TODO конвертирование TString string в параметрах и результате по ссылке и значению

#include "../../../BindingGenerator/external_bindings.h"

std::string PrintMethod(std::string value)
{
	char buf[200];
	sprintf(buf, value.c_str(), "");
	return std::string(buf) + "\n{}\n";
	return buf;
}

void BaluEngine::WorldInstance::GenerateScriptBindings(std::string output_path)
{
	try
	{
		std::string source;

		for (auto& v : BaluEngine::WorldInstance::Internal::TScriptClassesRegistry::get_enum_registry())
		{
			source += v.source;
			StoC_map[v.name] = v.c_name;
		}

		int offset = TSyntaxAnalyzer::GetBindingOffset()+ TSyntaxAnalyzer::GetBindingCount();

		std::vector<std::string> result;

		std::vector<SemanticApi::TExternalClassDecl> external_classes;
		std::vector<std::string> interface_classes;

		for (auto& v : BaluEngine::WorldInstance::Internal::TScriptClassesRegistry::get_external_class_registry())
		{
			SemanticApi::TExternalClassDecl t;
			t.size = LexerIntSizeOf(v.size);
			t.source = v.source;
			external_classes.push_back(t);
			StoC_map[v.name] = v.c_name;
			if (v.is_interface)
				interface_classes.push_back(v.name);
		}

		std::vector<SemanticApi::TExternalSMethod> _external_bindings;

		for (int i = 0; i < 1000; i++)
			_external_bindings.push_back(Bootstrap);


		source += "class GlobalCallback\n{\n";

		for (auto& v : WorldDef::GlobalCallbackSignature)
		{
			source += PrintMethod(v);
		}

		source += "}\n";

		BindingGen::Generate(source.c_str(), StoC_map, interface_classes,
			result, offset, external_classes, _external_bindings);

		std::ofstream file(output_path);
		for (auto v : result)
			file << v;
		file.close();
	}
	catch (std::string s)
	{
		printf(s.c_str());
	}

	printf("All done");
}