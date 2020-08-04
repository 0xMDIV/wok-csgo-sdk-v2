#pragma once

struct player_info_t {
	int64_t			pad0;
	union {
		int64_t		m_xuid;
		struct {
			int		m_xuid_low;
			int		m_xuid_high;
		};
	};
	char			m_name[128];
	int				m_user_id;
	char			m_guid[33];
	unsigned int	m_friends_id;
	char			m_friends_name[128];
	bool			m_fake_player;
	bool			m_is_hltv;
	unsigned int	m_custom_files[4];
	unsigned char	m_files_downloaded;
};

class c_bone_cache {
public:
	matrix3x4_t*	m_cached_bones;
	char			pad0[8];
	unsigned int	m_cached_bones_count;
};

class c_base_entity;
class c_base_animating;

class c_bone_accessor {
public:
	c_base_animating*	m_animating;
	matrix3x4a_t*		m_bones;
	int					m_readable_bones;
	int					m_writable_bones;
};

class c_animation_layer {
public:
	float			m_anim_time;
	float			m_fade_out_time;
	int				m_flags;
	int				m_activity;
	int				m_priority;
	int				m_order;
	int				m_sequence;
	float			m_prev_cycle;
	float			m_weight;
	float			m_weight_delta_rate;
	float			m_playback_rate;
	float			m_cycle;
	c_base_entity*	m_owner;
	int				m_invalidate_physics_bits;
};

class c_base_combat_weapon;

class c_anim_state {
public:
	VFUNC_SIG(reset(), "client.dll", "56 6A 01 68 ? ? ? ? 8B F1", void(__thiscall*)(void*))
	VFUNC_SIG(create(c_base_entity* entity), "client.dll", "55 8B EC 56 8B F1 B9 ? ? ? ? C7 46", void(__thiscall*)(void*, c_base_entity*), entity)

	void update(qangle_t angle) {
		static const auto update_fn = SIG("client.dll", "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 F3 0F 11 54 24").get();
		if (!update_fn)
			return;

		__asm {
			push 0

			mov ecx, this

			movss xmm1, dword ptr[angle + 4]
			movss xmm2, dword ptr[angle]

			call update_fn
		}
	}

	char					pad0[8];
	int						m_tick_count;
	char					pad1[83];
	c_base_entity*			m_base_entity;
	c_base_combat_weapon*	m_active_weapon;
	c_base_combat_weapon*	m_last_active_weapon;
	float					m_last_client_side_animation_update_time;
	int						m_last_client_side_animation_update_frame_count;
	float					m_delta_time;
	float					m_eye_yaw;
	float					m_eye_pitch;
	float					m_goal_feet_yaw;
	float					m_cur_feet_yaw;
	float					m_cur_torso_yaw;
	float					m_velocity_lean;
	float					m_lean_amount;
	char					pad2[4];
	float					m_feet_cycle;
	float					m_feet_yaw_rate;
	char					pad3[4];
	float					m_duck_amount;
	float					m_landing_duck_additive;
	char					pad4[4];
	vec3_t					m_origin;
	vec3_t					m_last_origin;
	vec3_t					m_velocity;
	vec3_t					m_velocity_normalized;
	vec3_t					m_last_velocity_non_zero;
	float					m_speed_2d;
	float					m_up_velocity;
	float					m_speed_normalized;
	float					m_feet_speed_forwards_or_sideways;
	float					m_feet_speed_unknown_forward_or_sideways;
	float					m_time_since_started_moving;
	float					m_time_since_stopped_moving;
	bool					m_on_ground;
	bool					m_in_hit_ground_animation;
	char					pad5[6];
	float					m_time_since_in_air;
	float					m_last_origin_z;
	float					m_head_height_or_offset_from_hitting_ground_animation;
	float					m_stop_to_full_running_fraction;
	char					pad6[4];
	float					m_magic_fraction;
	char					pad7[48];
	float					m_last_velocity_test_time;
	vec3_t					m_last_velocity;
	vec3_t					m_dst_acceleration;
	vec3_t					m_acceleration;
	float					m_acceleration_weight;
	char					pad8[428];
	float					m_min_body_yaw;
	float					m_max_body_yaw;
	float					m_min_body_pitch;
	float					m_max_body_pitch;
	int						m_anim_set_version;
};

