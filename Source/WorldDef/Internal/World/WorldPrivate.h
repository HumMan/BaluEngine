#include "../Scripts/EventsEditor.h"

class TWorld::TPrivate
{
public:
	std::map<std::string, std::unique_ptr<TWorldObject>> world_objects[(int)TWorldObjectType::None];

	template<class T, class M>
	std::vector<T*> GetVectorFromMap(M& map)
	{
		std::vector<T*> result;
		result.reserve(map.size());
		for (auto& v : map)
		{
			result.push_back(v.second.get());
		}
		return result;
	}

	std::unique_ptr<TEventsEditor> events_editor;

	TWorldChangeListenerArray listeners;

	TPrivate()
	{
		events_editor.reset(new TEventsEditor());
	}
};

