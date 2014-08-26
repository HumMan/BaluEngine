#include "../baluEditorDefs.h"

class TSpriteEditor
{
	TBaluSpriteDef* sprite;

	enum class CurrState
	{
		CanSubdivide,
		CanMoveSelected,
		MovingSelected,
		None
	} curr_state;

	std::vector<int> selected_points;

	int point_under_cursor;

	int nearest_point = -1;
	float nearest_point_dist = 0;

	int nearest_line = -1;
	float nearest_line_dist = 0;

	TVec2 cursor_pos;

	TVec2 old_cursor_pos;

public:
	TSpriteEditor();
	void StartEdit(TBaluSpriteDef* use_sprite);
	void EndEdit();

	void MouseMove(TVec2 new_pos);
	//void MouseClick(TVec2 new_pos);
	void MouseDown();
	void MouseUp();

	void SetAsBox(TVec2 size);

	void Render(TBaluRender* render);
};