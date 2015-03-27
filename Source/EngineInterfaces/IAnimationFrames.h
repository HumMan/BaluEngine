#pragma once

#include "../../BaluLib/Source/Math/vec.h"

#include <vector>


#include "../exportMacro.h"

namespace pugi
{
	class xml_node;
}

class TBaluWorld;
class TBaluSpritePolygon;

namespace EngineInterface
{

	class BALUENGINEDLL_API TFrame
	{
	public:
		TVec2 left_bottom;
		TVec2 right_top;
		TFrame(TVec2 left_bottom, TVec2 right_top);

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};

#ifdef BALU_ENGINE_SCRIPT_CLASSES

	void TFrame_constr(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
	}

	void TFrame_GetLeftBottom(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		auto obj = ((TFrame*)object.get());
		*(TVec2*)result.get() = obj->left_bottom;
	}

	void TFrame_GetRightTop(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		auto obj = ((TFrame*)object.get());
		*(TVec2*)result.get() = obj->right_top;
	}


	void TFrame_register(TClassRegistryParams& params)
	{
		auto& syntax = params.syntax;
		TClass* cl = new TClass(syntax->base_class.get());
		syntax->base_class->AddNested(cl);
		syntax->lexer.ParseSource(
			"class extern TFrame\n"
			"{\n"
			"copy(vec2 left_botom, vec2 left_top);\n"
			"func GetLeftBottom:vec2;\n"
			"func GetRightTop:vec2;\n"
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
		scl->GetMethods(m, syntax->lexer.GetIdFromName("GetLeftBottom"));
		m[0]->SetAsExternal(TFrame_GetLeftBottom);

		m.clear();
		scl->GetMethods(m, syntax->lexer.GetIdFromName("GetRightTop"));
		m[0]->SetAsExternal(TFrame_GetRightTop);
	}
	static bool TFrame_registered = TScriptClassesRegistry::Register("TFrame", TFrame_register);
#endif

	class TAnimDesc
	{
	public:
		virtual TFrame GetFrame(int index) = 0;

		virtual void Save(pugi::xml_node& parent_node, const int version)=0;
		virtual void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)=0;
	};

	typedef TAnimDesc*(*AnimDescClone)();
	class BALUENGINEDLL_API AnimDescFactory
	{
	public:
		static bool Register(const char* name, AnimDescClone clone);
		static TAnimDesc* Create(const char* name);
	};

	class BALUENGINEDLL_API TSpecificFrame : public TAnimDesc
	{
		TVec2 left_bottom;
		TVec2 right_top;
	public:
		TSpecificFrame()
		{
		}
		static TAnimDesc* Clone()
		{
			return new TSpecificFrame();
		}
		TSpecificFrame(TVec2 left_bottom, TVec2 right_top);
		TFrame GetFrame(int index);

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
	static bool TSpecificFrame_registered = AnimDescFactory::Register("SpecificFrame", TSpecificFrame::Clone);

	class BALUENGINEDLL_API TGridFrames : public TAnimDesc
	{
		TVec2 left_bottom;
		TVec2 width_height;
		int cell_count_x;
		int cell_count_y;
	public:
		TGridFrames()
		{
		}
		static TAnimDesc* Clone()
		{
			return new TGridFrames();
		}
		TGridFrames(TVec2 left_bottom, TVec2 width_height, int cell_count_x, int cell_count_y);
		TFrame GetFrame(int index);

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
	static bool TGridFrames_registered = AnimDescFactory::Register("GridFrames", TGridFrames::Clone);

	class BALUENGINEDLL_API TFramesRange
	{
		int start;
		int end;
	public:
		TFramesRange(int start, int end);
	};

	class BALUENGINEDLL_API TAnimationFrames
	{
	public:
		TAnimationFrames()
		{
		}
		TAnimDesc* desc;
		std::vector<int> frames;
		TAnimationFrames(TAnimDesc* desc, std::vector<int> frames);
		TAnimationFrames(TAnimDesc* desc, int frame);

		void Save(pugi::xml_node& parent_node, const int version, TBaluSpritePolygon* sprite_polygon);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world, TBaluSpritePolygon* sprite_polygon);
	};

	class BALUENGINEDLL_API TAnimLine
	{
	public:
		std::string line_name;
		std::vector<TAnimationFrames> frames;

		void Save(pugi::xml_node& parent_node, const int version, TBaluSpritePolygon* sprite_polygon);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world, TBaluSpritePolygon* sprite_polygon);
	};
}

BALUENGINEDLL_API std::vector<int> FramesRange(int start, int end);

#ifdef BALU_ENGINE_SCRIPT_CLASSES


#endif