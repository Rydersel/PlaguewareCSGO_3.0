// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "animation_system.h"
#include "..\ragebot\aim.h"
#include "LagCompensation.hpp"
float EyeAngles[64] = { 0 };



float GetBackwardYaw(player_t* player)
{
	return math::calculate_angle(g_ctx.local()->GetAbsOrigin(), player->GetAbsOrigin()).y;
}

int DetectStand(player_t* player)
{
	Vector src3D, dst3D, forward, right, up, src, dst;
	float back_two, right_two, left_two;
	trace_t tr;
	Ray_t ray, ray2, ray3, ray4, ray5;
	CTraceFilter filter;

	math::angle_vectors(Vector(0, GetBackwardYaw(player), 0), &forward, &right, &up);

	filter.pSkip = player;
	src3D = player->get_shoot_position();
	dst3D = src3D + (forward * 384); //Might want to experiment with other numbers, incase you don't know what the number does, its how far the trace will go. Lower = shorter.

	ray.Init(src3D, dst3D);
	m_trace()->TraceRay(ray, MASK_SHOT, &filter, &tr);
	back_two = (tr.endpos - tr.startpos).Length();

	ray2.Init(src3D + right * 35, dst3D + right * 35);
	m_trace()->TraceRay(ray2, MASK_SHOT, &filter, &tr);
	right_two = (tr.endpos - tr.startpos).Length();

	ray3.Init(src3D - right * 35, dst3D - right * 35);
	m_trace()->TraceRay(ray3, MASK_SHOT, &filter, &tr);
	left_two = (tr.endpos - tr.startpos).Length();

	if (left_two > right_two)
		return -1;
	else if (right_two > left_two)
		return 1;
	else
		return 0;
}

bool DetectFake(player_t* entity)
{
	auto local = g_ctx.local();
	return local->CanSeePlayer(entity, entity->hitbox_position(HITBOX_HEAD)) && local->CanSeePlayer(entity, entity->hitbox_position(HITBOX_RIGHT_FOOT)) && !local->CanSeePlayer(entity, entity->hitbox_position(HITBOX_LEFT_FOOT)) ||
		local->CanSeePlayer(entity, entity->hitbox_position(HITBOX_HEAD)) && local->CanSeePlayer(entity, entity->hitbox_position(HITBOX_LEFT_FOOT)) && !local->CanSeePlayer(entity, entity->hitbox_position(HITBOX_RIGHT_FOOT));

}
struct {
	bool faking = false;
	bool fakewalking = false;
	bool trace = false;


}backupss;

float GetForwardYaw(player_t* player)
{
	return math::normalize_yaw(GetBackwardYaw(player) - 180.f);
}

resolver_side FreeStand(player_t* e)
{

	float angle = math::normalize_yaw(e->m_angEyeAngles().y);

	bool forward = fabsf(math::normalize_yaw(angle - GetForwardYaw(e))) < 90.f;

	auto misses = g_ctx.globals.missed_shots[e->EntIndex()];

	int S = DetectStand(e);

	bool HIGHDELTA = misses >= 3;


	switch (misses % 2)
	{
	case 0:
		if (forward)
		{
			if (S == 1)
				return HIGHDELTA ? RESOLVER_SECOND : RESOLVER_LOW_SECOND;
			else
				return HIGHDELTA ? RESOLVER_FIRST : RESOLVER_LOW_FIRST;
		}
		else
		{
			if (S == 1)
				return HIGHDELTA ? RESOLVER_FIRST : RESOLVER_LOW_FIRST;
			else
				return HIGHDELTA ? RESOLVER_SECOND : RESOLVER_LOW_SECOND;
		}
		break;
	case 1:
		if (forward)
		{
			if (S == 1)
				return HIGHDELTA ? RESOLVER_FIRST : RESOLVER_LOW_FIRST;
			else
				return HIGHDELTA ? RESOLVER_SECOND : RESOLVER_LOW_SECOND;

		}
		else
		{
			if (S == 1)
				return HIGHDELTA ? RESOLVER_SECOND : RESOLVER_LOW_SECOND;
			else
				return HIGHDELTA ? RESOLVER_FIRST : RESOLVER_LOW_FIRST;
		}
		break;
	}

}


