#pragma once

#include "../../BaluLib/Source/Math/vec.h"
#include "../../BaluLib/Source/BVolumes/AABB.h"

class TMaterialInstance;

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

class NVGcontext;

namespace EngineInterface
{
	class IBaluSpritePolygonInstance;
}

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
	void* GetUserData()
	{
		return user_data;
	}
};

class TSMethod;

template<class T>
class CallbackWithData :public TCallbackData
{
private:
	T callback;
	bool is_script;
	std::string script_source;
	TSMethod* compiled_script;
public:
	void SetCompiledScript(TSMethod* method)
	{
		assert(compiled_script == nullptr);
		compiled_script = method;
	}
	TSMethod* GetCompiledScript()
	{
		return compiled_script;
	}
	bool IsScript()
	{
		return is_script;
	}
	std::string GetScriptSource()
	{
		return script_source;
	}
	bool operator==(const CallbackWithData& right)
	{
		return callback = right.callback;
	}
	template<typename... Args>
	void Execute(Args... args)
	{
		assert(!is_script);//должно производиться через TScriptInstance
		if (active_type->active_type==callback_type)
			callback(this, args...);
	}
	void Initialize(T callback, TCallbacksActiveType* active_type, void* user_data, int callback_type, char* script_source=nullptr)
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
		Initialize(nullptr, nullptr, nullptr, TCallbacksActiveType::DEFAULT, nullptr);
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
	//TODO заменить на матрицу ориентации и масштабирование
	TVec2 pos; //центр вида в координатах экрана
	TVec2 size; //ширина и высота в координатах экрана
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
	//координаты экрана x (0,1) y (0,1)

	//void Resize(TVec2i size);

	//void AddView(TView view);
	//int GetViewsCount();
	//TView GetView(int i);
	//void RemoveView(int i);

	//координаты view_coord x (0,1) y (0,1)
	TVec2 FromViewToScreen(TView view, TVec2 view_coord)
	{
		return (view_coord-TVec2(0.5,0.5)).ComponentMul(view.GetSize()) + view.GetPos();
	}
	TVec2 FromScreenToView(TView view, TVec2 screen_coord)
	{
		return ((screen_coord - view.GetPos()) / view.GetSize()) + TVec2(0.5,0.5);
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

//TODO в дальнейшем вся информация для рендера должна находиться полностью здесь, для возможности параллельной отрисовки

class TCustomDrawCommand
{
public:
	EngineInterface::IBaluSpritePolygonInstance* poly;
	TScreen* screen;
	TAABB2* viewport;
	TView* view;
	CallbackWithData<TCustomDrawCallback> command;
};