class c_cs_weapon_data {
public:
	char	pad0[4];
	char*	m_console_name;
	char	pad1[12];
	int		m_max_clip1;
	int		m_max_clip2;
	int		m_default_clip1;
	int		m_default_clip2;
	int		m_primary_reserve_ammo_max;
	int		m_secondary_reserve_ammo_max;
	char*	m_world_model;
	char*	m_view_model;
	char*	m_dropped_model;
	char	pad2[80];
	char*	m_hud_name;
	char*	m_weapon_name;
	char	pad3[2];
	bool	m_is_melee_weapon;
	char	pad4[9];
	float	m_weapon_weight;
	char	pad5[40];
	int		m_weapon_type;
	char	pad6[4];
	int		m_weapon_price;
	int		m_kill_award;
	char	pad7[4];
	float	m_cycle_time;
	float	m_cycle_time_alt;
	char	pad8[8];
	bool	m_full_auto;
	char	pad9[3];
	int		m_damage;
	float	m_armor_ratio;
	int		m_bullets;
	float	m_penetration;
	char	pad10[8];
	float	m_range;
	float	m_range_modifier;
	float	m_throw_velocity;
	char	pad11[12];
	bool	m_has_silencer;
	char	pad12[11];
	char*	m_bullet_type;
	float	m_max_speed;
	float	m_max_speed_alt;
	char	pad13[4];
	float	m_spread;
	float	m_spread_alt;
	float	m_inaccuracy_crouch;
	float	m_inaccuracy_crouch_alt;
	float	m_inaccuracy_stand;
	float	m_inaccuracy_stand_alt;
	float	m_inaccuracy_jump_initial;
	float	m_inaccuracy_jump_apex;
	float	m_inaccuracy_jump;
	float	m_inaccuracy_jump_alt;
	float	m_inaccuracy_land;
	float	m_inaccuracy_land_alt;
	float	m_inaccuracy_ladder;
	float	m_inaccuracy_ladder_alt;
	float	m_inaccuracy_fire;
	float	m_inaccuracy_fire_alt;
	float	m_inaccuracy_move;
	float	m_inaccuracy_move_alt;
	float	m_inaccuracy_reload;
	int		m_recoil_seed;
	float	m_recoil_angle;
	float	m_recoil_angle_alt;
	float	m_recoil_angle_variance;
	float	m_recoil_angle_variance_alt;
	float	m_recoil_magnitude;
	float	m_recoil_magnitude_alt;
	float	m_recoil_magnitude_variance;
	float	m_recoil_magnitude_variance_alt;
};

enum e_cs_weapon_type : int {
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SMG,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER,
	WEAPONTYPE_MACHINE_GUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_PLACE_HOLDER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN,
	WEAPONTYPE_MEDISHOT,
	WEAPONTYPE_FISTS,
	WEAPONTYPE_BREACH_CHARGE,
	WEAPONTYPE_BUMP_MINE,
	WEAPONTYPE_TABLET,
	WEAPONTYPE_MELEE
};

enum e_invalidate_physics_bits : unsigned {
	POSITION_CHANGED 	= (1 << 0),
	ANGLES_CHANGED 		= (1 << 1),
	VELOCITY_CHANGED 	= (1 << 2),
	ANIMATION_CHANGED 	= (1 << 3),
	BOUNDS_CHANGED 		= (1 << 4),
	SEQUENCE_CHANGED 	= (1 << 5)
};

enum e_class_id : int {
	C_AI_BASE_NPC,

	C_WEAPON_AK47,

	C_BASE_ANIMATING,
	C_BASE_ANIMATING_OVERLAY,
	C_BASE_ATTRIBUTABLE_ITEM,
	C_BASE_BUTTON,
	C_BASE_COMBAT_CHARACTER,
	C_BASE_COMBAT_WEAPON,
	C_BASE_CS_GRENADE,
	C_BASE_CS_GRENADE_PROJECTILE,
	C_BASE_DOOR,
	C_BASE_ENTITY,
	C_BASE_FLEX,
	C_BASE_GRENADE,
	C_BASE_PARTICLE_ENTITY,
	C_BASE_PLAYER,
	C_BASE_PROP_DOOR,
	C_BASE_TEAM_OBJECTIVE_RESOURCE,
	C_BASE_TEMP_ENTITY,
	C_BASE_TOGGLE,
	C_BASE_TRIGGER,
	C_BASE_VIEWMODEL,
	C_BASE_VPHYSICS_TRIGGER,
	C_BASE_WEAPON_WORLD_MODEL,

	C_BEAM,
	C_BEAM_SPOTLIGHT,

	C_BONE_FOLLOWER,

	C_BR_C4_TARGET,
	C_BREACH_CHARGE,
	C_BREACH_CHARGE_PROJECTILE,

	C_BREAKABLE_PROP,
	C_BREAKABLE_SURFACE,

	C_BUMP_MINE,
	C_BUMP_MINE_PROJECTILE,

	C_C4,

	C_CASCADE_LIGHT,

	C_CHICKEN,

	C_COLOR_CORRECTION,
	C_COLOR_CORRECTION_VOLUME,

