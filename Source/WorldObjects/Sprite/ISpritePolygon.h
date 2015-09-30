
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#if !defined(BALU_ENGINE_SCRIPT_CLASSES) && !defined(BALU_ENGINE_DLL_INTERFACES) && !defined(BALU_ENGINE_DISABLE_PRAGMA_ONCE)

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "../Class/IAnimationFrames.h"
#include "../Material/IMaterial.h"
#include <World\RenderCommand.h>
#endif

#include "../../BaluLib/Source/Math/vec.h"
#include <vector>
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluSpritePolygon
	{
	public:

		virtual bool PointCollide(TVec2 sprite_space_point)=0;
		virtual TOBB2 GetBoundingBox()=0;
		virtual bool IsEnable() = 0;
		virtual void SetEnable(bool enable)=0 ;
		virtual void AddAnimDesc(TAnimDesc* desc) = 0;
		virtual void CreateAnimationLine(std::string line_name, std::vector<TAnimationFrames> frames) = 0;
		virtual void CreateAnimationLine(std::string line_name, TAnimDesc* desc, std::vector<int> frames) = 0;

		virtual IBaluMaterial* GetMaterial() = 0;
		virtual void SetMaterial(IBaluMaterial* material) = 0;
		virtual void SetAsBox(float width, float height) = 0;
		virtual void SetPolygonFromTexture(std::string assets_dir) = 0;
		virtual void SetVertices(std::vector<TVec2> vertices) = 0;
		virtual std::vector<TVec2> GetTriangulatedVertices() = 0;
		virtual std::vector<TVec2> GetPolygon()=0;
		virtual std::vector<TVec2> GetTexCoords() = 0;

		virtual int GetVerticesCount() = 0;
		virtual void SetVertex(int id, TVec2 pos) = 0;
		virtual TVec2 GetPolygonVertex(int id) = 0;
		virtual TVec2 GetVertex(int id) = 0;

		virtual TBaluTransformWithScale GetTransformWithScale() = 0;
		virtual TBaluTransform GetTransform()=0;
		virtual TVec2 GetScale() = 0;
		virtual void SetTransform(TBaluTransform)=0;
		virtual void SetScale(TVec2 scale)=0;

		virtual void SetTexCoordsFromVertices(TVec2 origin, TVec2 scale) = 0;
		virtual void SetTexCoordsFromVerticesByRegion(TVec2 left_bottom, TVec2 right_top) = 0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	class TBaluSpritePolygon: public IBaluSpritePolygon
	{
	private:
		friend class TBaluSpritePolygonInstance;

		TBaluMaterial* material;

		std::vector<TVec2> polygon_vertices;//вершины замкнутого контура спрайта

		TVec2 size; //используется при генерации полигона по текстуре
		TBaluTransformWithScale transform; //положение полигона в спрайте

		std::vector<TVec2> triangulated;

		TVec2 tex_coord_origin, tex_coord_scale;
		std::vector<TVec2> tex_coordinates;

		std::vector<std::unique_ptr<TAnimDesc>> anim_descs;

		std::map<std::string, TAnimLine> animation_lines;

		bool enable;
		bool draw_triangles_grid;

		void UpdateTexCoords();
		void UpdatePolyVertices();
		void TriangulateGeometry();

		int layer;

		TAABB2 GetVerticesBox(); //AABB контура(polygon_vertices) без применения трансформации local
	public:

		void SetDrawTrianglesGrid(bool draw)
		{
			draw_triangles_grid = draw;
		}

		int GetAnimDescIndex(TAnimDesc* desc);
		TAnimDesc* GetAnimDesc(int index);

		TAABB2 GetAABB(TBaluTransformWithScale sprite_in_class);
		TOBB2 GetBoundingBox();

		bool PointCollide(TVec2 sprite_space_point);

		bool IsEnable()
		{
			return enable;
		}

		void SetEnable(bool enable)
		{
			this->enable = enable;
		}

		TBaluSpritePolygon();

		TBaluTransform GetTransform();
		TBaluTransformWithScale GetTransformWithScale();
		TVec2 GetScale()
		{
			return transform.scale;
		}
		void SetTransform(TBaluTransform);
		void SetScale(TVec2 scale);

		TBaluMaterial* GetMaterial();
		void SetMaterial(TBaluMaterial* material);
		void SetMaterial(IBaluMaterial* material);
		void SetAsBox(float width, float height);
		void SetPolygonFromTexture(std::string assets_dir);
		void SetVertices(std::vector<TVec2> vertices);
		std::vector<TVec2> GetTriangulatedVertices();
		std::vector<TVec2> GetPolygon();

		std::vector<TVec2> GetTexCoords();

		int GetVerticesCount();
		void SetVertex(int id, TVec2 pos);
		TVec2 GetPolygonVertex(int id);
		TVec2 GetVertex(int id);

		void SetTexCoordsFromVertices(TVec2 origin, TVec2 scale);
		void SetTexCoordsFromVerticesByRegion(TVec2 left_bottom, TVec2 right_top);

		void AddAnimDesc(TAnimDesc* desc);
		void CreateAnimationLine(std::string line_name, std::vector<TAnimationFrames> frames);
		void CreateAnimationLine(std::string line_name, TAnimDesc* desc, std::vector<int> frames);

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};
#endif
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluSpritePolygon, "ISpritePolygon");
	MUnpackA1(TYPE, SetScale, WrapValue<TVec2>);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif
}