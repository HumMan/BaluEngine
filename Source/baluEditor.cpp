#include "baluEditor.h"

#include "Editors\spriteEditor.h"

#include "Editors\abstractEditor.h"

enum class TCurrEditor
{
	SPRITE,
	PHYS_SHAPE,
	PHYS_BODY,
	CLASS,
	SCENE,

	//testing only
	BOUNDARY
};

class TBaluEditorInternal
{
public:
	std::unique_ptr<TBaluRender> render;
	std::unique_ptr<TBaluWorldDef> world;
	
	TCurrEditor curr_editor_mode;

	TSpriteEditor sprite_editor;
	TBoundaryEditor boundary_editor;

	TVec2 screen_pos;
	TVec2 screen_size;
	TBaluEditorInternal() :sprite_editor(world.get())
	{
		curr_editor_mode = TCurrEditor::BOUNDARY;
		boundary_editor.objects.push_back(TBoundaryObjectBehaivor());
	}
};

TBaluEditor::TBaluEditor(HWND hWnd, TVec2i use_size)
{
	p.reset(new TBaluEditorInternal());
	p->screen_size = TVec2(10,10);
	p->screen_pos = TVec2(0, 0);
	p->render.reset(new TBaluRender(hWnd, use_size));
	p->world.reset(new TBaluWorldDef());
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

	p->render->BeginScene();
	{
		p->render->Set.ClearColor(0, 0, 0);
		p->render->Set.Color(1, 1, 1, 1);
		p->render->Clear(true);

		//p->render->Texture.Enable(true);

		//p->render->AlphaTest.Enable(true);
		//p->render->Blend.Enable(true);

		//p->render->AlphaTest.Func(">=", 0.1);
		//p->render->Blend.Func("dc*(1-sa)+sc*sa");

		if (p->curr_editor_mode == TCurrEditor::SPRITE)
			p->sprite_editor.Render(p->render.get());
		if (p->curr_editor_mode == TCurrEditor::BOUNDARY)
			p->boundary_editor.Render(p->render.get());

		//p->render->Texture.Enable(false);
		//p->render->AlphaTest.Enable(false);
		p->render->Blend.Enable(false);
	}
	p->render->EndScene();
}

TVec2 TBaluEditor::ScreenToWorld(const TVec2& v)
{
	return p->screen_pos + (v + TVec2(-0.5, -0.5)).ComponentMul(p->screen_size);
}
TVec2 TBaluEditor::WorldToScreen(const TVec2& v)
{
	return (v - p->screen_pos) / p->screen_size + TVec2(-0.5f, -0.5f);
}

void TBaluEditor::OnMouseMove(TVec2i use_client_mouse_pos)
{
	TVec2i screen_size = p->render->ScreenSize();
	TVec2 pos = TVec2(use_client_mouse_pos[0] / (float)screen_size[0], 1 - use_client_mouse_pos[1] / (float)screen_size[1]);
	TVec2 world_pos = ScreenToWorld(pos);
	
	if (p->curr_editor_mode == TCurrEditor::SPRITE)
		p->sprite_editor.MouseMove(world_pos);
	if (p->curr_editor_mode == TCurrEditor::BOUNDARY)
		p->boundary_editor.OnMouseMove(world_pos);
}

void TBaluEditor::OnMouseClick(TVec2i use_client_mouse_pos)
{

	
}

void TBaluEditor::OnMouseDown()
{
	if (p->curr_editor_mode == TCurrEditor::SPRITE)
		p->sprite_editor.MouseDown();
	if (p->curr_editor_mode == TCurrEditor::BOUNDARY)
		p->boundary_editor.OnMouseDown();
}

void TBaluEditor::OnMouseUp()
{
	if (p->curr_editor_mode == TCurrEditor::SPRITE)
		p->sprite_editor.MouseUp();
	if (p->curr_editor_mode == TCurrEditor::BOUNDARY)
		p->boundary_editor.OnMouseUp();
}

void TBaluEditor::OnMiddleDown()
{

}

void TBaluEditor::OnMiddleUp()
{
	
}

void TBaluEditor::OnMouseScroll(float delta)
{

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
	p->sprite_editor.StartEdit(&p->world->sprites[buf]);
}
void TBaluEditor::NewMaterial()
{

}