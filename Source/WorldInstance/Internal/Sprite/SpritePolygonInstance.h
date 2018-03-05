#pragma once

#include "../../Interface.h"

#include "../Material/MaterialInstance.h"

#include "../../../Render/Render.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{

			class TSpritePolygonInstance : public ISpritePolygonInstance//, public IChangeListener
			{
			private:
				TMaterialInstance material;
				WorldDef::ISpritePolygon* source;

				std::vector<BaluLib::TVec2> vertices; //in scene coordinates
				std::vector<BaluLib::TVec2> tex_coords;

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

				TSpritePolygonInstance(WorldDef::ISpritePolygon* source, TResources* resources);
				~TSpritePolygonInstance();

				//void QueryAABB(TAABB2 frustum, std::vector<TSpritePolygonInstance>& results);

				void Render(std::vector<TRenderCommand>& commands/*, TLayersManager& layers*/);

				void UpdateTransform(WorldDef::TTransformWithScale global);
				void UpdateAnimation();

				WorldDef::ISpritePolygon* GetSpritePolygon();

				void SetActiveAnimation(const std::string&);
			};
		}
	}

}
