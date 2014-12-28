#pragma once

#include <string>
#include <memory>

class TBaluTexture
{
	int id;
public:
};

class TResoursesInternal;
class TBaluRender;

class TResourses
{
	friend class TBaluEngineRender;
	std::unique_ptr<TResoursesInternal> p;
	TResourses(TBaluRender* render);
public:
	TBaluTexture CreateTextureFromFile(std::string path);
	~TResourses();
};