	C_CS_GAMERULES_PROXY,
	C_CS_PLAYER,
	C_CS_PLAYER_RESOURCE,
	C_CS_RAGDOLL,
	C_CS_TEAM,

	C_DANGERZONE,
	C_DANGERZONE_CONTROLLER,

	C_DEAGLE,

	C_DECOY_GRENADE,
	C_DECOY_PROJECTILE,

	C_DRONE,
	C_DRONE_GUN,

	C_DYNAMIC_LIGHT,
	C_DYNAMIC_PROP,

	C_ECON_ENTITY,
	C_ECON_WEARABLE,

	C_EMBERS,

	C_ENTITY_DISSOLVE,
	C_ENTITY_FLAME,
	C_ENTITY_FREEZING,
	C_ENTITY_PARTICLE_TRAIL,

	C_ENV_AMBIENT_LIGHT,
	C_ENV_DETAIL_CONTROLLER,
	C_ENV_DOF_CONTROLLER,
	C_ENV_GAS_CANISTER,
	C_ENV_PARTICLE_SCRIPT,
	C_ENV_PROJECTED_TEXTURE,
	C_ENV_QUADRATIC_BEAM,
	C_ENV_SCREEN_EFFECT,
	C_ENV_SCREEN_OVERLAY,
	C_ENV_TONEMAP_CONTROLLER,
	C_ENV_WIND,

	C_FE_PLAYER_DECAL,

	C_FIRECRACKER_BLAST,
	C_FIRE_SMOKE,
	C_FIRE_TRAIL,

	C_FISH,

	C_FISTS,
	C_FLASHBANG,

	C_FOG_CONTROLLER,
	C_FOOTSTEP_CONTROL,

	C_FUNC_DUST,
	C_FUNC_LOD,
	C_FUNC_AREA_PORTAL_WINDOW,
	C_FUNC_BRUSH,
	C_FUNC_CONVEYOR,
	C_FUNC_LADDER,
	C_FUNC_MONITOR,
	C_FUNC_MOVE_LINEAR,
	C_FUNC_OCCLUDER,
	C_FUNC_REFLECTIVE_GLASS,
	C_FUNC_ROTATING,
	C_FUNC_SMOKE_VOLUME,
	C_FUNC_TRACK_TRAIN,

	C_GAMERULES_PROXY,
	C_GRASS_BURN,
	C_HANDLE_TEST,

	C_HE_GRENADE,

	C_HOSTAGE,
	C_HOSTAGE_CARRIABLE_PROP,

	C_INCENDIARY_GRENADE,
	C_INFERNO,

	C_INFO_LADDER_DISMOUNT,
	C_INFO_MAP_REGION,
	C_INFO_OVERLAY_ACCESSOR,

	C_ITEM_HEALTHSHOT,
	C_ITEM_CASH,
	C_ITEM_DOGTAGS,
	C_KNIFE,
	C_KNIFEGG,

	C_LIGHT_GLOW,
	C_MATERIAL_MODIFY_CONTROL,

	C_MELEE,
	C_MOLOTOV_GRENADE,
	C_MOLOTOV_PROJECTILE,

	C_MOVIE_DISPLAY,
	C_PARADROP_CHOPPER,

	C_PARTICLE_FIRE,
	C_PARTICLE_PERFORMANCE_MONITOR,
	C_PARTICLE_SYSTEM,

	C_PHYS_BOX,
	C_PHYS_BOX_MULTIPLAYER,
	C_PHYSICS_PROP,
	C_PHYSICS_PROP_MULTIPLAYER,
	C_PHYS_MAGNET,
	C_PHYS_PROP_AMMO_BOX,
	C_PHYS_PROP_LOOT_CRATE,
	C_PHYS_PROP_RADAR_JAMMER,
	C_PHYS_PROP_WEAPON_UPGRADE,

	C_PLANTED_C4,

	C_PLASMA,

	C_PLAYER_PING,
	C_PLAYER_RESOURCE,

	C_POINT_CAMERA,
	C_POINT_COMMENT_ARYNODE,
	C_POINT_WORLD_TEXT,

	C_POSE_CONTROLLER,
	C_POST_PROCESS_CONTROLLER,
	C_PRECIPITATION,
	C_PRECIPITATION_BLOCKER,
	C_PREDICTED_VIEWMODEL,

	C_PROP_HALLUCINATION,
	C_PROP_COUNTER,
	C_PROP_DOOR_ROTATING,
	C_PROP_JEEP,
	C_PROP_VEHICLE_DRIVEABLE,
	C_RAGDOLL_MANAGER,
	C_RAGDOLL_PROP,
	C_RAGDOLL_PROP_ATTACHED,

