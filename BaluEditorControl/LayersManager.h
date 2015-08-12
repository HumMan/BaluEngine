#pragma once

#include <vector>

#include "WorldDirector.h"

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

	class TLayersManagerPrivate;



	public ref class TLayersManager : public TEditor
	{
	internal:
		void OnBeforeWorldLoad()override;
		void OnAfterWorldLoad()override;
		void OnEditedObjectChange(TEditor^ sender, int type, int index)override;
	private:
		TLayersManagerPrivate* p;
		TWorldDirector^ director;
	public:
		TLayersManager(TWorldDirector^ director);

		void Destroy() override;
	};
}