
#include <vcclr.h>

#include "BaluEditorControlDesigner.h"
#include "BaluEditorControl.h"
#include "Source/PropertiesRegistry/propertiesRegistry.h"
#include <box2d.h>
#include <baluRender.h>
#include <baluEngine.h>
#include <baluScript.h>
#include "../Source/scriptClasses.h"

#include <msclr\marshal_cppstd.h>

HDC hDC;
HWND hWnd;

TTime time;

char buf[1000];

//TBaluEngine* engine;
TBaluEditor* engine;
char buf1[1000];
int curr_buf1;


//
//void InitEngine()
//{
//	curr_buf1 = 0;
//	{
//		engine->AddMaterial("mat1", "textures\\Crate005_ebox.png", TVec4(Randf(), Randf(), Randf(), 1));
//		engine->AddMaterial("mat2", "textures\\container_001a.png", TVec4(Randf(), Randf(), Randf(), 1));
//		TBaluShape shape;
//		float density = 0.01;
//		float rad = 0.3;
//		//shape.SetAsCircle(rad,density);
//		float k = 0.35;
//		shape.SetAsBox(TVec2(1 * k, 1 * k), density);
//		engine->AddShape("shape1", shape);
//		density = 0;
//		shape.SetAsBox(TVec2(65 * k, 2 * k), density);
//		engine->AddShape("shape2", shape);
//
//		engine->AddSprite("sprite1", "shape1", "mat1", TVec2(1, 1), 0, TVec2(0, 0), -1);
//		engine->AddSprite("sprite2", "shape2", "mat2", TVec2(65, 2), 0, TVec2(0, 0), -1);
//
//		TBaluClass o;
//		o.SetMembers("float t;");
//		//o.SetEvent(EVENT_CREATE,
//		//	"\n t=0;//t=Randf();vec2 tttt=Cross(vec2(0,1),vec2(1,1));\
//				//	//sprite.shape.SetAsBox(vec2(0.3,0.3),0.01);");
//		//o.SetEvent(EVENT_STEP,
//		//	"\n vec2 v=Normalize(Mouse.WorldPos-pos);\
//				//	\n //sprite.local_angle=Sign(v[1])*Acos(v[0])+t;\
//				//	\n if(Mouse.Button.Left){t-=0.2;}if(Mouse.Button.Right){t+=0.2;}");
//		//o.SetEvent(EVENT_GLOBALMOUSEDOWN,
//		//	"\n if(button==TMouseButton.Middle)t+=0.2;");
//		//o.SetEvent(EVENT_KEYUP,
//		//	"\n");
//		//o.SetEvent(EVENT_KEYDOWN,
//		//	"\n");
//
//		TBaluClass o1;
//		o1.SetMembers("float arr;");
//		//o1.SetMembers("int[][10] arr;");
//		o1.SetEvent(TBaluEvent::EVENT_STEP,
//			"sprite.local_angle+=Time.Step;\n");
//
//		TBaluClass mouse_contrl;
//		mouse_contrl.SetMembers("float arr;");
//		//mouse_contrl.SetEvent(EVENT_STEP,
//		//	"\n float ox=0,oy=0,coeff=1.0;\
//				//	\n if(Keyboard.Pressed('A'))ox=-1;\
//				//	\n if(Keyboard.Pressed('D'))ox=1;\
//				//	\n if(Keyboard.Pressed('S'))oy=-1;\
//				//	\n if(Keyboard.Pressed('W'))oy=1;\
//				//	\n if(Keyboard.Pressed(TVirtKey.LShift))coeff=5.0;\
//				//	\n Screen.SetPos(Screen.Pos+vec2(ox,oy)*Screen.Size[0]*0.01*coeff);");
//
//
//		//mouse_contrl.SetEvent(EVENT_GLOBALMOUSEWHEEL,
//		//	"Screen.SetSize(Screen.Size*(1.0+0.1*delta));");
//
//		engine->AddClass("Obj2", "sprite2", o1);
//		engine->AddClass("Obj1", "sprite1", o);
//		engine->AddClass("MouseContrl", "sprite1", mouse_contrl);
//		////
//		engine->AddInstance("MouseContrl", TVec2(0, -10), 0);
//		engine->AddInstance("Obj2", TVec2(0, -0.6), 0);
//		engine->AddInstance("Obj2", TVec2(6, -1), 45 * M_PI / 180);
//		engine->AddInstance("Obj2", TVec2(-6, -0.8), -45 * M_PI / 180);
//		for (int i = 5; i <= 10; i++)
//			for (int k = -8; k <= 8; k++)
//			{
//			engine->AddInstance("Obj1", TVec2(k * 1 + i*0.2, i * 4), 0);
//			}
//	}
//	//UpdateControls();
//	engine->Start();
//}
//
static DWORD last_tick_count;
//
//void UpdateControls()
//{
//	unsigned char key_states[256];
//	GetKeyboardState(&key_states[0]);
//	engine->UpdateKeyStates(&key_states[0]);
//	TVec2i v = GetCursorPos();
//	POINT local_corner;
//	local_corner.x = 0;
//	local_corner.y = 0;
//	if (!ClientToScreen(hWnd, &local_corner))
//	{
//		int i = GetLastError();
//		sprintf_s(buf1, "%i\nWindow handle: %i", i, hWnd);
//		//MessageBox(0,buf1,L"Error",MB_OK);
//	}
//	v[0] -= local_corner.x;
//	v[1] -= local_corner.y;
//	engine->UpdateMouseState(KeyDown(VK_LBUTTON), KeyDown(VK_MBUTTON), KeyDown(VK_RBUTTON), v);
//}