	C_ROPE_KEYFRAME,

	C_WEAPON_SCAR17,

	C_SCENE_ENTITY,
	C_SENSOR_GRENADE,
	C_SENSOR_GRENADE_PROJECTILE,
	C_SHADOW_CONTROL,
	C_SLIDE_SHOW_DISPLAY,
	C_SMOKE_GRENADE,
	C_SMOKE_GRENADE_PROJECTILE,
	C_SMOKE_STACK,
	C_SNOWBALL,
	C_SNOWBALL_PILE,
	C_SNOWBALL_PROJECTILE,
	C_SPATIAL_ENTITY,
	C_SPOTLIGHT_END,
	C_SPRITE,
	C_SPRITE_ORIENTED,
	C_SPRITE_TRAIL,
	C_STATUE_PROP,
	C_STEAMJET,

	C_SUN,
	C_SUNLIGHT_SHADOW_CONTROL,

	C_SURVIVAL_SPAWN_CHOPPER,
	C_TABLET,

	C_TEAM,
	C_TEAM_PLAYROUND_BASED_RULES_PROXY,
	C_TEAR_MORRICOCHET,

	C_TE_BASE_BEAM,
	C_TE_BEAM_ENT_POINT,
	C_TE_BEAM_ENTS,
	C_TE_BEAM_FOLLOW,
	C_TE_BEAM_LASER,
	C_TE_BEAM_POINTS,
	C_TE_BEAM_RING,
	C_TE_BEAM_RING_POINT,
	C_TE_BEAM_SPLINE,
	C_TE_BLOOD_SPRITE,
	C_TE_BLOOD_STREAM,
	C_TE_BREAK_MODEL,
	C_TE_BSP_DECAL,
	C_TE_BUBBLES,
	C_TE_BUBBLE_TRAIL,
	C_TE_CLIENT_PROJECTILE,
	C_TE_DECAL,
	C_TE_DUST,
	C_TE_DYNAMIC_LIGHT,
	C_TE_EFFECT_DISPATCH,
	C_TE_ENERGY_SPLASH,
	C_TE_EXPLOSION,
	C_TE_FIRE_BULLETS,
	C_TE_FIZZ,
	C_TE_FOOTPRINT_DECAL,
	C_TE_FOUNDRY_HELPERS,
	C_TE_GAUSS_EXPLOSION,
	C_TE_GLOW_SPRITE,
	C_TE_IMPACT,
	C_TE_KILL_PLAYER_ATTACHMENTS,
	C_TE_LARGE_FUNNEL,
	C_TE_METAL_SPARKS,
	C_TE_MUZZLE_FLASH,
	C_TE_PARTICLE_SYSTEM,
	C_TE_PHYSICS_PROP,
	C_TE_PLANT_BOMB,
	C_TE_PLAYER_ANIM_EVENT,
	C_TE_PLAYER_DECAL,
	C_TE_PROJECTED_DECAL,
	C_TE_RADIOICON,
	C_TE_SHATTER_SURFACE,
	C_TE_SHOW_LINE,
	C_TE_SLA,
	C_TE_SMOKE,
	C_TE_SPARKS,
	C_TE_SPRITE,
	C_TE_SPRITE_SPRAY,
	C_TEST_PROXY_TOGGLE_NETWORKABLE,
	C_TEST_TRACE_LINE,
	C_TE_WORLD_DECAL,

	C_TRIGGER_PLAYER_MOVEMENT,
	C_TRIGGER_SOUND_OPERATOR,

	C_VGUI_SCREEN,
	C_VOTE_CONTROLLER,

	C_WATER_BULLET,
	C_WATER_LOD_CONTROL,

	C_WEAPON_AUG,
	C_WEAPON_AWP,
	C_WEAPON_BASE_ITEM,
	C_WEAPON_PPBIZON,
	C_WEAPON_CS_BASE,
	C_WEAPON_CS_BASE_GUN,
	C_WEAPON_CYCLER,
	C_WEAPON_DUAL_BERETTAS,
	C_WEAPON_FAMAS,
	C_WEAPON_FIVESEVEN,
	C_WEAPON_G3SG1,
	C_WEAPON_GALIL,
	C_WEAPON_GALIL_AR,
	C_WEAPON_GLOCK18,
	C_WEAPON_P2000,
	C_WEAPON_M249,
	C_WEAPON_M3,
	C_WEAPON_M4A4,
	C_WEAPON_MAC10,
	C_WEAPON_MAG7,
	C_WEAPON_MP5SD,
	C_WEAPON_MP7,
	C_WEAPON_MP9,
	C_WEAPON_NEGEV,
	C_WEAPON_NOVA,
	C_WEAPON_P228,
	C_WEAPON_P250,
	C_WEAPON_P90,
	C_WEAPON_SAWEDOFF,
	C_WEAPON_SCAR20,
	C_WEAPON_SCOUT,
	C_WEAPON_SG550,
	C_WEAPON_SG552,
	C_WEAPON_SG553,
	C_WEAPON_BALLISTIC_SHIELD,
	C_WEAPON_SSG08,
	C_WEAPON_ZEUSX27,
	C_WEAPON_TEC9,
	C_WEAPON_TMP,
	C_WEAPON_UMP45,
	C_WEAPON_USP,
	C_WEAPON_XM1014,

