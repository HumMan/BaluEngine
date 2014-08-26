#pragma once


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

	TOBB<float, 2> bounding_box;

	TBaluInstanceDef target_object;
};

class TJointCreator
{
public:
	virtual void MoveTo() = 0;
	virtual void MouseDown() = 0;
	virtual void MouseUp() = 0;
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
