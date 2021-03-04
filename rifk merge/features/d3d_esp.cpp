#include "d3d_esp.h"
#include <rifk merge\renderer\c_renderer.h>

static const float pif = 3.141593f;
#define rad2deg(x) ((float)(x) * (float)(180.f / pif))
#define deg2rad(x) ((float)(x) * (float)(pif / 180.f))

static auto linear_fade = [](int32_t& current, const int32_t min, const int32_t max, const float frequency, const bool direction) -> void
{
	if (current < max && direction)
		current += static_cast<int>(std::ceil(frequency * m_globals()->m_frametime));
	else if (current > min && !direction)
		current -= static_cast<int>(std::ceil(frequency * m_globals()->m_frametime));

	current = std::clamp(current, min, max);
};


enum class hitbox
{
	head,
	neck,
	pelvis,
	body,
	thorax,
	chest,
	upper_chest,
	left_thigh,
	right_thigh,
	left_calf,
	right_calf,
	left_foot,
	right_foot,
	left_hand,
	right_hand,
	left_upper_arm,
	left_forearm,
	right_upper_arm,
	right_forearm,
	max
};

float esp_alpha_fade[64];
float plerp(float t, float a, float b) {
	return (1 - t) * a + t * b;
}
void c_esp::draw()
{
	if (!m_engine()->IsInGame())
	{
		if (!info.players.empty() || info.players.size() > 0)
			info.players.clear();

		return;
	}

	//std::scoped_lock<std::mutex> lock(info.mutex);

	//draw_dmg();
	draw_players();
	draw_nades();
	draw_debug();
	draw_scope();

}


void IClientEntityList::for_each_player(const std::function<void(player_t*)> fn)
{
	for (auto i = 0; i <= static_cast<int32_t>(m_engine()->GetMaxClients()); ++i) {
		const auto entity = reinterpret_cast<player_t*>(GetClientEntity(i));
		if (entity && entity->is_player())
			fn(reinterpret_cast<player_t*>(entity));
	}
}



bool c_esp::draw_valid_visual_player(player_t* e, bool check_team, bool check_dormant)
{
	if (!e) { return false; }

	if (e->IsDormant() && check_dormant) { return false; }

	if (!e->is_alive()) { return false; }

	if (!e->is_player()) { return false; }

	return true;
}

void c_esp::store_data()
{
	info.players.clear();
	info.players.reserve(64);

	if (!m_engine()->IsInGame())
		return;

	//std::scoped_lock<std::mutex> lock(info.mutex);

	info.world_to_screen_matrix = d3d_shonax_render.world_to_screen_matrix();

	static bool is_esp_checked = true;

	m_entitylist()->for_each_player([&](player_t* player) -> void
		{
			if (!draw_valid_visual_player(player, false, !is_esp_checked))
				return;

			//const auto anim_info = animation_system->get_animation_info(player);

			player_info current;
			current.handle = player->GetRefEHandle();
			current.player = player;
			current.index = player->EntIndex();

			memcpy(current.name, player->get_info().szName, 15);
			current.name[15] = '\0';
			current.origin = player->GetAbsOrigin();
			current.angles = player->GetAbsAngles();
			current.duck_amount = player->m_flDuckAmount();
			current.health = std::clamp(player->m_iHealth(), 0, 100);
			current.is_enemy = player->is_enemy();
			current.is_on_ground = player->is_on_ground();
			current.dormant = player->IsDormant();
			current.layers = *player->get_animation_layers();
			//current.reload = player->get_sequence_activity(current.layers[1].m_nSequence) == act_csgo_reload;
			current.good_bones = player->setup_bones_fixed(current.bones, BONE_USED_BY_ANYTHING);
			current.head_position = player->get_hitbox_position(0, current.bones);

			current.b_kevlar = player->m_ArmorValue() > 0;
			current.b_helmet = player->m_bHasHelmet();
			current.b_defusing = player->m_bIsDefusing();
			current.b_scoped = player->m_bIsScoped();

			//if (anim_info)
			//{
			//	current.shots_missed = anim_info->missed_due_to_resolver + anim_info->missed_due_to_spread;
			//
			//	switch (anim_info->brute_state)
			//	{
			//	case resolver_start:
			//		current.resolver_mode = 0;
			//		break;
			//	case resolver_inverse:
			//		current.resolver_mode = 1;
			//		break;
			//	case resolver_no_desync:
			//		current.resolver_mode = 2;
			//		break;
			//	default:
			//	case resolver_jitter:
			//		current.resolver_mode = 3;
			//		break;
			//	}
			//}

			const auto weapon = player->m_hActiveWeapon().Get();

			if (weapon)
			{
				const auto info = weapon->get_csweapon_info();
				current.ammo = weapon->m_iClip1();
				current.ammo_max = info->iMaxClip1;
				current.pWeapon = weapon;
			}
			else
			{
				current.pWeapon = nullptr;
				current.ammo = 0;
				current.ammo_max = 1;
			}

			info.players.push_back(current);
		});

	info.nades.clear();

	//client_entity_list()->for_each([](c_client_entity* entity) -> void {
	//	static const auto is_nade_projectile = [](uint32_t id) {
	//		switch (id) {
	//		case cbasecsgrenadeprojectile:
	//		case cdecoyprojectile:
	//		case csmokegrenadeprojectile:
	//		case cmolotovprojectile:
	//			return true;
	//		default:
	//			return false;
	//		}
	//	};
	//
	//	const auto base = reinterpret_cast<c_base_combat_weapon*>(entity);
	//
	//	if (!is_nade_projectile(base->get_class_id()))
	//		return;
	//
	//	nade_info current;
	//	current.origin = base->get_render_origin();
	//	current.type = base->get_class_id();
	//	info.nades.push_back(current);
	//	});
	//
	//const auto local = c_cs_player::get_local_player();

	if (!g_ctx.local())
		return;

	info.shoot_position = g_ctx.local()->get_shoot_position();
	info.is_scoped = g_ctx.local()->m_bIsScoped();
}