class TCallbackManagedBridge
{
	gcroot<Editor::BaluEditorControl^> managed_object;
public:
	TCallbackManagedBridge(Editor::BaluEditorControl^ use_obj){ managed_object = use_obj; }
	static void OnSelectionChanged(void* calle, TWorldObjectDef* old_selection, TWorldObjectDef* new_selection)
	{
		((TCallbackManagedBridge*)calle)->managed_object->OnSelectionChangedByEditor(old_selection, new_selection);
	}
	static void OnPropertiesChanged(void* calle, TWorldObjectDef* changed_obj)
	{
		((TCallbackManagedBridge*)calle)->managed_object->OnPropertiesChangedByEditor(changed_obj);
	}
	static void OnObjectCreated(void* calle, TWorldObjectDef* new_object)
	{
		((TCallbackManagedBridge*)calle)->managed_object->OnObjectCreatedByEditor(new_object);
	}
};


namespace Editor
{
	ref class TEditorToolEvent
	{
		TEditorTool* tool;
		TBaluEditor* engine;
		BaluEditorControl^ editor_control;
	public:
		TEditorToolEvent(TEditorTool* tool, TBaluEditor* engine, BaluEditorControl^ editor_control)
		{
			this->tool = tool;
			this->engine = engine;
			this->editor_control = editor_control;
		}
		void OnClick(Object ^ sender, EventArgs ^ e)
		{
			engine->SetActiveTool(tool);
			auto obj_sel = tool->NeedObjectSelect();
			if (obj_sel != TWorldObjectType::None)
			{
				editor_control->ToolObjectSelect->Enabled = true;
				editor_control->ToolObjectSelect->Items->Clear();
				std::vector<TWorldObjectDef*> selection_list;
				engine->ToolNeedObjectSelect(selection_list);
				for (auto v : selection_list)
					editor_control->ToolObjectSelect->Items->Add(gcnew String(v->GetName().c_str()));
			}
			else
			{
				editor_control->ToolObjectSelect->Enabled = false;
				editor_control->ToolObjectSelect->Items->Clear();
			}
		}
	};

	ref class TUtils
	{
	public:
		static void CreateEditorToolsToolBar(ToolStrip^ tool_strip, const std::vector<TToolWithDescription>& tools, TBaluEditor* engine, BaluEditorControl^ editor_control)
		{
			tool_strip->Items->Clear();
			for (const TToolWithDescription& tool : tools)
			{
				auto handler = gcnew TEditorToolEvent(tool.tool.get(), engine, editor_control);
				ToolStripItem^ i = gcnew ToolStripButton(gcnew String(tool.name.c_str()));
				i->Click += gcnew EventHandler(handler, &TEditorToolEvent::OnClick);
				tool_strip->Items->Add(i);
			}
		}
	};

	void BaluEditorControl::OnSelectionChangedByEditor(TWorldObjectDef* old_selection, TWorldObjectDef* new_selection)
	{
		TPropertiesObject^ obj = TPropertiesRegistry::CreateProperties(engine->GetWorld(), new_selection);
		SelectedObjectProperty->SelectedObject = obj;
	}
	
	void BaluEditorControl::OnPropertiesChangedByEditor(TWorldObjectDef* changed_obj)
	{
	}

	void BaluEditorControl::OnObjectCreatedByEditor(TWorldObjectDef* new_object)
	{
		WorldTreeView->Nodes->Clear();
		CreateWorldTree(WorldTreeView, engine->GetWorld());
	}

	void BaluEditorControl::InitializeEngine()
	{
		CreateWorldTree(WorldTreeView, engine->GetWorld());
	}

