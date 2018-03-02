#pragma once

#include <baluLib.h>
#include <vector>

namespace BaluEngine
{
	namespace WorldDef
	{

		class ISpritePolygon: public ISerializable
		{
		public:

			virtual bool PointCollide(BaluLib::TVec2 sprite_space_point) = 0;
			virtual BaluLib::TOBB2 GetBoundingBox() = 0;
			virtual bool IsEnable() = 0;
			virtual void SetEnable(bool enable) = 0;
			virtual void AddAnimDesc(IAnimDesc* desc) = 0;
			//virtual void CreateAnimationLine(std::string line_name, std::vector<std::unique_ptr<IAnimationFrames>> frames) = 0;
			virtual void CreateAnimationLine(std::string line_name, IAnimDesc* desc, std::vector<int> frames) = 0;

			virtual IMaterial* GetMaterial() = 0;
			virtual void SetMaterial(IMaterial* material) = 0;
			virtual void SetAsBox(float width, float height) = 0;
			virtual void SetPolygonFromTexture(std::string assets_dir) = 0;
			virtual void SetVertices(std::vector<BaluLib::TVec2> vertices) = 0;
			virtual std::vector<BaluLib::TVec2> GetTriangulatedVertices() = 0;
			virtual std::vector<BaluLib::TVec2> GetPolygon() = 0;
			virtual std::vector<BaluLib::TVec2> GetTexCoords() = 0;

			virtual int GetVerticesCount() = 0;
			virtual void SetVertex(int id, BaluLib::TVec2 pos) = 0;
			virtual BaluLib::TVec2 GetPolygonVertex(int id) = 0;
			virtual BaluLib::TVec2 GetVertex(int id) = 0;

			virtual TTransformWithScale GetTransformWithScale() = 0;
			virtual TTransform GetTransform() = 0;
			virtual BaluLib::TVec2 GetScale() = 0;
			virtual void SetTransform(TTransform) = 0;
			virtual void SetScale(BaluLib::TVec2 scale) = 0;

			virtual int GetAnimDescIndex(IAnimDesc* desc)const=0;
			virtual IAnimDesc* GetAnimDesc(int index)const=0;

			virtual void SetTexCoordsFromVertices(BaluLib::TVec2 origin, BaluLib::TVec2 scale) = 0;
			virtual void SetTexCoordsFromVerticesByRegion(BaluLib::TVec2 left_bottom, BaluLib::TVec2 right_top) = 0;
		};
	}
}