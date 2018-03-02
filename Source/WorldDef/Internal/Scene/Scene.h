#pragma once

#include "../../Interface.h"

#include "../Common/Common.h"

#include "../World/World.h"

#include "Layers.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{

			class TViewport : public IViewport
			{
				TTransform transform;
				float aspect; //��������� ������ � ������ (0.5 ������� �����)
				float width;
			public:
				TTransform GetTransform()
				{
					return transform;
				}

				void SetTransform(TTransform transform)
				{
					this->transform = transform;
				}
				void SetAspectRatio(float aspect)
				{
					this->aspect = aspect;
				}
				void SetWidth(float width)
				{
					this->width = width;
				}
				BaluLib::TAABB2 GetAABB()
				{
					BaluLib::TAABB2 aabb(BaluLib::TVec2(0, 0), BaluLib::TVec2(width, width * aspect)*0.5);

					return BaluLib::TOBB<float, 2>(transform.position, transform.GetOrientation(), aabb).GetAABB();
				}
				BaluLib::TVec2 GetSize()
				{
					return BaluLib::TVec2(width, width * aspect);
				}
				void SetSize(BaluLib::TVec2 size)
				{
					width = size[0];
					aspect = size[1] / size[0];
				}

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};

			class TScene : public IScene, public TWorldObject, public TChangeListenerArray
			{
			private:
				std::vector<std::unique_ptr<ISceneObject>> instances;

				std::map<std::string, TViewport> viewports;

				TLayersManager layers;

				TWorld* world;
			public:
				static TWorldObjectType GetWorldObjectType()
				{
					return TWorldObjectType::Scene;
				}
				TLayersManager* GetLayers()
				{
					return &layers;
				}
				TScene(const char* name, IWorld* world);

				TViewport* CreateViewport(const std::string& name);
				TViewport* FindViewport(const std::string& name);

				int GetInstancesCount();
				ISceneObject* GetInstance(int index);

				ISceneObject* CreateInstance(IClass* balu_class);

				void DestroyInstance(ISceneObject*);

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};

		}
	}
}
