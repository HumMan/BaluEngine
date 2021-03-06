#define NOMINMAX

#include "ISpritePolygon.h"

#include "Utils/texture_polygon.h"

#include <IL/ilut.h>

#include "../../poly2tri/poly2tri/poly2tri.h"

#include <string.h>

using namespace EngineInterface;

typedef std::vector < std::pair<const char*, AnimDescClone>> anim_descs_registry_type;

anim_descs_registry_type *anim_descs_registry;

bool AnimDescFactory::Register(const char* name, AnimDescClone clone)
{
	if (anim_descs_registry == nullptr)
		anim_descs_registry = new anim_descs_registry_type();
	anim_descs_registry->push_back(std::pair<const char*, AnimDescClone>(name, clone));
	return true;
}

TAnimDesc* AnimDescFactory::Create(const char* name)
{
	for (int i = 0; i < anim_descs_registry->size(); i++)
		if (strcmp((*anim_descs_registry)[i].first, name) == 0)
			return (*anim_descs_registry)[i].second();
	throw std::invalid_argument("��� �� ���������������");
}

void AnimDescFactory::UnregisterAll()
{
	delete anim_descs_registry;
}

TAABB2 TBaluSpritePolygon::GetVerticesBox()
{
	//if (vertices.size() > 0)
	//{
	//	TAABB2 box(vertices[0],TVec2(0));
	//	for (int i = 1; i < vertices.size(); i++)
	//		box += vertices[i];
	//	return box;
	//}
	//else
	//	return TAABB2(TVec2(0), TVec2(0));
	if (polygon_vertices.size() > 0)
	{
		TAABB2 box(polygon_vertices[0], TVec2(0));
		for (int i = 1; i < polygon_vertices.size(); i++)
			box +=polygon_vertices[i];
		return box;
	}
	else
		return TAABB2(TVec2(0), TVec2(0));
}

int TBaluSpritePolygon::GetAnimDescIndex(EngineInterface::TAnimDesc* desc)
{
	for (int i = 0; i < anim_descs.size(); i++)
		if (anim_descs[i].get() == desc)
			return i;
	return -1;
}
EngineInterface::TAnimDesc* TBaluSpritePolygon::GetAnimDesc(int index)
{
	return anim_descs[index].get();
}

TAABB2 TBaluSpritePolygon::GetAABB(TBaluTransformWithScale sprite_in_class)
{
	auto global = sprite_in_class.ToGlobal(transform);

	if (polygon_vertices.size() > 0)
	{
		TAABB2 box(global.ToGlobal(polygon_vertices[0]), TVec2(0));
		for (int i = 1; i < polygon_vertices.size(); i++)
			box += global.ToGlobal(polygon_vertices[i]);
		return box;
	}
	else
		return TAABB2(global.ToGlobal(TVec2(0)), TVec2(0));
}

TOBB2 TBaluSpritePolygon::GetBoundingBox()
{
	return transform.ToGlobal(GetVerticesBox());
}

bool TBaluSpritePolygon::PointCollide(TVec2 sprite_space_point)
{
	TVec2 p = this->transform.ToLocal(sprite_space_point);
	for (int i = 0; i < triangulated.size(); i += 3)
	{
		bool is_in = PointInTriangle(p, triangulated[i + 0], triangulated[i + 1], triangulated[i + 2]);
		if (is_in)
			return true;
	}
	return false;
}

TFramesRange::TFramesRange(int start, int end)
{
	this->start = start;
	this->end = end;
}

std::vector<int> TFramesRange::ToFramesArray()
{
	if (end < start)
		throw std::invalid_argument("end ������ ���� ������ start");
	std::vector<int> result;
	int length = end - start + 1;
	result.reserve(length);
	result.resize(length);
	for (int i = start; i <= end; i++)
	{
		result[i - start] = i;
	}
	return result;
}

using namespace EngineInterface;

TFrame::TFrame(TVec2 left_bottom, TVec2 right_top)
{
	this->left_bottom = left_bottom;
	this->right_top = right_top;
}

TSpecificFrame::TSpecificFrame(TVec2 left_bottom, TVec2 right_top)
{
	this->left_bottom = left_bottom;
	this->right_top = right_top;
}

TFrame TSpecificFrame::GetFrame(int index)
{
	if (index != 0)
		throw std::invalid_argument("");
	return TFrame(left_bottom, right_top);
}

