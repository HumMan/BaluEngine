#pragma once

#include "ISpritePolygon.h"
#include "../Material/IMaterialInstance.h"
#include <World\Layers.h>

namespace EngineInterface
{

	class IBaluSpritePolygonInstance
	{
	public:
		//virtual void SetSpritePolygon(std::string name) = 0;
		virtual IBaluSpritePolygon* GetSpritePolygon() = 0;

		virtual void SetActiveAnimation(const std::string&) = 0;
		//virtual TBaluTransform GetGlobalTransform() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluSpritePolygonInstance: public IBaluSpritePolygonInstance, public IChangeListener
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
		~TBaluSpritePolygonInstance();

		//void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance>& results);

		void Render(std::vector<TRenderCommand>& commands, TLayersManager& layers);

		void UpdateTransform(TBaluTransformWithScale global);
		void UpdateAnimation();

		TBaluSpritePolygon* GetSpritePolygon();

		void SetActiveAnimation(const std::string&);
	};
#endif

}