void c_esp::draw_players()
{
	if (info.players.empty())
		return;

	for (auto& player : info.players)
		draw_player(player);
}

void c_esp::draw_nade(nade_info& nade)
{

	//if (!config.esp.nade_esp_t)
	//	return;
	//
	//c_vector2d origin_screen;
	//
	//if (!renderer->screen_transform(nade.origin, origin_screen, info.world_to_screen_matrix))
	//	return;
	//
	//static const auto get_nade_string = [](int32_t definition) {
	//	switch (definition)
	//	{
	//	case cbasecsgrenadeprojectile:
	//		return std::string(_("GRENADE"));
	//	case cdecoyprojectile:
	//		return std::string(_("DECOY"));
	//	case csmokegrenadeprojectile:
	//		return std::string(_("SMOKE"));
	//	case cmolotovprojectile:
	//		return std::string(_("FIRE-BOMB"));
	//	default:
	//		return std::string();
	//	}
	//};
	//
	//if (config.esp.nade_esp_t == 2)
	//{
	//	c_vector3d forward;
	//	math::angle_vectors(engine_client()->get_view_angles(), forward);
	//	const auto transform = math::rotation_matrix(forward);
	//	renderer->ball(nade.origin, 6.f, transform, config.esp.nade_color, info.world_to_screen_matrix);
	//}
	//
	//renderer->text(origin_screen - c_vector2d(0, 18), get_nade_string(nade.type).c_str(), config.esp.nade_color, fnv1a("pro13"), esp_flags);
}

void c_esp::draw_debug()
{

}

void c_esp::draw_nades()
{
	for (auto& nade : info.nades)
		draw_nade(nade);
}

void c_esp::draw_scope()
{
	//if (!g_cfg.misc.no_scope || !info.is_scoped)
	//	return;
	//
	//const auto center = d3d_shonax_render.get_center();
	//d3d_shonax_render.line({ center.x, 0 }, { center.x, 2.f * center.y }, Color(0, 0, 0));
	//d3d_shonax_render.line({ 0, center.y }, { 2.f * center.x, center.y }, Color(0, 0, 0));

}


void c_esp::esp_name(player_info& player, const Vector2D& from, const float width, const Color& color)
{
	d3d_shonax_render.text(from + Vector2D(width / 2.f, -9.f), player.name, color, fnv1a("name_font"), esp_flags);
}

