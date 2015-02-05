#pragma once

#include "IMaterial.h"
#include "ISprite.h"
#include "IClass.h"
#include "IScene.h"


enum class TMouseButton
{
	Left,
	Right,
	Middle
};

struct TMouseEventArgs
{
	TMouseButton button;
	TVec2i location;
	TMouseEventArgs(){}
	TMouseEventArgs(TMouseButton button, TVec2i location)
	{
		this->button = button;
		this->location = location;
	}
};

typedef void(*MouseUpDownCallback)(TCallbackData* callback, TMouseEventArgs e, TVec2 world_cursor_location);
typedef void(*MouseMoveCallback)(TCallbackData* callback, TMouseEventArgs e, TVec2 world_cursor_location);

namespace EngineInterface
{
	class IBaluWorld
	{
	public:
		virtual TCallbacksActiveType& GetCallbacksActiveType() = 0;
		virtual bool TryFindClass(char* class_name, IBaluClass*& result)=0;

		virtual IBaluMaterial* CreateMaterial(char* mat_name) = 0;
		virtual IBaluSprite* CreateSprite(char* sprite_name) = 0;
		virtual IBaluClass* CreateClass(char* class_name) = 0;
		virtual IBaluScene* CreateScene(char* scene_name) = 0;

		virtual IBaluScene* GetScene(char* scene_name) = 0;

		virtual IBaluPhysShapeFactory* GetPhysShapeFactory() = 0;

		//void OnKeyDown(TKey key, KeyDownCallback callback);
		//void OnKeyUp(TKey key, KeyDownCallback callback);

		virtual void OnMouseDown(CallbackWithData<MouseUpDownCallback>) = 0;
		virtual void OnMouseUp(CallbackWithData<MouseUpDownCallback>) = 0;
		virtual void OnMouseMove(CallbackWithData<MouseUpDownCallback>) = 0;
		
	};
}