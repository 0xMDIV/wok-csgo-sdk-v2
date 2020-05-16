#include "events.h"

namespace events {
	void listener::fire_game_event(i_game_event* event) {
		for (auto& callback : m_callbacks) {
			if (fnv1a_rt(event->get_name()) != callback.m_hash)
				continue;

			callback.m_fn(event);
		}
	}

	void init() {
		auto add = [](std::string name, const std::function<void(i_game_event*)>& fn) -> void {
			m_callbacks.push_back(callback_t(fnv1a_rt(name.c_str()), fn));

			interfaces::event_manager->add_listener(&m_listener, name.c_str(), false);
		};

		add(_("player_hurt"), player_hurt);
	}

	void undo() {
		interfaces::event_manager->remove_listener(&m_listener);
	}

	listener m_listener;
	std::vector<callback_t> m_callbacks;
}