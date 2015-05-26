#pragma once

#include "Material.h"

#include <map>

#include "EngineInterfaces\IMaterial.h"

#include "EngineInterfaces\IAnimationFrames.h"

#include "EngineInterfaces\ISpritePolygon.h"

#include "EngineInterfaces\ICallbacks.h"

using namespace EngineInterface;

namespace pugi
{
	class xml_node;
}

class TBaluWorld;

class TBaluSpritePolygon: public EngineInterface::IBaluSpritePolygon
{
private:
	friend class TBaluSpritePolygonInstance;

	TBaluMaterial* material;

	TVec2 size; //используется при генерации полигона по текстуре
	TBaluTransformWithScale local; //положение полигона в спрайте

	std::vector<TVec2> polygon_vertices;

	std::vector<TVec2> triangulated;

	TVec2 tex_coord_origin, tex_coord_scale;
	std::vector<TVec2> tex_coordinates;

	std::vector<std::unique_ptr<EngineInterface::TAnimDesc>> anim_descs;
	
	std::map<std::string, EngineInterface::TAnimLine> animation_lines;

	bool enable;

	void UpdateTexCoords();
	void UpdatePolyVertices();
	void TriangulateGeometry();

	bool is_custom_draw;
	std::vector<CallbackWithData<TCustomDrawCallback>> custom_draw_callbacks;


	TAABB2 GetVerticesBox();
public:

	int GetAnimDescIndex(EngineInterface::TAnimDesc* desc);
	EngineInterface::TAnimDesc* GetAnimDesc(int index);

	TAABB2 GetAABB(TBaluTransformWithScale sprite_in_class);
	TOBB2 GetBoundingBox();

	bool PointCollide(TVec2 sprite_space_point);

	void AddOnCustomDraw(CallbackWithData<TCustomDrawCallback> callback);
	void RemoveOnCustomDraw(int index);

	bool IsCustomDraw()
	{
		return is_custom_draw;
	}

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
	TVec2 GetScale()
	{
		return local.scale;
	}
	void SetTransform(TBaluTransform);
	void SetScale(TVec2 scale);

	TBaluMaterial* GetMaterial();
	void SetMaterial(TBaluMaterial* material);
	void SetMaterial(EngineInterface::IBaluMaterial* material);
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

	void AddAnimDesc(EngineInterface::TAnimDesc* desc);
	void CreateAnimationLine(std::string line_name, std::vector<EngineInterface::TAnimationFrames> frames);
	void CreateAnimationLine(std::string line_name, EngineInterface::TAnimDesc* desc, std::vector<int> frames);

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};