bool ValidLBY(player_t* e, c_baseplayeranimationstate* animstate)
{
	if (e->m_vecVelocity().Length2D() > 0.1f) //moving
		return animstate->m_flTimeSinceStartedMoving < 0.22f;
	else
		return animstate->m_flTimeSinceStoppedMoving < 1.1;
}

bool CanSeeHitbox(player_t* p, int HITBOX)
{
	return g_ctx.local()->CanSeePlayer(p, p->hitbox_position(HITBOX));
}

struct {
	bool rightfoot = false;
	bool leftfoot = false;
	bool head = false;
}saw;

void resolver::initialize(player_t* e, adjust_data* record, const float& goal_feet_yaw, const float& pitch)
{
	player = e;
	player_record = record;

	original_goal_feet_yaw = math::normalize_yaw(goal_feet_yaw);
	original_pitch = math::normalize_pitch(pitch);
}

void resolver::reset()
{
	player = nullptr;
	player_record = nullptr;

	side = false;
	fake = false;

	was_first_bruteforce = false;
	was_second_bruteforce = false;

	original_goal_feet_yaw = 0.0f;
	original_pitch = 0.0f;
}

void resolver::resolve_yaw()
{
	player_info_t player_info;

	if (!m_engine()->GetPlayerInfo(player->EntIndex(), &player_info))
		return;

#if RELEASE
	if (player_info.fakeplayer || !g_ctx.local()->is_alive() || player->m_iTeamNum() == g_ctx.local()->m_iTeamNum()) //-V807
#else
	if (!g_ctx.local()->is_alive() || player->m_iTeamNum() == g_ctx.local()->m_iTeamNum())
#endif
	{
		player_record->side = RESOLVER_ORIGINAL;
		return;
	}

	if (g_ctx.globals.missed_shots[player->EntIndex()] >= 2 || g_ctx.globals.missed_shots[player->EntIndex()] && aim::get().last_target[player->EntIndex()].record.type != LBY)
	{
		switch (last_side)
		{
		case RESOLVER_ORIGINAL:
			g_ctx.globals.missed_shots[player->EntIndex()] = 0;
			fake = true;
			break;
		case RESOLVER_ZERO:
			player_record->type = BRUTEFORCE;
			player_record->side = RESOLVER_LOW_FIRST;

			was_first_bruteforce = false;
			was_second_bruteforce = false;
			return;
		case RESOLVER_FIRST:
			player_record->type = BRUTEFORCE;
			player_record->side = was_second_bruteforce ? RESOLVER_ZERO : RESOLVER_SECOND;

			was_first_bruteforce = true;
			return;
		case RESOLVER_SECOND:
			player_record->type = BRUTEFORCE;
			player_record->side = was_first_bruteforce ? RESOLVER_ZERO : RESOLVER_FIRST;

			was_second_bruteforce = true;
			return;
		case RESOLVER_LOW_FIRST:
			player_record->type = BRUTEFORCE;
			player_record->side = RESOLVER_LOW_SECOND;
			return;
		case RESOLVER_LOW_SECOND:
			player_record->type = BRUTEFORCE;
			player_record->side = RESOLVER_FIRST;
			return;
		}
	}

	auto animstate = player->get_animation_state();

	if (!animstate)
	{
		player_record->side = RESOLVER_ORIGINAL;
		return;
	}

	if (fabs(original_pitch) > 85.0f)
		fake = true;
	else if (!fake)
	{
		player_record->side = RESOLVER_ORIGINAL;
		return;
	}

	auto delta = math::normalize_yaw(player->m_angEyeAngles().y - original_goal_feet_yaw);
	auto valid_lby = true;

	if (animstate->m_velocity > 0.1f || fabs(animstate->flUpVelocity) > 100.f)
		valid_lby = animstate->m_flTimeSinceStartedMoving < 0.22f;

	if (fabs(delta) > 30.0f && valid_lby)
	{
		if (g_ctx.globals.missed_shots[player->EntIndex()])
			delta = -delta;

		if (delta > 30.0f)
		{
			player_record->type = LBY;
			player_record->side = RESOLVER_FIRST;
		}
		else if (delta < -30.0f)
		{
			player_record->type = LBY;
			player_record->side = RESOLVER_SECOND;
		}
	}
	else
	{
		auto trace = false;

		if (m_globals()->m_curtime - lock_side > 2.0f)
		{
			auto first_visible = util::visible(g_ctx.globals.eye_pos, player->hitbox_position_matrix(HITBOX_HEAD, player_record->matrixes_data.first), player, g_ctx.local());
			auto second_visible = util::visible(g_ctx.globals.eye_pos, player->hitbox_position_matrix(HITBOX_HEAD, player_record->matrixes_data.second), player, g_ctx.local());

			if (first_visible != second_visible)
			{
				trace = true;
				side = second_visible;
				lock_side = m_globals()->m_curtime;
			}
			else
			{
				auto first_position = g_ctx.globals.eye_pos.DistTo(player->hitbox_position_matrix(HITBOX_HEAD, player_record->matrixes_data.first));
				auto second_position = g_ctx.globals.eye_pos.DistTo(player->hitbox_position_matrix(HITBOX_HEAD, player_record->matrixes_data.second));

				if (fabs(first_position - second_position) > 1.0f)
					side = first_position > second_position;
			}
		}
		else
			trace = true;

		if (side)
		{
			player_record->type = trace ? TRACE : DIRECTIONAL;
			player_record->side = RESOLVER_FIRST;
		}
		else
		{
			player_record->type = trace ? TRACE : DIRECTIONAL;
			player_record->side = RESOLVER_SECOND;
		}
	}
}
float __fastcall AngleDiff(float destAngle, float srcAngle)
{
	/*float delta;

	delta = fmodf(destAngle - srcAngle, 360.0f);
	if (destAngle > srcAngle)
	{
		if (delta >= 180)
			delta -= 360;
	}
	else
	{
		if (delta <= -180)
			delta += 360;
	}
	return delta;*/
	float delta = destAngle - srcAngle;

	if (delta < -180)
		delta += 360;
	else if (delta > 180)
		delta -= 360;

	return delta;
}