void c_esp::esp_box(const Vector2D& from, const float width, const float height, const Color& color)
{
	d3d_shonax_render.rect(from - Vector2D(1, 1), Vector2D(width + 2, height + 2), Color(0, 0, 0, color.a()));
	d3d_shonax_render.rect(from + Vector2D(1, 1), Vector2D(width - 2, height - 2), Color(0, 0, 0, color.a()));
	d3d_shonax_render.rect(from, Vector2D(width, height), color);
}

void c_esp::draw_player_flags(player_info& player, const Vector2D& from, const float width, const float height, const Color& color)
{

	//Do all player flags inside of this
	int _x = from.x + width + 5, _y = from.y + 2;

	auto draw_flag = [&](Color color, const char* text, ...) -> void
	{
		d3d_shonax_render.text(Vector2D(_x, _y), text, color, fnv1a("pro13"), c_font::centered_y | c_font::font_flags::drop_shadow);
		_y += 8;
	};

	std::string text;

	if (player.b_helmet) text += "H";
	if (player.b_kevlar) text += "K";

	if (player.b_kevlar || player.b_helmet) // just flags
	{
		if (g_cfg.d3d_esp.enemy_flags.kevlar)
		{
			draw_flag(Color(g_cfg.d3d_esp.esp_color_e.r(), g_cfg.d3d_esp.esp_color_e.g(), g_cfg.d3d_esp.esp_color_e.b(), int(255 * esp_alpha_fade[player.index])), text.c_str());
		}
	}

	if (g_cfg.d3d_esp.enemy_flags.zoom) // cheat flags
	{
		if (player.b_scoped)
			draw_flag(Color(g_cfg.d3d_esp.esp_color_e.r(), g_cfg.d3d_esp.esp_color_e.g(), g_cfg.d3d_esp.esp_color_e.b(), int(255 * esp_alpha_fade[player.index])), "ZOOM");

		//if (player.reload && player.layers[1].cycle < 0.99f)
		//	draw_flag(Color(config.esp.esp_color_e.red, config.esp.esp_color_e.green, config.esp.esp_color_e.blue, int(255 * esp_alpha_fade[player.index])), "RELOAD");

		if (player.b_defusing)
			draw_flag(Color(g_cfg.d3d_esp.esp_color_e.r(), g_cfg.d3d_esp.esp_color_e.g(), g_cfg.d3d_esp.esp_color_e.b(), int(255 * esp_alpha_fade[player.index])), "DEFUSE");

	}
}



void c_esp::esp_health(player_info& player, const Vector2D& from, const float height, const Color& color, bool should_devide)
{
	// grey background
	d3d_shonax_render.rect_filled_linear_gradient(Vector2D(from.x - 8, from.y),
		Vector2D(4, height), Color(20, 20, 20, int(200 * esp_alpha_fade[player.index])), Color(80, 80, 80, int(200 * esp_alpha_fade[player.index])));

	const auto health_removed = 100 - player.health;
	const auto health_scaled = static_cast<float>(health_removed) / 100.f * height;

	// actual health
	d3d_shonax_render.rect_filled_linear_gradient(Vector2D(from.x - 8, from.y + health_scaled),
		Vector2D(4, height - health_scaled), Color(50, 150, 50, int(200 * esp_alpha_fade[player.index])), color);

	if (player.health != player.last_health && player.health_fade == 0)
	{
		player.last_health = player.health;
		player.health_fade = 255;
	}
	else if (player.health == player.last_health && health_removed > 0)
	{
		d3d_shonax_render.rect_filled(Vector2D(from.x - 8, from.y + health_scaled - 2),
			Vector2D(4, 2), Color(200, 200, 200, int(255 * esp_alpha_fade[player.index])));
	}
	else if (player.health != player.last_health)
	{
		linear_fade(player.health_fade, 0, 255, fade_frequency, false);

		const auto damage = static_cast<float>(player.last_health - player.health) / 100.f * height;

		// draw white filled rect
		d3d_shonax_render.rect_filled_linear_gradient(Vector2D(from.x - 8, from.y - damage + health_scaled),
			Vector2D(4, damage), Color(150, 150, 150, int(200 * esp_alpha_fade[player.index])),
			Color(225, 225, 225, int(200 * esp_alpha_fade[player.index])));
	}

	// black outline
	d3d_shonax_render.rect(Vector2D(from.x - 8, from.y),
		Vector2D(4, height), Color(0, 0, 0, int(255 * esp_alpha_fade[player.index])));
}


