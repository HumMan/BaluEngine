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
				char* source;
				source =
					"class TFrame\n"
					"{\n"
					"	func extern GetLeftBottom():vec2;\n"
					"	func extern GetRightTop():vec2;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "TFrame", sizeof(WorldDef::TFrame), false, false, "WorldDef::TFrame");

				source =
					"class extern IClassPhysBody\n"
					"{\n"
					"	default();\n"
					"	copy(IClassPhysBody& copy_from);\n"
					"	destr();\n"
					"	operator static =(IClassPhysBody& v,IClassPhysBody& l);\n"

					"	func GetLinearVelocity():vec2;\n"
					"	func SetLinearVelocity(vec2 value);\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IClassPhysBody", sizeof(TScriptSharedPointer<IClassPhysBodyIntance>), false, true, "IClassPhysBodyIntance");

				source =
					"class extern ISkeletonAnimation\n"
					"{\n"
					"	default();\n"
					"	copy(ISkeletonAnimation& copy_from);\n"
					"	destr();\n"
					"	operator static =(ISkeletonAnimation& v,ISkeletonAnimation& l);\n"

					"	func PlayAnimation(string name, float pos);\n"
					"	func StopAnimation(string name);\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ISkeletonAnimation", sizeof(TScriptSharedPointer<ISkeletonAnimationInstance>), false, true, "ISkeletonAnimationInstance");

				source =
					"class TMouseEventArgs\n"
					"{\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "TMouseEventArgs", sizeof(WorldDef::TMouseEventArgs), false, false, "WorldDef::TMouseEventArgs");

				source =
					"class TRot\n"
					"{\n"
					"	func extern Set(float value);\n"
					"	func extern SetIdentity();\n"
					"	func extern GetAngle():float;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "TRot", sizeof(WorldDef::TRot), false, false, "WorldDef::TRot");

				source =
					"class TTransform\n"
					"{\n"
					"	func extern Transform(vec2 vertex, vec2 scale): vec2;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "TTransform", sizeof(WorldDef::TTransform), false, false, "WorldDef::TTransform");

				source =
					"class TTransformWithScale\n"
					"{\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "TTransformWithScale", sizeof(WorldDef::TTransform), false, false, "WorldDef::TTransformWithScale");

				source =
					"class IViewport\n"
					"{\n"
					"	func extern SetSize(vec2 size);\n"
					"	func extern GetSize(): vec2;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IViewport", sizeof(void*), true, false, "WorldDef::IViewport");

				source =
					"class extern IProperties\n"
					"{\n"
					"	default();\n"
					"	copy(IProperties& copy_from);\n"
					"	destr();\n"
					"	operator static =(IProperties& v,IProperties& l);\n"

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
				TScriptClassesRegistry::RegisterExternal(source, "IProperties", sizeof(TScriptSharedPointer<WorldDef::IRuntimeProperties>), false, true, "WorldDef::IRuntimeProperties");

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
				TScriptClassesRegistry::RegisterExternal(source, "ISceneDef", sizeof(void*), true, false, "WorldDef::IScene");

				source =
					"class extern IScene\n"
					"{\n"
					"	default();\n"
					"	copy(IScene& copy_from);\n"
					"	destr();\n"
					"	operator static =(IScene& v,IScene& l);\n"

					"	func GetSource(): ISceneDef;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IScene", sizeof(TScriptSharedPointer<IScene>), false, true, "IScene");

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
					"	default();\n"
					"	copy(IComposerStage& copy_from);\n"
					"	destr();\n"
					"	operator static =(IComposerStage& v,IComposerStage& l);\n"

					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IComposerStage", sizeof(TScriptSharedPointer<IComposerStage>), false, true, "IComposerStage");
				
				source =
					"class extern IComposer\n"
					"{\n"
					"	default();\n"
					"	copy(IComposer& copy_from);\n"
					"	destr();\n"
					"	operator static =(IComposer& v,IComposer& l);\n"

					"	func AddToRender(IScene scene, IViewport viewport);\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IComposer", sizeof(TScriptSharedPointer<IComposer>), false, true, "IComposer");

				source =
					"class IWorldDef\n"
					"{\n"
					"	func extern GetScene(string name):ISceneDef;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IWorldDef", sizeof(void*), true, false, "WorldDef::IWorld");

				source =
					"class extern IWorld\n"
					"{\n"
					"	default();\n"
					"	copy(IWorld& copy_from);\n"
					"	destr();\n"
					"	operator static =(IWorld& v,IWorld& l);\n"

					"	func GetScene(int index):IScene;\n"
					"	func RunScene(ISceneDef scene):IScene;\n"
					"	func GetSource():IWorldDef;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IWorld", sizeof(TScriptSharedPointer<IWorld>), false, true, "IWorld");
				
				source =
					"class extern IDirector\n"
					"{\n"
					"	default();\n"
					"	copy(IDirector& copy_from);\n"
					"	destr();\n"
					"	operator static =(IDirector& v,IDirector& l);\n"

					"	func GetWorld():IWorld;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IDirector", sizeof(TScriptSharedPointer<IDirector>), false, true, "IDirector");

				source =
					"class IPhysShapeDef\n"
					"{\n"
					"	func extern SetIsSensor(bool is_sensor);\n"
					"	func extern GetIsSensor():bool;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IPhysShapeDef", sizeof(void*), true, false, "WorldDef::IPhysShape");

				source =
					"class extern IPhysShape\n"
					"{\n"
					"	default();\n"
					"	copy(IPhysShape& copy_from);\n"
					"	destr();\n"
					"	operator static =(IPhysShape& v,IPhysShape& l);\n"

					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IPhysShape", sizeof(TScriptSharedPointer<IPhysShapeInstance>), false, true, "IPhysShapeInstance");
				
				source =
					"class ISpritePolygonDef\n"
					"{\n"
					"	func extern SetScale(vec2 scale);\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ISpritePolygonDef", sizeof(void*), true, false, "WorldDef::ISpritePolygon");

				source =
					"class ISpriteDef\n"
					"{\n"
					"	func extern SetPhysShape(IPhysShapeDef shape);\n"
					"	func extern GetPhysShape():IPhysShapeDef;\n"
					"	func extern GetPolygon():ISpritePolygonDef;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ISpriteDef", sizeof(void*), true, false, "WorldDef::ISprite");

				source =
					"class ITransformedSpriteDef\n"
					"{\n"
					"	func extern GetSprite():ISpriteDef;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ITransformedSpriteDef", sizeof(void*), true, false, "WorldDef::ITransformedSprite");

				
				source =
					"class extern ISpritePolygon\n"
					"{\n"
					"	default();\n"
					"	copy(ISpritePolygon& copy_from);\n"
					"	destr();\n"
					"	operator static =(ISpritePolygon& v,ISpritePolygon& l);\n"

					"	func SetActiveAnimation(string name);\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ISpritePolygon", sizeof(TScriptSharedPointer<ISpritePolygonInstance>), false, true, "ISpritePolygonInstance");

				source =
					"class extern ITransformedSprite\n"
					"{\n"
					"	default();\n"
					"	copy(ITransformedSprite& copy_from);\n"
					"	destr();\n"
					"	operator static =(ITransformedSprite& v,ITransformedSprite& l);\n"

					"	func GetSource():ITransformedSpriteDef;\n"
					"	func GetPhysShape():IPhysShape;\n"
					"	func GetScale():vec2;\n"
					"	func GetPolygon():ISpritePolygon;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "ITransformedSprite", sizeof(TScriptSharedPointer<ITransformedSpriteInstance>), false, true, "ITransformedSpriteInstance");

				source =
					"class extern IInstance\n"
					"{\n"
					"	default();\n"
					"	copy(IInstance& copy_from);\n"
					"	destr();\n"
					"	operator static =(IInstance& v,IInstance& l);\n"

					"	func SetScale(vec2 scale);\n"
					"	func GetProperties():IProperties;\n"
					"	func GetPhysBody():IClassPhysBody;\n"
					"	func GetSprite(int index):ITransformedSprite;\n"
					"	func GetSkeletonAnimation():ISkeletonAnimation;\n"
					"}\n"
					;
				TScriptClassesRegistry::RegisterExternal(source, "IInstance", sizeof(TScriptSharedPointer<ITransformedClassInstance>), false, true, "ITransformedClassInstance");

				return true;
			}
			static bool Class_binded = BindClass();
		}
	}
}