BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluPhysShape, "IPhysShape");
MUnpackA1(TYPE, SetIsSensor, WrapValue<bool>);
MUnpackRA0(WrapValue<bool>, TYPE, IsSensor);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluPhysShapeInstance, "IPhysShapeInstance");
MUnpackRA0(WrapPointer<IBaluInstance>, TYPE, GetParent);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluSprite, "ISprite");
MUnpackA1(TYPE, SetPhysShape, WrapInterface<IBaluPhysShape>);
MUnpackRA0(WrapPointer<IBaluPhysShape>, TYPE, GetPhysShape);
MUnpackRA0(WrapPointer<IBaluSpritePolygon>, TYPE, GetPolygon);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluClassSpriteInstance, "IClassSpriteInstance");
MUnpackRA0(WrapPointer<IBaluSprite>, TYPE, GetSprite);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluClassInstanceSpriteInstance, "IClassInstanceSpriteInstance");
MUnpackRA0(WrapPointer<IBaluClassSpriteInstance>, TYPE, GetSource);
MUnpackRA0(WrapPointer<IBaluPhysShapeInstance>, TYPE, GetPhysShape);
MUnpackRA0(WrapValue<TVec2>, TYPE, GetScale);
MUnpackRA0(WrapPointer<IBaluSpritePolygonInstance>, TYPE, GetPolygon);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluSpritePolygon, "ISpritePolygon");
MUnpackA1(TYPE, SetScale, WrapValue<TVec2>);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluSpritePolygonInstance, "ISpritePolygonInstance");
MUnpackA1(TYPE, SetActiveAnimation, TString);
BALU_ENGINE_SCRIPT_END_CLASS;