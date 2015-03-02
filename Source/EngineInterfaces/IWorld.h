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

typedef void(*MouseUpDownCallback)(TCallbackData* callback, TMouseEventArgs e);
typedef void(*MouseMoveCallback)(TCallbackData* callback, TMouseEventArgs e);

namespace EngineInterface
{
	class IBaluWorld
	{
	public:
		virtual TCallbacksActiveType& GetCallbacksActiveType() = 0;
		virtual bool TryFindClass(const char* class_name, IBaluClass*& result) = 0;

		virtual IBaluMaterial* CreateMaterial(const char* mat_name) = 0;
		virtual IBaluSprite* CreateSprite(const char* sprite_name) = 0;
		virtual IBaluClass* CreateClass(const char* class_name) = 0;
		virtual IBaluScene* CreateScene(const char* scene_name) = 0;

		virtual std::vector<std::pair<std::string, EngineInterface::IBaluMaterial*>> GetMaterials() = 0;
		virtual std::vector<std::pair<std::string, EngineInterface::IBaluSprite*>> GetSprites() = 0;
		virtual std::vector<std::pair<std::string, EngineInterface::IBaluClass*>> GetClasses() = 0;
		virtual std::vector<std::pair<std::string, EngineInterface::IBaluScene*>> GetScenes() = 0;

		virtual IBaluScene* GetScene(const char* scene_name) = 0;

		virtual IBaluPhysShapeFactory* GetPhysShapeFactory() = 0;

		//void OnKeyDown(TKey key, KeyDownCallback callback);
		//void OnKeyUp(TKey key, KeyDownCallback callback);

		virtual void OnMouseDown(CallbackWithData<MouseUpDownCallback>) = 0;
		virtual void OnMouseUp(CallbackWithData<MouseUpDownCallback>) = 0;
		virtual void OnMouseMove(CallbackWithData<MouseMoveCallback>) = 0;

		virtual void SaveToXML(std::string path) = 0;
		virtual void LoadFromXML(std::string path) = 0;
		
	};
}