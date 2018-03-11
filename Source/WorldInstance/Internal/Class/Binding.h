#pragma once

#include "../Scripts/ScriptClassesRegistry.h"

#include "WorldDef/ICommon.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{
			static bool BindClass()
			{
				//TODO рассмотреть вариант генерации интерфейсов и перечислений из скриптов

				char* source;
				source =
					"class TFrame\n"
					"{\n"
					"	func extern GetLeftBottom():vec2;\n"
					"	func extern GetRightTop():vec2;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "TFrame", sizeof(WorldDef::TFrame), false, "WorldDef::TFrame");

				source =
					"class IClassPhysBody\n"
					"{\n"
					"	func extern GetLinearVelocity():vec2;\n"
					"	func extern SetLinearVelocity(vec2 value);\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IClassPhysBody", sizeof(void*), true, "IClassPhysBodyIntance");

				source =
					"class ISkeletonAnimation\n"
					"{\n"
					"	func extern PlayAnimation(string name, float pos);\n"
					"	func extern StopAnimation(string name);\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ISkeletonAnimation", sizeof(void*), true, "ISkeletonAnimationInstance");

				source =
					"class TMouseEventArgs\n"
					"{\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "TMouseEventArgs", sizeof(void*), true, "WorldDef::TMouseEventArgs");

				source =
					"class TRot\n"
					"{\n"
					"	func extern Set(float value);\n"
					"	func extern SetIdentity();\n"
					"	func extern GetAngle():float;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "TRot", sizeof(WorldDef::TRot), false, "WorldDef::TRot");

				source =
					"class TTransform\n"
					"{\n"
					"	func extern Transform(vec2 vertex, vec2 scale): vec2;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "TTransform", sizeof(WorldDef::TTransform), false, "WorldDef::TTransform");

				source =
					"class TTransformWithScale\n"
					"{\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "TTransformWithScale", sizeof(WorldDef::TTransform), false, "WorldDef::TTransformWithScale");

				source =
					"class IViewport\n"
					"{\n"
					"	func extern SetSize(vec2 size);\n"
					"	func extern GetSize(): vec2;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IViewport", sizeof(void*), true, "WorldDef::IViewport");

				source =
					"class IProperties\n"
					"{\n"
					"	func extern HasProperty(string name, PropertyType& type): bool;\n"
					"	func extern SetBool(string name, bool value);\n"
					"	func extern GetBool(string name): bool;\n"
					"	func extern SetInt(string name, int value);\n"
					"	func extern GetInt(string name):int;\n"
					"	func extern SetFloat(string name, float value);\n"
					"	func extern GetFloat(string name):float;\n"
					"	func extern SetString(string name, string value);\n"
					"	func extern GetString(string name):string;\n"
					"	func extern SetVec2(string name, vec2 value);\n"
					"	func extern GetVec2(string name):vec2;\n"
					/*"	func extern Setvec3(string name, vec3 value);\n"
					"	func extern Getvec3(string name):vec3;\n"
					"	func extern SetVec4(string name, vec4 value);\n"
					"	func extern GetVec4(string name):vec4;\n"*/
					"	func extern SetTransformWithScale(string name, TTransformWithScale value);\n"
					"	func extern GetTransformWithScale(string name):TTransformWithScale;\n"
					"	func extern SetTransform(string name, TTransform value);\n"
					"	func extern GetTransform(string name):TTransform;\n"
					"	func extern SetRotation(string name, TRot value);\n"
					"	func extern GetRotation(string name):TRot;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IProperties", sizeof(void*), true, "WorldDef::IRuntimeProperties");

				source =
					"enum TKey\n"
					"{\n"
					"	Left,\n"
					"	Right,\n"
					"	Up,\n"
					"	Down,\n"
					"}\n";
				TScriptClassesRegistry::RegisterEnum(source, "TKey", "WorldDef::TKey");

				source =
					"enum PropertyType\n"
					"{\n"
					"	Bool,\n"
					"	Int,\n"
					"	Float,\n"
					"	String,\n"
					"	Vec2,\n"
					"	Vec3,\n"
					"	Vec4,\n"
					"	TransformWithScale,\n"
					"	Transform,\n"
					"	Rotation,\n"
					"}\n";
				TScriptClassesRegistry::RegisterEnum(source,"PropertyType", "WorldDef::RuntimePropertyType");

				source =
					"class ISceneDef\n"
					"{\n"
					"	func extern FindViewport(string name): IViewport;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ISceneDef", sizeof(void*), true, "WorldDef::IScene");

				source =
					"class IScene\n"
					"{\n"
					"	func extern GetSource(): ISceneDef;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IScene", sizeof(void*), true, "IScene");

				source =
					"enum TMouseButton\n"
					"{\n"
					"	Left,\n"
					"	Right,\n"
					"	Middle,\n"
					"}\n";
				TScriptClassesRegistry::RegisterEnum(source, "TMouseButton", "TMouseButton");

				source =
					"class IComposerStage\n"
					"{\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IComposerStage", sizeof(void*), true, "IComposerStage");
				
				source =
					"class IComposer\n"
					"{\n"
					"	func extern AddToRender(IScene scene, IViewport viewport);\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IComposer", sizeof(void*), true, "IComposer");

				source =
					"class IWorldDef\n"
					"{\n"
					"	func extern GetScene(string name):ISceneDef;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IWorldDef", sizeof(void*), true, "WorldDef::IWorld");

				source =
					"class IWorld\n"
					"{\n"
					"	func extern GetScene(int index):IScene;\n"
					"	func extern RunScene(ISceneDef scene):IScene;\n"
					"	func extern GetSource():IWorldDef;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IWorld", sizeof(void*), true, "IWorld");
				
				source =
					"class IDirector\n"
					"{\n"
					"	func extern GetWorld():IWorld;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IDirector", sizeof(void*), true, "IDirector");

				

				source =
					"class IPhysShapeDef\n"
					"{\n"
					"	func extern SetIsSensor(bool is_sensor);\n"
					"	func extern GetIsSensor():bool;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IPhysShapeDef", sizeof(void*), true, "WorldDef::IPhysShape");

				source =
					"class IPhysShape\n"
					"{\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IPhysShape", sizeof(void*), true, "IPhysShapeInstance");
				
				source =
					"class ISpritePolygonDef\n"
					"{\n"
					"	func extern SetScale(vec2 scale);\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ISpritePolygonDef", sizeof(void*), true, "WorldDef::ISpritePolygon");

				source =
					"class ISpriteDef\n"
					"{\n"
					"	func extern SetPhysShape(IPhysShapeDef shape);\n"
					"	func extern GetPhysShape():IPhysShapeDef;\n"
					"	func extern GetPolygon():ISpritePolygonDef;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ISpriteDef", sizeof(void*), true, "WorldDef::ISprite");

				source =
					"class ITransformedSpriteDef\n"
					"{\n"
					"	func extern GetSprite():ISpriteDef;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ITransformedSpriteDef", sizeof(void*), true, "WorldDef::ITransformedSprite");

				
				source =
					"class ISpritePolygon\n"
					"{\n"
					"	func extern SetActiveAnimation(string name);\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ISpritePolygon", sizeof(void*), true, "ISpritePolygonInstance");

				source =
					"class ITransformedSprite\n"
					"{\n"
					"	func extern GetSource():ITransformedSpriteDef;\n"
					"	func extern GetPhysShape():IPhysShape;\n"
					"	func extern GetScale():vec2;\n"
					"	func extern GetPolygon():ISpritePolygon;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ITransformedSprite", sizeof(void*), true, "ITransformedSpriteInstance");

				source =
					"class IInstance\n"
					"{\n"
					"	func extern SetScale(vec2 scale);\n"
					"	func extern GetProperties():IProperties;\n"
					"	func extern GetPhysBody():IClassPhysBody;\n"
					"	func extern GetSprite(int index):ITransformedSprite;\n"
					"	func extern GetSkeletonAnimation():ISkeletonAnimation;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IInstance", sizeof(void*), true, "ITransformedClassInstance");

				return true;
			}
			static bool Class_binded = BindClass();
		}
	}
}