#pragma once

#include "../../BaluLib/Source/Math/vec.h"
#include "../../BaluLib/Source/BVolumes/AABB.h"

class TSMethod;
class TBaluScriptInstance;

class TMaterialInstance;
class NVGcontext;


namespace EngineInterface
{
		struct TRenderCommand
	{
	public:
		TMaterialInstance* material_id;

		int vertices_count;
		TVec2* vertices;
		TVec2* tex_coords;
		TVec4* colors;
		//int indices_count;
		//int* indices;

		TRenderCommand(){}

		TRenderCommand(TMaterialInstance* material_id, int vertices_count, TVec2* vertices, TVec2* tex_coords, TVec4* colors)//, int indices_count, int* indices)
		{
			this->material_id = material_id;
			this->vertices_count = vertices_count;
			this->vertices = vertices;
			this->tex_coords = tex_coords;
			this->colors = colors;
			//this->indices_count = indices_count;
			//this->indices = indices;
		}
	};

	
	class IBaluSpritePolygonInstance;

	class TCallbacksActiveType
	{
	public:
		enum
		{
			DEFAULT = 0,
			EDITOR = 1
		};
		int active_type;
	};

	class TCallbackData
	{
	protected:
		void* user_data;
		int callback_type;
		TCallbacksActiveType* active_type;
	public:
		TCallbackData()
		{
			user_data = nullptr;
			callback_type = TCallbacksActiveType::DEFAULT;
			active_type = nullptr;
		}
		void* GetUserData()
		{
			return user_data;
		}
	};

	

	class TScriptData
	{
	protected:
		std::string script_source;
		TSMethod* compiled_script;
		TBaluScriptInstance* script_engine;
		bool is_script;
	public:
		TScriptData()
		{
			compiled_script = nullptr;
			script_engine = nullptr;
			is_script = false;
		}
		void SetCompiledScript(TSMethod* method, TBaluScriptInstance* script_engine)
		{
			assert(compiled_script == nullptr);
			this->compiled_script = method;
			this->script_engine = script_engine;
		}
		TSMethod* GetCompiledScript()
		{
			assert(compiled_script != nullptr);
			return compiled_script;
		}
		TBaluScriptInstance* GetScriptEngine()
		{
			assert(script_engine != nullptr);
			return script_engine;
		}
		bool IsScript()
		{
			return is_script;
		}
		std::string GetScriptSource()
		{
			assert(is_script);
			return script_source;
		}
	};

	template<class T>
	class CallbackWithData :public TCallbackData, public TScriptData
	{
	private:
		T callback;
	public:
		bool operator==(const CallbackWithData& right)
		{
			return callback = right.callback;
		}
		template<typename... Args>
		void Execute(Args... args)
		{
			assert(!is_script);//������ ������������� ����� TScriptInstance
			if (active_type->active_type == callback_type)
				callback(this, args...);
		}
		void Initialize(T callback, TCallbacksActiveType* active_type, void* user_data, int callback_type, char* script_source = nullptr)
		{
			this->callback = callback;
			this->user_data = user_data;
			this->callback_type = callback_type;
			this->active_type = active_type;
			this->is_script = script_source != nullptr;
			if (is_script)
				this->script_source = script_source;
			compiled_script = nullptr;
		}
		CallbackWithData()
		{
			callback = nullptr;
		}
		CallbackWithData(char* script_source, TCallbacksActiveType* active_type, int callback_type)
		{
			Initialize(nullptr, active_type, nullptr, callback_type, script_source);
		}
		CallbackWithData(T callback, TCallbacksActiveType* active_type, void* user_data, int callback_type)
		{
			Initialize(callback, active_type, user_data, callback_type);
		}
		CallbackWithData(T callback, TCallbacksActiveType* active_type, void* user_data)
		{
			Initialize(callback, active_type, user_data, TCallbacksActiveType::DEFAULT);
		}
		CallbackWithData(T callback, TCallbacksActiveType* active_type)
		{
			Initialize(callback, active_type, nullptr, TCallbacksActiveType::DEFAULT);
		}
	};

	class TCustomDrawCommand;

	typedef void(*TCustomDrawCallback)(TCallbackData* callback, NVGcontext* vg, TCustomDrawCommand* params);

	class TView
	{
		//TODO �������� �� ������� ���������� � ���������������
		TVec2 pos; //����� ���� � ����������� ������
		TVec2 size; //������ � ������ � ����������� ������
		//EngineInterface::IViewport* viewport;
	public:
		TView(){}
		TView(TVec2 pos, TVec2 size)//, EngineInterface::IViewport* viewport)
		{
			this->pos = pos;
			this->size = size;
			//this->viewport = viewport;
		}
		//EngineInterface::IViewport* GetViewport()
		//{
		//	return viewport;
		//}
		TVec2 GetPos()
		{
			return pos;
		}
		TVec2 GetSize()
		{
			return size;
		}
	};

	class TScreen
	{
	public:
		TVec2i size;
		//std::vector<TView> views;
	public:
		TScreen(TVec2i size)
		{
			this->size = size;
		}
		//���������� ������ x (0,1) y (0,1)

		//void Resize(TVec2i size);

		//void AddView(TView view);
		//int GetViewsCount();
		//TView GetView(int i);
		//void RemoveView(int i);

		//���������� view_coord x (0,1) y (0,1)
		TVec2 FromViewToScreen(TView view, TVec2 view_coord)
		{
			return (view_coord - TVec2(0.5, 0.5)).ComponentMul(view.GetSize()) + view.GetPos();
		}
		TVec2 FromScreenToView(TView view, TVec2 screen_coord)
		{
			return ((screen_coord - view.GetPos()) / view.GetSize()) + TVec2(0.5, 0.5);
		}
		TVec2i ToScreenPixels(TVec2 coord)
		{
			return TVec2i(
				size[0] * coord[0],
				size[1] * coord[1]
				);
		}
		TVec2 FromScreenPixels(TVec2i coord)
		{
			return TVec2(
				coord[0] / size[0],
				coord[1] / size[1]
				);
		}
		TVec2i ToScreenPixels2(TVec2 coord)
		{
			return TVec2i(
				size[0] * coord[0],
				size[1] * (1 - coord[1])
				);
		}
		TVec2 FromScreenPixels2(TVec2i coord)
		{
			return TVec2(
				(float)coord[0] / size[0],
				1 - (float)coord[1] / size[1]
				);
		}
	};

	//TODO � ���������� ��� ���������� ��� ������� ������ ���������� ��������� �����, ��� ����������� ������������ ���������

	class TCustomDrawCommand
	{
	public:
		EngineInterface::IBaluSpritePolygonInstance* poly;
		TScreen* screen;
		TAABB2* viewport;
		TView* view;
		CallbackWithData<TCustomDrawCallback> command;
	};

}