	C_WORLD,
	C_WORLD_VGUI_TEXT,

	DUST_TRAIL,
	MOVIE_EXPLOSION,
	PARTICLE_SMOKE_GRENADE,
	ROCKET_TRAIL,
	SMOKE_TRAIL,
	SPORE_EXPLOSION,
	SPORE_TRAIL
};

enum e_item_definition_index : short {
	WEAPON_NONE = 0,

	WEAPON_DESERT_EAGLE,
	WEAPON_DUAL_BERETTAS,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK18,

	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALIL_AR = 13,
	WEAPON_M249,
	WEAPON_M4A4 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_REPULSOR_DEVICE,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,

	WEAPON_PPBIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_ZEUS_X27,

	WEAPON_P2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_BALLISTIC_SHIELD,
	WEAPON_SCAR20,
	WEAPON_SG_553,
	WEAPON_SSG_08,

	WEAPON_KNIFE_GOLD,
	WEAPON_KNIFE_DEFAULT_CT,

	WEAPON_GRENADE_FLASHBANG,
	WEAPON_GRENADE_HE,
	WEAPON_GRENADE_SMOKE,
	WEAPON_GRENADE_MOLOTOV,
	WEAPON_GRENADE_DECOY,
	WEAPON_GRENADE_INCENDIARY,
	WEAPON_C4,

	ITEM_KEVLAR,
	ITEM_KEVLAR_HELMET,
	ITEM_HEAVY_ASSAULT_SUIT,
	ITEM_DEFUSE_KIT = 55,
	ITEM_RESCUE_KIT,

	WEAPON_MEDISHOT,

	WEAPON_KNIFE_DEFAULT_T = 59,
	WEAPON_M4A1S,
	WEAPON_USPS,
	WEAPON_CZ75A = 63,
	WEAPON_R8_REVOLVER,

	WEAPON_GRENADE_TA = 68,
	WEAPON_BARE_HANDS,
	WEAPON_BREACH_CHARGE,
	WEAPON_TABLET = 72,

	WEAPON_MELEE = 74,
	WEAPON_AXE,
	WEAPON_HAMMER,
	WEAPON_WRENCH = 78,
	WEAPON_KNIFE_SPECTRAL_SHIV = 80,

	WEAPON_GRENADE_FIRE_BOMB,
	WEAPON_GRENADE_DIVERSION_DEVICE,
	WEAPON_GRENADE_FRAG,
	WEAPON_SNOWBALL,
	WEAPON_BUMP_MINE,

	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_CLASSIC = 503,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_HUNTSMAN,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_SHADOW_DAGGERS,
	WEAPON_KNIFE_PARACORD,
	WEAPON_KNIFE_SURVIVAL,
	WEAPON_KNIFE_URSUS,
	WEAPON_KNIFE_NAVAJA,
	WEAPON_KNIFE_NOMAD,
	WEAPON_KNIFE_STILETTO,
	WEAPON_KNIFE_TALON,
	WEAPON_KNIFE_SKELETON = 525,

	GLOVE_BLOODHOUND = 5027,
	GLOVE_DEFAULT_T,
	GLOVE_DEFAULT_CT,
	GLOVE_SPORT,
	GLOVE_DRIVER,
	GLOVE_HAND_WRAPS,
	GLOVE_MOTO,
	GLOVE_SPECIALIST,
	GLOVE_HYDRA,