//side detection inspired by ot
int resolver::sideDetect(player_t* player, adjust_data* record)
{
	int m_flSide;
	if (player->m_vecVelocity().Length2D() <= 0.1)
	{
		if (record->layers[3].m_flWeight == 0.0 && record->layers[3].m_flCycle == 0.0)
		{
			m_flSide = 2 * AngleDiff(player->get_animation_state()->m_flEyeYaw, player->get_animation_state()->m_flGoalFeetYaw) <= 0.0f ? -1 : 1;
		}
	}
	else if (!(record->layers[12].m_flWeight * 1000.0f) && (record->layers[6].m_flWeight * 1000.0f) == (player->get_animlayers()[6].m_flWeight * 1000.f))
	{
		AnimationLayer moveLayers[3][13];

		memcpy(moveLayers[0], player->get_animlayers(), sizeof(AnimationLayer) * 13);
		memcpy(moveLayers[1], player->get_animlayers(), sizeof(AnimationLayer) * 13);
		memcpy(moveLayers[2], player->get_animlayers(), sizeof(AnimationLayer) * 13);

		float DeltaFirst = abs(record->layers[6].m_flPlaybackRate - moveLayers[0][6].m_flPlaybackRate);
		float DeltaSecond = abs(record->layers[6].m_flPlaybackRate - moveLayers[2][6].m_flPlaybackRate);
		float DeltaThird = abs(record->layers[6].m_flPlaybackRate - moveLayers[1][6].m_flPlaybackRate);

		if (DeltaFirst < DeltaSecond || DeltaThird <= DeltaSecond || (DeltaSecond * 1000.0f))
		{
			if (DeltaFirst >= DeltaThird && DeltaSecond > DeltaThird && !(DeltaThird * 1000.0f))
				m_flSide = 1; // Right side
		}
		else
			m_flSide = -1; // Left side
	}

	return m_flSide;
}


float resolver::resolve_pitch()
{
	return original_pitch;
}