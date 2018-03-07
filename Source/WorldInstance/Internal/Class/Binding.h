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
					"class extern IClassPhysBody\n"
					"{\n"
					"	func GetLinearVelocity():vec2;\n"
					"	func SetLinearVelocity(vec2 value);\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IClassPhysBody", sizeof(void*), true, "IClassPhysBodyIntance");

				source =
					"class extern ISkeletonAnimation\n"
					"{\n"
					"	func PlayAnimation(string name, float pos);\n"
					"	func StopAnimation(string name);\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ISkeletonAnimation", sizeof(void*), true, "ISkeletonAnimationInstance");

				source =
					"class extern TMouseEventArgs\n"
					"{\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "TMouseEventArgs", sizeof(void*), true, "WorldDef::TMouseEventArgs");

				source =
					"class extern TRot\n"
					"{\n"
					"	func Set(float value);\n"
					"	func SetIdentity();\n"
					"	func GetAngle():float;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "TRot", sizeof(WorldDef::TRot), false, "WorldDef::TRot");

				source =
					"class extern TTransform\n"
					"{\n"
					"	func Transform(vec2 vertex, vec2 scale): vec2;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "TTransform", sizeof(WorldDef::TTransform), false, "WorldDef::TTransform");

				source =
					"class extern TTransformWithScale\n"
					"{\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "TTransformWithScale", sizeof(WorldDef::TTransform), false, "WorldDef::TTransformWithScale");

				source =
					"class extern IViewport\n"
					"{\n"
					"	func SetSize(vec2 size);\n"
					"	func GetSize(): vec2;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IViewport", sizeof(void*), true, "WorldDef::IViewport");

				source =
					"class extern IProperties\n"
					"{\n"
					"	func HasProperty(string name, PropertyType& type): bool;\n"
					"	func SetBool(string name, bool value);\n"
					"	func GetBool(string name): bool;\n"
					"	func SetInt(string name, int value);\n"
					"	func GetInt(string name):int;\n"
					"	func SetFloat(string name, float value);\n"
					"	func GetFloat(string name):float;\n"
					"	func SetString(string name, string value);\n"
					"	func GetString(string name):string;\n"
					"	func SetVec2(string name, vec2 value);\n"
					"	func GetVec2(string name):vec2;\n"
					/*"	func Setvec3(string name, vec3 value);\n"
					"	func Getvec3(string name):vec3;\n"
					"	func SetVec4(string name, vec4 value);\n"
					"	func GetVec4(string name):vec4;\n"*/
					"	func SetTransformWithScale(string name, TTransformWithScale value);\n"
					"	func GetTransformWithScale(string name):TTransformWithScale;\n"
					"	func SetTransform(string name, TTransform value);\n"
					"	func GetTransform(string name):TTransform;\n"
					"	func SetRotation(string name, TRot value);\n"
					"	func GetRotation(string name):TRot;\n"
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
					"class extern ISceneDef\n"
					"{\n"
					"	func FindViewport(string name): IViewport;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ISceneDef", sizeof(void*), true, "WorldDef::IScene");

				source =
					"class extern IScene\n"
					"{\n"
					"	func GetSource(): ISceneDef;\n"
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
					"class extern IComposerStage\n"
					"{\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IComposerStage", sizeof(void*), true, "IComposerStage");
				
				source =
					"class extern IComposer\n"
					"{\n"
					"	func AddToRender(IScene scene, IViewport viewport);\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IComposer", sizeof(void*), true, "IComposer");

				source =
					"class extern IWorldDef\n"
					"{\n"
					"	func GetScene(string name):ISceneDef;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IWorldDef", sizeof(void*), true, "WorldDef::IWorld");

				source =
					"class extern IWorld\n"
					"{\n"
					"	func GetSceneInstance(int index):IScene;\n"
					"	func RunScene(ISceneDef scene):IScene;\n"
					"	func GetSource():IWorldDef;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IWorld", sizeof(void*), true, "IWorld");
				
				source =
					"class extern IDirector\n"
					"{\n"
					"	func GetWorldInstance():IWorld;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IDirector", sizeof(void*), true, "IDirector");

				

				source =
					"class extern IPhysShapeDef\n"
					"{\n"
					"	func SetIsSensor(bool is_sensor);\n"
					"	func GetIsSensor():bool;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IPhysShapeDef", sizeof(void*), true, "WorldDef::IPhysShape");

				source =
					"class extern IPhysShape\n"
					"{\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IPhysShape", sizeof(void*), true, "IPhysShapeInstance");
				
				source =
					"class extern ISpritePolygonDef\n"
					"{\n"
					"	func SetScale(vec2 scale);\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ISpritePolygonDef", sizeof(void*), true, "WorldDef::ISpritePolygon");

				source =
					"class extern ISpriteDef\n"
					"{\n"
					"	func SetPhysShape(IPhysShapeDef shape);\n"
					"	func GetPhysShape():IPhysShapeDef;\n"
					"	func GetPolygon():ISpritePolygonDef;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ISpriteDef", sizeof(void*), true, "WorldDef::ISprite");

				source =
					"class extern ITransformedSpriteDef\n"
					"{\n"
					"	func GetSprite():ISpriteDef;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ITransformedSpriteDef", sizeof(void*), true, "WorldDef::ITransformedSprite");

				
				source =
					"class extern ISpritePolygon\n"
					"{\n"
					"	func SetActiveAnimation(string name);\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ISpritePolygon", sizeof(void*), true, "ISpritePolygonInstance");

				source =
					"class extern ITransformedSprite\n"
					"{\n"
					"	func GetSource():ITransformedSpriteDef;\n"
					"	func GetPhysShape():IPhysShape;\n"
					"	func GetScale():vec2;\n"
					"	func GetPolygon():ISpritePolygon;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ITransformedSprite", sizeof(void*), true, "ITransformedSpriteInstance");

				source =
					"class extern IInstance\n"
					"{\n"
					"	func SetScale(vec2 scale);\n"
					"	func GetProperties():IProperties;\n"
					"	func GetPhysBody():IClassPhysBody;\n"
					"	func GetSprite(int index):ITransformedSprite;\n"
					"	func GetSkeletonAnimation():ISkeletonAnimation;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IInstance", sizeof(void*), true, "ITransformedClassInstance");

				return true;
			}
			static bool Class_binded = BindClass();
		}
	}
}