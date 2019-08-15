#pragma once
namespace BaluEngine
{
	namespace WorldInstance
	{
		class ISpritePolygonInstance
		{
		public:
			//virtual void SetSpritePolygon(std::string name) = 0;
			virtual WorldDef::ISpritePolygon* GetSpritePolygon() = 0;

			virtual void SetActiveAnimation(const std::string&) = 0;
			//virtual TBaluTransform GetGlobalTransform() = 0;
			virtual bool IsEnabled() = 0;

			virtual void SetEnable(bool enabled) = 0;

			virtual ~ISpritePolygonInstance() {}
		};
	}
}