void c_esp::esp_armor(player_info& player, const Vector2D& from, const float height, const Color& color, bool should_devide)
{
	//#ifdef PRINT_DEBUG
	//	printf("esp_armor \n");
	//#endif
	//	// grey background
	//	//renderer->rect_filled_linear_gradient(c_vector2d(from.x - 8, from.y), c_vector2d(4, height), c_color(20, 20, 20, 200), c_color(80, 80, 80, 200));
	//	float addshit = config.esp.enemy.health ? 12 : 6;
	//	const auto health_removed = 100 - player.player->get_armor();
	//	const auto health_scaled = static_cast<float>(health_removed) / 100.f * (height + 2);
	//	auto c = config.esp.armor_color;
	//	int Red =  c.red;
	//	int Green = c.green;
	//	renderer->rect_filled(c_vector2d(from.x - addshit, from.y - 1), c_vector2d(3, height + 2), c_color(0, 0, 0, 100 * esp_alpha_fade[player.index]));
	//
	//	
	//	renderer->rect_filled(c_vector2d(from.x - addshit, from.y - 1 + health_scaled), c_vector2d(3, height + 2 - health_scaled), c_color(Red, Green, c.blue, (255 * esp_alpha_fade[player.index])));
	//
	//	
	//	renderer->rect(c_vector2d(from.x - addshit, from.y - 1), c_vector2d(3, height + 2), c_color(0, 0, 0, 255 * esp_alpha_fade[player.index]));
	//
}


void c_esp::esp_ammo(player_info& player, const Vector2D& from, const float width, const float height, const Color& color)
{
	if ((player.ammo <= 0 || player.ammo_max <= 1) && !player.reload)
		return;

	// grey background
	d3d_shonax_render.rect_filled_linear_gradient(Vector2D(from.x, from.y + height + 4),
		Vector2D(width, 4), Color(20, 20, 20, int(200 * esp_alpha_fade[player.index])), Color(80, 80, 80, int(200 * esp_alpha_fade[player.index])));
	
	auto ammo = static_cast<float>(player.ammo) / static_cast<float>(player.ammo_max)* width;
	
	if (player.reload && player.layers[1].m_flCycle > 0.f)
		ammo = player.layers[1].m_flCycle * width;
	
	// actual health
	d3d_shonax_render.rect_filled_linear_gradient(Vector2D(from.x, from.y + height + 4),
		Vector2D(ammo, 4), color, Color(210, 190, 40, int(color.a() * esp_alpha_fade[player.index])), true);
	
	// black outline
	d3d_shonax_render.rect(Vector2D(from.x, from.y + height + 4),
		Vector2D(width, 4), Color(0, 0, 0, int(255 * esp_alpha_fade[player.index])));
}


void c_esp::esp_radar(std::optional<Vector> position, const Color& color)
{
	if (!position.has_value())
		return;

	const auto local = g_ctx.local();

	if (!local)
		return;

	const auto view = m_engine()->get_view_angles();
	const auto angle_to = math::calculate_angle(info.shoot_position, position.value());
	auto target_angle = angle_to - view;
	math::normalize(target_angle);

	const auto angle = target_angle.y;
	const auto height = 400.f;

	const auto a = d3d_shonax_render.get_center() - Vector2D(
		(height - 20) * sin(deg2rad(angle + 2)),
		(height - 20) * cos(deg2rad(angle + 2))
	);

	const auto b = d3d_shonax_render.get_center() - Vector2D(
		height * sin(deg2rad(angle)),
		height * cos(deg2rad(angle))
	);

	const auto c = d3d_shonax_render.get_center() - Vector2D(
		(height - 20) * sin(deg2rad(angle - 2)),
		(height - 20) * cos(deg2rad(angle - 2))
	);

	d3d_shonax_render.triangle_filled_linear_gradient(a, b, c, Color(40, 40, 40, color.a()), color, color);
	d3d_shonax_render.triangle(a, b, c, Color(0, 0, 0, color.a()));
}

