#include "LagCompensation.hpp"
#include "animation_system.h"
#include "..\ragebot\aim.h"


void CMBacktracking::FrameUpdatePostEntityThink( )
{
	static auto sv_unlag = m_cvar()->FindVar( "sv_unlag" );
	if ( m_globals()->m_maxclients <= 1 || !sv_unlag->GetBool( ) )
	{
		CMBacktracking::get( ).ClearHistory( );
		return;
	}

	for ( int i = 1; i <= m_globals()->m_maxclients; i++ )
	{
		player_t *player = static_cast< player_t * >( m_entitylist()->GetClientEntity(i) );

		auto &lag_records = this->m_LagRecord[ i ];

		if ( !IsPlayerValid( player ) )
		{
			if ( lag_records.size( ) > 0 )
				lag_records.clear( );

			continue;
		}

		int32_t ent_index = player->EntIndex( );
		float_t sim_time = player->m_flSimulationTime( );

		LagRecord cur_lagrecord;

		RemoveBadRecords( ent_index, lag_records );

		if ( lag_records.size( ) > 0 )
		{
			auto &tail = lag_records.back( );

			if ( tail.m_flSimulationTime == sim_time )
				continue;
		}

		UpdateAnimations( player ); // update animations
		cur_lagrecord.SaveRecord( player ); // first let's create the record

		if ( !lag_records.empty( ) ) // apply specific stuff that is needed
		{
			auto &temp_lagrecord = lag_records.back( );
			int32_t priority_level = GetPriorityLevel( player, &temp_lagrecord );

			cur_lagrecord.m_iPriority = priority_level;
			cur_lagrecord.m_flPrevLowerBodyYaw = temp_lagrecord.m_flPrevLowerBodyYaw;
			cur_lagrecord.m_arrflPrevPoseParameters = temp_lagrecord.m_arrflPrevPoseParameters;

			if ( priority_level == 3 )
				cur_lagrecord.m_angAngles.y = temp_lagrecord.m_angAngles.y;
		}

		lag_records.emplace_back( cur_lagrecord );
	}
}

void CMBacktracking::ProcessCMD( int iTargetIdx, CUserCmd *usercmd )
{
	LagRecord recentLR = m_RestoreLagRecord[ iTargetIdx ].first;
	player_t *player = static_cast< player_t * >( m_entitylist( )->GetClientEntity( iTargetIdx ) );
	if ( !IsTickValid( TIME_TO_TICKS( recentLR.m_flSimulationTime ) ) )
		usercmd->m_tickcount = TIME_TO_TICKS( player->m_flSimulationTime( ) + GetLerpTime( ) );
	else
		usercmd->m_tickcount = TIME_TO_TICKS( recentLR.m_flSimulationTime + GetLerpTime( ) );
}

void CMBacktracking::RemoveBadRecords( int Idx, std::deque<LagRecord> &records )
{
	auto &m_LagRecords = records; // Should use rbegin but can't erase
	for ( auto lag_record = m_LagRecords.begin( ); lag_record != m_LagRecords.end( ); lag_record++ )
	{
		if ( !IsTickValid( TIME_TO_TICKS( lag_record->m_flSimulationTime ) ) )
		{
			m_LagRecords.erase( lag_record );
			if ( !m_LagRecords.empty( ) )
				lag_record = m_LagRecords.begin( );
			else break;
		}
	}
}

bool CMBacktracking::StartLagCompensation( player_t *player )
{
	backtrack_records.clear( );

	enum
	{

		TYPE_BEST_RECORDS,

		TYPE_BEST_AND_NEWEST,

		TYPE_ALL_RECORDS,
	};

	auto &m_LagRecords = this->m_LagRecord[ player->EntIndex( ) ];
	m_RestoreLagRecord[ player->EntIndex( ) ].second.SaveRecord( player );

	
			for ( auto it : m_LagRecords )
			{
				if ( it.m_iPriority >= 1 || ( it.m_vecVelocity.Length2D( ) > 10.f ) )
					backtrack_records.emplace_back( it );
			}


	std::sort( backtrack_records.begin( ), backtrack_records.end( ), [ ]( LagRecord const &a, LagRecord const &b )
	{
		return a.m_iPriority > b.m_iPriority;
	} );
	return backtrack_records.size( ) > 0;
}

