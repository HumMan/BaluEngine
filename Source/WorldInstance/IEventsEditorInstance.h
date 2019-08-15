#pragma once

namespace BaluEngine
{
	namespace WorldInstance
	{

		class IMouseEventListener
		{
		public:
			virtual void OnMouseMove(WorldDef::TMouseEventArgs e) {}
			virtual void OnMouseDown(WorldDef::TMouseEventArgs e) {}
			virtual void OnMouseUp(WorldDef::TMouseEventArgs e) {}
		};

		class IEventsEditorInstance: public ISceneContactListener
		{
		public:
			virtual void MouseDown(WorldDef::TMouseEventArgs e) = 0;
			virtual void MouseMove(WorldDef::TMouseEventArgs e) = 0;
			virtual void MouseUp(WorldDef::TMouseEventArgs e) = 0;
			virtual void MouseVerticalWheel(int amount) = 0;

			virtual void PrePhysStep() = 0;

			virtual void Compile() = 0;

			virtual void KeyDown(WorldDef::TKey key) = 0;
			virtual void KeyUp(WorldDef::TKey key) = 0;

			virtual void OnCreate(std::shared_ptr<ITransformedClassInstance> object)=0;

			virtual void WorldStart(std::shared_ptr<IWorld>world_instance, std::shared_ptr< IComposer> composer) = 0;

			virtual void AddMouseEventListener(IMouseEventListener*) = 0;
			virtual void RemoveMouseEventListener(IMouseEventListener*) = 0;

			virtual void ViewportResize(std::shared_ptr < IDirector> director, BaluLib::TVec2i old_size, BaluLib::TVec2i new_size) = 0;
		};
	}
}