void c_esp::esp_skeleton(player_info& player, const Color& color, const bool retro)
{
	Vector2D bone, bone_parent;

	//const auto entity = reinterpret_cast<c_cs_player*>(client_entity_list()->get_client_entity(player.index));
	//if (!entity)
	//	return;
	//
	//const auto model = entity->get_model();
	//if (!model)
	//	return;
	//
	//const auto studio_model = model_info_client()->get_studio_model(model);
	//
	//if (!studio_model)
	//	return;
	//
	//if (!player.good_bones)
	//	return;
	//
	//const auto head_id = retro ? entity->get_hitbox_bone_attachment(c_cs_player::hitbox::head) : std::nullopt;
	//const auto left_hand_id = retro ? entity->get_hitbox_bone_attachment(c_cs_player::hitbox::left_hand) : std::nullopt;
	//const auto right_hand_id = retro ? entity->get_hitbox_bone_attachment(c_cs_player::hitbox::right_hand) : std::nullopt;
	//
	//for (auto i = 0; i < studio_model->numbones; i++)
	//{
	//	if (head_id.has_value() && head_id.value() == i)
	//		continue;
	//
	//	const auto p_bone = studio_model->get_bone(i);
	//	if (!p_bone || p_bone->parent == -1)
	//		continue;
	//
	//	if ((!p_bone->has_parent(studio_model, left_hand_id.value_or(-2))
	//		&& !p_bone->has_parent(studio_model, right_hand_id.value_or(-2)))
	//		|| !retro)
	//		if (!(p_bone->flags & bone_used_by_hitbox))
	//			continue;
	//
	//	if (!renderer->screen_transform(c_vector3d(player.bones[i][0][3], player.bones[i][1][3], player.bones[i][2][3]), bone,
	//		info.world_to_screen_matrix) || !renderer->screen_transform(c_vector3d(player.bones[p_bone->parent][0][3],
	//			player.bones[p_bone->parent][1][3], player.bones[p_bone->parent][2][3]), bone_parent, info.world_to_screen_matrix))
	//		continue;
	//
	//	renderer->line(bone, bone_parent, color);
	//}
	//
	//if (retro && player.head_position.has_value())
	//{
	//	c_vector3d forward;
	//	math::angle_vectors(player.angles, forward);
	//	const auto transform = math::rotation_matrix(forward);
	//	renderer->ball(player.head_position.value(), head_radius, transform,
	//		color, info.world_to_screen_matrix);
	//}
}



void c_esp::esp_weapon(player_info& player, const Vector2D& from, const float width, const float height, const Color& color, bool draw_ammo)
{
	if (!player.pWeapon)
		return;

	bool IsAmmoDrawing = (player.ammo <= 0 || player.ammo_max <= 1) && !player.reload;
	float additive = 9;
	if (IsAmmoDrawing && g_cfg.d3d_esp.health_bar_t == 2) additive += 9;
	d3d_shonax_render.text(Vector2D(from.x + (width / 2), from.y + height + additive + 3), player.pWeapon->get_name().c_str(), color, fnv1a("pro12"), esp_flags);
}

