//auto-generated code
namespace ns_Script 
{
	void callScriptFromC_Print(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, const float p0 /*v*/) 
	{
		TMethodRunContext method_context(&global_context);
		auto& params=method_context.GetFormalParams();
		params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
		*(float*)params[0].get() = p0;
		TreeRunner::Run(compiled_method, method_context);
	}
	namespace ns_int 
	{
		void callScriptFromC_operator_PlusA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, int& p0 /*l*/, const int p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_operator_MinusA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, int& p0 /*l*/, const int p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_operator_MulA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, int& p0 /*l*/, const int p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_operator_DivA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, int& p0 /*l*/, const int p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_operator_PercentA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, int& p0 /*l*/, const int p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_operator_Increment(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, int& p0 /*l*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int**)params[0].get() = &p0;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_operator_Decrement(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, int& p0 /*l*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("int"))));
			*(int**)params[0].get() = &p0;
			TreeRunner::Run(compiled_method, method_context);
		}
	}
	namespace ns_float 
	{
		void callScriptFromC_operator_PlusA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, float& p0 /*l*/, const float p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_operator_MinusA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, float& p0 /*l*/, const float p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_operator_MulA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, float& p0 /*l*/, const float p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_operator_DivA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, float& p0 /*l*/, const float p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("float"))));
			*(float*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
	}
	namespace ns_bool 
	{
	}
	namespace ns_vec2 
	{
		void callScriptFromC_operator_PlusA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2& p0 /*l*/, const BaluLib::TVec2 p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_operator_MinusA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2& p0 /*l*/, const BaluLib::TVec2 p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_operator_MulA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2& p0 /*l*/, const BaluLib::TVec2 p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_operator_DivA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2& p0 /*l*/, const BaluLib::TVec2 p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2"))));
			*(BaluLib::TVec2*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
	}
	namespace ns_vec2i 
	{
		void callScriptFromC_operator_PlusA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2i& p0 /*l*/, const BaluLib::TVec2i p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_operator_MinusA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2i& p0 /*l*/, const BaluLib::TVec2i p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_operator_MulA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2i& p0 /*l*/, const BaluLib::TVec2i p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_operator_DivA(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, BaluLib::TVec2i& p0 /*l*/, const BaluLib::TVec2i p1 /*r*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(true, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i**)params[0].get() = &p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
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
		void callScriptFromC_MouseUp_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, std::shared_ptr<IWorld> const &p0 /*world*/, const WorldDef::TMouseEventArgs p1 /*event*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IWorld"))));
			*(TScriptSharedPointer<IWorld>*)params[0].get() = TScriptSharedPointer<IWorld>(p0);
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("TMouseEventArgs"))));
			*(WorldDef::TMouseEventArgs*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
			{
				TStackValue destructor_result;
				std::vector<TStackValue> without_params;
				TMethodRunContext method_run_context(&global_context);
				method_run_context.GetObject() = params[0];
				TreeRunner::Run(method_run_context.GetObject().GetClass()->GetDestructor(), method_run_context);
			}
		}
		void callScriptFromC_MouseDown_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, std::shared_ptr<IWorld> const &p0 /*world*/, const WorldDef::TMouseEventArgs p1 /*event*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IWorld"))));
			*(TScriptSharedPointer<IWorld>*)params[0].get() = TScriptSharedPointer<IWorld>(p0);
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("TMouseEventArgs"))));
			*(WorldDef::TMouseEventArgs*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
			{
				TStackValue destructor_result;
				std::vector<TStackValue> without_params;
				TMethodRunContext method_run_context(&global_context);
				method_run_context.GetObject() = params[0];
				TreeRunner::Run(method_run_context.GetObject().GetClass()->GetDestructor(), method_run_context);
			}
		}
		void callScriptFromC_MouseMove_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, std::shared_ptr<IWorld> const &p0 /*world*/, const WorldDef::TMouseEventArgs p1 /*event*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IWorld"))));
			*(TScriptSharedPointer<IWorld>*)params[0].get() = TScriptSharedPointer<IWorld>(p0);
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("TMouseEventArgs"))));
			*(WorldDef::TMouseEventArgs*)params[1].get() = p1;
			TreeRunner::Run(compiled_method, method_context);
			{
				TStackValue destructor_result;
				std::vector<TStackValue> without_params;
				TMethodRunContext method_run_context(&global_context);
				method_run_context.GetObject() = params[0];
				TreeRunner::Run(method_run_context.GetObject().GetClass()->GetDestructor(), method_run_context);
			}
		}
		void callScriptFromC_WorldStart_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, std::shared_ptr<IWorld> const &p0 /*world*/, std::shared_ptr<IComposer> const &p1 /*composer*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IWorld"))));
			*(TScriptSharedPointer<IWorld>*)params[0].get() = TScriptSharedPointer<IWorld>(p0);
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IComposer"))));
			*(TScriptSharedPointer<IComposer>*)params[1].get() = TScriptSharedPointer<IComposer>(p1);
			TreeRunner::Run(compiled_method, method_context);
			{
				TStackValue destructor_result;
				std::vector<TStackValue> without_params;
				TMethodRunContext method_run_context(&global_context);
				method_run_context.GetObject() = params[0];
				TreeRunner::Run(method_run_context.GetObject().GetClass()->GetDestructor(), method_run_context);
			}
			{
				TStackValue destructor_result;
				std::vector<TStackValue> without_params;
				TMethodRunContext method_run_context(&global_context);
				method_run_context.GetObject() = params[1];
				TreeRunner::Run(method_run_context.GetObject().GetClass()->GetDestructor(), method_run_context);
			}
		}
		void callScriptFromC_ViewportResize_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, std::shared_ptr<IDirector> const &p0 /*director*/, const BaluLib::TVec2i p1 /*old_size*/, const BaluLib::TVec2i p2 /*new_size*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IDirector"))));
			*(TScriptSharedPointer<IDirector>*)params[0].get() = TScriptSharedPointer<IDirector>(p0);
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i*)params[1].get() = p1;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("vec2i"))));
			*(BaluLib::TVec2i*)params[2].get() = p2;
			TreeRunner::Run(compiled_method, method_context);
			{
				TStackValue destructor_result;
				std::vector<TStackValue> without_params;
				TMethodRunContext method_run_context(&global_context);
				method_run_context.GetObject() = params[0];
				TreeRunner::Run(method_run_context.GetObject().GetClass()->GetDestructor(), method_run_context);
			}
		}
		void callScriptFromC_BeforePhysics_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_KeyDown_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, const WorldDef::TKey p0 /*key*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("TKey"))));
			*(WorldDef::TKey*)params[0].get() = p0;
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_KeyUp_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, const WorldDef::TKey p0 /*key*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("TKey"))));
			*(WorldDef::TKey*)params[0].get() = p0;
			TreeRunner::Run(compiled_method, method_context);
		}
	}
	namespace ns_GlobalKeyCallback 
	{
		void callScriptFromC_KeyDown_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			TreeRunner::Run(compiled_method, method_context);
		}
		void callScriptFromC_KeyUp_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			TreeRunner::Run(compiled_method, method_context);
		}
	}
	namespace ns_ClassCallback 
	{
		void callScriptFromC_BeforePhysics_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, std::shared_ptr<ITransformedClassInstance> const &p0 /*object*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(TScriptSharedPointer<ITransformedClassInstance>*)params[0].get() = TScriptSharedPointer<ITransformedClassInstance>(p0);
			TreeRunner::Run(compiled_method, method_context);
			{
				TStackValue destructor_result;
				std::vector<TStackValue> without_params;
				TMethodRunContext method_run_context(&global_context);
				method_run_context.GetObject() = params[0];
				TreeRunner::Run(method_run_context.GetObject().GetClass()->GetDestructor(), method_run_context);
			}
		}
		void callScriptFromC_KeyDown_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, const WorldDef::TKey p0 /*key*/, std::shared_ptr<ITransformedClassInstance> const &p1 /*object*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("TKey"))));
			*(WorldDef::TKey*)params[0].get() = p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(TScriptSharedPointer<ITransformedClassInstance>*)params[1].get() = TScriptSharedPointer<ITransformedClassInstance>(p1);
			TreeRunner::Run(compiled_method, method_context);
			{
				TStackValue destructor_result;
				std::vector<TStackValue> without_params;
				TMethodRunContext method_run_context(&global_context);
				method_run_context.GetObject() = params[1];
				TreeRunner::Run(method_run_context.GetObject().GetClass()->GetDestructor(), method_run_context);
			}
		}
		void callScriptFromC_KeyUp_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, const WorldDef::TKey p0 /*key*/, std::shared_ptr<ITransformedClassInstance> const &p1 /*object*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("TKey"))));
			*(WorldDef::TKey*)params[0].get() = p0;
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(TScriptSharedPointer<ITransformedClassInstance>*)params[1].get() = TScriptSharedPointer<ITransformedClassInstance>(p1);
			TreeRunner::Run(compiled_method, method_context);
			{
				TStackValue destructor_result;
				std::vector<TStackValue> without_params;
				TMethodRunContext method_run_context(&global_context);
				method_run_context.GetObject() = params[1];
				TreeRunner::Run(method_run_context.GetObject().GetClass()->GetDestructor(), method_run_context);
			}
		}
		void callScriptFromC_Created_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, std::shared_ptr<ITransformedClassInstance> const &p0 /*object*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(TScriptSharedPointer<ITransformedClassInstance>*)params[0].get() = TScriptSharedPointer<ITransformedClassInstance>(p0);
			TreeRunner::Run(compiled_method, method_context);
			{
				TStackValue destructor_result;
				std::vector<TStackValue> without_params;
				TMethodRunContext method_run_context(&global_context);
				method_run_context.GetObject() = params[0];
				TreeRunner::Run(method_run_context.GetObject().GetClass()->GetDestructor(), method_run_context);
			}
		}
	}
	namespace ns_ClassKeyCallback 
	{
		void callScriptFromC_KeyDown_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, std::shared_ptr<ITransformedClassInstance> const &p0 /*object*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(TScriptSharedPointer<ITransformedClassInstance>*)params[0].get() = TScriptSharedPointer<ITransformedClassInstance>(p0);
			TreeRunner::Run(compiled_method, method_context);
			{
				TStackValue destructor_result;
				std::vector<TStackValue> without_params;
				TMethodRunContext method_run_context(&global_context);
				method_run_context.GetObject() = params[0];
				TreeRunner::Run(method_run_context.GetObject().GetClass()->GetDestructor(), method_run_context);
			}
		}
		void callScriptFromC_KeyUp_(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, std::shared_ptr<ITransformedClassInstance> const &p0 /*object*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(TScriptSharedPointer<ITransformedClassInstance>*)params[0].get() = TScriptSharedPointer<ITransformedClassInstance>(p0);
			TreeRunner::Run(compiled_method, method_context);
			{
				TStackValue destructor_result;
				std::vector<TStackValue> without_params;
				TMethodRunContext method_run_context(&global_context);
				method_run_context.GetObject() = params[0];
				TreeRunner::Run(method_run_context.GetObject().GetClass()->GetDestructor(), method_run_context);
			}
		}
	}
	namespace ns_OnCollideCallback 
	{
		void callScriptFromC_Collide(TGlobalRunContext& global_context, SemanticApi::ISMethod* compiled_method, ISyntaxAnalyzer* syntax, std::shared_ptr<ITransformedClassInstance> const &p0 /*object*/, std::shared_ptr<IPhysShapeInstance> const &p1 /*source*/, std::shared_ptr<ITransformedClassInstance> const &p2 /*obstancle*/) 
		{
			TMethodRunContext method_context(&global_context);
			auto& params=method_context.GetFormalParams();
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(TScriptSharedPointer<ITransformedClassInstance>*)params[0].get() = TScriptSharedPointer<ITransformedClassInstance>(p0);
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IPhysShape"))));
			*(TScriptSharedPointer<IPhysShapeInstance>*)params[1].get() = TScriptSharedPointer<IPhysShapeInstance>(p1);
			params.push_back(TStackValue(false, syntax->GetCompiledBaseClass()->GetClass(syntax->GetLexer()->GetIdFromName("IInstance"))));
			*(TScriptSharedPointer<ITransformedClassInstance>*)params[2].get() = TScriptSharedPointer<ITransformedClassInstance>(p2);
			TreeRunner::Run(compiled_method, method_context);
			{
				TStackValue destructor_result;
				std::vector<TStackValue> without_params;
				TMethodRunContext method_run_context(&global_context);
				method_run_context.GetObject() = params[0];
				TreeRunner::Run(method_run_context.GetObject().GetClass()->GetDestructor(), method_run_context);
			}
			{
				TStackValue destructor_result;
				std::vector<TStackValue> without_params;
				TMethodRunContext method_run_context(&global_context);
				method_run_context.GetObject() = params[1];
				TreeRunner::Run(method_run_context.GetObject().GetClass()->GetDestructor(), method_run_context);
			}
			{
				TStackValue destructor_result;
				std::vector<TStackValue> without_params;
				TMethodRunContext method_run_context(&global_context);
				method_run_context.GetObject() = params[2];
				TreeRunner::Run(method_run_context.GetObject().GetClass()->GetDestructor(), method_run_context);
			}
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
	namespace ns_TPtr 
	{
	}
	namespace ns_TFrame 
	{
		void bind_GetLeftBottom(TMethodRunContext& run_context) 
		{
			// return --- BaluLib::TVec2
			WorldDef::TFrame* obj = ((WorldDef::TFrame*)(run_context.GetObject().get()));
			BaluLib::TVec2  result = 
			obj->GetLeftBottom();
			*(BaluLib::TVec2*)run_context.GetResult().get() = result;
		}
		void bind_GetRightTop(TMethodRunContext& run_context) 
		{
			// return --- BaluLib::TVec2
			WorldDef::TFrame* obj = ((WorldDef::TFrame*)(run_context.GetObject().get()));
			BaluLib::TVec2  result = 
			obj->GetRightTop();
			*(BaluLib::TVec2*)run_context.GetResult().get() = result;
		}
	}
	namespace ns_IClassPhysBody 
	{
		void bind_def_constr(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<IClassPhysBodyIntance>* obj = ((TScriptSharedPointer<IClassPhysBodyIntance>*)(run_context.GetObject().get()));
			obj->def_constr();
		}
		void bind_copy_constr(TMethodRunContext& run_context) 
		{
			//IClassPhysBodyIntance&  copy_from return --- nothing
			TScriptSharedPointer<IClassPhysBodyIntance>* obj = ((TScriptSharedPointer<IClassPhysBodyIntance>*)(run_context.GetObject().get()));
			TScriptSharedPointer<IClassPhysBodyIntance>* param0 = ((TScriptSharedPointer<IClassPhysBodyIntance>*)run_context.GetFormalParams()[0].get());
			obj->copy_constr(param0);
		}
		void bind_destructor(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<IClassPhysBodyIntance>* obj = ((TScriptSharedPointer<IClassPhysBodyIntance>*)(run_context.GetObject().get()));
			obj->destructor();
		}
		void bind_operator_Assign(TMethodRunContext& run_context) 
		{
			//static - IClassPhysBodyIntance&  v, IClassPhysBodyIntance&  l return --- nothing
			TScriptSharedPointer<IClassPhysBodyIntance>* param0 = ((TScriptSharedPointer<IClassPhysBodyIntance>*)run_context.GetFormalParams()[0].get());
			TScriptSharedPointer<IClassPhysBodyIntance>* param1 = ((TScriptSharedPointer<IClassPhysBodyIntance>*)run_context.GetFormalParams()[1].get());
			param0->operator_Assign(param1);
		}
		void bind_GetLinearVelocity(TMethodRunContext& run_context) 
		{
			// return --- BaluLib::TVec2
			TScriptSharedPointer<IClassPhysBodyIntance>* obj = ((TScriptSharedPointer<IClassPhysBodyIntance>*)(run_context.GetObject().get()));
			BaluLib::TVec2  result = 
			(*obj)->GetLinearVelocity();
			*(BaluLib::TVec2*)run_context.GetResult().get() = result;
		}
		void bind_SetLinearVelocity(TMethodRunContext& run_context) 
		{
			//BaluLib::TVec2  value return --- nothing
			TScriptSharedPointer<IClassPhysBodyIntance>* obj = ((TScriptSharedPointer<IClassPhysBodyIntance>*)(run_context.GetObject().get()));
			const BaluLib::TVec2&  param0 = *((BaluLib::TVec2*)run_context.GetFormalParams()[0].get());
			(*obj)->SetLinearVelocity(param0);
		}
	}
	namespace ns_ISkeletonAnimation 
	{
		void bind_def_constr(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<ISkeletonAnimationInstance>* obj = ((TScriptSharedPointer<ISkeletonAnimationInstance>*)(run_context.GetObject().get()));
			obj->def_constr();
		}
		void bind_copy_constr(TMethodRunContext& run_context) 
		{
			//ISkeletonAnimationInstance&  copy_from return --- nothing
			TScriptSharedPointer<ISkeletonAnimationInstance>* obj = ((TScriptSharedPointer<ISkeletonAnimationInstance>*)(run_context.GetObject().get()));
			TScriptSharedPointer<ISkeletonAnimationInstance>* param0 = ((TScriptSharedPointer<ISkeletonAnimationInstance>*)run_context.GetFormalParams()[0].get());
			obj->copy_constr(param0);
		}
		void bind_destructor(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<ISkeletonAnimationInstance>* obj = ((TScriptSharedPointer<ISkeletonAnimationInstance>*)(run_context.GetObject().get()));
			obj->destructor();
		}
		void bind_operator_Assign(TMethodRunContext& run_context) 
		{
			//static - ISkeletonAnimationInstance&  v, ISkeletonAnimationInstance&  l return --- nothing
			TScriptSharedPointer<ISkeletonAnimationInstance>* param0 = ((TScriptSharedPointer<ISkeletonAnimationInstance>*)run_context.GetFormalParams()[0].get());
			TScriptSharedPointer<ISkeletonAnimationInstance>* param1 = ((TScriptSharedPointer<ISkeletonAnimationInstance>*)run_context.GetFormalParams()[1].get());
			param0->operator_Assign(param1);
		}
		void bind_PlayAnimation(TMethodRunContext& run_context) 
		{
			//TString  name, float  pos return --- nothing
			TScriptSharedPointer<ISkeletonAnimationInstance>* obj = ((TScriptSharedPointer<ISkeletonAnimationInstance>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const float&  param1 = *((float*)run_context.GetFormalParams()[1].get());
			(*obj)->PlayAnimation(param0, param1);
		}
		void bind_StopAnimation(TMethodRunContext& run_context) 
		{
			//TString  name return --- nothing
			TScriptSharedPointer<ISkeletonAnimationInstance>* obj = ((TScriptSharedPointer<ISkeletonAnimationInstance>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			(*obj)->StopAnimation(param0);
		}
	}
	namespace ns_TMouseEventArgs 
	{
	}
	namespace ns_TRot 
	{
		void bind_Set(TMethodRunContext& run_context) 
		{
			//float  value return --- nothing
			WorldDef::TRot* obj = ((WorldDef::TRot*)(run_context.GetObject().get()));
			const float&  param0 = *((float*)run_context.GetFormalParams()[0].get());
			obj->Set(param0);
		}
		void bind_SetIdentity(TMethodRunContext& run_context) 
		{
			// return --- nothing
			WorldDef::TRot* obj = ((WorldDef::TRot*)(run_context.GetObject().get()));
			obj->SetIdentity();
		}
		void bind_GetAngle(TMethodRunContext& run_context) 
		{
			// return --- float
			WorldDef::TRot* obj = ((WorldDef::TRot*)(run_context.GetObject().get()));
			float  result = 
			obj->GetAngle();
			*(float*)run_context.GetResult().get() = result;
		}
	}
	namespace ns_TTransform 
	{
		void bind_Transform(TMethodRunContext& run_context) 
		{
			//BaluLib::TVec2  vertex, BaluLib::TVec2  scale return --- BaluLib::TVec2
			WorldDef::TTransform* obj = ((WorldDef::TTransform*)(run_context.GetObject().get()));
			const BaluLib::TVec2&  param0 = *((BaluLib::TVec2*)run_context.GetFormalParams()[0].get());
			const BaluLib::TVec2&  param1 = *((BaluLib::TVec2*)run_context.GetFormalParams()[1].get());
			BaluLib::TVec2  result = 
			obj->Transform(param0, param1);
			*(BaluLib::TVec2*)run_context.GetResult().get() = result;
		}
	}
	namespace ns_TTransformWithScale 
	{
	}
	namespace ns_IViewport 
	{
		void bind_SetSize(TMethodRunContext& run_context) 
		{
			//BaluLib::TVec2  size return --- nothing
			WorldDef::IViewport** obj = ((WorldDef::IViewport**)(run_context.GetObject().get()));
			const BaluLib::TVec2&  param0 = *((BaluLib::TVec2*)run_context.GetFormalParams()[0].get());
			(*obj)->SetSize(param0);
		}
		void bind_GetSize(TMethodRunContext& run_context) 
		{
			// return --- BaluLib::TVec2
			WorldDef::IViewport** obj = ((WorldDef::IViewport**)(run_context.GetObject().get()));
			BaluLib::TVec2  result = 
			(*obj)->GetSize();
			*(BaluLib::TVec2*)run_context.GetResult().get() = result;
		}
	}
	namespace ns_IProperties 
	{
		void bind_def_constr(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			obj->def_constr();
		}
		void bind_copy_constr(TMethodRunContext& run_context) 
		{
			//WorldDef::IRuntimeProperties&  copy_from return --- nothing
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* param0 = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)run_context.GetFormalParams()[0].get());
			obj->copy_constr(param0);
		}
		void bind_destructor(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			obj->destructor();
		}
		void bind_operator_Assign(TMethodRunContext& run_context) 
		{
			//static - WorldDef::IRuntimeProperties&  v, WorldDef::IRuntimeProperties&  l return --- nothing
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* param0 = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)run_context.GetFormalParams()[0].get());
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* param1 = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)run_context.GetFormalParams()[1].get());
			param0->operator_Assign(param1);
		}
		void bind_HasProperty(TMethodRunContext& run_context) 
		{
			//TString  name, WorldDef::RuntimePropertyType&  type return --- bool
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			WorldDef::RuntimePropertyType& param1 = *((WorldDef::RuntimePropertyType*)run_context.GetFormalParams()[1].get());
			bool  result = 
			(*obj)->HasProperty(param0, param1);
			*(bool*)run_context.GetResult().get() = result;
		}
		void bind_SetBool(TMethodRunContext& run_context) 
		{
			//TString  name, bool  value return --- nothing
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const bool&  param1 = *((bool*)run_context.GetFormalParams()[1].get());
			(*obj)->SetBool(param0, param1);
		}
		void bind_GetBool(TMethodRunContext& run_context) 
		{
			//TString  name return --- bool
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			bool  result = 
			(*obj)->GetBool(param0);
			*(bool*)run_context.GetResult().get() = result;
		}
		void bind_SetInt(TMethodRunContext& run_context) 
		{
			//TString  name, int  value return --- nothing
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const int&  param1 = *((int*)run_context.GetFormalParams()[1].get());
			(*obj)->SetInt(param0, param1);
		}
		void bind_GetInt(TMethodRunContext& run_context) 
		{
			//TString  name return --- int
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			int  result = 
			(*obj)->GetInt(param0);
			*(int*)run_context.GetResult().get() = result;
		}
		void bind_SetFloat(TMethodRunContext& run_context) 
		{
			//TString  name, float  value return --- nothing
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const float&  param1 = *((float*)run_context.GetFormalParams()[1].get());
			(*obj)->SetFloat(param0, param1);
		}
		void bind_GetFloat(TMethodRunContext& run_context) 
		{
			//TString  name return --- float
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			float  result = 
			(*obj)->GetFloat(param0);
			*(float*)run_context.GetResult().get() = result;
		}
		void bind_SetString(TMethodRunContext& run_context) 
		{
			//TString  name, TString  value return --- nothing
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const TString& temp_param1 = *((TString*)run_context.GetFormalParams()[1].get());
			std::string param1 = Convert_TString_to_stdstring(temp_param1);
			(*obj)->SetString(param0, param1);
		}
		void bind_GetString(TMethodRunContext& run_context) 
		{
			//TString  name return --- TString
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			std::string temp_result = 
			(*obj)->GetString(param0);
			TString result = Convert_stdstring_to_TString(temp_result);
			*(TString*)run_context.GetResult().get() = result;
		}
		void bind_SetVec2(TMethodRunContext& run_context) 
		{
			//TString  name, BaluLib::TVec2  value return --- nothing
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const BaluLib::TVec2&  param1 = *((BaluLib::TVec2*)run_context.GetFormalParams()[1].get());
			(*obj)->SetVec2(param0, param1);
		}
		void bind_GetVec2(TMethodRunContext& run_context) 
		{
			//TString  name return --- BaluLib::TVec2
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			BaluLib::TVec2  result = 
			(*obj)->GetVec2(param0);
			*(BaluLib::TVec2*)run_context.GetResult().get() = result;
		}
		void bind_SetTransformWithScale(TMethodRunContext& run_context) 
		{
			//TString  name, WorldDef::TTransformWithScale  value return --- nothing
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const WorldDef::TTransformWithScale&  param1 = *((WorldDef::TTransformWithScale*)run_context.GetFormalParams()[1].get());
			(*obj)->SetTransformWithScale(param0, param1);
		}
		void bind_GetTransformWithScale(TMethodRunContext& run_context) 
		{
			//TString  name return --- WorldDef::TTransformWithScale
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			WorldDef::TTransformWithScale  result = 
			(*obj)->GetTransformWithScale(param0);
			*(WorldDef::TTransformWithScale*)run_context.GetResult().get() = result;
		}
		void bind_SetTransform(TMethodRunContext& run_context) 
		{
			//TString  name, WorldDef::TTransform  value return --- nothing
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const WorldDef::TTransform&  param1 = *((WorldDef::TTransform*)run_context.GetFormalParams()[1].get());
			(*obj)->SetTransform(param0, param1);
		}
		void bind_GetTransform(TMethodRunContext& run_context) 
		{
			//TString  name return --- WorldDef::TTransform
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			WorldDef::TTransform  result = 
			(*obj)->GetTransform(param0);
			*(WorldDef::TTransform*)run_context.GetResult().get() = result;
		}
		void bind_SetRotation(TMethodRunContext& run_context) 
		{
			//TString  name, WorldDef::TRot  value return --- nothing
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			const WorldDef::TRot&  param1 = *((WorldDef::TRot*)run_context.GetFormalParams()[1].get());
			(*obj)->SetRotation(param0, param1);
		}
		void bind_GetRotation(TMethodRunContext& run_context) 
		{
			//TString  name return --- WorldDef::TRot
			TScriptSharedPointer<WorldDef::IRuntimeProperties>* obj = ((TScriptSharedPointer<WorldDef::IRuntimeProperties>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			WorldDef::TRot  result = 
			(*obj)->GetRotation(param0);
			*(WorldDef::TRot*)run_context.GetResult().get() = result;
		}
	}
	namespace ns_ISceneDef 
	{
		void bind_FindViewport(TMethodRunContext& run_context) 
		{
			//TString  name return --- WorldDef::IViewport
			WorldDef::IScene** obj = ((WorldDef::IScene**)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			WorldDef::IViewport*  result = 
			(*obj)->FindViewport(param0);
			*(WorldDef::IViewport**)run_context.GetResult().get() = result;
		}
	}
	namespace ns_IScene 
	{
		void bind_def_constr(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<IScene>* obj = ((TScriptSharedPointer<IScene>*)(run_context.GetObject().get()));
			obj->def_constr();
		}
		void bind_copy_constr(TMethodRunContext& run_context) 
		{
			//IScene&  copy_from return --- nothing
			TScriptSharedPointer<IScene>* obj = ((TScriptSharedPointer<IScene>*)(run_context.GetObject().get()));
			TScriptSharedPointer<IScene>* param0 = ((TScriptSharedPointer<IScene>*)run_context.GetFormalParams()[0].get());
			obj->copy_constr(param0);
		}
		void bind_destructor(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<IScene>* obj = ((TScriptSharedPointer<IScene>*)(run_context.GetObject().get()));
			obj->destructor();
		}
		void bind_operator_Assign(TMethodRunContext& run_context) 
		{
			//static - IScene&  v, IScene&  l return --- nothing
			TScriptSharedPointer<IScene>* param0 = ((TScriptSharedPointer<IScene>*)run_context.GetFormalParams()[0].get());
			TScriptSharedPointer<IScene>* param1 = ((TScriptSharedPointer<IScene>*)run_context.GetFormalParams()[1].get());
			param0->operator_Assign(param1);
		}
		void bind_GetSource(TMethodRunContext& run_context) 
		{
			// return --- WorldDef::IScene
			TScriptSharedPointer<IScene>* obj = ((TScriptSharedPointer<IScene>*)(run_context.GetObject().get()));
			WorldDef::IScene*  result = 
			(*obj)->GetSource();
			*(WorldDef::IScene**)run_context.GetResult().get() = result;
		}
	}
	namespace ns_IComposerStage 
	{
		void bind_def_constr(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<IComposerStage>* obj = ((TScriptSharedPointer<IComposerStage>*)(run_context.GetObject().get()));
			obj->def_constr();
		}
		void bind_copy_constr(TMethodRunContext& run_context) 
		{
			//IComposerStage&  copy_from return --- nothing
			TScriptSharedPointer<IComposerStage>* obj = ((TScriptSharedPointer<IComposerStage>*)(run_context.GetObject().get()));
			TScriptSharedPointer<IComposerStage>* param0 = ((TScriptSharedPointer<IComposerStage>*)run_context.GetFormalParams()[0].get());
			obj->copy_constr(param0);
		}
		void bind_destructor(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<IComposerStage>* obj = ((TScriptSharedPointer<IComposerStage>*)(run_context.GetObject().get()));
			obj->destructor();
		}
		void bind_operator_Assign(TMethodRunContext& run_context) 
		{
			//static - IComposerStage&  v, IComposerStage&  l return --- nothing
			TScriptSharedPointer<IComposerStage>* param0 = ((TScriptSharedPointer<IComposerStage>*)run_context.GetFormalParams()[0].get());
			TScriptSharedPointer<IComposerStage>* param1 = ((TScriptSharedPointer<IComposerStage>*)run_context.GetFormalParams()[1].get());
			param0->operator_Assign(param1);
		}
	}
	namespace ns_IComposer 
	{
		void bind_def_constr(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<IComposer>* obj = ((TScriptSharedPointer<IComposer>*)(run_context.GetObject().get()));
			obj->def_constr();
		}
		void bind_copy_constr(TMethodRunContext& run_context) 
		{
			//IComposer&  copy_from return --- nothing
			TScriptSharedPointer<IComposer>* obj = ((TScriptSharedPointer<IComposer>*)(run_context.GetObject().get()));
			TScriptSharedPointer<IComposer>* param0 = ((TScriptSharedPointer<IComposer>*)run_context.GetFormalParams()[0].get());
			obj->copy_constr(param0);
		}
		void bind_destructor(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<IComposer>* obj = ((TScriptSharedPointer<IComposer>*)(run_context.GetObject().get()));
			obj->destructor();
		}
		void bind_operator_Assign(TMethodRunContext& run_context) 
		{
			//static - IComposer&  v, IComposer&  l return --- nothing
			TScriptSharedPointer<IComposer>* param0 = ((TScriptSharedPointer<IComposer>*)run_context.GetFormalParams()[0].get());
			TScriptSharedPointer<IComposer>* param1 = ((TScriptSharedPointer<IComposer>*)run_context.GetFormalParams()[1].get());
			param0->operator_Assign(param1);
		}
		void bind_AddToRender(TMethodRunContext& run_context) 
		{
			//IScene  scene, WorldDef::IViewport  viewport return --- nothing
			TScriptSharedPointer<IComposer>* obj = ((TScriptSharedPointer<IComposer>*)(run_context.GetObject().get()));
			std::shared_ptr<IScene> param0 = *((TScriptSharedPointer<IScene>*)run_context.GetFormalParams()[0].get())->v;
			WorldDef::IViewport* param1 = *((WorldDef::IViewport**)run_context.GetFormalParams()[1].get());
			(*obj)->AddToRender(param0, param1);
		}
	}
	namespace ns_IWorldDef 
	{
		void bind_GetScene(TMethodRunContext& run_context) 
		{
			//TString  name return --- WorldDef::IScene
			WorldDef::IWorld** obj = ((WorldDef::IWorld**)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			WorldDef::IScene*  result = 
			(*obj)->GetScene(param0);
			*(WorldDef::IScene**)run_context.GetResult().get() = result;
		}
	}
	namespace ns_IWorld 
	{
		void bind_def_constr(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<IWorld>* obj = ((TScriptSharedPointer<IWorld>*)(run_context.GetObject().get()));
			obj->def_constr();
		}
		void bind_copy_constr(TMethodRunContext& run_context) 
		{
			//IWorld&  copy_from return --- nothing
			TScriptSharedPointer<IWorld>* obj = ((TScriptSharedPointer<IWorld>*)(run_context.GetObject().get()));
			TScriptSharedPointer<IWorld>* param0 = ((TScriptSharedPointer<IWorld>*)run_context.GetFormalParams()[0].get());
			obj->copy_constr(param0);
		}
		void bind_destructor(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<IWorld>* obj = ((TScriptSharedPointer<IWorld>*)(run_context.GetObject().get()));
			obj->destructor();
		}
		void bind_operator_Assign(TMethodRunContext& run_context) 
		{
			//static - IWorld&  v, IWorld&  l return --- nothing
			TScriptSharedPointer<IWorld>* param0 = ((TScriptSharedPointer<IWorld>*)run_context.GetFormalParams()[0].get());
			TScriptSharedPointer<IWorld>* param1 = ((TScriptSharedPointer<IWorld>*)run_context.GetFormalParams()[1].get());
			param0->operator_Assign(param1);
		}
		void bind_GetScene(TMethodRunContext& run_context) 
		{
			//int  index return --- IScene
			TScriptSharedPointer<IWorld>* obj = ((TScriptSharedPointer<IWorld>*)(run_context.GetObject().get()));
			const int&  param0 = *((int*)run_context.GetFormalParams()[0].get());
			std::shared_ptr<IScene> result =
			(*obj)->GetScene(param0);
			*(TScriptSharedPointer<IScene>*)run_context.GetResult().get() = TScriptSharedPointer<IScene>(result);
		}
		void bind_RunScene(TMethodRunContext& run_context) 
		{
			//WorldDef::IScene  scene return --- IScene
			TScriptSharedPointer<IWorld>* obj = ((TScriptSharedPointer<IWorld>*)(run_context.GetObject().get()));
			WorldDef::IScene* param0 = *((WorldDef::IScene**)run_context.GetFormalParams()[0].get());
			std::shared_ptr<IScene> result =
			(*obj)->RunScene(param0);
			*(TScriptSharedPointer<IScene>*)run_context.GetResult().get() = TScriptSharedPointer<IScene>(result);
		}
		void bind_GetSource(TMethodRunContext& run_context) 
		{
			// return --- WorldDef::IWorld
			TScriptSharedPointer<IWorld>* obj = ((TScriptSharedPointer<IWorld>*)(run_context.GetObject().get()));
			WorldDef::IWorld*  result = 
			(*obj)->GetSource();
			*(WorldDef::IWorld**)run_context.GetResult().get() = result;
		}
	}
	namespace ns_IDirector 
	{
		void bind_def_constr(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<IDirector>* obj = ((TScriptSharedPointer<IDirector>*)(run_context.GetObject().get()));
			obj->def_constr();
		}
		void bind_copy_constr(TMethodRunContext& run_context) 
		{
			//IDirector&  copy_from return --- nothing
			TScriptSharedPointer<IDirector>* obj = ((TScriptSharedPointer<IDirector>*)(run_context.GetObject().get()));
			TScriptSharedPointer<IDirector>* param0 = ((TScriptSharedPointer<IDirector>*)run_context.GetFormalParams()[0].get());
			obj->copy_constr(param0);
		}
		void bind_destructor(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<IDirector>* obj = ((TScriptSharedPointer<IDirector>*)(run_context.GetObject().get()));
			obj->destructor();
		}
		void bind_operator_Assign(TMethodRunContext& run_context) 
		{
			//static - IDirector&  v, IDirector&  l return --- nothing
			TScriptSharedPointer<IDirector>* param0 = ((TScriptSharedPointer<IDirector>*)run_context.GetFormalParams()[0].get());
			TScriptSharedPointer<IDirector>* param1 = ((TScriptSharedPointer<IDirector>*)run_context.GetFormalParams()[1].get());
			param0->operator_Assign(param1);
		}
		void bind_GetWorld(TMethodRunContext& run_context) 
		{
			// return --- IWorld
			TScriptSharedPointer<IDirector>* obj = ((TScriptSharedPointer<IDirector>*)(run_context.GetObject().get()));
			std::shared_ptr<IWorld> result =
			(*obj)->GetWorld();
			*(TScriptSharedPointer<IWorld>*)run_context.GetResult().get() = TScriptSharedPointer<IWorld>(result);
		}
	}
	namespace ns_IPhysShapeDef 
	{
		void bind_SetIsSensor(TMethodRunContext& run_context) 
		{
			//bool  is_sensor return --- nothing
			WorldDef::IPhysShape** obj = ((WorldDef::IPhysShape**)(run_context.GetObject().get()));
			const bool&  param0 = *((bool*)run_context.GetFormalParams()[0].get());
			(*obj)->SetIsSensor(param0);
		}
		void bind_GetIsSensor(TMethodRunContext& run_context) 
		{
			// return --- bool
			WorldDef::IPhysShape** obj = ((WorldDef::IPhysShape**)(run_context.GetObject().get()));
			bool  result = 
			(*obj)->GetIsSensor();
			*(bool*)run_context.GetResult().get() = result;
		}
	}
	namespace ns_IPhysShape 
	{
		void bind_def_constr(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<IPhysShapeInstance>* obj = ((TScriptSharedPointer<IPhysShapeInstance>*)(run_context.GetObject().get()));
			obj->def_constr();
		}
		void bind_copy_constr(TMethodRunContext& run_context) 
		{
			//IPhysShapeInstance&  copy_from return --- nothing
			TScriptSharedPointer<IPhysShapeInstance>* obj = ((TScriptSharedPointer<IPhysShapeInstance>*)(run_context.GetObject().get()));
			TScriptSharedPointer<IPhysShapeInstance>* param0 = ((TScriptSharedPointer<IPhysShapeInstance>*)run_context.GetFormalParams()[0].get());
			obj->copy_constr(param0);
		}
		void bind_destructor(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<IPhysShapeInstance>* obj = ((TScriptSharedPointer<IPhysShapeInstance>*)(run_context.GetObject().get()));
			obj->destructor();
		}
		void bind_operator_Assign(TMethodRunContext& run_context) 
		{
			//static - IPhysShapeInstance&  v, IPhysShapeInstance&  l return --- nothing
			TScriptSharedPointer<IPhysShapeInstance>* param0 = ((TScriptSharedPointer<IPhysShapeInstance>*)run_context.GetFormalParams()[0].get());
			TScriptSharedPointer<IPhysShapeInstance>* param1 = ((TScriptSharedPointer<IPhysShapeInstance>*)run_context.GetFormalParams()[1].get());
			param0->operator_Assign(param1);
		}
	}
	namespace ns_ISpritePolygonDef 
	{
		void bind_SetScale(TMethodRunContext& run_context) 
		{
			//BaluLib::TVec2  scale return --- nothing
			WorldDef::ISpritePolygon** obj = ((WorldDef::ISpritePolygon**)(run_context.GetObject().get()));
			const BaluLib::TVec2&  param0 = *((BaluLib::TVec2*)run_context.GetFormalParams()[0].get());
			(*obj)->SetScale(param0);
		}
	}
	namespace ns_ISpriteDef 
	{
		void bind_SetPhysShape(TMethodRunContext& run_context) 
		{
			//WorldDef::IPhysShape  shape return --- nothing
			WorldDef::ISprite** obj = ((WorldDef::ISprite**)(run_context.GetObject().get()));
			WorldDef::IPhysShape* param0 = *((WorldDef::IPhysShape**)run_context.GetFormalParams()[0].get());
			(*obj)->SetPhysShape(param0);
		}
		void bind_GetPhysShape(TMethodRunContext& run_context) 
		{
			// return --- WorldDef::IPhysShape
			WorldDef::ISprite** obj = ((WorldDef::ISprite**)(run_context.GetObject().get()));
			WorldDef::IPhysShape*  result = 
			(*obj)->GetPhysShape();
			*(WorldDef::IPhysShape**)run_context.GetResult().get() = result;
		}
		void bind_GetPolygon(TMethodRunContext& run_context) 
		{
			// return --- WorldDef::ISpritePolygon
			WorldDef::ISprite** obj = ((WorldDef::ISprite**)(run_context.GetObject().get()));
			WorldDef::ISpritePolygon*  result = 
			(*obj)->GetPolygon();
			*(WorldDef::ISpritePolygon**)run_context.GetResult().get() = result;
		}
	}
	namespace ns_ITransformedSpriteDef 
	{
		void bind_GetSprite(TMethodRunContext& run_context) 
		{
			// return --- WorldDef::ISprite
			WorldDef::ITransformedSprite** obj = ((WorldDef::ITransformedSprite**)(run_context.GetObject().get()));
			WorldDef::ISprite*  result = 
			(*obj)->GetSprite();
			*(WorldDef::ISprite**)run_context.GetResult().get() = result;
		}
	}
	namespace ns_ISpritePolygon 
	{
		void bind_def_constr(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<ISpritePolygonInstance>* obj = ((TScriptSharedPointer<ISpritePolygonInstance>*)(run_context.GetObject().get()));
			obj->def_constr();
		}
		void bind_copy_constr(TMethodRunContext& run_context) 
		{
			//ISpritePolygonInstance&  copy_from return --- nothing
			TScriptSharedPointer<ISpritePolygonInstance>* obj = ((TScriptSharedPointer<ISpritePolygonInstance>*)(run_context.GetObject().get()));
			TScriptSharedPointer<ISpritePolygonInstance>* param0 = ((TScriptSharedPointer<ISpritePolygonInstance>*)run_context.GetFormalParams()[0].get());
			obj->copy_constr(param0);
		}
		void bind_destructor(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<ISpritePolygonInstance>* obj = ((TScriptSharedPointer<ISpritePolygonInstance>*)(run_context.GetObject().get()));
			obj->destructor();
		}
		void bind_operator_Assign(TMethodRunContext& run_context) 
		{
			//static - ISpritePolygonInstance&  v, ISpritePolygonInstance&  l return --- nothing
			TScriptSharedPointer<ISpritePolygonInstance>* param0 = ((TScriptSharedPointer<ISpritePolygonInstance>*)run_context.GetFormalParams()[0].get());
			TScriptSharedPointer<ISpritePolygonInstance>* param1 = ((TScriptSharedPointer<ISpritePolygonInstance>*)run_context.GetFormalParams()[1].get());
			param0->operator_Assign(param1);
		}
		void bind_SetActiveAnimation(TMethodRunContext& run_context) 
		{
			//TString  name return --- nothing
			TScriptSharedPointer<ISpritePolygonInstance>* obj = ((TScriptSharedPointer<ISpritePolygonInstance>*)(run_context.GetObject().get()));
			const TString& temp_param0 = *((TString*)run_context.GetFormalParams()[0].get());
			std::string param0 = Convert_TString_to_stdstring(temp_param0);
			(*obj)->SetActiveAnimation(param0);
		}
	}
	namespace ns_ITransformedSprite 
	{
		void bind_def_constr(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<ITransformedSpriteInstance>* obj = ((TScriptSharedPointer<ITransformedSpriteInstance>*)(run_context.GetObject().get()));
			obj->def_constr();
		}
		void bind_copy_constr(TMethodRunContext& run_context) 
		{
			//ITransformedSpriteInstance&  copy_from return --- nothing
			TScriptSharedPointer<ITransformedSpriteInstance>* obj = ((TScriptSharedPointer<ITransformedSpriteInstance>*)(run_context.GetObject().get()));
			TScriptSharedPointer<ITransformedSpriteInstance>* param0 = ((TScriptSharedPointer<ITransformedSpriteInstance>*)run_context.GetFormalParams()[0].get());
			obj->copy_constr(param0);
		}
		void bind_destructor(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<ITransformedSpriteInstance>* obj = ((TScriptSharedPointer<ITransformedSpriteInstance>*)(run_context.GetObject().get()));
			obj->destructor();
		}
		void bind_operator_Assign(TMethodRunContext& run_context) 
		{
			//static - ITransformedSpriteInstance&  v, ITransformedSpriteInstance&  l return --- nothing
			TScriptSharedPointer<ITransformedSpriteInstance>* param0 = ((TScriptSharedPointer<ITransformedSpriteInstance>*)run_context.GetFormalParams()[0].get());
			TScriptSharedPointer<ITransformedSpriteInstance>* param1 = ((TScriptSharedPointer<ITransformedSpriteInstance>*)run_context.GetFormalParams()[1].get());
			param0->operator_Assign(param1);
		}
		void bind_GetSource(TMethodRunContext& run_context) 
		{
			// return --- WorldDef::ITransformedSprite
			TScriptSharedPointer<ITransformedSpriteInstance>* obj = ((TScriptSharedPointer<ITransformedSpriteInstance>*)(run_context.GetObject().get()));
			WorldDef::ITransformedSprite*  result = 
			(*obj)->GetSource();
			*(WorldDef::ITransformedSprite**)run_context.GetResult().get() = result;
		}
		void bind_GetPhysShape(TMethodRunContext& run_context) 
		{
			// return --- IPhysShapeInstance
			TScriptSharedPointer<ITransformedSpriteInstance>* obj = ((TScriptSharedPointer<ITransformedSpriteInstance>*)(run_context.GetObject().get()));
			std::shared_ptr<IPhysShapeInstance> result =
			(*obj)->GetPhysShape();
			*(TScriptSharedPointer<IPhysShapeInstance>*)run_context.GetResult().get() = TScriptSharedPointer<IPhysShapeInstance>(result);
		}
		void bind_GetScale(TMethodRunContext& run_context) 
		{
			// return --- BaluLib::TVec2
			TScriptSharedPointer<ITransformedSpriteInstance>* obj = ((TScriptSharedPointer<ITransformedSpriteInstance>*)(run_context.GetObject().get()));
			BaluLib::TVec2  result = 
			(*obj)->GetScale();
			*(BaluLib::TVec2*)run_context.GetResult().get() = result;
		}
		void bind_GetPolygon(TMethodRunContext& run_context) 
		{
			// return --- ISpritePolygonInstance
			TScriptSharedPointer<ITransformedSpriteInstance>* obj = ((TScriptSharedPointer<ITransformedSpriteInstance>*)(run_context.GetObject().get()));
			std::shared_ptr<ISpritePolygonInstance> result =
			(*obj)->GetPolygon();
			*(TScriptSharedPointer<ISpritePolygonInstance>*)run_context.GetResult().get() = TScriptSharedPointer<ISpritePolygonInstance>(result);
		}
	}
	namespace ns_IInstance 
	{
		void bind_def_constr(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<ITransformedClassInstance>* obj = ((TScriptSharedPointer<ITransformedClassInstance>*)(run_context.GetObject().get()));
			obj->def_constr();
		}
		void bind_copy_constr(TMethodRunContext& run_context) 
		{
			//ITransformedClassInstance&  copy_from return --- nothing
			TScriptSharedPointer<ITransformedClassInstance>* obj = ((TScriptSharedPointer<ITransformedClassInstance>*)(run_context.GetObject().get()));
			TScriptSharedPointer<ITransformedClassInstance>* param0 = ((TScriptSharedPointer<ITransformedClassInstance>*)run_context.GetFormalParams()[0].get());
			obj->copy_constr(param0);
		}
		void bind_destructor(TMethodRunContext& run_context) 
		{
			// return --- nothing
			TScriptSharedPointer<ITransformedClassInstance>* obj = ((TScriptSharedPointer<ITransformedClassInstance>*)(run_context.GetObject().get()));
			obj->destructor();
		}
		void bind_operator_Assign(TMethodRunContext& run_context) 
		{
			//static - ITransformedClassInstance&  v, ITransformedClassInstance&  l return --- nothing
			TScriptSharedPointer<ITransformedClassInstance>* param0 = ((TScriptSharedPointer<ITransformedClassInstance>*)run_context.GetFormalParams()[0].get());
			TScriptSharedPointer<ITransformedClassInstance>* param1 = ((TScriptSharedPointer<ITransformedClassInstance>*)run_context.GetFormalParams()[1].get());
			param0->operator_Assign(param1);
		}
		void bind_SetScale(TMethodRunContext& run_context) 
		{
			//BaluLib::TVec2  scale return --- nothing
			TScriptSharedPointer<ITransformedClassInstance>* obj = ((TScriptSharedPointer<ITransformedClassInstance>*)(run_context.GetObject().get()));
			const BaluLib::TVec2&  param0 = *((BaluLib::TVec2*)run_context.GetFormalParams()[0].get());
			(*obj)->SetScale(param0);
		}
		void bind_GetProperties(TMethodRunContext& run_context) 
		{
			// return --- WorldDef::IRuntimeProperties
			TScriptSharedPointer<ITransformedClassInstance>* obj = ((TScriptSharedPointer<ITransformedClassInstance>*)(run_context.GetObject().get()));
			std::shared_ptr<WorldDef::IRuntimeProperties> result =
			(*obj)->GetProperties();
			*(TScriptSharedPointer<WorldDef::IRuntimeProperties>*)run_context.GetResult().get() = TScriptSharedPointer<WorldDef::IRuntimeProperties>(result);
		}
		void bind_GetPhysBody(TMethodRunContext& run_context) 
		{
			// return --- IClassPhysBodyIntance
			TScriptSharedPointer<ITransformedClassInstance>* obj = ((TScriptSharedPointer<ITransformedClassInstance>*)(run_context.GetObject().get()));
			std::shared_ptr<IClassPhysBodyIntance> result =
			(*obj)->GetPhysBody();
			*(TScriptSharedPointer<IClassPhysBodyIntance>*)run_context.GetResult().get() = TScriptSharedPointer<IClassPhysBodyIntance>(result);
		}
		void bind_GetSprite(TMethodRunContext& run_context) 
		{
			//int  index return --- ITransformedSpriteInstance
			TScriptSharedPointer<ITransformedClassInstance>* obj = ((TScriptSharedPointer<ITransformedClassInstance>*)(run_context.GetObject().get()));
			const int&  param0 = *((int*)run_context.GetFormalParams()[0].get());
			std::shared_ptr<ITransformedSpriteInstance> result =
			(*obj)->GetSprite(param0);
			*(TScriptSharedPointer<ITransformedSpriteInstance>*)run_context.GetResult().get() = TScriptSharedPointer<ITransformedSpriteInstance>(result);
		}
		void bind_GetSkeletonAnimation(TMethodRunContext& run_context) 
		{
			// return --- ISkeletonAnimationInstance
			TScriptSharedPointer<ITransformedClassInstance>* obj = ((TScriptSharedPointer<ITransformedClassInstance>*)(run_context.GetObject().get()));
			std::shared_ptr<ISkeletonAnimationInstance> result =
			(*obj)->GetSkeletonAnimation();
			*(TScriptSharedPointer<ISkeletonAnimationInstance>*)run_context.GetResult().get() = TScriptSharedPointer<ISkeletonAnimationInstance>(result);
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
		result.push_back(ns_Script::ns_IClassPhysBody::bind_def_constr);
		result.push_back(ns_Script::ns_IClassPhysBody::bind_copy_constr);
		result.push_back(ns_Script::ns_IClassPhysBody::bind_destructor);
		result.push_back(ns_Script::ns_IClassPhysBody::bind_operator_Assign);
		result.push_back(ns_Script::ns_IClassPhysBody::bind_GetLinearVelocity);
		result.push_back(ns_Script::ns_IClassPhysBody::bind_SetLinearVelocity);
		result.push_back(ns_Script::ns_ISkeletonAnimation::bind_def_constr);
		result.push_back(ns_Script::ns_ISkeletonAnimation::bind_copy_constr);
		result.push_back(ns_Script::ns_ISkeletonAnimation::bind_destructor);
		result.push_back(ns_Script::ns_ISkeletonAnimation::bind_operator_Assign);
		result.push_back(ns_Script::ns_ISkeletonAnimation::bind_PlayAnimation);
		result.push_back(ns_Script::ns_ISkeletonAnimation::bind_StopAnimation);
		result.push_back(ns_Script::ns_TRot::bind_Set);
		result.push_back(ns_Script::ns_TRot::bind_SetIdentity);
		result.push_back(ns_Script::ns_TRot::bind_GetAngle);
		result.push_back(ns_Script::ns_TTransform::bind_Transform);
		result.push_back(ns_Script::ns_IViewport::bind_SetSize);
		result.push_back(ns_Script::ns_IViewport::bind_GetSize);
		result.push_back(ns_Script::ns_IProperties::bind_def_constr);
		result.push_back(ns_Script::ns_IProperties::bind_copy_constr);
		result.push_back(ns_Script::ns_IProperties::bind_destructor);
		result.push_back(ns_Script::ns_IProperties::bind_operator_Assign);
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
		result.push_back(ns_Script::ns_IScene::bind_def_constr);
		result.push_back(ns_Script::ns_IScene::bind_copy_constr);
		result.push_back(ns_Script::ns_IScene::bind_destructor);
		result.push_back(ns_Script::ns_IScene::bind_operator_Assign);
		result.push_back(ns_Script::ns_IScene::bind_GetSource);
		result.push_back(ns_Script::ns_IComposerStage::bind_def_constr);
		result.push_back(ns_Script::ns_IComposerStage::bind_copy_constr);
		result.push_back(ns_Script::ns_IComposerStage::bind_destructor);
		result.push_back(ns_Script::ns_IComposerStage::bind_operator_Assign);
		result.push_back(ns_Script::ns_IComposer::bind_def_constr);
		result.push_back(ns_Script::ns_IComposer::bind_copy_constr);
		result.push_back(ns_Script::ns_IComposer::bind_destructor);
		result.push_back(ns_Script::ns_IComposer::bind_operator_Assign);
		result.push_back(ns_Script::ns_IComposer::bind_AddToRender);
		result.push_back(ns_Script::ns_IWorldDef::bind_GetScene);
		result.push_back(ns_Script::ns_IWorld::bind_def_constr);
		result.push_back(ns_Script::ns_IWorld::bind_copy_constr);
		result.push_back(ns_Script::ns_IWorld::bind_destructor);
		result.push_back(ns_Script::ns_IWorld::bind_operator_Assign);
		result.push_back(ns_Script::ns_IWorld::bind_GetScene);
		result.push_back(ns_Script::ns_IWorld::bind_RunScene);
		result.push_back(ns_Script::ns_IWorld::bind_GetSource);
		result.push_back(ns_Script::ns_IDirector::bind_def_constr);
		result.push_back(ns_Script::ns_IDirector::bind_copy_constr);
		result.push_back(ns_Script::ns_IDirector::bind_destructor);
		result.push_back(ns_Script::ns_IDirector::bind_operator_Assign);
		result.push_back(ns_Script::ns_IDirector::bind_GetWorld);
		result.push_back(ns_Script::ns_IPhysShapeDef::bind_SetIsSensor);
		result.push_back(ns_Script::ns_IPhysShapeDef::bind_GetIsSensor);
		result.push_back(ns_Script::ns_IPhysShape::bind_def_constr);
		result.push_back(ns_Script::ns_IPhysShape::bind_copy_constr);
		result.push_back(ns_Script::ns_IPhysShape::bind_destructor);
		result.push_back(ns_Script::ns_IPhysShape::bind_operator_Assign);
		result.push_back(ns_Script::ns_ISpritePolygonDef::bind_SetScale);
		result.push_back(ns_Script::ns_ISpriteDef::bind_SetPhysShape);
		result.push_back(ns_Script::ns_ISpriteDef::bind_GetPhysShape);
		result.push_back(ns_Script::ns_ISpriteDef::bind_GetPolygon);
		result.push_back(ns_Script::ns_ITransformedSpriteDef::bind_GetSprite);
		result.push_back(ns_Script::ns_ISpritePolygon::bind_def_constr);
		result.push_back(ns_Script::ns_ISpritePolygon::bind_copy_constr);
		result.push_back(ns_Script::ns_ISpritePolygon::bind_destructor);
		result.push_back(ns_Script::ns_ISpritePolygon::bind_operator_Assign);
		result.push_back(ns_Script::ns_ISpritePolygon::bind_SetActiveAnimation);
		result.push_back(ns_Script::ns_ITransformedSprite::bind_def_constr);
		result.push_back(ns_Script::ns_ITransformedSprite::bind_copy_constr);
		result.push_back(ns_Script::ns_ITransformedSprite::bind_destructor);
		result.push_back(ns_Script::ns_ITransformedSprite::bind_operator_Assign);
		result.push_back(ns_Script::ns_ITransformedSprite::bind_GetSource);
		result.push_back(ns_Script::ns_ITransformedSprite::bind_GetPhysShape);
		result.push_back(ns_Script::ns_ITransformedSprite::bind_GetScale);
		result.push_back(ns_Script::ns_ITransformedSprite::bind_GetPolygon);
		result.push_back(ns_Script::ns_IInstance::bind_def_constr);
		result.push_back(ns_Script::ns_IInstance::bind_copy_constr);
		result.push_back(ns_Script::ns_IInstance::bind_destructor);
		result.push_back(ns_Script::ns_IInstance::bind_operator_Assign);
		result.push_back(ns_Script::ns_IInstance::bind_SetScale);
		result.push_back(ns_Script::ns_IInstance::bind_GetProperties);
		result.push_back(ns_Script::ns_IInstance::bind_GetPhysBody);
		result.push_back(ns_Script::ns_IInstance::bind_GetSprite);
		result.push_back(ns_Script::ns_IInstance::bind_GetSkeletonAnimation);
		return result;
	}
	const int BindingOffset = 22;
	const int BindingCount = 102;
}