	AGENT_CT_DEFAULT,
	AGENT_T_DEFAULT,
	AGENT_T_ANARCHIST,
	AGENT_T_ANARCHIST_A,
	AGENT_T_ANARCHIST_B,
	AGENT_T_ANARCHIST_C,
	AGENT_T_ANARCHIST_D,
	AGENT_T_PIRATE,
	AGENT_T_PIRATE_A,
	AGENT_T_PIRATE_B,
	AGENT_T_PIRATE_C,
	AGENT_T_PIRATE_D,
	AGENT_T_PROFESSIONAL,
	AGENT_T_PROFESSIONAL_A,
	AGENT_T_PROFESSIONAL_B,
	AGENT_T_PROFESSIONAL_C,
	AGENT_T_PROFESSIONAL_D,
	AGENT_T_SEPARATIST,
	AGENT_T_SEPARATIST_A,
	AGENT_T_SEPARATIST_B,
	AGENT_T_SEPARATIST_C,
	AGENT_T_SEPARATIST_D,
	AGENT_CT_GIGN,
	AGENT_CT_GIGN_A,
	AGENT_CT_GIGN_B,
	AGENT_CT_GIGN_C,
	AGENT_CT_GIGN_D,
	AGENT_CT_GSG9,
	AGENT_CT_GSG9_A,
	AGENT_CT_GSG9_B,
	AGENT_CT_GSG9_C,
	AGENT_CT_GSG9_D,
	AGENT_CT_IDF,
	AGENT_CT_IDF_B,
	AGENT_CT_IDF_C,
	AGENT_CT_IDF_D,
	AGENT_CT_IDF_E,
	AGENT_CT_IDF_F,
	AGENT_CT_SWAT,
	AGENT_CT_SWAT_A,
	AGENT_CT_SWAT_B,
	AGENT_CT_SWAT_C,
	AGENT_CT_SWAT_D,
	AGENT_CT_SAS_A,
	AGENT_CT_SAS_B,
	AGENT_CT_SAS_C,
	AGENT_CT_SAS_D,
	AGENT_CT_ST6,
	AGENT_CT_ST6_A,
	AGENT_CT_ST6_B,
	AGENT_CT_ST6_C,
	AGENT_CT_ST6_D,
	AGENT_T_BALKAN,
	AGENT_T_BALKAN_A,
	AGENT_T_BALKAN_B,
	AGENT_T_BALKAN_C,
	AGENT_T_BALKAN_D,
	AGENT_T_JUMPSUIT_A,
	AGENT_T_JUMPSUIT_B,
	AGENT_T_JUMPSUIT_C,
	AGENT_T_HEAVY,
	AGENT_CT_HEAVY,

	AGENT_T_LEET_A = 5100,
	AGENT_T_LEET_B,
	AGENT_T_LEET_C,
	AGENT_T_LEET_D,
	AGENT_T_LEET_E,
	AGENT_T_ELITE_CREW_GROUND_REBEL,
	AGENT_T_ELITE_CREW_OSIRIS,
	AGENT_T_ELITE_CREW_PROF_SHAHMAT,
	AGENT_T_ELITE_CREW_MR_MUHLIK,

	AGENT_T_PHOENIX = 5200,
	AGENT_T_PHOENIX_A,
	AGENT_T_PHOENIX_B,
	AGENT_T_PHOENIX_C,
	AGENT_T_PHOENIX_D,
	AGENT_T_PHOENIX_SOLDIER,
	AGENT_T_PHOENIX_ENFORCER,
	AGENT_T_PHOENIX_SLINGSHOT,

	AGENT_CT_FBI = 5300,
	AGENT_CT_FBI_A,
	AGENT_CT_FBI_C,
	AGENT_CT_FBI_D,
	AGENT_CT_FBI_E,
	AGENT_CT_FBI_SWAT_OPERATOR,
	AGENT_CT_FBI_HRT_MARKUS_DELROW,
	AGENT_CT_FBI_SNIPER_MICHAEL_SYFERS,
	AGENT_CT_FBI_SPECIAL_AGENT_AVA,
	AGENT_CT_KSK_3RD_COMMANDO_COMPANY = 5400,

	AGENT_CT_NSWC_SEAL_TEAM_6_SOLDIER,
	AGENT_CT_NSWC_SEAL_BUCKSHOT,
	AGENT_CT_USAF_TACP_TWO_TIMES_MCCOY,
	AGENT_CT_NSWC_SEAL_LT_COMMANDER_RICKSAW,

	AGENT_T_SABRE_DRAGOMIR = 5500,
	AGENT_T_SABRE_MAXIMUS,
	AGENT_T_SABRE_REZAN_THE_READY,
	AGENT_T_SABRE_BLACKWOLF,
	AGENT_T_SABRE_THE_DOCTOR_ROMANOV,

	AGENT_CT_SAS = 5600,
	AGENT_CT_SAS_B_SQUADRON_OFFICER
};

