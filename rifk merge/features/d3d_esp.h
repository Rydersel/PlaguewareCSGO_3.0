#pragma once







#include "../../includes.hpp"
#include <mutex>
#include <rifk merge\renderer\c_font.h>

class c_esp
{
	struct player_info
	{
		CBaseHandle handle{};
		player_t* player{};
		int32_t index{};
		char name[16]{};
		Vector origin;
		Vector angles;
		std::optional<Vector> head_position;
		float duck_amount{};
		int health{}, last_health{}, health_fade{}, ammo{}, ammo_max{}, shots_missed{}, resolver_mode{};
		bool is_enemy{}, is_on_ground{}, dormant{}, reload{};
		animation_layers layers{};
		matrix3x4_t bones[128]{};
		bool good_bones{};
		bool b_kevlar{};
		bool b_helmet{};
		bool b_defusing{};
		bool b_scoped{};
		weapon_t* pWeapon;
	};
	struct nade_info
	{
		int32_t type;
		Vector origin;
	};
	struct esp_info
	{
		esp_info() { }  // NOLINT(hicpp-use-equals-default, modernize-use-equals-default)

		std::vector<player_info> players;
		std::vector<nade_info> nades;
		Vector shoot_position{};
		bool is_scoped{};
		viewmatrix world_to_screen_matrix{};
		std::mutex mutex;
	};
public:
	static void clear_dmg();
	//static void adddmg(c_game_event* event);
	//static void AddShot(c_cs_player* target, int type);
	static void draw_health_effect(player_t* target, bool when_hit = false, bool when_kill = false);
	static void show_lag_hitbox(player_t* target);
	static void dark_mode();
	static void draw();
	static void draw_spectators();
	
	static bool draw_valid_visual_player(player_t* e, bool check_team, bool check_dormant);

	static void store_data();

	inline static esp_info info;
private:
	static constexpr auto esp_flags = c_font::font_flags::centered_x | c_font::font_flags::centered_y | c_font::font_flags::drop_shadow;
	static constexpr auto collision_box_top = 72.f;
	static constexpr auto collision_box_mod = 18.f;
	static constexpr auto head_radius = 6.5f;
	static constexpr auto fade_frequency = 255 / 1.f;

	static void esp_name(player_info& player, const Vector2D& from, float width, const Color& color);
	static void esp_box(const Vector2D& from, float width, float height, const Color& color);
	static void esp_health(player_info& player, const Vector2D& from, float height, const Color& color, bool should_devide);
	static void esp_armor(player_info& player, const Vector2D& from, const float height, const Color& color, bool should_devide);
	static void draw_player_flags(player_info& player, const Vector2D& from, const float width, const float height, const Color& color);
	static void esp_ammo(player_info& player, const Vector2D& from, float width, float height, const Color& color);


	static void esp_weapon(player_info& player, const Vector2D& from, const float width, const float height, const Color& color, bool drawing_ammo);

	static void esp_radar(std::optional<Vector> position, const Color& color);
	static void esp_skeleton(player_info& player, const Color& color, bool retro = false);

	static void draw_player(player_info& player);

	static void draw_dmg();
	static void draw_players();
	static void draw_recoilcrosshair();

	static void draw_nade(nade_info& nade);
	static void draw_nades();
	static void draw_debug();
	static void pen_crosshair();
	static void Fonts(HWND window, IDirect3DDevice9* pDevice);
	static void draw_scope();
	static void draw_impact(Vector start, Vector end, Color color);
};




inline c_esp d3d_shonax_esp;

//later
//
//
//class c_nadepoint {
//public:
//	c_nadepoint() {
//		m_valid = false;
//	}
//
//	c_nadepoint(c_vector3d start, c_vector3d end, bool plane, bool valid, c_vector3d normal, bool detonate) {
//		m_start = start;
//		m_end = end;
//		m_plane = plane;
//		m_valid = valid;
//		m_normal = normal;
//		m_detonate = detonate;
//	}
//
//	c_vector3d m_start, m_end, m_normal;
//	bool m_valid, m_plane, m_detonate;
//};
//
//enum nade_throw_act {
//	ACT_NONE,
//	ACT_THROW,
//	ACT_LOB,
//	ACT_DROP
//};
//
//class c_nade_prediction {
//	std::array< c_nadepoint, 500 >	_points{ };
//	bool		 _predicted = false;
//
//	void predict(c_user_cmd* ucmd, c_cs_player* local);
//	bool detonated(c_base_combat_weapon* weapon, float time, game_trace& trace);
//public:
//	void trace(c_user_cmd* ucmd, c_cs_player* local);
//	void draw();
//};
//
//extern c_nade_prediction g_nadepred;