bool CMBacktracking::FindViableRecord( player_t *player, LagRecord *record )
{
	auto &m_LagRecords = this->m_LagRecord[ player->EntIndex( ) ];

	// Ran out of records to check. Go back.
	if ( backtrack_records.empty( ) )
	{
		return false;
	}

	LagRecord
		recentLR = *backtrack_records.begin( ),
		prevLR;

	// Should still use m_LagRecords because we're checking for LC break.
	auto iter = std::find( m_LagRecords.begin( ), m_LagRecords.end( ), recentLR );
	auto idx = std::distance( m_LagRecords.begin( ), iter );
	if ( 0 != idx ) prevLR = *std::prev( iter );

	// Saving first record for processcmd.
	m_RestoreLagRecord[ player->EntIndex( ) ].first = recentLR;

	if ( !IsTickValid( TIME_TO_TICKS( recentLR.m_flSimulationTime ) ) )
	{
		backtrack_records.pop_front( );
		return backtrack_records.size( ) > 0; // RET_NO_RECORDS true false
	}

	// Remove a record...
	backtrack_records.pop_front( );

	if ( ( 0 != idx ) && ( recentLR.m_vecOrigin - prevLR.m_vecOrigin ).LengthSqr( ) > 4096.f )
	{
		/*float simulationTimeDelta = recentLR.m_flSimulationTime - prevLR.m_flSimulationTime;

		int simulationTickDelta = clamp(TIME_TO_TICKS(simulationTimeDelta), 1, 15);

		for (; simulationTickDelta > 0; simulationTickDelta--)
			RebuildGameMovement::Get().FullWalkMove(player);*/
		FakelagFix( player );

		// Bandage fix so we "restore" to the lagfixed player.
		m_RestoreLagRecord[ player->EntIndex( ) ].second.SaveRecord( player );
		*record = m_RestoreLagRecord[ player->EntIndex( ) ].second;

		// Clear so we don't try to bt shit we can't
		backtrack_records.clear( );

		return true; // Return true so we still try to aimbot.
	}
	else
	{
		player->invalidate_bone_cache( );

		player->GetCollideable( )->OBBMins( ) = recentLR.m_vecMins;
		player->GetCollideable( )->OBBMaxs( ) = recentLR.m_vecMax;

		player->set_abs_angles( Vector( 0, recentLR.m_angAngles.y, 0 ) );
		player->set_abs_origin( recentLR.m_vecOrigin );

		player->m_fFlags( ) = recentLR.m_nFlags;

		int layerCount = player->animlayer_count( );
		for ( int i = 0; i < layerCount; ++i )
		{
			AnimationLayer *currentLayer = player->GetAnimOverlay( i );
			currentLayer->m_nOrder = recentLR.m_LayerRecords[ i ].m_nOrder;
			currentLayer->m_nSequence = recentLR.m_LayerRecords[ i ].m_nSequence;
			currentLayer->m_flWeight = recentLR.m_LayerRecords[ i ].m_flWeight;
			currentLayer->m_flCycle = recentLR.m_LayerRecords[ i ].m_flCycle;
		}

		player->m_flPoseParameter( ) = recentLR.m_arrflPoseParameters;

		*record = recentLR;
		return true;
	}
}

void CMBacktracking::FinishLagCompensation( player_t *player )
{
	int idx = player->EntIndex( );

	player->invalidate_bone_cache( );

	player->GetCollideable( )->OBBMins( ) = m_RestoreLagRecord[ idx ].second.m_vecMins;
	player->GetCollideable( )->OBBMaxs( ) = m_RestoreLagRecord[ idx ].second.m_vecMax;

	player->set_abs_angles( Vector( 0, m_RestoreLagRecord[ idx ].second.m_angAngles.y, 0 ) );
	player->set_abs_origin( m_RestoreLagRecord[ idx ].second.m_vecOrigin );

	player->m_fFlags( ) = m_RestoreLagRecord[ idx ].second.m_nFlags;

	int layerCount = player->animlayer_count( );
	for ( int i = 0; i < layerCount; ++i )
	{
		AnimationLayer *currentLayer = player->GetAnimOverlay( i );
		currentLayer->m_nOrder = m_RestoreLagRecord[ idx ].second.m_LayerRecords[ i ].m_nOrder;
		currentLayer->m_nSequence = m_RestoreLagRecord[ idx ].second.m_LayerRecords[ i ].m_nSequence;
		currentLayer->m_flWeight = m_RestoreLagRecord[ idx ].second.m_LayerRecords[ i ].m_flWeight;
		currentLayer->m_flCycle = m_RestoreLagRecord[ idx ].second.m_LayerRecords[ i ].m_flCycle;
	}

	player->m_flPoseParameter( ) = m_RestoreLagRecord[ idx ].second.m_arrflPoseParameters;
}

