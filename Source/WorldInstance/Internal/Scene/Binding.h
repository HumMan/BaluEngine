BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluScene, "IScene");
MUnpackRA1(WrapInterface<IViewport>, TYPE, FindViewport, WrapString);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluSceneInstance, "ISceneInstance");
MUnpackRA0(WrapInterface<IBaluScene>, TYPE, GetSource);
BALU_ENGINE_SCRIPT_END_CLASS;