#include "physBodyEditor.h"

#include "../baluEditorDefs.h"

void TPhysBodyEditor::Initialize(TWorldObjectDef* obj)
{

}

void TPhysBodyEditor::Initialize(TBaluPhysBodyDef* obj)
{
	for (const std::unique_ptr<TBaluShapeDef>& v : obj->fixtures)
	{
		auto b = v->GetOBB();
		auto boundary_obj = TBoundaryObjectBehaivor(b);
		boundary_editor.objects.push_back(boundary_obj);
	}
}

bool TPhysBodyEditor::CanSetSelectedAsWork()
{

}

void TPhysBodyEditor::SetSelectedAsWork()
{

}

bool TPhysBodyEditor::CanEndSelectedAsWork()
{

}
void TPhysBodyEditor::EndSelectedAsWork()
{

}

void TPhysBodyEditor::OnMouseDown(TMouseEventArgs e)
{

}

void TPhysBodyEditor::OnMouseMove(TMouseEventArgs e)
{

}

void TPhysBodyEditor::OnMouseUp(TMouseEventArgs e)
{

}