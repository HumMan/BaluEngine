#pragma once


namespace BaluEngine
{
	namespace WorldDef
	{

		enum class PropertyType
		{
			Bool,
			Int,
			Float,
			String,
			Color,
			ColorWithAlpha,
			TransparentMode,
			AlphaTestFunc,
			BlendFunc,
			BlendEquation,
			TexFilter,
			TexClamp,
			Size,
			TransformWithScale,
			Transform,
			Scale,
			Pos,
			Rotation,
			Material,
			PhysShapeType,
			Layer,
			Properties,
		};

		class IProperties: public ISerializable
		{
		public:
			virtual bool HasProperty(const std::string& name, PropertyType& type) = 0;
			virtual void SetBool(const std::string& name, bool value) = 0;
			virtual bool GetBool(const std::string& name) = 0;
		};
	}
}