enum e_move_type : int {
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

enum e_entity_flags {
	FL_ONGROUND		= (1 << 0),
	FL_DUCKING		= (1 << 1),
	FL_DUCKING_ANIM		= (1 << 2),
	FL_WATER_JUMP		= (1 << 3),
	FL_ON_TRAIN		= (1 << 4),
	FL_IN_RAIN		= (1 << 5),
	FL_FROZEN		= (1 << 6),
	FL_AT_CONTROLS		= (1 << 7),
	FL_CLIENT		= (1 << 8),
	FL_FAKE_CLIENT		= (1 << 9),
	FL_IN_WATER		= (1 << 10),
	FL_FLY			= (1 << 11),
	FL_SWIM			= (1 << 12),
	FL_CONVEYOR		= (1 << 13),
	FL_NPC			= (1 << 14),
	FL_GODMODE		= (1 << 15),
	FL_NO_TARGET		= (1 << 16),
	FL_AIM_TARGET		= (1 << 17),
	FL_PARTIAL_GROUND	= (1 << 18),
	FL_STATIC_PROP		= (1 << 19),
	FL_GRAPHED		= (1 << 20),
	FL_GRENADE		= (1 << 21),
	FL_STEP_MOVEMENT	= (1 << 22),
	FL_DONT_TOUCH		= (1 << 23),
	FL_BASE_VELOCITY	= (1 << 24),
	FL_WORLD_BRUSH		= (1 << 25),
	FL_OBJECT		= (1 << 26),
	FL_KILL_ME		= (1 << 27),
	FL_ON_FIRE		= (1 << 28),
	FL_DISSOLVING		= (1 << 29),
	FL_RAGDOLL		= (1 << 30),
	FL_UNBLOCKABLE		= (1 << 31)
};

enum e_life_state : int {
	LIFE_ALIVE = 0,
	LIFE_DYING,
	LIFE_DEAD,
	LIFE_RESPAWNABLE,
	LIFE_DISCARDBODY
};

enum e_observer_mode : int {
	OBS_MODE_NONE = 0,
	OBS_MODE_DEATHCAM,
	OBS_MODE_FREEZECAM,
	OBS_MODE_FIXED,
	OBS_MODE_IN_EYE,
	OBS_MODE_CHASE,
	OBS_MODE_POI,
	OBS_MODE_ROAMING
};

enum e_team_id : int {
	TEAM_UNASSIGNED = 0,
	TEAM_SPECTATOR,
	TEAM_TERRORIST,
	TEAM_COUNTER_TERRORIST
};

enum e_anim_state_poses : int {
	ACT_DIE_STAND = 953,
	ACT_DIE_STAND_HEADSHOT,
	ACT_DIE_CROUCH,
	ACT_DIE_CROUCH_HEADSHOT,
	ACT_NULL,
	ACT_DEFUSE,
	ACT_DEFUSE_WITH_KIT,
	ACT_FLASHBANG_REACTION,
	ACT_FIRE_PRIMARY,
	ACT_FIRE_PRIMARY_OPT_1,
	ACT_FIRE_PRIMARY_OPT_2,
	ACT_FIRE_SECONDARY,
	ACT_FIRE_SECONDARY_OPT_1,
	ACT_FIRE_SECONDARY_OPT_2,
	ACT_RELOAD,
	ACT_RELOAD_START,
	ACT_RELOAD_LOOP,
	ACT_RELOAD_END,
	ACT_OPERATE,
	ACT_DEPLOY,
	ACT_CATCH,
	ACT_SILENCER_DETACH,
	ACT_SILENCER_ATTACH,
	ACT_TWITCH,
	ACT_TWITCH_BUYZONE,
	ACT_PLANT_BOMB,
	ACT_IDLE_ADJUST_TURN,
	ACT_IDLE_ADJUST_STOPPEDMOVING,
	ACT_ALIVE_LOOP,
	ACT_FLINCH,
	ACT_FLINCH_HEAD,
	ACT_FLINCH_MOLOTOV,
	ACT_JUMP,
	ACT_FALL,
	ACT_CLIMB_LADDER,
	ACT_LAND_LIGHT,
	ACT_LAND_HEAVY,
	ACT_EXIT_LADDER_TOP,
	ACT_EXIT_LADDER_BOTTOM
};

enum e_anim_layer : int {
	ANIMATION_LAYER_AIMMATRIX = 0,
	ANIMATION_LAYER_WEAPON_ACTION,
	ANIMATION_LAYER_WEAPON_ACTION_RECROUCH,
	ANIMATION_LAYER_ADJUST,
	ANIMATION_LAYER_MOVEMENT_JUMP_OR_FALL,
	ANIMATION_LAYER_MOVEMENT_LAND_OR_CLIMB,
	ANIMATION_LAYER_MOVEMENT_MOVE,
	ANIMATION_LAYER_MOVEMENT_STRAFECHANGE,
	ANIMATION_LAYER_WHOLE_BODY,
	ANIMATION_LAYER_FLASHED,
	ANIMATION_LAYER_FLINCH,
	ANIMATION_LAYER_ALIVELOOP,
	ANIMATION_LAYER_LEAN,
	ANIMATION_LAYER_COUNT,
};

enum e_collision_group : int {
	COLLISION_GROUP_NONE = 0,
	COLLISION_GROUP_DEBRIS,
	COLLISION_GROUP_DEBRIS_TRIGGER,
	COLLISION_GROUP_INTERACTIVE_DEBRIS,
	COLLISION_GROUP_INTERACTIVE,
	COLLISION_GROUP_PLAYER,
	COLLISION_GROUP_BREAKABLE_GLASS,
	COLLISION_GROUP_VEHICLE,
	COLLISION_GROUP_PLAYER_MOVEMENT,
			
