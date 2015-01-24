#include "Resources.h"

#include <baluRender.h>

#include <map>

class TResourcesInternal
{
public:
	std::map<std::string, TTextureId> textures;
	TBaluRender* render;
};

TBaluTexture TResources::CreateTextureFromFile(std::string path)
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

TResources::TResources(TBaluRender* render)
{
	p.reset(new TResourcesInternal());
	p->render = render;
}

TResources::~TResources()
{
}
