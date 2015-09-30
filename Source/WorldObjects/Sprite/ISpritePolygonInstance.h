
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#if !defined(BALU_ENGINE_SCRIPT_CLASSES) && !defined(BALU_ENGINE_DLL_INTERFACES) && !defined(BALU_ENGINE_DISABLE_PRAGMA_ONCE)

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "ISpritePolygon.h"
#include "../Material/IMaterialInstance.h"
#include <World\Layers.h>
#endif

#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluSpritePolygonInstance
	{
	public:
		//virtual void SetSpritePolygon(std::string name) = 0;
		virtual IBaluSpritePolygon* GetSpritePolygon() = 0;

		virtual void SetActiveAnimation(std::string) = 0;
		//virtual TBaluTransform GetGlobalTransform() = 0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	class TBaluSpritePolygonInstance: public IBaluSpritePolygonInstance
	{
	private:
		TMaterialInstance material;
		TBaluSpritePolygon* source;

		std::vector<TVec2> vertices; //in scene coordinates
		std::vector<TVec2> tex_coords;

		std::string active_animation_line;

		int active_desc_index;
		int active_frame_index;

		float animation_time_from_start;

		void NextFrame();

		void UpdateGeometry();

		bool enable;
		int layer;
	public:

		bool IsEnable()
		{
			return enable;
		}

		void SetEnable(bool enable)
		{
			this->enable = enable;
		}

		TBaluSpritePolygonInstance(TBaluSpritePolygon* source, TResources* resources);

		//void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance>& results);

		void Render(std::vector<TRenderCommand>& commands, TLayersManagerInstance& layers);

		void UpdateTransform(TBaluTransformWithScale global);
		void UpdateAnimation();

		TBaluSpritePolygon* GetSpritePolygon();

		void SetActiveAnimation(std::string);
};
#endif
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluSpritePolygonInstance, "ISpritePolygonInstance");
	MUnpackA1(TYPE, SetActiveAnimation, TString);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif
}