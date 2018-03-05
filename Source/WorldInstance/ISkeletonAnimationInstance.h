#pragma once

namespace BaluEngine
{
	namespace WorldInstance
	{
		class ISkeletonAnimationInstance
		{
		public:
			virtual void Update(float step) = 0;
			virtual void PlayAnimation(const std::string& name, float alpha) = 0;
			virtual void StopAnimation(const std::string& name) = 0;
		};
	}
}