	Void BaluEditorControl::CreateMaterial()
	{
		engine->CreateMaterial();
	}
	Void BaluEditorControl::CreateSprite()
	{
		engine->CreateSprite();
	}
	Void BaluEditorControl::CreatePhysBody()
	{
		engine->CreatePhysBody();
	}
	Void BaluEditorControl::CreateClass()
	{
		engine->CreateClass();
	}
	Void BaluEditorControl::CreateScene()
	{
		engine->CreateScene();
	}

	Void BaluEditorControl::SetSelectedWorldNode(TWolrdTreeNodeTag^ node)
	{
		TPropertiesObject^ obj = TPropertiesRegistry::CreateProperties(engine->GetWorld(), node->world_object);
		SelectedObjectProperty->SelectedObject = obj;
	}

	Void BaluEditorControl::SetEditedWorldNode(TWolrdTreeNodeTag^ node)
	{
		engine->Edit(node->world_object);
		auto &tools = engine->GetAvailableTools();
		TUtils::CreateEditorToolsToolBar(EditorToolsBar, tools,engine, this);
	}

	bool BaluEditorControl::CanSetSelectedAsWork()
	{
		return engine->CanSetSelectedAsWork();
	}
	void BaluEditorControl::SetSelectedAsWork()
	{
		engine->SetSelectedAsWork();
		auto &tools = engine->GetAvailableTools();
		TUtils::CreateEditorToolsToolBar(EditorToolsBar, tools, engine, this);
	}

	bool BaluEditorControl::CanEndSelectedAsWork()
	{
		return engine->CanEndSelectedAsWork();
	}
	void BaluEditorControl::EndSelectedAsWork()
	{
		engine->EndSelectedAsWork();
	}

	void BaluEditorControl::SetToolSelectedObject(String^ name)
	{
		engine->SetToolSelectedObject(msclr::interop::marshal_as<std::string>(name));
	}

	void BaluEditorControl::SaveWorldTo(String^ path)
	{
		engine->SaveWorldTo(msclr::interop::marshal_as<std::string>(path));
	}
	
	void BaluEditorControl::LoadWorldFrom(String^ path)
	{
		WorldTreeView->Nodes->Clear();
		engine->LoadWorldFrom(msclr::interop::marshal_as<std::string>(path));
		CreateWorldTree(WorldTreeView, engine->GetWorld());
	}

