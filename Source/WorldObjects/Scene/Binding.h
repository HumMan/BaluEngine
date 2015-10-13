BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluScene, "IScene");
MUnpackRA1(WrapPointer<IViewport>, TYPE, FindViewport, TString);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluSceneInstance, "ISceneInstance");
MUnpackRA0(WrapPointer<IBaluScene>, TYPE, GetSource);
BALU_ENGINE_SCRIPT_END_CLASS;