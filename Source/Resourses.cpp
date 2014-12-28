#include "Resourses.h"

#include <baluRender.h>

#include <map>

class TResoursesInternal
{
public:
	std::map<std::string, TTextureId> textures;
	TBaluRender* render;
};

TBaluTexture TResourses::CreateTextureFromFile(std::string path)
{
	TBaluTexture tex;

	if (p->textures.find(path) != p->textures.end())
		return *(TBaluTexture*)&p->textures[path];
	else
	{
		TTextureId id = p->render->Texture.Create(path.c_str());
		p->textures[path] = id;
		return *(TBaluTexture*)&id;
	}

}

TResourses::TResourses(TBaluRender* render)
{
	p.reset(new TResoursesInternal());
	p->render = render;
}

TResourses::~TResourses()
{
}
