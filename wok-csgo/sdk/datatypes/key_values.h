#pragma once

class key_values {
public:
	~key_values();

	CUSTOM_VFUNC(init(const char* key_name), "client_panorama.dll", "55 8B EC 51 33 C0 C7 45", void(__thiscall*)(void*, const char*), key_name)
	CUSTOM_VFUNC(load_from_buffer(const char* resource_name, const char* buf, void* file_sys = nullptr, const char* path_id = nullptr, void* eval_sym_proc = nullptr, void* unk = nullptr), 
		"client_panorama.dll", "55 8B EC 51 33 C0 C7 45", void(__thiscall*)(void*, const char*, const char*, void*, const char*, void*, void*), resource_name, buf, file_sys, path_id, eval_sym_proc, unk)
	CUSTOM_VFUNC(find_key(const char* name, bool create), "client_panorama.dll", "55 8B EC 83 EC 1C 53 8B D9 85 DB", key_values*(__thiscall*)(void*, const char*, bool), name, create)

	void set_int(const char* name, int val) {
		auto key = find_key(name, true);
		if (!key)
			return;

		*reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(key) + 0xC) = val;
		*reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(key) + 0x10) = 2;
	}

	void set_string(const char* name, const char* a2) {
		auto key = find_key(name, true);
		if (!key)
			return;

		static auto set_string_fn = reinterpret_cast<void(__thiscall*)(void*, const char*)>(SIG("client_panorama.dll", "55 8B EC A1 ? ? ? ? 53 56 57 8B F9 8B 08 8B 01"));
		set_string_fn(key, a2);
	}
};