void c_esp::draw_player(player_info& player)
{
	if (!player.head_position.has_value())
		return;

	// crashfix, do not remove 
	// ^^-- nice you dont fucking say ocorn! fucking genius --^^ -- loki was here
	if (!m_engine()->IsInGame() || !m_engine()->IsConnected())
		return;

	if (!player.is_enemy)
		return;

	int idx = player.index;

	float in = (1.f / 0.2f) * m_globals()->m_frametime;
	float out = (1.f / 2.f) * m_globals()->m_frametime;

	if (!player.dormant)
	{
		if (esp_alpha_fade[idx] < 1.f)
			esp_alpha_fade[idx] += in;
	}
	else
	{
		if (esp_alpha_fade[idx] > 0.f)
			esp_alpha_fade[idx] -= out;
	}

	esp_alpha_fade[idx] = (esp_alpha_fade[idx] > 1.f ? 1.f : esp_alpha_fade[idx] < 0.f ? 0.f : esp_alpha_fade[idx]);

	const auto& esp = g_cfg.d3d_esp.enemy;

	const auto& esp_main = g_cfg.d3d_esp;

	Vector2D origin_screen, top_screen;
	Color set_color = Color(g_cfg.d3d_esp.esp_color_e.r(), g_cfg.d3d_esp.esp_color_e.g(), g_cfg.d3d_esp.esp_color_e.b(), int(g_cfg.d3d_esp.esp_color_e.a() * esp_alpha_fade[idx]));

	const auto collision_box_interpolated = collision_box_top - collision_box_mod * player.duck_amount;

	const auto view_height = player.head_position.value().z - player.origin.z;

	auto top = player.origin + Vector(0.f, 0.f, collision_box_interpolated);

	if (view_height == 46.f && !player.is_on_ground)
		top = player.head_position.value_or(Vector()) + Vector(0.f, 0.f, 9.f);

	if (g_cfg.d3d_esp.out_of_fov_e_t == 2)
		esp_radar(player.head_position, set_color);

	if (!d3d_shonax_render.screen_transform(player.origin, origin_screen, info.world_to_screen_matrix)
		|| !d3d_shonax_render.screen_transform(top, top_screen, info.world_to_screen_matrix))
	{
		if (g_cfg.d3d_esp.out_of_fov_e_t == 1)
			esp_radar(player.head_position, set_color);
		return;
	}

	const auto height = origin_screen.y - top_screen.y + 6;
	const auto width = height / 1.9f;
	const auto from = Vector2D(top_screen.x - width / 2.f, top_screen.y);

	//auto scale_and_draw = [](player_t* entity, hitbox hitbox, float point_scale, matrix3x4* bones_t)
	//{
	//	if (!entity)
	//		return;
	//
	//	c_vector3d scaled[7] = { };
	//	c_vector2d scaled_screenspace[7] = { };
	//	auto hitbox_pos = entity->get_hitbox_position(hitbox, bones_t);
	//
	//	if (!hitbox_pos.has_value())
	//		return;
	//
	//	std::fill_n(scaled, 7, hitbox_pos.value());
	//
	//	scaled[1][2] += point_scale;
	//	scaled[2][2] -= point_scale;
	//	scaled[3][1] -= point_scale;
	//	scaled[4][1] += point_scale;
	//
	//	int max_num = hitbox == hitbox::head ? 3 : 5;
	//
	//	for (int i = 0; i < max_num; i++)
	//	{
	//		if (!d3d_shonax_render.screen_transform(scaled[i], scaled_screenspace[i], info.world_to_screen_matrix))
	//			return;
	//
	//		d3d_shonax_render.rect(c_vector2d((int)scaled_screenspace[i].x - 2, (int)scaled_screenspace[i].y - 2), c_vector2d(4, 4), c_color(255, 0, 0, 255 * esp_alpha_fade[entity->index()]));
	//	}
	//};

	if (g_cfg.d3d_esp.out_of_fov_e_t == 1 && !d3d_shonax_render.is_on_screen(
		player.head_position.value_or(player.origin), width, info.world_to_screen_matrix))
		esp_radar(player.head_position, set_color);

	if (g_cfg.d3d_esp.skeleton_e_t)
		esp_skeleton(player, set_color, g_cfg.d3d_esp.skeleton_e_t == 2);

	if (esp.box)
		esp_box(from, width, height, set_color);

	if (g_cfg.d3d_esp.health_bar_t == 1 || g_cfg.d3d_esp.health_bar_t == 2)
		esp_health(player, from, height, set_color, false);

	if (g_cfg.d3d_esp.health_bar_t == 2)
		esp_ammo(player, from, width, height, set_color);

	if (esp.name)
		esp_name(player, from, width, set_color);

	if (esp.weapon)
		esp_weapon(player, from, width, height, set_color, esp.ammo);

	if (esp.flags)
		draw_player_flags(player, from, width, height, set_color);


	//if (config.esp.multipoint)
	//{
	//	c_cs_player::hitbox hitboxes[] = { c_cs_player::hitbox::head, c_cs_player::hitbox::pelvis, c_cs_player::hitbox::chest, c_cs_player::hitbox::thorax, c_cs_player::hitbox::left_thigh, c_cs_player::hitbox::right_thigh, c_cs_player::hitbox::left_foot, c_cs_player::hitbox::right_foot , c_cs_player::hitbox::right_upper_arm, c_cs_player::hitbox::left_upper_arm };
	//
	//	for (int i = 0; i < _ARRAYSIZE(hitboxes); i++)
	//	{
	//		float pointscale = i == 0 ? 1.5f : 4.f;
	//		scale_and_draw(player.player, hitboxes[i], pointscale, player.bones);
	//	}
	//}
}
