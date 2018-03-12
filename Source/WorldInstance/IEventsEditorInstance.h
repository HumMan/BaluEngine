#pragma once

namespace BaluEngine
{
	namespace WorldInstance
	{

		class TMouseEventListener
		{
		public:
			virtual void OnMouseMove(WorldDef::TMouseEventArgs e) {}
			virtual void OnMouseDown(WorldDef::TMouseEventArgs e) {}
			virtual void OnMouseUp(WorldDef::TMouseEventArgs e) {}
		};

		class IEventsEditorInstance
		{
		public:
			virtual void MouseDown(WorldDef::TMouseEventArgs e) = 0;
			virtual void MouseMove(WorldDef::TMouseEventArgs e) = 0;
			virtual void MouseUp(WorldDef::TMouseEventArgs e) = 0;
			virtual void MouseVerticalWheel(int amount) = 0;

			virtual void PrePhysStep() = 0;

			virtual void KeyDown(WorldDef::TKey key) = 0;
			virtual void KeyUp(WorldDef::TKey key) = 0;

			virtual void WorldStart(IWorld* world_instance, IComposer* composer) = 0;

			//virtual void AddMouseEventListener(TMouseEventListener*) = 0;
			//virtual void RemoveMouseEventListener(TMouseEventListener*) = 0;

			virtual void ViewportResize(IDirector* director, BaluLib::TVec2i old_size, BaluLib::TVec2i new_size) = 0;

			virtual void Collide(ITransformedClassInstance* object,
				ITransformedSpriteInstance* obj_a, ITransformedClassInstance* obj_b)=0;
		};
	}
}
