#include "editorResourses.h"

#include <map>

class TEditorResoursesInternal
{
public:
	std::map<std::string, TTextureId> textures;
};

TTextureId TEditorResourses::CreateTextureFromFile(std::string path)
{
	return TTextureId();
}