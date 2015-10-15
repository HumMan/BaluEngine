BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluPhysShape, "IPhysShape");
MUnpackA1(TYPE, SetIsSensor, WrapValue<bool>);
MUnpackRA0(WrapValue<bool>, TYPE, IsSensor);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluPhysShapeInstance, "IPhysShapeInstance");
MUnpackRA0(WrapInterface<IBaluTransformedClassInstance>, TYPE, GetParent);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluSprite, "ISprite");
MUnpackA1(TYPE, SetPhysShape, WrapInterface<IBaluPhysShape>);
MUnpackRA0(WrapInterface<IBaluPhysShape>, TYPE, GetPhysShape);
MUnpackRA0(WrapInterface<IBaluSpritePolygon>, TYPE, GetPolygon);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluTransformedSprite, "IClassSpriteInstance");
MUnpackRA0(WrapInterface<IBaluSprite>, TYPE, GetSprite);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluTransformedSpriteInstance, "IClassInstanceSpriteInstance");
MUnpackRA0(WrapInterface<IBaluTransformedSprite>, TYPE, GetSource);
MUnpackRA0(WrapInterface<IBaluPhysShapeInstance>, TYPE, GetPhysShape);
MUnpackRA0(WrapValue<TVec2>, TYPE, GetScale);
MUnpackRA0(WrapInterface<IBaluSpritePolygonInstance>, TYPE, GetPolygon);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluSpritePolygon, "ISpritePolygon");
MUnpackA1(TYPE, SetScale, WrapValue<TVec2>);
BALU_ENGINE_SCRIPT_END_CLASS;

BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluSpritePolygonInstance, "ISpritePolygonInstance");
MUnpackA1(TYPE, SetActiveAnimation, WrapString);
BALU_ENGINE_SCRIPT_END_CLASS;