#pragma once

namespace BaluEngine
{
	namespace WorldDef
	{
		class ILayer : public virtual IProperties, public ISerializable
		{
		public:
		};

		class ILayersManagerChangeListener
		{
		public:
			virtual void LayerAdded(int layer_id) = 0;
			virtual void LayerRemoved(int layer_id) = 0;
			virtual void LayerChanged(int layer_id) = 0;
		};
	}
}