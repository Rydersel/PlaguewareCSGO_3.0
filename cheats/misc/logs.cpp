// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "logs.h"
#include "../eventlog.h"

void eventlogs::paint_traverse()
{
	if (logs.empty())
		return;

	while (logs.size() > 10)
		logs.pop_back();

	auto last_y = 146;
	
	for (size_t i = 0; i < logs.size(); i++)
	{
		auto& log = logs.at(i);

		if (util::epoch_time() - log.log_time > 4600) 
		{
			auto factor = log.log_time + 5000.0f - (float)util::epoch_time();
			factor *= 0.001f;

			auto opacity = (int)(255.0f * factor);

			if (opacity < 2)
			{
				logs.erase(logs.begin() + i);
				continue;
			}

			log.color.SetAlpha(opacity);
			log.y -= factor * 1.25f;
		}

		last_y -= 14;

		auto logs_size_inverted = 10 - logs.size();
		render::get().text(fonts[LOGS], log.x, last_y + log.y - logs_size_inverted * 14, log.color, HFONT_CENTERED_NONE, log.message.c_str());
	}
}

void eventlogs::events(IGameEvent* event) 
{
	static auto get_hitgroup_name = [](int hitgroup) -> std::string
	{
		switch (hitgroup)
		{
		case HITGROUP_HEAD:
			return crypt_str("head");
		case HITGROUP_CHEST:
			return crypt_str("chest");
		case HITGROUP_STOMACH:
			return crypt_str("stomach");
		case HITGROUP_LEFTARM:
			return crypt_str("left arm");
		case HITGROUP_RIGHTARM:
			return crypt_str("right arm");
		case HITGROUP_LEFTLEG:
			return crypt_str("left leg");
		case HITGROUP_RIGHTLEG:
			return crypt_str("right leg");
		default:
			return crypt_str("generic");
		}
	};


	if (g_cfg.misc.events_to_log[EVENTLOG_VOTE] && !strcmp(event->GetName(), crypt_str("vote_cast")))
	{
		auto userid = event->GetInt(crypt_str("entityid"));

		player_info_t userid_info;

		if (!m_engine()->GetPlayerInfo(userid, &userid_info))
			return;

		std::stringstream ss;
		ss << userid_info.szName << crypt_str(" Voted: ") << (event->GetInt(crypt_str("vote_option")) == 0 ? crypt_str("YES") : crypt_str("NO"));

		add(ss.str());

	}
	if (g_cfg.misc.events_to_log[EVENTLOG_HIT] && !strcmp(event->GetName(), crypt_str("player_hurt")))
	{
		auto userid = event->GetInt(crypt_str("userid")), attacker = event->GetInt(crypt_str("attacker"));

		if (!userid || !attacker) 
			return;

		auto userid_id = m_engine()->GetPlayerForUserID(userid), attacker_id = m_engine()->GetPlayerForUserID(attacker); //-V807

		player_info_t userid_info, attacker_info;

		if (!m_engine()->GetPlayerInfo(userid_id, &userid_info)) 
			return;

		if (!m_engine()->GetPlayerInfo(attacker_id, &attacker_info)) 
			return;

		auto m_victim = static_cast<player_t *>(m_entitylist()->GetClientEntity(userid_id));
		

		std::stringstream ss;

		if (attacker_id == m_engine()->GetLocalPlayer() && userid_id != m_engine()->GetLocalPlayer()) 
		{
			ss << crypt_str("Hit ") << userid_info.szName << crypt_str(" in the ") << get_hitgroup_name(event->GetInt(crypt_str("hitgroup"))) << crypt_str(" for ") << event->GetInt(crypt_str("dmg_health"));
			ss << crypt_str(" damage (") << event->GetInt(crypt_str("health")) << crypt_str(" health remaining)");

			add(ss.str());
		}
		else if (userid_id == m_engine()->GetLocalPlayer() && attacker_id != m_engine()->GetLocalPlayer()) 
		{
			ss << crypt_str("Take ") << event->GetInt(crypt_str("dmg_health")) << crypt_str(" damage from ") << attacker_info.szName << crypt_str(" in the ") << get_hitgroup_name(event->GetInt(crypt_str("hitgroup")));
			ss << crypt_str(" (") << event->GetInt(crypt_str("health")) << crypt_str(" health remaining)");

			add(ss.str());
		}
	}

	if (g_cfg.misc.events_to_log[EVENTLOG_ITEM_PURCHASES] && !strcmp(event->GetName(), crypt_str("item_purchase")))
	{
		auto userid = event->GetInt(crypt_str("userid"));

		if (!userid) 
			return;

		auto userid_id = m_engine()->GetPlayerForUserID(userid);

		player_info_t userid_info;

		if (!m_engine()->GetPlayerInfo(userid_id, &userid_info)) 
			return;

		auto m_player = static_cast<player_t *>(m_entitylist()->GetClientEntity(userid_id));

		if (!g_ctx.local() || !m_player) 
			return;

		if (g_ctx.local() == m_player)
			g_ctx.globals.should_buy = 0;

		if (m_player->m_iTeamNum() == g_ctx.local()->m_iTeamNum()) 
			return;

		std::string weapon = event->GetString(crypt_str("weapon"));
		
		std::stringstream ss;
		ss << userid_info.szName << crypt_str(" bought ") << weapon;

		add(ss.str());
	}

	if (g_cfg.misc.events_to_log[EVENTLOG_BOMB] && !strcmp(event->GetName(), crypt_str("bomb_beginplant")))
	{
		auto userid = event->GetInt(crypt_str("userid"));

		if (!userid) 
			return;

		auto userid_id = m_engine()->GetPlayerForUserID(userid);

		player_info_t userid_info;

		if (!m_engine()->GetPlayerInfo(userid_id, &userid_info)) 
			return;

		auto m_player = static_cast<player_t *>(m_entitylist()->GetClientEntity(userid_id));

		if (!m_player) 
			return;

		std::stringstream ss;
		ss << userid_info.szName << crypt_str(" has began planting the bomb");

		add(ss.str());
	}

	if (g_cfg.misc.events_to_log[EVENTLOG_BOMB] && !strcmp(event->GetName(), crypt_str("bomb_begindefuse")))
	{
		auto userid = event->GetInt(crypt_str("userid"));

		if (!userid) 
			return;

		auto userid_id = m_engine()->GetPlayerForUserID(userid);

		player_info_t userid_info;

		if (!m_engine()->GetPlayerInfo(userid_id, &userid_info)) 
			return;

		auto m_player = static_cast<player_t *>(m_entitylist()->GetClientEntity(userid_id));

		if (!m_player) 
			return;

		std::stringstream ss;
		ss << userid_info.szName << crypt_str(" has began defusing the bomb ") << (event->GetBool(crypt_str("haskit")) ? crypt_str("with defuse kit") : crypt_str("without defuse kit"));

		add(ss.str());
	}
}

