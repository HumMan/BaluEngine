BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, TFrame, "TFrame");
MUnpackConstrA2(WrapInterface<TFrame>, Constr, WrapValue<TVec2>, WrapValue<TVec2>);
MUnpackRA0(WrapValue<TVec2>, WrapInterface<TFrame>, GetLeftBottom);
MUnpackRA0(WrapValue<TVec2>, WrapInterface<TFrame>, GetRightTop);
BALU_ENGINE_SCRIPT_END_CLASS;

void TKey_register(TClassRegistryParams& params)
{
	auto scl = RegisterEnum(params,
		"enum TKey\n"
		"{\n"
		"	Left,\n"
		"	Right,\n"
		"	Up,\n"
		"	Down,\n"
		"}\n");
}
static bool TKey_registered = TScriptClassesRegistry::RegisterEnum("TKey", TKey_register);

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluClassPhysBodyIntance, "IClassPhysBodyInstance");
MUnpackRA0(WrapValue<TVec2>, TYPE, GetLinearVelocity);
MUnpackA1(TYPE, SetLinearVelocity, WrapValue<TVec2>);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, ISkeletonAnimationInstance, "ISkeletonAnimationInstance");
MUnpackA2(TYPE, PlayAnimation, TStringWrapper<std::string>, WrapValue<float>);
MUnpackA1(TYPE, StopAnimation, TStringWrapper<std::string>);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluInstance, "IInstance");
MUnpackA1(TYPE, SetScale, WrapValue<TVec2>);
MUnpackRA0(WrapPointer<IProperties>, TYPE, GetProperties);
MUnpackRA0(WrapPointer<IBaluClassPhysBodyIntance>, TYPE, GetPhysBody);
MUnpackRA1(WrapPointer<IBaluClassInstanceSpriteInstance>, TYPE, GetSprite, WrapValue<int>);
MUnpackRA0(WrapPointer<ISkeletonAnimationInstance>, TYPE, GetSkeletonAnimation);
BALU_ENGINE_SCRIPT_END_CLASS;