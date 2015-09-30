#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#include <baluLib.h>
using namespace BaluLib;

#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include <World/ICallbacks.h>
#endif
#endif

namespace EngineInterface
{
	class IBaluSpritePolygonInstance;
	class TMaterialInstance;
	class TDrawingHelper;
}

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	struct TRenderCommand
	{
	public:
		TMaterialInstance* material_id;

		bool draw_triangles_grid;
		int vertices_count;
		TVec2* vertices;
		TVec2* tex_coords;
		TVec4* colors;
		int layer_order;
		float alpha;

		TRenderCommand(){}

		TRenderCommand(TMaterialInstance* material_id, int vertices_count, TVec2* vertices, TVec2* tex_coords, TVec4* colors)
		{
			this->material_id = material_id;
			this->vertices_count = vertices_count;
			this->vertices = vertices;
			this->tex_coords = tex_coords;
			this->colors = colors;
		}
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
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
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class TScreen
	{
	public:
		TVec2i size;
		//std::vector<TView> views;
	public:
		TScreen(){}
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
#endif

	//TODO в дальнейшем вся информация для рендера должна находиться полностью здесь, для возможности параллельной отрисовки

	
#ifndef BALU_ENGINE_SCRIPT_CLASSES
#ifndef BALU_ENGINE_DLL_INTERFACES
	class IGUIVisual
	{
	public:
		virtual void Render(TDrawingHelper* helper)const = 0;
	};
#endif
#endif
}