TGridFrames::TGridFrames(TVec2 left_bottom, TVec2 width_height, int cell_count_x, int cell_count_y)
{
	this->left_bottom = left_bottom;
	this->width_height = width_height;
	this->cell_count_x = cell_count_x;
	this->cell_count_y = cell_count_y;
}

TFrame TGridFrames::GetFrame(int index)
{
	if (index < 0 || index>cell_count_x*cell_count_y-1)
		throw std::invalid_argument("");
	int x = index % cell_count_y;
	int y = index / cell_count_x;

	float cell_size_x = width_height[0] / cell_count_x;
	float cell_size_y = width_height[1] / cell_count_y;

	auto frame_left_bottom = TVec2(left_bottom[0] + cell_size_x*x, left_bottom[1] + width_height[1] - cell_size_y*(y+1));
	return TFrame(frame_left_bottom, TVec2(frame_left_bottom[0] + cell_size_x, frame_left_bottom[1] + cell_size_y));
}

TAnimationFrames::TAnimationFrames(TAnimDesc* desc, std::vector<int> frames)
{
	this->desc = desc;
	this->frames = frames;
}

TAnimationFrames::TAnimationFrames(TAnimDesc* desc, int frame)
{
	this->desc = desc;
	this->frames = std::vector < int > {frame};
}

TBaluSpritePolygon::TBaluSpritePolygon()
{
	layer = 0;
	enable = true;
	draw_triangles_grid = true;
	material = nullptr;

	size = TVec2(1,1);

	tex_coord_origin = TVec2(0, 0);
	tex_coord_scale = TVec2(1, 1);
}
TBaluTransformWithScale TBaluSpritePolygon::GetTransformWithScale()
{
	return transform;
}
TBaluTransform TBaluSpritePolygon::GetTransform()
{
	return transform.transform;
}

void TBaluSpritePolygon::SetTransform(TBaluTransform t)
{
	transform.transform = t;
}

void TBaluSpritePolygon::SetScale(TVec2 scale)
{
	transform.scale = scale;
}

void TBaluSpritePolygon::SetPolygonFromTexture(std::string assets_dir)
{
	if (material != nullptr)
	{
		ILuint handle;
		ilGenImages(1, &handle);
		ilBindImage(handle);
		if (ilLoadImage((assets_dir+"//"+material->GetImagePath()).c_str()))
		{
			auto w = ilGetInteger(IL_IMAGE_WIDTH);
			auto h = ilGetInteger(IL_IMAGE_HEIGHT);
			int memory_needed = w * h * sizeof(unsigned int);
			ILuint * data = new ILuint[memory_needed];
			ilCopyPixels(0, 0, 0, w, h, 1, IL_ALPHA, IL_UNSIGNED_INT, data);


			int temp = std::numeric_limits<unsigned int>().max() / 255;
			for (int i = 0; i < w * h; i++)
				data[i] = data[i] / temp;

			polygon_vertices = FarseerPhysics_Common_TextureTools::TextureConverter::DetectVertices(data, w*h, w);

			delete[] data;

			ilDeleteImage(handle);

			for (int i = 0; i < polygon_vertices.size(); i++)
				polygon_vertices[i] = TVec2(polygon_vertices[i][0], h-polygon_vertices[i][1]) / TVec2(w, h) - TVec2(0.5, 0.5);

			UpdatePolyVertices();
		}
		else
		{
			auto err = ilGetError();
			auto err_string = iluErrorString(err);
			ilDeleteImage(handle);
		}
	}
	TriangulateGeometry();
}


void TBaluSpritePolygon::TriangulateGeometry()
{
	if (polygon_vertices.size() <= 2)
	{
		triangulated.clear();
		
		return;
	}
	try

	{
		std::vector<p2t::Point> points;
		points.resize(polygon_vertices.size());
		for (int i = 0; i < points.size(); i++)
			points[i] = p2t::Point(polygon_vertices[i][0], polygon_vertices[i][1]);

		std::vector<p2t::Point*> polyline;
		polyline.resize(points.size());
		for (int i = 0; i < polyline.size(); i++)
			polyline[i] = &points[i];

		p2t::CDT cdt(polyline);
		cdt.Triangulate();
		auto triangles = cdt.GetTriangles();
		triangulated.resize(triangles.size() * 3);
		for (int i = 0; i < triangles.size(); i++)
		{
			for (int k = 0; k < 3; k++)
			{
				auto tri_point = triangles[i]->GetPoint(k);
				triangulated[i * 3 + k] = TVec2(tri_point->x, tri_point->y);
			}
		}
	}
	catch (std::exception ex)
	{
		triangulated.clear();
		return;
	}
}

