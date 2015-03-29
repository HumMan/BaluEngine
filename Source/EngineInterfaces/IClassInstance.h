#pragma once

#include "IClass.h"

#include "ISpriteInstance.h"

namespace EngineInterface
{
	class ISensorInstance
	{

	};

	class IBaluClassPhysBodyIntance
	{
	public:
		virtual TVec2 GetLinearVelocity() = 0;
		virtual void SetLinearVelocity(TVec2 velocity) = 0;
	};


#ifdef BALU_ENGINE_SCRIPT_CLASSES

	void IBaluClassPhysBodyIntance_GetLinearVelocity(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		*result.get_as<TVec2>()=(*object.get_as<IBaluClassPhysBodyIntance*>())->GetLinearVelocity();
	}

	void IBaluClassPhysBodyIntance_SetLinearVelocity(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		(*object.get_as<IBaluClassPhysBodyIntance*>())->SetLinearVelocity(
			*formal_params[0].get_as<TVec2>()
			);
	}

	void IBaluClassPhysBodyIntance_register(TClassRegistryParams& params)
	{
		auto scl = RegisterExternClass(params,
			"class extern IPhysBodyInstance\n"
			"{\n"
			"func GetLinearVelocity:vec2;\n"
			"func SetLinearVelocity(vec2 velocity);\n"
			"}\n",
			sizeof(IBaluClassPhysBodyIntance*));
		RegisterMethod(params, scl, "GetLinearVelocity", IBaluClassPhysBodyIntance_GetLinearVelocity);
		RegisterMethod(params, scl, "SetLinearVelocity", IBaluClassPhysBodyIntance_SetLinearVelocity);
	}
	static bool IBaluClassPhysBodyIntance_registered = TScriptClassesRegistry::Register("IPhysBodyInstance", IBaluClassPhysBodyIntance_register);
#endif

	class ISkeletonAnimationInstance
	{
	public:
		virtual void Update(float step) = 0;
		virtual void PlayAnimation(std::string name, float alpha) = 0;
		virtual void StopAnimation(std::string name) = 0;
	};

	class IBaluInstance
	{
	public:
		virtual void UpdateTranform() = 0;
		virtual TOBB2 GetOBB()=0;
		virtual IBaluClass* GetClass()=0;
		virtual TBaluTransform GetTransform()=0;
		virtual void SetTransform(TBaluTransform) = 0;
		virtual TVec2 GetScale() = 0;
		virtual void SetScale(TVec2 scale) = 0;
		virtual int GetSpritesCount() = 0;
		virtual IBaluSpriteInstance* GetSprite(int index) = 0;
		virtual IProperties* GetProperties() = 0;
		virtual IBaluClassPhysBodyIntance* GetPhysBody() = 0;
		virtual ISkeletonAnimationInstance* GetSkeletonAnimation() = 0;
	};

#ifdef BALU_ENGINE_SCRIPT_CLASSES

	void IBaluInstance_GetProperties(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		*result.get_as<IProperties*>() = (*object.get_as<IBaluInstance*>())->GetProperties();
	}

	void IBaluInstance_GetPhysBody(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		*result.get_as<IBaluClassPhysBodyIntance*>() = (*object.get_as<IBaluInstance*>())->GetPhysBody();
	}

	void IBaluInstance_register(TClassRegistryParams& params)
	{
		auto scl = RegisterExternClass(params,
			"class extern IClassInstance\n"
			"{\n"
			"func GetProperties:IProperties;\n"
			"func GetPhysBody:IPhysBodyInstance;\n"
			"}\n",
			sizeof(IBaluClassPhysBodyIntance*));
		RegisterMethod(params, scl, "GetProperties", IBaluInstance_GetProperties);
		RegisterMethod(params, scl, "GetPhysBody", IBaluInstance_GetPhysBody);
	}
	static bool IBaluInstance_registered = TScriptClassesRegistry::Register("IClassInstance", IBaluInstance_register);
#endif
}