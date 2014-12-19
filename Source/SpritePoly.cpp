#define NOMINMAX

#include "SpritePoly.h"

#include "Utils/texture_polygon.h"

#include <IL/ilut.h>

#include "../poly2tri/poly2tri/poly2tri.h"

void TBaluSpritePolygon::SetPolygonFromTexture()
{
	if (material != nullptr)
	{
		ILuint handle;
		ilGenImages(1, &handle);
		ilBindImage(handle);
		ilLoadImage(material->GetImagePath().c_str());

		auto w = ilGetInteger(IL_IMAGE_WIDTH);
		auto h = ilGetInteger(IL_IMAGE_HEIGHT);
		int memory_needed = w * h * sizeof(unsigned int);
		ILuint * data = new ILuint[memory_needed];
		ilCopyPixels(0, 0, 0, w, h, 1, IL_ALPHA, IL_UNSIGNED_INT, data);


		int temp = std::numeric_limits<unsigned int>().max() / 255;
		for (int i = 0; i < w * h; i++)
			data[i] = data[i] / temp;

		vertices = FarseerPhysics_Common_TextureTools::TextureConverter::DetectVertices(data, w*h, w);

		delete[] data;

		ilDeleteImage(handle);

		for (int i = 0; i < vertices.size(); i++)
			vertices[i] = vertices[i] / TVec2(w, h);

		UpdatePolyVertices();
	}
}


void TBaluSpritePolygon::TriangulateGeometry()
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

void TBaluSpritePolygon::UpdatePolyVertices()
{
	polygon_vertices = vertices;
	for (int i = 0; i < polygon_vertices.size(); i++)
		polygon_vertices[i] = polygon_vertices[i].ComponentMul(size) - origin;
}

void TBaluSpritePolygon::SetMaterial(TBaluMaterial* material)
{
	this->material = material;
	SetPolygonFromTexture();
}
void TBaluSpritePolygon::SetPolygonVertices(std::vector<TVec2> polygon_vertices)
{
	this->polygon_vertices = polygon_vertices;
}
void TBaluSpritePolygon::SetVertices(std::vector<TVec2> vertices)
{
	this->vertices = vertices;
	UpdatePolyVertices();
}
std::vector<TVec2> TBaluSpritePolygon::GetVertices()
{
	return polygon_vertices;
}
int TBaluSpritePolygon::GetVerticesCount()
{
	return polygon_vertices.size();
}
void TBaluSpritePolygon::SetVertex(int id, TVec2 pos)
{

}
TVec2 TBaluSpritePolygon::GetPolygonVertex(int id)
{
	return polygon_vertices[id];
}
TVec2 TBaluSpritePolygon::GetVertex(int id)
{
	return vertices[id];
}
//void TBaluSpritePolygon::SetTexCoords(std::vector<TVec2> tex_coordinates)
//{
//	this->tex_coordinates = tex_coordinates;
//}
void TBaluSpritePolygon::SetTexCoordsFromVertices(TVec2 origin, TVec2 scale)
{
	tex_coordinates = triangulated;
	for (int i = 0; i < tex_coordinates.size(); i++)
	{
		tex_coordinates[i] = ((triangulated[i]-this->origin)/this->size).ComponentMul(scale) - origin;
	}
}