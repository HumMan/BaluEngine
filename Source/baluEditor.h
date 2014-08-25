#pragma once

#include <baluLib.h>

#include <map>

class TAbstractEditorObject
{

};

class TAbstractEditor
{
public:
	std::vector<TAbstractEditor*> parent_editors;

	TAbstractEditor* current_local_editor;

	void MouseMove();
	void MouseDown();
	void MouseUp();

	//void Edit(TAbstractEditorObject* obj);

	std::map<std::string, TAbstractEditorObject*> CanCreateObjects();
};



class TSceneObject
{
public:
	void CanMove();
	void CanResize();
	void CanRotate();
	void OnMove();
	void OnResize();
	void OnRotate();
	void Clone();
	void Draw();

	bool CanEdit();
	void Edit();

	TOBB<float,2> bounding_box;

	TBaluInstanceDef target_object;
};


class TJointCreator
{
public:
	virtual void MoveTo()=0;
	virtual void MouseDown()=0;
	virtual void MouseUp()=0;
};

class TDistanceJointCreator : public TJointCreator
{
	void MoveTo();
	void MouseDown();
	void MouseUp();
};

class TControlPoint
{
public:
	void CanMove();
	void OnMove();
};

class TSceneJoint
{
public:
	std::vector<TControlPoint*> control_points;
};

class TSceneEditor : public TAbstractEditor
{
	std::vector<TSceneObject> scene_objects;
	std::vector<TSceneJoint> scene_joints;

	void SetScene(TBaluScene* scene_to_edit);
	void Render(TBaluRender* render);
};

class TPhysShape 
{
public:

	TAABB<float, 2> bounding_box;
};

class TPhysShapeEditor : public TAbstractEditor
{

};

class TEditorPhysShape
{
public:
	void CanMove();
	void CanResize();
	void CanRotate();
	void OnMove();
	void OnResize();
	void OnRotate();
	void Clone();
	void Draw();

	bool CanEdit();
	TAbstractEditor* Edit();

	TOBB<float, 2> bounding_box;
};

class TPhysBodyEditor : public TAbstractEditor
{

};

class TTextEditor : public TAbstractEditor
{

};

class TBaluEditorInternal;
class BALUENGINEDLL_API TBaluEditor
{
private:
	std::unique_ptr<TBaluEditorInternal> p;
public:
	TBaluEditor(HWND hWnd, TVec2i use_size);
	~TBaluEditor();
	void Render();
	void SetViewport(TVec2i use_size);
	void OnMouseMove(TVec2i use_client_mouse_pos);
	void OnMouseScroll(float delta);

	//
	void NewScene();
	void NewClass();
	void NewPhysBody();
	void NewSprite();
	void NewMaterial();
};