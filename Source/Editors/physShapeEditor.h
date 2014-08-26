#include "abstractEditor.h"

//class TPhysShape
//{
//public:
//
//};

class TPhysShapeEditor : public TAbstractEditor
{
public:
	void ConvertToCircle();
	void ConvertToPolygon();

	void OnMouseMove();
	void OnMouseClick();
};