	COLLISION_GROUP_NPC,
	COLLISION_GROUP_IN_VEHICLE,
	COLLISION_GROUP_WEAPON,
	COLLISION_GROUP_VEHICLE_CLIP,
	COLLISION_GROUP_PROJECTILE,
	COLLISION_GROUP_DOOR_BLOCKER,
	COLLISION_GROUP_PASSABLE_DOOR,
	COLLISION_GROUP_DISSOLVING,
	COLLISION_GROUP_PUSHAWAY,

	COLLISION_GROUP_NPC_ACTOR,
	COLLISION_GROUP_NPC_SCRIPTED,

	LAST_SHARED_COLLISION_GROUP
};

enum e_effects_type : unsigned {
	EF_BONE_MERGE		= (1 << 0),
	EF_BRIGHT_LIGHT		= (1 << 1),
	EF_DIMLIGHT		= (1 << 2),
	EF_NO_INTERP		= (1 << 3),
	EF_NO_SHADOW		= (1 << 4),
	EF_NO_DRAW		= (1 << 5),
	EF_NO_RECEIVE_SHADOW	= (1 << 6),
	EF_BONEMERGE_FASTCULL	= (1 << 7),
	EF_ITEM_BLINK		= (1 << 8),
	EF_PARENT_ANIMATES	= (1 << 9),
	EF_FAST_REFLECTION	= (1 << 10),
	EF_NO_SHADOWDEPTH	= (1 << 11),
	EF_NO_SHADOWDEPTH_CACHE = (1 << 12),
	EF_NO_FLASHLIGHT	= (1 << 13),
	EF_NO_CSM		= (1 << 14)
};

enum e_eflags_type : unsigned {
	EFL_KILLME 				= (1 << 0),
	EFL_DORMANT 				= (1 << 1),
	EFL_NOCLIP_ACTIVE 			= (1 << 2),
	EFL_SETTING_UP_BONES 			= (1 << 3),
	EFL_KEEP_ON_RECREATE_ENTITIES 		= (1 << 4),
	EFL_HAS_PLAYER_CHILD 			= (1 << 4),
	EFL_DIRTY_SHADOWUPDATE 			= (1 << 5),
	EFL_NOTIFY 				= (1 << 6),
	EFL_FORCE_CHECK_TRANSMIT 		= (1 << 7),
	EFL_BOT_FROZEN 				= (1 << 8),
	EFL_SERVER_ONLY 			= (1 << 9),
	EFL_NO_AUTO_EDICT_ATTACH 		= (1 << 10),
	EFL_DIRTY_ABSTRANSFORM 			= (1 << 11),
	EFL_DIRTY_ABSVELOCITY 			= (1 << 12),
	EFL_DIRTY_ABSANGVELOCITY 		= (1 << 13),
	EFL_DIRTY_SURROUNDING_COLLISION_BOUNDS 	= (1 << 14),
	EFL_DIRTY_SPATIAL_PARTITION 		= (1 << 15),
	EFL_IN_SKYBOX 				= (1 << 17),
	EFL_USE_PARTITION_WHEN_NOT_SOLID 	= (1 << 18),
	EFL_TOUCHING_FLUID 			= (1 << 19),
	EFL_IS_BEING_LIFTED_BY_BARNACLE 	= (1 << 20),
	EFL_NO_ROTORWASH_PUSH 			= (1 << 21),
	EFL_NO_THINK_FUNCTION 			= (1 << 22),
	EFL_NO_GAME_PHYSICS_SIMULATION 		= (1 << 23),
	EFL_CHECK_UNTOUCH 			= (1 << 24),
	EFL_DONTBLOCKLOS 			= (1 << 25),
	EFL_DONTWALKON 				= (1 << 26),
	EFL_NO_DISSOLVE 			= (1 << 27),
	EFL_NO_MEGAPHYSCANNON_RAGDOLL 		= (1 << 28),
	EFL_NO_WATER_VELOCITY_CHANGE 		= (1 << 29),
	EFL_NO_PHYSCANNON_INTERACTION 		= (1 << 30),
	EFL_NO_DAMAGE_FORCES 			= (1 << 31)
};
