#pragma once

#include <string>
#include <map>
#include <set>

class TLayer
{
private:
	int order; //0 - bottom, max - top

	std::string name;
	bool initial_visible;
	float opacity;
	bool editor_visible;
	bool locked;
public:
};

class TLayersManager
{
	std::map<std::string, TLayer> layers;
public:
};

class TLayerInstance;

class TLayerObjectInstance
{
	TLayer* layer;
	TLayerInstance* manager;
public:
	//virtual void SetVisible(bool visible) = 0;
	//virtual void SetLocked(bool locked) = 0;
	//virtual void SetOpacity(float opacity) = 0;
	//virtual void SetZOrderValue(float z_value) = 0;
	//virtual TLayer* GetLayer() = 0;
};

class TLayersManagerInstance;

class TLayerInstance
{
private:
	TLayer* source;

	std::set<TLayerObjectInstance*> objects_on_layer;

	TLayersManagerInstance* manager;
};



class TLayersManagerInstance
{
	std::map<std::string, TLayerInstance> layers;
public:
	TLayersManagerInstance();
	void AddObjectToDefault(TLayerObjectInstance* object);
	void AddObjectToLayer(std::string layer_name, TLayerObjectInstance* object);
};
