#pragma once

#pragma once

namespace BaluEngine
{
	namespace WorldDef
	{
		enum class RuntimePropertyType
		{
			Bool,
			Int,
			Float,
			String,
			Vec2,
			Vec3,
			Vec4,
			TransformWithScale,
			Transform,
			Rotation,
		};

		

		class IRuntimeProperties : public ISerializable
		{
		public:
			virtual bool HasProperty(const std::string& name, RuntimePropertyType& type) = 0;

			virtual void SetBool(const std::string& name, const bool& value) = 0;
			virtual bool GetBool(const std::string& name) = 0;
			virtual void SetInt(const std::string& name, const int& value) = 0;
			virtual int GetInt(const std::string& name) = 0;
			virtual void SetFloat(const std::string& name, const float& value) = 0;
			virtual float GetFloat(const std::string& name) = 0;
			virtual void SetString(const std::string& name, const std::string& value) = 0;
			virtual std::string GetString(const std::string& name) = 0;
			virtual void SetVec2(const std::string& name, const BaluLib::TVec2& value) = 0;
			virtual BaluLib::TVec2 GetVec2(const std::string& name) = 0;
			virtual void SetVec3(const std::string& name, const BaluLib::TVec3& value) = 0;
			virtual BaluLib::TVec3 GetVec3(const std::string& name) = 0;
			virtual void SetVec4(const std::string& name, const BaluLib::TVec4& value) = 0;
			virtual BaluLib::TVec4 GetVec4(const std::string& name) = 0;
			virtual void SetTransformWithScale(const std::string& name, const TTransformWithScale& value) = 0;
			virtual TTransformWithScale GetTransformWithScale(const std::string& name) = 0;
			virtual void SetTransform(const std::string& name, const TTransform& value) = 0;
			virtual TTransform GetTransform(const std::string& name) = 0;
			virtual void SetRotation(const std::string& name, const TRot& value) = 0;
			virtual TRot GetRotation(const std::string& name) = 0;
			virtual ~IRuntimeProperties() {};
		};
	}
}