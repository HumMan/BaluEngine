#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>

class TLayer
{
private:
	int order; //0 - bottom, max - top
	std::string name;
	bool visible;

	//only in editor
	float alpha;
	bool locked;
	bool editor_visible;
public:
};

class TLayersManager
{
	std::vector<TLayer> layers;
public:
	bool IsLayerVisible(int layer_id);
};



class TLayersManagerInstance
{
public:
};
