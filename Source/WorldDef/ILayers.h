#pragma once

namespace BaluEngine
{
	namespace WorldDef
	{
		class TLayersManagerChangeListener
		{
		public:
			virtual void LayerAdded(int layer_id) = 0;
			virtual void LayerRemoved(int layer_id) = 0;
			virtual void LayerChanged(int layer_id) = 0;
		};
	}
}