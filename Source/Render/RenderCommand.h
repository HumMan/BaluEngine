#pragma once

#include <baluLib.h>

namespace BaluEngine
{
	namespace WorldInstance
	{
		class TView
		{
			//TODO заменить на матрицу ориентации и масштабирование
			BaluLib::TVec2 pos; //центр вида в координатах экрана
			BaluLib::TVec2 size; //ширина и высота в координатах экрана
								 //EngineInterface::IViewport* viewport;
		public:
			TView() {}
			TView(BaluLib::TVec2 pos, BaluLib::TVec2 size)//, EngineInterface::IViewport* viewport)
			{
				this->pos = pos;
				this->size = size;
				//this->viewport = viewport;
			}
			//EngineInterface::IViewport* GetViewport()
			//{
			//	return viewport;
			//}
			BaluLib::TVec2 GetPos()
			{
				return pos;
			}
			BaluLib::TVec2 GetSize()
			{
				return size;
			}
		};

		class TScreen
		{
		public:
			BaluLib::TVec2i size;
			//std::vector<TView> views;
		public:
			TScreen() {}
			TScreen(BaluLib::TVec2i size)
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
			BaluLib::TVec2 FromViewToScreen(TView view, BaluLib::TVec2 view_coord)
			{
				return (view_coord - BaluLib::TVec2(0.5, 0.5)).ComponentMul(view.GetSize()) + view.GetPos();
			}
			BaluLib::TVec2 FromScreenToView(TView view, BaluLib::TVec2 screen_coord)
			{
				return ((screen_coord - view.GetPos()) / view.GetSize()) + BaluLib::TVec2(0.5, 0.5);
			}
			BaluLib::TVec2i ToScreenPixels(BaluLib::TVec2 coord)
			{
				return BaluLib::TVec2i(
					size[0] * coord[0],
					size[1] * coord[1]
				);
			}
			BaluLib::TVec2 FromScreenPixels(BaluLib::TVec2i coord)
			{
				return BaluLib::TVec2(
					coord[0] / size[0],
					coord[1] / size[1]
				);
			}
			BaluLib::TVec2i ToScreenPixels2(BaluLib::TVec2 coord)
			{
				return BaluLib::TVec2i(
					size[0] * coord[0],
					size[1] * (1 - coord[1])
				);
			}
			BaluLib::TVec2 FromScreenPixels2(BaluLib::TVec2i coord)
			{
				return BaluLib::TVec2(
					(float)coord[0] / size[0],
					1 - (float)coord[1] / size[1]
				);
			}
		};

		namespace Internal
		{			
			class TMaterialInstance;

			struct TRenderCommand
			{
			public:
				TMaterialInstance* material_id;

				bool draw_triangles_grid;
				int vertices_count;
				BaluLib::TVec2* vertices;
				BaluLib::TVec2* tex_coords;
				BaluLib::TVec4* colors;
				//int layer_order;
				float alpha;

				TRenderCommand() {}

				TRenderCommand(TMaterialInstance* material_id, int vertices_count, BaluLib::TVec2* vertices, BaluLib::TVec2* tex_coords, BaluLib::TVec4* colors)
				{
					this->material_id = material_id;
					this->vertices_count = vertices_count;
					this->vertices = vertices;
					this->tex_coords = tex_coords;
					this->colors = colors;
				}
			};

			//TODO в дальнейшем вся информация для рендера должна находиться полностью здесь, для возможности параллельной отрисовки
			class TDrawingHelper;

			class IGUIVisual
			{
			public:
				virtual void Render(TDrawingHelper* helper)const = 0;
			};
		}
	}
}