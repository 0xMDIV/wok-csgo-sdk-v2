#pragma once
#include "common_includes.h"
#include "sdk/interfaces.h"
#include "singleton.h"
#include "menu/menu.h"

namespace g {
	extern HMODULE			module;
	extern c_local_player	local;
	extern c_user_cmd*		cmd;
	extern bool				send_packet;
}