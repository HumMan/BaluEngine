#pragma once

#include "../../Interface.h"

#include "../Material/Material.h"

#include "AnimationFrames.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			class TSpritePolygon : public ISpritePolygon, public TChangeListenerArray
			{
			private:
				TMaterial* material;

				std::vector<BaluLib::TVec2> polygon_vertices;//вершины замкнутого контура спрайта

				BaluLib::TVec2 size; //используется при генерации полигона по текстуре
				TTransformWithScale transform; //положение полигона в спрайте

				std::vector<BaluLib::TVec2> triangulated;

				BaluLib::TVec2 tex_coord_origin, tex_coord_scale;
				std::vector<BaluLib::TVec2> tex_coordinates;

				std::vector<std::unique_ptr<IAnimDesc>> anim_descs;

				std::map<std::string, std::unique_ptr<TAnimLine>> animation_lines;

				bool enable;
				bool draw_triangles_grid;

				void UpdateTexCoords();
				void UpdatePolyVertices();
				void TriangulateGeometry();

				int layer;

				BaluLib::TAABB2 GetVerticesBox(); //AABB контура(polygon_vertices) без применения трансформации local
			public:

				void SetDrawTrianglesGrid(bool draw)
				{
					draw_triangles_grid = draw;
				}

				int GetAnimDescIndex(IAnimDesc* desc)const;
				IAnimDesc* GetAnimDesc(int index)const;

				BaluLib::TAABB2 GetAABB(TTransformWithScale sprite_in_class);
				BaluLib::TOBB2 GetBoundingBox();

				bool PointCollide(BaluLib::TVec2 sprite_space_point);

				bool IsEnable()
				{
					return enable;
				}

				void SetEnable(bool enable)
				{
					this->enable = enable;
				}

				TSpritePolygon();

				TTransform GetTransform();
				TTransformWithScale GetTransformWithScale();
				BaluLib::TVec2 GetScale()
				{
					return transform.scale;
				}
				void SetTransform(TTransform);
				void SetScale(BaluLib::TVec2 scale);

				IMaterial* GetMaterial();
				void SetMaterial(IMaterial* material);
				void SetAsBox(float width, float height);
				void SetPolygonFromTexture(std::string assets_dir);
				void SetVertices(std::vector<BaluLib::TVec2> vertices);
				std::vector<BaluLib::TVec2> GetTriangulatedVertices();
				std::vector<BaluLib::TVec2> GetPolygon();

				std::vector<BaluLib::TVec2> GetTexCoords();

				int GetVerticesCount();
				void SetVertex(int id, BaluLib::TVec2 pos);
				BaluLib::TVec2 GetPolygonVertex(int id);
				BaluLib::TVec2 GetVertex(int id);

				void SetTexCoordsFromVertices(BaluLib::TVec2 origin, BaluLib::TVec2 scale);
				void SetTexCoordsFromVerticesByRegion(BaluLib::TVec2 left_bottom, BaluLib::TVec2 right_top);

				void AddAnimDesc(IAnimDesc* desc);
				//void CreateAnimationLine(std::string line_name, std::vector<std::unique_ptr<IAnimationFrames>> frames);
				void CreateAnimationLine(std::string line_name, IAnimDesc* desc, std::vector<int> frames);

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
		}
	}
}