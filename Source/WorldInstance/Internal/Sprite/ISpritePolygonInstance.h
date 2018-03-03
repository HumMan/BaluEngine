#pragma once

#include <WorldDef/Objects/Sprite/ISpritePolygon.h>
#include <WorldDef/Objects/Scene/Layers.h>

#include "../Material/IMaterialInstance.h"

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
	class TSpritePolygonInstance: public IBaluSpritePolygonInstance, public IChangeListener
	{
	private:
		TMaterialInstance material;
		TSpritePolygon* source;

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

		TSpritePolygonInstance(TSpritePolygon* source, TResources* resources);
		~TSpritePolygonInstance();

		//void QueryAABB(TAABB2 frustum, std::vector<TSpritePolygonInstance>& results);

		void Render(std::vector<TRenderCommand>& commands, TLayersManager& layers);

		void UpdateTransform(TBaluTransformWithScale global);
		void UpdateAnimation();

		TSpritePolygon* GetSpritePolygon();

		void SetActiveAnimation(const std::string&);
	};
#endif

}
