
DECL_SCRIPT_TYPE(PropertyType, "PropertyType");

void PropertyType_register(TClassRegistryParams& params)
{
	auto scl = RegisterEnum(params,
		"enum PropertyType\n"
		"{\n"
		"Bool,\n"
		"Int,\n"
		"Float,\n"
		"String,\n"
		"}\n"
		);
}
static bool PropertyType_registered = TScriptClassesRegistry::RegisterEnum("PropertyType", PropertyType_register);

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IProperties, "IProperties");
MUnpackRA2(WrapValue<bool>, WrapInterface<IProperties>, HasProperty, TStringWrapper<std::string _COMMA const std::string&>, WrapValue<PropertyType _COMMA PropertyType&>);
MUnpackRA1(WrapValue<bool>, WrapInterface<IProperties>, GetBool, TStringWrapper<std::string _COMMA const std::string&>);
MUnpackA2(WrapInterface<IProperties>, SetBool, TStringWrapper<std::string _COMMA const std::string&>, WrapValue<bool>);
BALU_ENGINE_SCRIPT_END_CLASS;

void TMouseButton_register(TClassRegistryParams& params)
{
	auto scl = RegisterEnum(params,
		"enum TMouseButton\n"
		"{\n"
		"	Left,\n"
		"	Right,\n"
		"	Middle,\n"
		"}\n");
}
static bool TMouseButton_registered = TScriptClassesRegistry::RegisterEnum("TMouseButton", TMouseButton_register);

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, TMouseEventArgs, "TMouseEventArgs");
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapValue, TRot, "TRot");
MUnpackA1(TYPE, Set, WrapValue<float>);
MUnpackA0(TYPE, SetIdentity);
MUnpackCRA0(WrapValue<float>, TYPE, GetAngle);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapValue, TBaluTransform, "TTransform");
MUnpackRA2(WrapValue<TVec2>, TYPE, Transform, WrapValue<TVec2>, WrapValue<TVec2>);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IViewport, "IViewport");
MUnpackA1(TYPE, SetSize, WrapValue<TVec2>);
MUnpackRA0(WrapValue<TVec2>, TYPE, GetSize);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluWorldObject, "TBaluWorldObject");
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IComposerStage, "IComposerStage");
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IComposer, "IComposer");
MUnpackRA2(WrapInterface<IComposerStage>, WrapInterface<IComposer>, AddToRender, WrapInterface<IBaluSceneInstance>, WrapInterface<IViewport>);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IDirector, "IDirector");
MUnpackRA0(WrapPointer<IBaluWorldInstance>, WrapInterface<IDirector>, GetWorldInstance);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluWorld, "IBaluWorld");
//MUnpackRA1(WrapPointer<IBaluScene>, WrapInterface<IBaluWorld>, GetScene, WrapValue<int>);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluWorldInstance, "IWorldInstance");
MUnpackRA1(WrapPointer<IBaluSceneInstance>, WrapInterface<IBaluWorldInstance>, GetSceneInstance, WrapValue<int>);
MUnpackRA1(WrapPointer<IBaluSceneInstance>, WrapInterface<IBaluWorldInstance>, RunScene, WrapInterface<IBaluScene>);
MUnpackRA0(WrapPointer<IBaluWorld>, WrapInterface<IBaluWorldInstance>, GetSource);
BALU_ENGINE_SCRIPT_END_CLASS;