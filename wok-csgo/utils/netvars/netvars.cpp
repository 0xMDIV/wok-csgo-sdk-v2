#include "../utils.h"
#include "../../sdk/interfaces.h"

namespace netvars {
	void init() {
		for (auto data = interfaces::client_dll->get_all_classes(); data; data = data->m_next) {
			if (!data->m_recv_table)
				continue;

			dump_recursive(data->m_network_name, data->m_recv_table, 0);
		}
	}

	void dump_recursive(const char* base_class, recv_table* table, uint16_t offset) {
		for (int i = 0; i < table->m_num_props; i++) {
			auto prop = &table->m_props[i];
			if (!prop
				|| isdigit(prop->m_var_name[0])
				|| !strcmp(prop->m_var_name, _("baseclass")))
				continue;

			if (prop->m_recv_type == DPT_DATATABLE
				&& prop->m_data_table
				&& prop->m_data_table->m_net_table_name[0] == 'D')
				dump_recursive(base_class, prop->m_data_table, offset + prop->m_offset);

			char hash_name[256];
			strcpy_s(hash_name, base_class);
			strcat_s(hash_name, _("->"));
			strcat_s(hash_name, prop->m_var_name);
			auto hash = fnv1a_rt(static_cast<const char*>(hash_name));

			props[hash] = { prop, static_cast<uint16_t>(offset + prop->m_offset) };
		}
	}

	std::unordered_map<uint32_t, data> props;

	uint16_t get_offset(uint32_t hash) { return props[hash].offset; }
	recv_prop* get_prop(uint32_t hash) { return props[hash].prop; }
}