void eventlogs::add(std::string text, bool full_display)
{
	
	Game_Msg(text.c_str()); 
	
	
	
	logs.emplace_front(loginfo_t(util::epoch_time(), text, g_cfg.misc.log_color));

	if (!full_display)
		return;

	if (g_cfg.misc.log_output[EVENTLOG_OUTPUT_CONSOLE])
	{
		last_log = true;

#if RELEASE
#if BETA
		m_cvar()->ConsoleColorPrintf(g_cfg.misc.log_color, crypt_str("[ Plagueware] ")); //-V807
#else
		m_cvar()->ConsoleColorPrintf(g_cfg.misc.log_color, crypt_str("[ Plagueware ] "));
#endif
#else
		m_cvar()->ConsoleColorPrintf(g_cfg.misc.log_color, crypt_str("[ Plague ] ")); //-V807
#endif

		m_cvar()->ConsoleColorPrintf(Color::White, text.c_str());
		m_cvar()->ConsolePrintf(crypt_str("\n"));
	}

	if (g_cfg.misc.log_output[EVENTLOG_OUTPUT_CHAT])
	{
		static CHudChat* chat = nullptr;

		if (!chat)
			chat = util::FindHudElement <CHudChat> (crypt_str("CHudChat"));

#if RELEASE
#if BETA
		auto log = crypt_str("[ \x0CPlagueware \x01] ") + text;
		chat->chat_print(log.c_str());
#else
		auto log = crypt_str("[ \x0CPlagueware \x01] ") + text;
		chat->chat_print(log.c_str());
#endif
#else
		auto log = crypt_str("[ \x0CPlague \x01] ") + text;
		chat->chat_print(log.c_str());
#endif
	}
}