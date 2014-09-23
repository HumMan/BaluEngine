#include "baluEditor.h"

#include "Editors\spriteEditor.h"

#include "Editors\abstractEditor.h"
//#include "Editors\BoundaryEditor.h"
#include "Editors\editorResourses.h"
#include "Editors\physBodyEditor.h"
#include "Editors\physBodyEditorTools.h"

#include <baluRender.h>

//enum class TCurrEditor
//{
//	SPRITE,
//	PHYS_SHAPE,
//	PHYS_BODY,
//	CLASS,
//	SCENE,
//
//	//testing only
//	BOUNDARY
//};

class TBaluEditorInternal
{
public:
	std::unique_ptr<TBaluRender> render;
	std::unique_ptr<TBaluWorldDef> world;
	
	std::unique_ptr<TDrawingHelper> drawing_helper;

	std::unique_ptr<TEditorResourses> resourses;

	//TCurrEditor curr_editor_mode;

	//TSpriteEditor sprite_editor;
	//TBoundaryEditor boundary_editor;
	TAbstractEditor* active_editor;

	TVec2 screen_pos;
	TVec2 screen_size;

	bool screen_moving;
	TVec2i old_cursor_pos;

	TBaluEditorInternal()// :sprite_editor(world.get())
	{
		screen_moving = false;
		//curr_editor_mode = TCurrEditor::BOUNDARY;
		//curr_editor_mode = TCurrEditor::SPRITE;
		//boundary_editor.objects.push_back(TBoundaryObjectBehaivor());
		auto ed = new TPhysBodyEditor();
		ed->SetActiveTool(new TCreatePolygonTool(ed));
		active_editor = ed;
		
	}
};

void TBaluEditor::AddSelectionChangedCallback(void* calle, SelectionChangedCallbackRefType MyCallback)
{
	SelectionChangedCallbackRef = MyCallback;
	SelectionChangedCallbackRef_calle = calle;
}

void TBaluEditor::RemoveSelectionChangedCallback(SelectionChangedCallbackRefType MyCallback)
{
	SelectionChangedCallbackRef = NULL;
	SelectionChangedCallbackRef_calle = NULL;
}

TBaluEditor::TBaluEditor(int hWnd, TVec2i use_size)
{
	p.reset(new TBaluEditorInternal());
	p->screen_size = TVec2(10,10);
	p->screen_pos = TVec2(0, 0);
	p->render.reset(new TBaluRender(hWnd, use_size));
	p->world.reset(new TBaluWorldDef());
	p->resourses.reset(new TEditorResourses(p->render.get()));
	p->drawing_helper.reset(new TDrawingHelper(p->render.get(), p->resourses.get()));
	p->render->BeginScene();
}

TBaluEditor::~TBaluEditor()
{

}

void TBaluEditor::SetViewport(TVec2i use_size)
{

	p->render->Set.Viewport(use_size);
}

void TBaluEditor::Render()
{
	TMatrix<float, 4> ortho_m = TMatrix<float, 4>::GetOrtho(p->screen_pos, p->screen_size, -10, 10);
	TMatrix<float, 4> ortho_m_inv = ortho_m.GetInverted();
	p->render->Set.Projection(ortho_m);

	//p->render->BeginScene();
	if(true){
		p->render->Set.ClearColor(0, 0, 0);
		p->render->Set.Color(1, 1, 1, 1);
		p->render->Clear(true);

		//p->render->Texture.Enable(true);

		//p->render->AlphaTest.Enable(true);
		//p->render->Blend.Enable(true);

		//p->render->AlphaTest.Func(">=", 0.1);
		//p->render->Blend.Func("dc*(1-sa)+sc*sa");

		p->active_editor->Render(p->drawing_helper.get());

		

		//p->render->Texture.Enable(false);
		//p->render->AlphaTest.Enable(false);
		//p->render->Blend.Enable(false);
	}
	p->render->EndScene();
}

TVec2 TBaluEditor::ScreenToWorld(const TVec2& v)
{
	return p->screen_pos + (v + TVec2(-0.5, -0.5)).ComponentMul(p->screen_size);
}

TVec2 TBaluEditor::DirScreenToWorld(const TVec2& v)
{
	return (v).ComponentMul(p->screen_size);
}

TVec2 TBaluEditor::WorldToScreen(const TVec2& v)
{
	return (v - p->screen_pos) / p->screen_size + TVec2(-0.5f, -0.5f);
}

TVec2 TBaluEditor::ScreenToWorld(const TVec2i& screen)
{
	TVec2i use_client_mouse_pos = screen;
	TVec2i screen_size = p->render->ScreenSize();
	TVec2 pos = TVec2(use_client_mouse_pos[0] / (float)screen_size[0], 1 - use_client_mouse_pos[1] / (float)screen_size[1]);
	TVec2 world_pos = ScreenToWorld(pos);
	return world_pos;
}

TVec2 TBaluEditor::DirScreenToWorld(const TVec2i& screen)
{
	TVec2i use_client_mouse_pos = screen;
	TVec2i screen_size = p->render->ScreenSize();
	TVec2 pos = TVec2(use_client_mouse_pos[0] / (float)screen_size[0], - use_client_mouse_pos[1] / (float)screen_size[1]);
	TVec2 world_pos = DirScreenToWorld(pos);
	return world_pos;
}

void TBaluEditor::OnMouseMove(TMouseEventArgs e)
{
	TVec2 world_pos = ScreenToWorld(e.location);
	if (p->screen_moving)
	{
		p->screen_pos -= DirScreenToWorld( e.location - p->old_cursor_pos);
		p->old_cursor_pos = e.location;
	}
	else
	{
		p->active_editor->OnMouseMove(e, world_pos);
	}
}

void TBaluEditor::OnMouseDown(TMouseEventArgs e)
{
	if (e.button == TMouseButton::Middle)
	{
		p->screen_moving = true;
		TVec2 world_pos = ScreenToWorld(e.location);
		p->old_cursor_pos = e.location;
	}
	else
	{
		TVec2 world_pos = ScreenToWorld(e.location);
		p->active_editor->OnMouseDown(e, world_pos);
	}
}

void TBaluEditor::OnMouseUp(TMouseEventArgs e)
{
	if (e.button == TMouseButton::Middle)
	{
		p->screen_moving = false;
	}
	else
	{
		TVec2 world_pos = ScreenToWorld(e.location);
		p->active_editor->OnMouseUp(e, world_pos);
	}
}

void TBaluEditor::OnMouseWheel(float delta)
{
	p->screen_size += (p->screen_size*0.1* delta / abs(delta));
}

void TBaluEditor::NewScene()
{

}
void TBaluEditor::NewClass()
{

}
void TBaluEditor::NewPhysBody()
{

}
void TBaluEditor::NewSprite()
{
	int static sprites_id = 0;
	sprites_id++;
	char buf[100];
	sprintf_s(buf, "sprite%i", sprites_id);
	p->world->sprites[buf].sprite_name = buf;

	//p->curr_editor_mode = TCurrEditor::SPRITE;
	//p->sprite_editor.StartEdit(&p->world->sprites[buf]);
	SelectionChangedCallbackRef(SelectionChangedCallbackRef_calle, NULL, new TBaluPolygonShapeDef());
}
void TBaluEditor::NewMaterial()
{

}