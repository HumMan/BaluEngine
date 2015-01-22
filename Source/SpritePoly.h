#pragma once

#include "Material.h"

#include <map>

class TFrame
{
public:
	TVec2 left_bottom;
	TVec2 right_top;
	TFrame(TVec2 left_bottom, TVec2 right_top);
};

class TAnimDesc
{
public:
	virtual TFrame GetFrame(int index)=0;
};

class TSpecificFrame : public TAnimDesc
{
	TVec2 left_bottom;
	TVec2 right_top;
public:
	TSpecificFrame(TVec2 left_bottom, TVec2 right_top);
	TFrame GetFrame(int index);
};

class TGridFrames : public TAnimDesc
{
	TVec2 left_bottom;
	TVec2 width_height;
	int cell_count_x;
	int cell_count_y;
public:
	TGridFrames(TVec2 left_bottom, TVec2 width_height, int cell_count_x, int cell_count_y);
	TFrame GetFrame(int index);
};

struct TAnimationFrames
{
	TAnimDesc* desc;
	std::vector<int> frames;
	TAnimationFrames(TAnimDesc* desc, std::vector<int> frames);
	TAnimationFrames(TAnimDesc* desc, int frame);
};

std::vector<int> FramesRange(int start, int end);

class TAnimLine
{
public:
	std::string line_name;
	std::vector<TAnimationFrames> frames;
};

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

	std::vector<std::unique_ptr<TAnimDesc>> anim_descs;
	
	std::map<std::string, TAnimLine> animation_lines;

	bool enable;

	void SetPolygonFromTexture();
	void UpdatePolyVertices();
	void TriangulateGeometry();
public:

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

	void AddAnimDesc(TAnimDesc* desc);
	void CreateAnimationLine(std::string line_name, std::vector<TAnimationFrames> frames);
	void CreateAnimationLine(std::string line_name, TAnimDesc* desc, std::vector<int> frames);
};
