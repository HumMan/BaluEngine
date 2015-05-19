#pragma once

#include <vector>

class TWorldDirectorPrivate;

namespace Editor
{
	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::Windows::Forms;
	using namespace System::ComponentModel;
	using namespace System::Threading;
	using namespace System::Collections::Generic;

	ref class TEventsEditor;
	ref class TWorldTreeEditor;

	public ref class TWorldDirector
	{
	private:
		TWorldDirectorPrivate* p;
	public:
		String^ GetAssetsDir();

		TEventsEditor^ GetEventsEditor();
		TWorldTreeEditor^ GetTreeEditor();

		void SaveWorldTo(String^ path);
		void LoadWorldFrom(String^ path);
		void LoadDemoWorld();
	};
}
