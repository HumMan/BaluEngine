#pragma once

#include <vector>

class TCallbackManagedBridge;

namespace EngineInterface
{
	class IBaluWorldObject;
	class IBaluWorld;
	class IAbstractEditor;
}

namespace Editor
{
	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::Collections::Generic;

	using namespace EngineInterface;

	//public ref class TWolrdTreeNodeTag
	//{
	//public:
	//	IBaluWorldObject* world_object;
	//	TNodeType NodeType;
	//	bool IsSpecialNode;
	//	TWolrdTreeNodeTag(TNodeType NodeType)
	//	{
	//		IsSpecialNode = true;
	//		this->NodeType = NodeType;
	//	}
	//	TWolrdTreeNodeTag(TNodeType NodeType, IBaluWorldObject* world_object)
	//	{
	//		IsSpecialNode = false;
	//		this->NodeType = NodeType;
	//		this->world_object = world_object;
	//	}
	//};

	ref class TWorldDirector;

	class TWorldTreeEditorPrivate;

	public ref class TWorldTreeEditor
	{
	internal:
		TWorldTreeEditorPrivate* p;
		
		std::vector<std::string> GetObjectNames(int obj_type);
	public:

		TWorldTreeEditor(TWorldDirector^ world);

		void Deinitialize();

		int GetWorldObjectTypesCount();
		String^ GetObjectTypeName(int obj_type);

		int GetObjectsCount(int obj_type);
		String^ GetObjectName(int obj_type, int obj_index);
		void SetObjectName(int obj_type, int obj_index, String^ new_name);
		bool CanSetObjectName(int obj_type, int obj_index, String^ new_name);

		void CreateObject(int obj_type);
		void DestroyObject(int obj_type, int obj_index);
	};
}