int CMBacktracking::GetPriorityLevel( player_t *player, LagRecord *lag_record )
{
	int priority = 0;

	if ( lag_record->m_flPrevLowerBodyYaw != player->m_flLowerBodyYawTarget( ) )
	{
		lag_record->m_angAngles.y = player->m_flLowerBodyYawTarget( );
		priority = 3;
	}

	if ( ( player->m_flPoseParameter( )[ 1 ] > ( 0.85f ) && lag_record->m_arrflPrevPoseParameters[ 1 ] <= ( 0.85f ) ) || ( player->m_flPoseParameter( )[ 1 ] <= ( 0.85f ) && lag_record->m_arrflPrevPoseParameters[ 1 ] > ( 0.85f ) ) )
		priority = 1;

	lag_record->m_flPrevLowerBodyYaw = player->m_flLowerBodyYawTarget( );
	lag_record->m_arrflPrevPoseParameters = player->m_flPoseParameter( );

	return priority;
}

void CMBacktracking::SimulateMovement( Vector &velocity, Vector &origin, player_t *player, int &flags, bool was_in_air )
{
	if ( !( flags & FL_ONGROUND ) )
		velocity.z -= ( m_globals()->m_frametime * m_cvar()->FindVar( "sv_gravity" )->GetFloat( ) );
	else if ( was_in_air )
		velocity.z = m_cvar()->FindVar( "sv_jump_impulse" )->GetFloat( );

	const Vector mins = player->GetCollideable( )->OBBMins( );
	const Vector max = player->GetCollideable( )->OBBMaxs( );

	const Vector src = origin;
	Vector end = src + ( velocity * m_globals()->m_frametime );

	Ray_t ray;
	ray.Init( src, end, mins, max );

	trace_t trace;
	CTraceFilter filter;
	filter.pSkip = ( void * ) ( player );

	m_trace()->TraceRay( ray, MASK_PLAYERSOLID, &filter, &trace );

	if ( trace.fraction != 1.f )
	{
		for ( int i = 0; i < 2; i++ )
		{
			velocity -= trace.plane.normal * velocity.Dot( trace.plane.normal );

			const float dot = velocity.Dot( trace.plane.normal );
			if ( dot < 0.f )
			{
				velocity.x -= dot * trace.plane.normal.x;
				velocity.y -= dot * trace.plane.normal.y;
				velocity.z -= dot * trace.plane.normal.z;
			}

			end = trace.endpos + ( velocity * ( m_globals()->m_intervalpertick * ( 1.f - trace.fraction ) ) );

			ray.Init( trace.endpos, end, mins, max );
			m_trace()->TraceRay( ray, MASK_PLAYERSOLID, &filter, &trace );

			if ( trace.fraction == 1.f )
				break;
		}
	}

	origin = trace.endpos;
	end = trace.endpos;
	end.z -= 2.f;

	ray.Init( origin, end, mins, max );
	m_trace()->TraceRay( ray, MASK_PLAYERSOLID, &filter, &trace );

	flags &= ~( 1 << 0 );

	if ( trace.DidHit( ) && trace.plane.normal.z > 0.7f )
		flags |= ( 1 << 0 );
}

void CMBacktracking::FakelagFix( player_t *player )
{
	auto &lag_records = this->m_LagRecord[ player->EntIndex( ) ];

	if ( lag_records.size( ) > 2 )
	{
		bool bChocked = TIME_TO_TICKS( player->m_flSimulationTime( ) - lag_records.back( ).m_flSimulationTime ) > 1;
		bool bInAir = false;

		if ( !( player->m_fFlags( ) & FL_ONGROUND ) || !( lag_records.back( ).m_nFlags & FL_ONGROUND ) )
			bInAir = true;

		if ( bChocked )
		{
			player->m_vecOrigin( ) = lag_records.back( ).m_vecOrigin;
			player->set_abs_origin( lag_records.back( ).m_vecAbsOrigin );
			player->m_vecVelocity( ) = lag_records.back( ).m_vecVelocity;
			player->m_fFlags( ) = lag_records.back( ).m_nFlags;
		}

		Vector data_origin = player->m_vecOrigin( );
		Vector data_velocity = player->m_vecVelocity( );
		int data_flags = player->m_fFlags( );

		if ( bChocked )
		{
			SimulateMovement( data_velocity, data_origin, player, data_flags, bInAir );

			player->m_vecOrigin( ) = data_origin;
			player->set_abs_origin( data_origin );
			player->m_vecVelocity( ) = data_velocity;

			player->m_fFlags( ) &= 0xFFFFFFFE;
			auto penultimate_record = *std::prev( lag_records.end( ), 2 );
			if ( ( lag_records.back( ).m_nFlags & FL_ONGROUND ) && ( penultimate_record.m_nFlags & FL_ONGROUND ) )
				player->m_fFlags( ) |= 1;
			if ( *( float * ) ( ( uintptr_t ) player->GetAnimOverlay( 0 ) + 0x138 ) > 0.f )
				player->m_fFlags( ) |= 1;
		}
	}
}

