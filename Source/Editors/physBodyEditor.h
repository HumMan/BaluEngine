

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
