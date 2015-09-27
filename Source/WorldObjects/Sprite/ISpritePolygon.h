
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "../Material/IMaterial.h"
#include "../Class/IAnimationFrames.h"
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
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluSpritePolygon, "ISpritePolygon");
	MUnpackA1(TYPE, SetScale, WrapValue<TVec2>);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif
}