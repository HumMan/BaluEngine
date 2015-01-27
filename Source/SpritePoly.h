#pragma once

#include "Material.h"

#include <map>

#include "EngineInterfaces\IMaterial.h"

#include "EngineInterfaces\IAnimationFrames.h"



class TBaluSpritePolygon: public EngineInterface::IBaluSpritePolygon
{
private:
	friend class TBaluSpritePolygonInstance;

	TBaluMaterial* material;

	TVec2 size;
	TBaluTransform local;

	std::vector<TVec2> vertices;
	std::vector<TVec2> polygon_vertices;
	std::vector<TVec2> triangulated;

	TVec2 tex_coord_origin, tex_coord_scale;
	std::vector<TVec2> tex_coordinates;

	std::vector<std::unique_ptr<EngineInterface::TAnimDesc>> anim_descs;
	
	std::map<std::string, EngineInterface::TAnimLine> animation_lines;

	bool enable;

	void SetPolygonFromTexture();
	void UpdatePolyVertices();
	void TriangulateGeometry();

	bool is_custom_draw;
	TCustomDrawCallback custom_draw_callback;
public:

	void OnCustomDraw(TCustomDrawCallback callback);

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

	TBaluMaterial* GetMaterial();
	void SetMaterial(TBaluMaterial* material);
	void SetMaterial(EngineInterface::IBaluMaterial* material);
	void SetPolygonVertices(std::vector<TVec2> polygon_vertices);
	void SetAsBox(float width, float height);

	void SetVertices(std::vector<TVec2> vertices);
	std::vector<TVec2> GetVertices();

	std::vector<TVec2> GetTexCoords();

	int GetVerticesCount();
	void SetVertex(int id, TVec2 pos);
	TVec2 GetPolygonVertex(int id);
	TVec2 GetVertex(int id);

	//void SetTexCoords(std::vector<TVec2> tex_coordinates);
	void SetTexCoordsFromVertices(TVec2 origin, TVec2 scale);
	void SetTexCoordsFromVerticesByRegion(TVec2 left_bottom, TVec2 right_top);

	void AddAnimDesc(EngineInterface::TAnimDesc* desc);
	void CreateAnimationLine(std::string line_name, std::vector<EngineInterface::TAnimationFrames> frames);
	void CreateAnimationLine(std::string line_name, EngineInterface::TAnimDesc* desc, std::vector<int> frames);
};
