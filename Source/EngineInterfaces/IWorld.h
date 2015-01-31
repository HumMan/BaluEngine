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
};

typedef void(*MouseUpDownCallback)(TMouseEventArgs e, TVec2 world_cursor_location, void* user_data);
typedef void(*MouseMoveCallback)(TMouseEventArgs e, TVec2 world_cursor_location, void* user_data);

namespace EngineInterface
{
	class IBaluWorld
	{
	public:
		virtual IBaluMaterial* CreateMaterial(char* mat_name) = 0;
		virtual IBaluSprite* CreateSprite(char* sprite_name) = 0;
		virtual IBaluClass* CreateClass(char* class_name) = 0;
		virtual IBaluScene* CreateScene(char* scene_name) = 0;

		virtual IBaluScene* GetScene(char* scene_name) = 0;

		virtual IBaluPhysShapeFactory* GetPhysShapeFactory() = 0;

		//void OnKeyDown(TKey key, KeyDownCallback callback);
		//void OnKeyUp(TKey key, KeyDownCallback callback);

		virtual void OnMouseDown(MouseUpDownCallback) = 0;
		virtual void OnMouseDown(MouseUpDownCallback, void* user_data) = 0;
		virtual void OnMouseUp(MouseUpDownCallback) = 0;
		virtual void OnMouseUp(MouseUpDownCallback, void* user_data) = 0;
		virtual void OnMouseMove(MouseMoveCallback) = 0;
		virtual void OnMouseMove(MouseMoveCallback, void* user_data) = 0;
		
	};
}