#pragma once


#include "../../abstractEditor.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{
			class TSceneEditorScene;

			class TSceneEditorToolsRegistry
			{
			public:
				std::vector<TToolWithDescription> tools;
				TSceneEditorScene* scene;
			public:
				TSceneEditorToolsRegistry(TSceneEditorScene* scene);
				TSceneEditorToolsRegistry(TSceneEditorToolsRegistry&& o);
				const std::vector<TToolWithDescription>& GetTools();
				~TSceneEditorToolsRegistry();
			};

		}
	}
}