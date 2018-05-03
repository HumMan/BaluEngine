//auto-generated code
namespace ns_Script 
{
	void callScriptFromC_Print(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, const float p0 /*v*/) 
	{
		std::vector<TStackValue> params;
		params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
		*(float*)params[0].get() = p0;
		TStackValue result, object;
		TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
	}
	namespace ns_int 
	{
		void callScriptFromC_operator_PlusA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, int& p0 /*l*/, const int p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_operator_MinusA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, int& p0 /*l*/, const int p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_operator_MulA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, int& p0 /*l*/, const int p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_operator_DivA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, int& p0 /*l*/, const int p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_operator_PercentA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, int& p0 /*l*/, const int p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_operator_Increment(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, int& p0 /*l*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int**)params[0].get() = &p0;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_operator_Decrement(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, int& p0 /*l*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int**)params[0].get() = &p0;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
	}
	namespace ns_float 
	{
		void callScriptFromC_operator_PlusA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, float& p0 /*l*/, const float p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_operator_MinusA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, float& p0 /*l*/, const float p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_operator_MulA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, float& p0 /*l*/, const float p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_operator_DivA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, float& p0 /*l*/, const float p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
	}
	namespace ns_bool 
	{
	}
	namespace ns_vec2 
	{
		void callScriptFromC_operator_PlusA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2& p0 /*l*/, const BaluLib::TVec2 p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_operator_MinusA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2& p0 /*l*/, const BaluLib::TVec2 p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_operator_MulA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2& p0 /*l*/, const BaluLib::TVec2 p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_operator_DivA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2& p0 /*l*/, const BaluLib::TVec2 p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
	}
	namespace ns_vec2i 
	{
		void callScriptFromC_operator_PlusA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2i& p0 /*l*/, const BaluLib::TVec2i p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_operator_MinusA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2i& p0 /*l*/, const BaluLib::TVec2i p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_operator_MulA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2i& p0 /*l*/, const BaluLib::TVec2i p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_operator_DivA(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2i& p0 /*l*/, const BaluLib::TVec2i p1 /*r*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
	}
	namespace ns_char 
	{
	}
	namespace ns_TKey 
	{
	}
	namespace ns_PropertyType 
	{
	}
	namespace ns_TMouseButton 
	{
	}
	namespace ns_GlobalCallback 
	{
		void callScriptFromC_MouseUp_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, IWorld* const p0 /*world*/, const WorldDef::TMouseEventArgs p1 /*event*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IWorld"))));
			*(IWorld**)params[0].get() = p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("TMouseEventArgs"))));
			*(WorldDef::TMouseEventArgs*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_MouseDown_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, IWorld* const p0 /*world*/, const WorldDef::TMouseEventArgs p1 /*event*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IWorld"))));
			*(IWorld**)params[0].get() = p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("TMouseEventArgs"))));
			*(WorldDef::TMouseEventArgs*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_MouseMove_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, IWorld* const p0 /*world*/, const WorldDef::TMouseEventArgs p1 /*event*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IWorld"))));
			*(IWorld**)params[0].get() = p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("TMouseEventArgs"))));
			*(WorldDef::TMouseEventArgs*)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_WorldStart_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, IWorld* const p0 /*world*/, IComposer* const p1 /*composer*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IWorld"))));
			*(IWorld**)params[0].get() = p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IComposer"))));
			*(IComposer**)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_ViewportResize_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, IDirector* const p0 /*director*/, const BaluLib::TVec2i p1 /*old_size*/, const BaluLib::TVec2i p2 /*new_size*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IDirector"))));
			*(IDirector**)params[0].get() = p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i*)params[1].get() = p1;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i*)params[2].get() = p2;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_BeforePhysics_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax) 
		{
			std::vector<TStackValue> params;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_KeyDown_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, const WorldDef::TKey p0 /*key*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("TKey"))));
			*(WorldDef::TKey*)params[0].get() = p0;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_KeyUp_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, const WorldDef::TKey p0 /*key*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("TKey"))));
			*(WorldDef::TKey*)params[0].get() = p0;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
	}
	namespace ns_GlobalKeyCallback 
	{
		void callScriptFromC_KeyDown_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax) 
		{
			std::vector<TStackValue> params;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_KeyUp_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax) 
		{
			std::vector<TStackValue> params;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
	}
	namespace ns_ClassCallback 
	{
		void callScriptFromC_BeforePhysics_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, ITransformedClassInstance* const p0 /*object*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(ITransformedClassInstance**)params[0].get() = p0;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_KeyDown_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, const WorldDef::TKey p0 /*key*/, ITransformedClassInstance* const p1 /*object*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("TKey"))));
			*(WorldDef::TKey*)params[0].get() = p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(ITransformedClassInstance**)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_KeyUp_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, const WorldDef::TKey p0 /*key*/, ITransformedClassInstance* const p1 /*object*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("TKey"))));
			*(WorldDef::TKey*)params[0].get() = p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(ITransformedClassInstance**)params[1].get() = p1;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_Created_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, ITransformedClassInstance* const p0 /*object*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(ITransformedClassInstance**)params[0].get() = p0;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
	}
	namespace ns_ClassKeyCallback 
	{
		void callScriptFromC_KeyDown_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, ITransformedClassInstance* const p0 /*object*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(ITransformedClassInstance**)params[0].get() = p0;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
		void callScriptFromC_KeyUp_(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, ITransformedClassInstance* const p0 /*object*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(ITransformedClassInstance**)params[0].get() = p0;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
	}
	namespace ns_OnCollideCallback 
	{
		void callScriptFromC_Collide(std::vector<TStaticValue>* static_fields, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, ITransformedClassInstance* const p0 /*object*/, IPhysShapeInstance* const p1 /*source*/, ITransformedClassInstance* const p2 /*obstancle*/) 
		{
			std::vector<TStackValue> params;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(ITransformedClassInstance**)params[0].get() = p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IPhysShape"))));
			*(IPhysShapeInstance**)params[1].get() = p1;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(ITransformedClassInstance**)params[2].get() = p2;
			TStackValue result, object;
			TreeRunner::Run(compiled_method, TMethodRunContext(static_fields, &params, &result, &object));
		}
	}
	namespace ns_dword 
	{
	}
	namespace ns_TDynArray 
	{
	}
	namespace ns_TStaticArray 
	{
	}
	namespace ns_string 
	{
	}
	namespace ns_TFrame 
	{
		void bind_GetLeftBottom(TMethodRunContext* run_context) 
		{
			// return --- BaluLib::TVec2
			WorldDef::TFrame* obj = ((WorldDef::TFrame*)(run_context->object->get()));
			BaluLib::TVec2  result = 
			obj->GetLeftBottom();
			*(BaluLib::TVec2*)run_context->result->get() = result;
		}
		void bind_GetRightTop(TMethodRunContext* run_context) 
		{
			// return --- BaluLib::TVec2
			WorldDef::TFrame* obj = ((WorldDef::TFrame*)(run_context->object->get()));
			BaluLib::TVec2  result = 
			obj->GetRightTop();
			*(BaluLib::TVec2*)run_context->result->get() = result;
		}
	}
	namespace ns_IClassPhysBody 
	{
		void bind_GetLinearVelocity(TMethodRunContext* run_context) 
		{
			// return --- BaluLib::TVec2
			IClassPhysBodyIntance** obj = ((IClassPhysBodyIntance**)(run_context->object->get()));
			BaluLib::TVec2  result = 
			(*obj)->GetLinearVelocity();
			*(BaluLib::TVec2*)run_context->result->get() = result;
		}
		void bind_SetLinearVelocity(TMethodRunContext* run_context) 
		{
			//BaluLib::TVec2  value return --- nothing
			IClassPhysBodyIntance** obj = ((IClassPhysBodyIntance**)(run_context->object->get()));
			const BaluLib::TVec2&  param0 = *((BaluLib::TVec2*)(*run_context->formal_params)[0].get());
			(*obj)->SetLinearVelocity(param0);
		}
	}
	namespace ns_ISkeletonAnimation 
	{
		void bind_PlayAnimation(TMethodRunContext* run_context) 
		{
			//TString  name, float  pos return --- nothing
			ISkeletonAnimationInstance** obj = ((ISkeletonAnimationInstance**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const float&  param1 = *((float*)(*run_context->formal_params)[1].get());
			(*obj)->PlayAnimation(param0, param1);
		}
		void bind_StopAnimation(TMethodRunContext* run_context) 
		{
			//TString  name return --- nothing
			ISkeletonAnimationInstance** obj = ((ISkeletonAnimationInstance**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			(*obj)->StopAnimation(param0);
		}
	}
	namespace ns_TMouseEventArgs 
	{
	}
	namespace ns_TRot 
	{
		void bind_Set(TMethodRunContext* run_context) 
		{
			//float  value return --- nothing
			WorldDef::TRot* obj = ((WorldDef::TRot*)(run_context->object->get()));
			const float&  param0 = *((float*)(*run_context->formal_params)[0].get());
			obj->Set(param0);
		}
		void bind_SetIdentity(TMethodRunContext* run_context) 
		{
			// return --- nothing
			WorldDef::TRot* obj = ((WorldDef::TRot*)(run_context->object->get()));
			obj->SetIdentity();
		}
		void bind_GetAngle(TMethodRunContext* run_context) 
		{
			// return --- float
			WorldDef::TRot* obj = ((WorldDef::TRot*)(run_context->object->get()));
			float  result = 
			obj->GetAngle();
			*(float*)run_context->result->get() = result;
		}
	}
	namespace ns_TTransform 
	{
		void bind_Transform(TMethodRunContext* run_context) 
		{
			//BaluLib::TVec2  vertex, BaluLib::TVec2  scale return --- BaluLib::TVec2
			WorldDef::TTransform* obj = ((WorldDef::TTransform*)(run_context->object->get()));
			const BaluLib::TVec2&  param0 = *((BaluLib::TVec2*)(*run_context->formal_params)[0].get());
			const BaluLib::TVec2&  param1 = *((BaluLib::TVec2*)(*run_context->formal_params)[1].get());
			BaluLib::TVec2  result = 
			obj->Transform(param0, param1);
			*(BaluLib::TVec2*)run_context->result->get() = result;
		}
	}
	namespace ns_TTransformWithScale 
	{
	}
	namespace ns_IViewport 
	{
		void bind_SetSize(TMethodRunContext* run_context) 
		{
			//BaluLib::TVec2  size return --- nothing
			WorldDef::IViewport** obj = ((WorldDef::IViewport**)(run_context->object->get()));
			const BaluLib::TVec2&  param0 = *((BaluLib::TVec2*)(*run_context->formal_params)[0].get());
			(*obj)->SetSize(param0);
		}
		void bind_GetSize(TMethodRunContext* run_context) 
		{
			// return --- BaluLib::TVec2
			WorldDef::IViewport** obj = ((WorldDef::IViewport**)(run_context->object->get()));
			BaluLib::TVec2  result = 
			(*obj)->GetSize();
			*(BaluLib::TVec2*)run_context->result->get() = result;
		}
	}
	namespace ns_IProperties 
	{
		void bind_HasProperty(TMethodRunContext* run_context) 
		{
			//TString  name, WorldDef::RuntimePropertyType&  type return --- bool
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			WorldDef::RuntimePropertyType& param1 = *((WorldDef::RuntimePropertyType*)(*run_context->formal_params)[1].get());
			bool  result = 
			(*obj)->HasProperty(param0, param1);
			*(bool*)run_context->result->get() = result;
		}
		void bind_SetBool(TMethodRunContext* run_context) 
		{
			//TString  name, bool  value return --- nothing
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const bool&  param1 = *((bool*)(*run_context->formal_params)[1].get());
			(*obj)->SetBool(param0, param1);
		}
		void bind_GetBool(TMethodRunContext* run_context) 
		{
			//TString  name return --- bool
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			bool  result = 
			(*obj)->GetBool(param0);
			*(bool*)run_context->result->get() = result;
		}
		void bind_SetInt(TMethodRunContext* run_context) 
		{
			//TString  name, int  value return --- nothing
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const int&  param1 = *((int*)(*run_context->formal_params)[1].get());
			(*obj)->SetInt(param0, param1);
		}
		void bind_GetInt(TMethodRunContext* run_context) 
		{
			//TString  name return --- int
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			int  result = 
			(*obj)->GetInt(param0);
			*(int*)run_context->result->get() = result;
		}
		void bind_SetFloat(TMethodRunContext* run_context) 
		{
			//TString  name, float  value return --- nothing
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const float&  param1 = *((float*)(*run_context->formal_params)[1].get());
			(*obj)->SetFloat(param0, param1);
		}
		void bind_GetFloat(TMethodRunContext* run_context) 
		{
			//TString  name return --- float
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			float  result = 
			(*obj)->GetFloat(param0);
			*(float*)run_context->result->get() = result;
		}
		void bind_SetString(TMethodRunContext* run_context) 
		{
			//TString  name, TString  value return --- nothing
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const TString& temp_param1 = *((TString*)(*run_context->formal_params)[1].get());
			std::string param1 = Convert_TString_to_stdstring(temp_param1);
			(*obj)->SetString(param0, param1);
		}
		void bind_GetString(TMethodRunContext* run_context) 
		{
			//TString  name return --- TString
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			std::string temp_result = 
			(*obj)->GetString(param0);
			TString result = Convert_stdstring_to_TString(temp_result);
			*(TString*)run_context->result->get() = result;
		}
		void bind_SetVec2(TMethodRunContext* run_context) 
		{
			//TString  name, BaluLib::TVec2  value return --- nothing
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const BaluLib::TVec2&  param1 = *((BaluLib::TVec2*)(*run_context->formal_params)[1].get());
			(*obj)->SetVec2(param0, param1);
		}
		void bind_GetVec2(TMethodRunContext* run_context) 
		{
			//TString  name return --- BaluLib::TVec2
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			BaluLib::TVec2  result = 
			(*obj)->GetVec2(param0);
			*(BaluLib::TVec2*)run_context->result->get() = result;
		}
		void bind_SetTransformWithScale(TMethodRunContext* run_context) 
		{
			//TString  name, WorldDef::TTransformWithScale  value return --- nothing
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const WorldDef::TTransformWithScale&  param1 = *((WorldDef::TTransformWithScale*)(*run_context->formal_params)[1].get());
			(*obj)->SetTransformWithScale(param0, param1);
		}
		void bind_GetTransformWithScale(TMethodRunContext* run_context) 
		{
			//TString  name return --- WorldDef::TTransformWithScale
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			WorldDef::TTransformWithScale  result = 
			(*obj)->GetTransformWithScale(param0);
			*(WorldDef::TTransformWithScale*)run_context->result->get() = result;
		}
		void bind_SetTransform(TMethodRunContext* run_context) 
		{
			//TString  name, WorldDef::TTransform  value return --- nothing
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const WorldDef::TTransform&  param1 = *((WorldDef::TTransform*)(*run_context->formal_params)[1].get());
			(*obj)->SetTransform(param0, param1);
		}
		void bind_GetTransform(TMethodRunContext* run_context) 
		{
			//TString  name return --- WorldDef::TTransform
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			WorldDef::TTransform  result = 
			(*obj)->GetTransform(param0);
			*(WorldDef::TTransform*)run_context->result->get() = result;
		}
		void bind_SetRotation(TMethodRunContext* run_context) 
		{
			//TString  name, WorldDef::TRot  value return --- nothing
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const WorldDef::TRot&  param1 = *((WorldDef::TRot*)(*run_context->formal_params)[1].get());
			(*obj)->SetRotation(param0, param1);
		}
		void bind_GetRotation(TMethodRunContext* run_context) 
		{
			//TString  name return --- WorldDef::TRot
			WorldDef::IRuntimeProperties** obj = ((WorldDef::IRuntimeProperties**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			WorldDef::TRot  result = 
			(*obj)->GetRotation(param0);
			*(WorldDef::TRot*)run_context->result->get() = result;
		}
	}
	namespace ns_ISceneDef 
	{
		void bind_FindViewport(TMethodRunContext* run_context) 
		{
			//TString  name return --- WorldDef::IViewport
			WorldDef::IScene** obj = ((WorldDef::IScene**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			WorldDef::IViewport*  result = 
			(*obj)->FindViewport(param0);
			*(WorldDef::IViewport**)run_context->result->get() = result;
		}
	}
	namespace ns_IScene 
	{
		void bind_GetSource(TMethodRunContext* run_context) 
		{
			// return --- WorldDef::IScene
			IScene** obj = ((IScene**)(run_context->object->get()));
			WorldDef::IScene*  result = 
			(*obj)->GetSource();
			*(WorldDef::IScene**)run_context->result->get() = result;
		}
	}
	namespace ns_IComposerStage 
	{
	}
	namespace ns_IComposer 
	{
		void bind_AddToRender(TMethodRunContext* run_context) 
		{
			//IScene  scene, WorldDef::IViewport  viewport return --- nothing
			IComposer** obj = ((IComposer**)(run_context->object->get()));
			IScene* param0 = *((IScene**)(*run_context->formal_params)[0].get());
			WorldDef::IViewport* param1 = *((WorldDef::IViewport**)(*run_context->formal_params)[1].get());
			(*obj)->AddToRender(param0, param1);
		}
	}
	namespace ns_IWorldDef 
	{
		void bind_GetScene(TMethodRunContext* run_context) 
		{
			//TString  name return --- WorldDef::IScene
			WorldDef::IWorld** obj = ((WorldDef::IWorld**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			WorldDef::IScene*  result = 
			(*obj)->GetScene(param0);
			*(WorldDef::IScene**)run_context->result->get() = result;
		}
	}
	namespace ns_IWorld 
	{
		void bind_GetScene(TMethodRunContext* run_context) 
		{
			//int  index return --- IScene
			IWorld** obj = ((IWorld**)(run_context->object->get()));
			const int&  param0 = *((int*)(*run_context->formal_params)[0].get());
			IScene*  result = 
			(*obj)->GetScene(param0);
			*(IScene**)run_context->result->get() = result;
		}
		void bind_RunScene(TMethodRunContext* run_context) 
		{
			//WorldDef::IScene  scene return --- IScene
			IWorld** obj = ((IWorld**)(run_context->object->get()));
			WorldDef::IScene* param0 = *((WorldDef::IScene**)(*run_context->formal_params)[0].get());
			IScene*  result = 
			(*obj)->RunScene(param0);
			*(IScene**)run_context->result->get() = result;
		}
		void bind_GetSource(TMethodRunContext* run_context) 
		{
			// return --- WorldDef::IWorld
			IWorld** obj = ((IWorld**)(run_context->object->get()));
			WorldDef::IWorld*  result = 
			(*obj)->GetSource();
			*(WorldDef::IWorld**)run_context->result->get() = result;
		}
	}
	namespace ns_IDirector 
	{
		void bind_GetWorld(TMethodRunContext* run_context) 
		{
			// return --- IWorld
			IDirector** obj = ((IDirector**)(run_context->object->get()));
			IWorld*  result = 
			(*obj)->GetWorld();
			*(IWorld**)run_context->result->get() = result;
		}
	}
	namespace ns_IPhysShapeDef 
	{
		void bind_SetIsSensor(TMethodRunContext* run_context) 
		{
			//bool  is_sensor return --- nothing
			WorldDef::IPhysShape** obj = ((WorldDef::IPhysShape**)(run_context->object->get()));
			const bool&  param0 = *((bool*)(*run_context->formal_params)[0].get());
			(*obj)->SetIsSensor(param0);
		}
		void bind_GetIsSensor(TMethodRunContext* run_context) 
		{
			// return --- bool
			WorldDef::IPhysShape** obj = ((WorldDef::IPhysShape**)(run_context->object->get()));
			bool  result = 
			(*obj)->GetIsSensor();
			*(bool*)run_context->result->get() = result;
		}
	}
	namespace ns_IPhysShape 
	{
	}
	namespace ns_ISpritePolygonDef 
	{
		void bind_SetScale(TMethodRunContext* run_context) 
		{
			//BaluLib::TVec2  scale return --- nothing
			WorldDef::ISpritePolygon** obj = ((WorldDef::ISpritePolygon**)(run_context->object->get()));
			const BaluLib::TVec2&  param0 = *((BaluLib::TVec2*)(*run_context->formal_params)[0].get());
			(*obj)->SetScale(param0);
		}
	}
	namespace ns_ISpriteDef 
	{
		void bind_SetPhysShape(TMethodRunContext* run_context) 
		{
			//WorldDef::IPhysShape  shape return --- nothing
			WorldDef::ISprite** obj = ((WorldDef::ISprite**)(run_context->object->get()));
			WorldDef::IPhysShape* param0 = *((WorldDef::IPhysShape**)(*run_context->formal_params)[0].get());
			(*obj)->SetPhysShape(param0);
		}
		void bind_GetPhysShape(TMethodRunContext* run_context) 
		{
			// return --- WorldDef::IPhysShape
			WorldDef::ISprite** obj = ((WorldDef::ISprite**)(run_context->object->get()));
			WorldDef::IPhysShape*  result = 
			(*obj)->GetPhysShape();
			*(WorldDef::IPhysShape**)run_context->result->get() = result;
		}
		void bind_GetPolygon(TMethodRunContext* run_context) 
		{
			// return --- WorldDef::ISpritePolygon
			WorldDef::ISprite** obj = ((WorldDef::ISprite**)(run_context->object->get()));
			WorldDef::ISpritePolygon*  result = 
			(*obj)->GetPolygon();
			*(WorldDef::ISpritePolygon**)run_context->result->get() = result;
		}
	}
	namespace ns_ITransformedSpriteDef 
	{
		void bind_GetSprite(TMethodRunContext* run_context) 
		{
			// return --- WorldDef::ISprite
			WorldDef::ITransformedSprite** obj = ((WorldDef::ITransformedSprite**)(run_context->object->get()));
			WorldDef::ISprite*  result = 
			(*obj)->GetSprite();
			*(WorldDef::ISprite**)run_context->result->get() = result;
		}
	}
	namespace ns_ISpritePolygon 
	{
		void bind_SetActiveAnimation(TMethodRunContext* run_context) 
		{
			//TString  name return --- nothing
			ISpritePolygonInstance** obj = ((ISpritePolygonInstance**)(run_context->object->get()));
			const TString& temp_param0 = *((TString*)(*run_context->formal_params)[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			(*obj)->SetActiveAnimation(param0);
		}
	}
	namespace ns_ITransformedSprite 
	{
		void bind_GetSource(TMethodRunContext* run_context) 
		{
			// return --- WorldDef::ITransformedSprite
			ITransformedSpriteInstance** obj = ((ITransformedSpriteInstance**)(run_context->object->get()));
			WorldDef::ITransformedSprite*  result = 
			(*obj)->GetSource();
			*(WorldDef::ITransformedSprite**)run_context->result->get() = result;
		}
		void bind_GetPhysShape(TMethodRunContext* run_context) 
		{
			// return --- IPhysShapeInstance
			ITransformedSpriteInstance** obj = ((ITransformedSpriteInstance**)(run_context->object->get()));
			IPhysShapeInstance*  result = 
			(*obj)->GetPhysShape();
			*(IPhysShapeInstance**)run_context->result->get() = result;
		}
		void bind_GetScale(TMethodRunContext* run_context) 
		{
			// return --- BaluLib::TVec2
			ITransformedSpriteInstance** obj = ((ITransformedSpriteInstance**)(run_context->object->get()));
			BaluLib::TVec2  result = 
			(*obj)->GetScale();
			*(BaluLib::TVec2*)run_context->result->get() = result;
		}
		void bind_GetPolygon(TMethodRunContext* run_context) 
		{
			// return --- ISpritePolygonInstance
			ITransformedSpriteInstance** obj = ((ITransformedSpriteInstance**)(run_context->object->get()));
			ISpritePolygonInstance*  result = 
			(*obj)->GetPolygon();
			*(ISpritePolygonInstance**)run_context->result->get() = result;
		}
	}
	namespace ns_IInstance 
	{
		void bind_SetScale(TMethodRunContext* run_context) 
		{
			//BaluLib::TVec2  scale return --- nothing
			ITransformedClassInstance** obj = ((ITransformedClassInstance**)(run_context->object->get()));
			const BaluLib::TVec2&  param0 = *((BaluLib::TVec2*)(*run_context->formal_params)[0].get());
			(*obj)->SetScale(param0);
		}
		void bind_GetProperties(TMethodRunContext* run_context) 
		{
			// return --- WorldDef::IRuntimeProperties
			ITransformedClassInstance** obj = ((ITransformedClassInstance**)(run_context->object->get()));
			WorldDef::IRuntimeProperties*  result = 
			(*obj)->GetProperties();
			*(WorldDef::IRuntimeProperties**)run_context->result->get() = result;
		}
		void bind_GetPhysBody(TMethodRunContext* run_context) 
		{
			// return --- IClassPhysBodyIntance
			ITransformedClassInstance** obj = ((ITransformedClassInstance**)(run_context->object->get()));
			IClassPhysBodyIntance*  result = 
			(*obj)->GetPhysBody();
			*(IClassPhysBodyIntance**)run_context->result->get() = result;
		}
		void bind_GetSprite(TMethodRunContext* run_context) 
		{
			//int  index return --- ITransformedSpriteInstance
			ITransformedClassInstance** obj = ((ITransformedClassInstance**)(run_context->object->get()));
			const int&  param0 = *((int*)(*run_context->formal_params)[0].get());
			ITransformedSpriteInstance*  result = 
			(*obj)->GetSprite(param0);
			*(ITransformedSpriteInstance**)run_context->result->get() = result;
		}
		void bind_GetSkeletonAnimation(TMethodRunContext* run_context) 
		{
			// return --- ISkeletonAnimationInstance
			ITransformedClassInstance** obj = ((ITransformedClassInstance**)(run_context->object->get()));
			ISkeletonAnimationInstance*  result = 
			(*obj)->GetSkeletonAnimation();
			*(ISkeletonAnimationInstance**)run_context->result->get() = result;
		}
	}
}
namespace ns_Script
{
	std::vector<SemanticApi::TExternalSMethod> Register()
	{
		std::vector<SemanticApi::TExternalSMethod> result;
		result.push_back(ns_Script::ns_TFrame::bind_GetLeftBottom);
		result.push_back(ns_Script::ns_TFrame::bind_GetRightTop);
		result.push_back(ns_Script::ns_IClassPhysBody::bind_GetLinearVelocity);
		result.push_back(ns_Script::ns_IClassPhysBody::bind_SetLinearVelocity);
		result.push_back(ns_Script::ns_ISkeletonAnimation::bind_PlayAnimation);
		result.push_back(ns_Script::ns_ISkeletonAnimation::bind_StopAnimation);
		result.push_back(ns_Script::ns_TRot::bind_Set);
		result.push_back(ns_Script::ns_TRot::bind_SetIdentity);
		result.push_back(ns_Script::ns_TRot::bind_GetAngle);
		result.push_back(ns_Script::ns_TTransform::bind_Transform);
		result.push_back(ns_Script::ns_IViewport::bind_SetSize);
		result.push_back(ns_Script::ns_IViewport::bind_GetSize);
		result.push_back(ns_Script::ns_IProperties::bind_HasProperty);
		result.push_back(ns_Script::ns_IProperties::bind_SetBool);
		result.push_back(ns_Script::ns_IProperties::bind_GetBool);
		result.push_back(ns_Script::ns_IProperties::bind_SetInt);
		result.push_back(ns_Script::ns_IProperties::bind_GetInt);
		result.push_back(ns_Script::ns_IProperties::bind_SetFloat);
		result.push_back(ns_Script::ns_IProperties::bind_GetFloat);
		result.push_back(ns_Script::ns_IProperties::bind_SetString);
		result.push_back(ns_Script::ns_IProperties::bind_GetString);
		result.push_back(ns_Script::ns_IProperties::bind_SetVec2);
		result.push_back(ns_Script::ns_IProperties::bind_GetVec2);
		result.push_back(ns_Script::ns_IProperties::bind_SetTransformWithScale);
		result.push_back(ns_Script::ns_IProperties::bind_GetTransformWithScale);
		result.push_back(ns_Script::ns_IProperties::bind_SetTransform);
		result.push_back(ns_Script::ns_IProperties::bind_GetTransform);
		result.push_back(ns_Script::ns_IProperties::bind_SetRotation);
		result.push_back(ns_Script::ns_IProperties::bind_GetRotation);
		result.push_back(ns_Script::ns_ISceneDef::bind_FindViewport);
		result.push_back(ns_Script::ns_IScene::bind_GetSource);
		result.push_back(ns_Script::ns_IComposer::bind_AddToRender);
		result.push_back(ns_Script::ns_IWorldDef::bind_GetScene);
		result.push_back(ns_Script::ns_IWorld::bind_GetScene);
		result.push_back(ns_Script::ns_IWorld::bind_RunScene);
		result.push_back(ns_Script::ns_IWorld::bind_GetSource);
		result.push_back(ns_Script::ns_IDirector::bind_GetWorld);
		result.push_back(ns_Script::ns_IPhysShapeDef::bind_SetIsSensor);
		result.push_back(ns_Script::ns_IPhysShapeDef::bind_GetIsSensor);
		result.push_back(ns_Script::ns_ISpritePolygonDef::bind_SetScale);
		result.push_back(ns_Script::ns_ISpriteDef::bind_SetPhysShape);
		result.push_back(ns_Script::ns_ISpriteDef::bind_GetPhysShape);
		result.push_back(ns_Script::ns_ISpriteDef::bind_GetPolygon);
		result.push_back(ns_Script::ns_ITransformedSpriteDef::bind_GetSprite);
		result.push_back(ns_Script::ns_ISpritePolygon::bind_SetActiveAnimation);
		result.push_back(ns_Script::ns_ITransformedSprite::bind_GetSource);
		result.push_back(ns_Script::ns_ITransformedSprite::bind_GetPhysShape);
		result.push_back(ns_Script::ns_ITransformedSprite::bind_GetScale);
		result.push_back(ns_Script::ns_ITransformedSprite::bind_GetPolygon);
		result.push_back(ns_Script::ns_IInstance::bind_SetScale);
		result.push_back(ns_Script::ns_IInstance::bind_GetProperties);
		result.push_back(ns_Script::ns_IInstance::bind_GetPhysBody);
		result.push_back(ns_Script::ns_IInstance::bind_GetSprite);
		result.push_back(ns_Script::ns_IInstance::bind_GetSkeletonAnimation);
		return result;
	}
	const int BindingOffset = 17;
	const int BindingCount = 54;
}
