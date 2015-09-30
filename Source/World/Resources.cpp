#include "IResources.h"

#include <baluRender.h>
using namespace BaluRender;
using namespace EngineInterface;
#include <map>

namespace EngineInterface
{
	class TResourcesInternal
	{
	public:
		std::map<std::string, TTextureId> textures;
		TBaluRender* render;
		std::string assets_dir;
	};
}

TBaluTexture TResources::CreateTextureFromFile(std::string path)
{
	TBaluTexture tex;

	path = p->assets_dir + "\\" + path;

	if (p->textures.find(path) != p->textures.end())
		return *(TBaluTexture*)&p->textures[path];
	else
	{
		TTextureId id = p->render->Texture.Create(path.c_str());
		p->textures[path] = id;
		return *(TBaluTexture*)&id;
	}

}

TResources::TResources(TBaluRender* render, std::string assets_dir)
{
	p.reset(new TResourcesInternal());
	p->render = render;
	p->assets_dir = assets_dir;
}

std::string TResources::GetAssetsDir()
{
	return p->assets_dir;
}

TResources::~TResources()
{
}