void CMBacktracking::UpdateAnimations( player_t *player )
{
	c_baseplayeranimationstate *state = player->get_animation_state( );
	if ( state )
	{
		// backup
		const float curtime = m_globals()->m_curtime;
		const float frametime = m_globals( )->m_curtime;

		static auto host_timescale = m_cvar()->FindVar( ( "host_timescale" ) );

		m_globals( )->m_frametime = m_globals( )->m_intervalpertick * host_timescale->GetFloat( );
		m_globals( )->m_curtime = player->m_flOldSimulationTime( ) + m_globals()->m_intervalpertick;

		Vector backup_origin = player->m_vecOrigin( );
		Vector backup_absorigin = player->GetAbsOrigin( );
		Vector backup_velocity = player->m_vecVelocity( );
		int backup_flags = player->m_fFlags( );
		int backup_eflags = player->m_iEFlags( );

		AnimationLayer backup_layers[ 15 ];
		std::memcpy( backup_layers, player->get_animlayers( ), ( sizeof( AnimationLayer ) * player->animlayer_count( ) ) );

		if ( state->m_bOnGround )
		{
			player->m_fFlags( ) |= FL_ONGROUND;
		}
		else
		{
			player->m_fFlags( ) &= ~FL_ONGROUND;
		}
		player->m_iEFlags( ) &= ~0x1000;

		player->m_vecAbsVelocity( ) = player->m_vecVelocity( );

		// invalidates prior animations so the entity gets animated on our client 100% via UpdateClientSideAnimation
		if ( state->m_flLastClientSideAnimationUpdateTime == m_globals( )->m_framecount )
			state->m_flLastClientSideAnimationUpdateTime = m_globals()->m_framecount - 1;

		player->m_bClientSideAnimation( ) = true;

		// updates local animations + poses + calculates new abs angle based on eyeangles and other stuff
		player->update_clientside_animation( );

		player->m_bClientSideAnimation( ) = false;

		// restore
		std::memcpy( player->get_animlayers( ), backup_layers, ( sizeof( AnimationLayer ) * player->animlayer_count( ) ) );
		player->m_vecOrigin( ) = backup_origin;
		player->set_abs_origin( backup_absorigin );
		player->m_vecVelocity( ) = backup_velocity;
		player->m_fFlags( ) = backup_flags;
		player->m_iEFlags( ) = backup_eflags;

		m_globals()->m_curtime = curtime;
		m_globals( )->m_frametime = frametime;

		player->SetupBones( nullptr, -1, 0x7FF00, m_globals( )->m_curtime );
	}
}



void LagRecord::SaveRecord( player_t *player)
{
	m_vecOrigin = player->m_vecOrigin();
	m_vecAbsOrigin = player->GetAbsOrigin();
	m_angAngles = player->m_angEyeAngles();
	m_flSimulationTime = player->m_flSimulationTime();
	m_vecMins = player->GetCollideable()->OBBMins();
	m_vecMax = player->GetCollideable()->OBBMaxs();
	m_nFlags = player->m_fFlags();
	m_vecVelocity = player->m_vecVelocity();

	int layerCount = player->animlayer_count();
	for (int i = 0; i < layerCount; i++)
	{
		AnimationLayer *currentLayer = player->GetAnimOverlay(i);
		m_LayerRecords[i].m_nOrder = currentLayer->m_nOrder;
		m_LayerRecords[i].m_nSequence = currentLayer->m_nSequence;
		m_LayerRecords[i].m_flWeight = currentLayer->m_flWeight;
		m_LayerRecords[i].m_flCycle = currentLayer->m_flCycle;
	}
	m_arrflPoseParameters = player->m_flPoseParameter();

	m_iTickCount = m_globals()->m_tickcount;
	m_vecHeadSpot = player->hitbox_position(8);
}