void TBaluSpritePolygon::UpdatePolyVertices()
{
	for (int i = 0; i < polygon_vertices.size(); i++)
		polygon_vertices[i] = transform.ToGlobal(polygon_vertices[i]);
}

TBaluMaterial* TBaluSpritePolygon::GetMaterial()
{
	return material;
}

void TBaluSpritePolygon::SetMaterial(TBaluMaterial* material)
{
	this->material = material;
}

void TBaluSpritePolygon::SetMaterial(EngineInterface::IBaluMaterial* material)
{
	SetMaterial(dynamic_cast<TBaluMaterial*>(material));
}

void TBaluSpritePolygon::SetAsBox(float width, float height)
{
	size = TVec2(width, height);
	polygon_vertices.resize(4);
	polygon_vertices[0] = TVec2(-width / 2, -height / 2);
	polygon_vertices[1] = TVec2(width / 2, -height / 2);
	polygon_vertices[2] = TVec2(width / 2, height / 2);
	polygon_vertices[3] = TVec2(-width / 2, height / 2);
	TriangulateGeometry();
}

void TBaluSpritePolygon::SetVertices(std::vector<TVec2> vertices)
{
	this->polygon_vertices = vertices;
	TriangulateGeometry();
	UpdateTexCoords();
}
std::vector<TVec2> TBaluSpritePolygon::GetPolygon()
{
	return polygon_vertices;
}
std::vector<TVec2> TBaluSpritePolygon::GetTriangulatedVertices()
{
	return triangulated;
}

std::vector<TVec2> TBaluSpritePolygon::GetTexCoords()
{
	return tex_coordinates;
}

int TBaluSpritePolygon::GetVerticesCount()
{
	return polygon_vertices.size();
}

void TBaluSpritePolygon::SetVertex(int id, TVec2 pos)
{
	polygon_vertices[id] = pos;
	TriangulateGeometry();
	UpdateTexCoords();
}

TVec2 TBaluSpritePolygon::GetPolygonVertex(int id)
{
	return polygon_vertices[id];
}

TVec2 TBaluSpritePolygon::GetVertex(int id)
{
	return polygon_vertices[id];
}

void TBaluSpritePolygon::SetTexCoordsFromVertices(TVec2 tex_coord_origin, TVec2 tex_coord_scale)
{
	this->tex_coord_origin = tex_coord_origin;
	this->tex_coord_scale = tex_coord_scale;
	UpdateTexCoords();
}

void TBaluSpritePolygon::UpdateTexCoords()
{
	tex_coordinates.resize(triangulated.size());
	auto vertex_left_bottom = - size*0.5;

	TVec2 right_top = tex_coord_origin + tex_coord_scale*0.5;
	TVec2 left_bottom = tex_coord_origin - tex_coord_scale*0.5;

	auto tex_coord_size = right_top - left_bottom;

	for (int i = 0; i < tex_coordinates.size(); i++)
	{
		tex_coordinates[i] = ((triangulated[i] - vertex_left_bottom) / size).ComponentMul(tex_coord_size) + left_bottom;
	}
}

void TBaluSpritePolygon::SetTexCoordsFromVerticesByRegion(TVec2 left_bottom, TVec2 right_top)
{
	this->tex_coord_origin = (left_bottom+right_top)*0.5;
	this->tex_coord_scale = (left_bottom - right_top).GetAbs();

	UpdateTexCoords();
}

void TBaluSpritePolygon::AddAnimDesc(TAnimDesc* desc)
{
	anim_descs.push_back(std::unique_ptr<TAnimDesc>(desc));
}

void TBaluSpritePolygon::CreateAnimationLine(std::string line_name, std::vector<TAnimationFrames> frames)
{
	TAnimLine new_line;
	new_line.line_name = line_name;
	new_line.frames = frames;
	animation_lines[line_name] = new_line;
}

void TBaluSpritePolygon::CreateAnimationLine(std::string line_name, TAnimDesc* desc, std::vector<int> frames)
{
	std::vector<TAnimationFrames> anim_frames;
	anim_frames.push_back(TAnimationFrames(desc, frames));
	CreateAnimationLine(line_name, anim_frames);
}