	void BaluEditorControl::CreateWorldTree(TreeView^ WorldTreeView, TBaluWorldDef* world)
	{
		auto world_node = gcnew TreeNode("World");
		world_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::World);
		WorldTreeView->Nodes->Add(world_node);
		{
			auto Materialst_node = gcnew TreeNode("Materials");
			Materialst_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material);
			world_node->Nodes->Add(Materialst_node);
			for (auto i = world->materials.begin(); i != world->materials.end(); i++)
			{
				auto new_sprite_node = gcnew TreeNode(gcnew String(i->first.c_str()));
				new_sprite_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material, &i->second);
				Materialst_node->Nodes->Add(new_sprite_node);
			}
		}
		{
			auto Sprites_node = gcnew TreeNode("Sprites");
			Sprites_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material);
			world_node->Nodes->Add(Sprites_node);
			for (auto i = world->sprites.begin(); i != world->sprites.end(); i++)
			{
				auto new_sprite_node = gcnew TreeNode(gcnew String(i->first.c_str()));
				new_sprite_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Sprite,&i->second);
				Sprites_node->Nodes->Add(new_sprite_node);
			}
		}
		{
			auto PhysBodies_node = gcnew TreeNode("PhysBodies");
			PhysBodies_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material);
			world_node->Nodes->Add(PhysBodies_node);
			for (auto i = world->phys_bodies.begin(); i != world->phys_bodies.end(); i++)
			{
				auto new_physbody_node = gcnew TreeNode(gcnew String(i->first.c_str()));
				new_physbody_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::PhysBody, &i->second);
				PhysBodies_node->Nodes->Add(new_physbody_node);
			}
		}
		{
			auto Classes_node = gcnew TreeNode("Classes");
			Classes_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material);
			world_node->Nodes->Add(Classes_node);
			for (auto i = world->classes.begin(); i != world->classes.end(); i++)
			{
				auto new_class_node = gcnew TreeNode(gcnew String(i->first.c_str()));
				new_class_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::PhysBody, &i->second);
				Classes_node->Nodes->Add(new_class_node);
			}
		}
		{
			auto Scenes_node = gcnew TreeNode("Scenes");
			Scenes_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material);
			world_node->Nodes->Add(Scenes_node);
			for (auto i = world->scenes.begin(); i != world->scenes.end(); i++)
			{
				auto new_scene_node = gcnew TreeNode(gcnew String(i->first.c_str()));
				new_scene_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::PhysBody, &i->second);
				Scenes_node->Nodes->Add(new_scene_node);
			}
		}
	}

	void BaluEditorControl::Render()
	{
		if (DesignMode)
			return;
		//time.Tick();
		//if(time.ShowFPS())
		//{
		//	sprintf(&buf[0],"%7.1f FPS",time.GetFPS());
		//	SetWindowText(hWnd,&buf[0]);
		//}
		if (GetTickCount() - last_tick_count<14)
		{
			Sleep(5);
			return;
		}
		float step_time = (GetTickCount() - last_tick_count) / 1000.0f;
		last_tick_count = GetTickCount();
		{
			//UpdateControls();
			//engine->Step(step_time, GetTickCount() / 1000.0f);
			engine->Render();
		}
	}

	Void BaluEditorControl::OnResize(EventArgs^ e)
	{
		if (DesignMode)
			return;
		__super::OnResize(e);
		engine->SetViewport(TVec2i(this->Width, this->Height));
	}

	BaluEditorControl::BaluEditorControl()
	{
		if (System::ComponentModel::LicenseManager::UsageMode == System::ComponentModel::LicenseUsageMode::Designtime)
		{
			DesignMode = true;
			return;
		}
		else
		{

			callbackbridge = new TCallbackManagedBridge(this);

			Activated = true;
			DesignMode = false;
			hWnd = static_cast<HWND>(this->Handle.ToPointer());
			RECT rect;
			GetClientRect(hWnd, &rect);

			engine = new TBaluEditor(*(int*)&hWnd, TVec2i(rect.right - rect.left, rect.bottom - rect.top));

			engine->AddSelectionChangedCallback(callbackbridge, TCallbackManagedBridge::OnSelectionChanged);
			engine->AddPropertiesChangedCallback(callbackbridge, TCallbackManagedBridge::OnPropertiesChanged);
			engine->AddObjectCreatedCallback(callbackbridge, TCallbackManagedBridge::OnObjectCreated);

			last_tick_count = GetTickCount();

			time.Start();
		}
	}
	BaluEditorControl::~BaluEditorControl()
	{
		delete callbackbridge;
	}

	Void BaluEditorControl::OnPaint(PaintEventArgs^ e)
	{
		if (DesignMode || !Activated)
		{
			__super::OnPaint(e);
			return;
		}
	}

	Void BaluEditorControl::OnPaintBackground(PaintEventArgs^ e)
	{
		if (DesignMode || !Activated)
			__super::OnPaintBackground(e);
	}

	Void BaluEditorControl::OnKeyDown(KeyEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;
	}

	Void BaluEditorControl::OnKeyPress(KeyPressEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;
	}

	Void BaluEditorControl::OnKeyUp(KeyEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;
	}

	Void BaluEditorControl::OnMouseClick(MouseEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;
	}

	Void BaluEditorControl::OnMouseDoubleClick(MouseEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;
	}

	TMouseEventArgs Convert(MouseEventArgs^ e)
	{
		TMouseEventArgs result;
		switch (e->Button)
		{
		case MouseButtons::Left:
			result.button = TMouseButton::Left; break;
		case MouseButtons::Middle:
			result.button = TMouseButton::Middle; break;
		case MouseButtons::Right:
			result.button = TMouseButton::Right; break;
		}
		result.location[0] = e->X;
		result.location[1] = e->Y;
		return result;
	}

	Void BaluEditorControl::OnMouseDown(MouseEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;
		engine->OnMouseDown(Convert(e));
	}

	//Void BaluEditorControl::OnMouseEnter(EventArgs^ e)
	//{
	//	if (!Activated || DesignMode)
	//		return;
	//}

	Void BaluEditorControl::OnMouseHover(EventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;
	}

	Void BaluEditorControl::OnMouseLeave(EventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;
	}

	Void BaluEditorControl::OnMouseMove(MouseEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;
		engine->OnMouseMove(Convert(e));
	}

	Void BaluEditorControl::OnMouseUp(MouseEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;
		engine->OnMouseUp(Convert(e));
	}

	Void BaluEditorControl::OnMouseWheel(MouseEventArgs^ e)
	{
		if (!Activated || DesignMode)
			return;
		engine->OnMouseWheel(e->Delta);
	}

	Void BaluEditorControl::OnLoad(EventArgs^ e)
	{
	}

	Void BaluEditorControl::WndProc(Message% m)
	{
		switch (m.Msg)
		{
		case WM_PAINT:
			OnPaint(gcnew PaintEventArgs(Graphics::FromHwnd(Handle), ClientRectangle));
			break;

		case WM_ERASEBKGND:
			OnPaintBackground(gcnew PaintEventArgs(Graphics::FromHwnd(Handle), ClientRectangle));
			break;
		}

		__super::WndProc(m);
	}
}