#include "editorResourses.h"

#include <map>

class TEditorResoursesInternal
{
public:
	std::map<std::string, TTextureId> textures;
	TBaluRender* render;
};

TTextureId TEditorResourses::CreateTextureFromFile(std::string path)
{
	if (p->textures.find(path) != p->textures.end())
		return p->textures[path];
	else
	{
		TTextureId id = p->render->Texture.Create(path.c_str());
		p->textures[path] = id;
		return id;
	}
}

TEditorResourses::TEditorResourses(TBaluRender* render)
{
	p.reset(new TEditorResoursesInternal());
	p->render = render;
}

TEditorResourses::~TEditorResourses()
{

}