void CMBacktracking::RageBacktrack( player_t *target, CUserCmd *usercmd, Vector &aim_point )
{
	auto firedShots = g_ctx.local()->m_iShotsFired( );
	if ( StartLagCompensation( target ) )
	{
		LagRecord cur_record;
		auto &m_LagRecords = this->m_LagRecord[ target->EntIndex( ) ];
		while ( FindViableRecord( target, &cur_record ) )
		{
			auto iter = std::find( m_LagRecords.begin( ), m_LagRecords.end( ), cur_record );
			if ( iter == m_LagRecords.end( ) )
				continue;

			if ( iter->m_bNoGoodSpots )
			{
				// Already awalled from same spot, don't try again like a dumbass.
				if ( iter->m_vecLocalAimspot == g_ctx.local()->get_shoot_position())
					continue;
				else
					iter->m_bNoGoodSpots = false;
			}

			if ( !iter->m_bMatrixBuilt )
			{
				if ( !target->SetupBones( iter->matrix, 128, 256, iter->m_flSimulationTime ) )
					continue;

				iter->m_bMatrixBuilt = true;
			}
		

			if ( !aim_point.IsValid( ) )
			{
				FinishLagCompensation( target );
				iter->m_bNoGoodSpots = true;
				iter->m_vecLocalAimspot = g_ctx.local( )->get_shoot_position( );
				continue;
			}


			this->current_record[ target->EntIndex( ) ] = *iter;
			break;
		}
		FinishLagCompensation( target );
		ProcessCMD( target->EntIndex( ), usercmd );
	}
}

void CMBacktracking::SetOverwriteTick(player_t *player, Vector angles, float_t correct_time)
{
	int idx = player->EntIndex();
	LagRecord overwrite_record;
	auto& m_LagRecords = this->m_LagRecord[player->EntIndex()];

	if (!IsTickValid(TIME_TO_TICKS(correct_time)))
		m_cvar()->ConsoleColorPrintf(Color(255, 0, 0, 255), "Dev Error: failed to overwrite tick, delta too big. Priority: %d\n", 1);

	overwrite_record.SaveRecord(player);
	overwrite_record.m_angAngles = angles;
	overwrite_record.m_iPriority = 1;
	overwrite_record.m_flSimulationTime = correct_time;
	m_LagRecords.emplace_back(overwrite_record);
}


bool CMBacktracking::IsTickValid(int tick)
{	
	// better use polak's version than our old one, getting more accurate results

	INetChannelInfo *nci = m_engine()->GetNetChannelInfo();

	static auto sv_maxunlag = m_cvar()->FindVar("sv_maxunlag");

	if (!nci || !sv_maxunlag)
		return false;

	float correct = clamp(nci->GetLatency(FLOW_OUTGOING) + GetLerpTime(), 0.f, sv_maxunlag->GetFloat());

	float deltaTime = correct - (m_globals()->m_curtime - TICKS_TO_TIME(tick));

	return fabsf(deltaTime) < 0.2f;
}

bool CMBacktracking::IsPlayerValid(player_t *player)
{
	if (!player)
		return false;

	if (!player->is_player())
		return false;

	if (player == g_ctx.local())
		return false;

	if (player->IsDormant())
		return false;

	if (!player->is_alive())
		return false;

	if (player->m_bGunGameImmunity())
		return false;

	return true;
}

float CMBacktracking::GetLerpTime()
{
	int ud_rate = m_cvar()->FindVar("cl_updaterate")->GetInt();
	ConVar *min_ud_rate = m_cvar()->FindVar("sv_minupdaterate");
	ConVar *max_ud_rate = m_cvar()->FindVar("sv_maxupdaterate");

	if (min_ud_rate && max_ud_rate)
		ud_rate = max_ud_rate->GetInt();

	float ratio = m_cvar()->FindVar("cl_interp_ratio")->GetFloat();

	if (ratio == 0)
		ratio = 1.0f;

	float lerp = m_cvar()->FindVar("cl_interp")->GetFloat();
	ConVar *c_min_ratio = m_cvar()->FindVar("sv_client_min_interp_ratio");
	ConVar *c_max_ratio = m_cvar()->FindVar("sv_client_max_interp_ratio");

	if (c_min_ratio && c_max_ratio && c_min_ratio->GetFloat() != 1)
		ratio = clamp(ratio, c_min_ratio->GetFloat(), c_max_ratio->GetFloat());

	return max(lerp, (ratio / ud_rate));
}

template<class T, class U>
T CMBacktracking::clamp(T in, U low, U high)
{
	if (in <= low)
		return low;

	if (in >= high)
		return high;

	return in;
}