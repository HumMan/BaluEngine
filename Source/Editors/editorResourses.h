#pragma once

#include <memory>

#include <baluRender.h>

class TEditorResoursesInternal;
class TEditorResourses
{
	std::unique_ptr<TEditorResoursesInternal> p;
public:
	TEditorResourses(TBaluRender* render);
	TTextureId CreateTextureFromFile(std::string path);
};