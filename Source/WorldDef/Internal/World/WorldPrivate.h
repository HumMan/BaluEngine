#include "../Scripts/EventsEditor.h"

class TCommandList : public ICommandList
{
private:
	std::vector<std::unique_ptr<ICommand>> list;
	int done_index; //последняя команда которая выполнена
	bool can_add_commands;
public:
	TCommandList()
	{
		done_index = -1;
		can_add_commands = true;
	}
	void Undo()
	{
		if (CanUndo())
		{
			can_add_commands = false;
			list[done_index].get()->Undo();
			done_index--;
			can_add_commands = true;
		}
	}
	void Redo()
	{
		if (CanRedo())
		{
			can_add_commands = false;
			done_index++;
			list[done_index].get()->Do();
			can_add_commands = true;
		}
	}
	void AddCommmand(ICommand* command)
	{
		if (can_add_commands)
		{
			done_index++;
			list.resize(done_index);
			list.push_back(std::unique_ptr<ICommand>(command));
		}
	}
	bool CanRedo()
	{
		return done_index < (int(list.size())-1);
	}
	bool CanUndo() 
	{
		return done_index >= 0;
	}
};

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

	std::unique_ptr<TCommandList> command_list;

	TPrivate()
	{
		events_editor.reset(new TEventsEditor());
		command_list.reset(new TCommandList());
	}
};

