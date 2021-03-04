#pragma once
#include <functional>
#include "../misc/IHandleEntity.hpp"

class IClientNetworkable;
class IClientEntity;
class player_t;
class IClientEntityList
{
public:
    virtual IClientNetworkable*   GetClientNetworkable(int entnum) = 0;
    virtual void*                 vtablepad0x1(void) = 0;
    virtual void*                 vtablepad0x2(void) = 0;
    virtual IClientEntity*        GetClientEntity(int entNum) = 0;
    virtual IClientEntity*        GetClientEntityFromHandle(CBaseHandle hEnt) = 0;
    virtual int                   NumberOfEntities(bool bIncludeNonNetworkable) = 0;
    virtual int                   GetHighestEntityIndex(void) = 0;
    virtual void                  SetMaxEntities(int maxEnts) = 0;
    virtual int                   GetMaxEntities() = 0;


	void for_each(const std::function<void(IClientEntity*)> fn)
	{
		for (auto i = 0; i <= GetHighestEntityIndex(); ++i) {
			const auto entity = GetClientEntity(i);
			if (entity)
				fn(entity);
		}
	}

	void for_each_player(const std::function<void(player_t*)> fn);
	

	//void for_each_player_fixed_z_order(const std::function<void(c_cs_player*)> fn)
	//{
	//	std::vector<std::pair<c_cs_player*, float>> order;
	//	order.reserve(64);
	//
	//	const auto local = c_cs_player::get_local_player();
	//	if (!local)
	//		return;
	//
	//	const auto origin = local->get_origin();
	//
	//	for_each_player([&](c_cs_player* player) -> void
	//		{
	//			if (player->is_dormant() || !player->is_alive() || player->is_local_player())
	//				return;
	//
	//			// do not use shoot position here, the underlaying virtual does not lock the studiohdr
	//			// this breaks the entire animation state and is a pain in the ass to debug!
	//			order.push_back(std::make_pair(player,
	//				(player->get_origin() - origin).length2d()));
	//		});
	//
	//	// closest players will be drawn last
	//	// so their esp is actually going to overlap players with bigger distances
	//	std::sort(order.begin(), order.end(),
	//		[](const std::pair<c_cs_player*, float>& a,
	//			const std::pair<c_cs_player*, float>& b) -> bool {
	//				return a.second > b.second;
	//		});
	//
	//	for (auto const& entity : order)
	//		fn(entity.first);
	//}
};