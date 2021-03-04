#pragma once

#include "../../sdk/structs.hpp"
#include "../../utils/singleton.h"

#include <deque>

struct LayerRecord
{
	LayerRecord()
	{
		m_nOrder = 0;
		m_nSequence = 0;
		m_flWeight = 0.f;
		m_flCycle = 0.f;
	}

	LayerRecord(const LayerRecord &src)
	{
		m_nOrder = src.m_nOrder;
		m_nSequence = src.m_nSequence;
		m_flWeight = src.m_flWeight;
		m_flCycle = src.m_flCycle;
	}

	uint32_t m_nOrder;
	uint32_t m_nSequence;
	float_t m_flWeight;
	float_t m_flCycle;
};

struct LagRecord
{
	LagRecord()
	{
		m_iPriority = -1;

		m_flSimulationTime = -1.f;
		m_vecOrigin.Init();
		m_angAngles.Init();
		m_vecMins.Init();
		m_vecMax.Init();
		m_bMatrixBuilt = false;
	}

	bool operator==(const LagRecord &rec)
	{
		return m_flSimulationTime == rec.m_flSimulationTime;
	}

	void SaveRecord(player_t *player);

	matrix3x4_t	matrix[128];
	bool m_bMatrixBuilt;
	Vector m_vecHeadSpot;
	float m_iTickCount;

	// For priority/other checks
	int32_t m_iPriority;
	Vector  m_vecVelocity;
	float_t m_flPrevLowerBodyYaw;
	std::array<float_t, 24> m_arrflPrevPoseParameters;
	Vector  m_vecLocalAimspot;
	bool    m_bNoGoodSpots;

	// For backtracking
	float_t m_flSimulationTime;
	int32_t m_nFlags;
	Vector m_vecOrigin;	   // Server data, change to this for accuracy
	Vector m_vecAbsOrigin;
	Vector m_angAngles;
	Vector m_vecMins;
	Vector m_vecMax;
	std::array<float_t, 24> m_arrflPoseParameters;
	std::array<LayerRecord, 15> m_LayerRecords;
};

class CMBacktracking : public singleton<CMBacktracking>
{
public:

	void RageBacktrack( player_t * target, CUserCmd *usercmd, Vector &aim_point);

	std::deque<LagRecord> m_LagRecord[64]; // All records
	std::pair<LagRecord, LagRecord> m_RestoreLagRecord[64]; // Used to restore/change
	std::deque<LagRecord> backtrack_records; // Needed to select records based on menu option.
	LagRecord current_record[64]; // Used for various other actions where we need data of the current lag compensated player

	inline void ClearHistory()
	{
		for (int i = 0; i < 64; i++)
			m_LagRecord[i].clear();
	}

	void FrameUpdatePostEntityThink();
	void ProcessCMD(int iTargetIdx, CUserCmd *usercmd);

	void RemoveBadRecords(int Idx, std::deque<LagRecord>& records);

	bool StartLagCompensation( player_t *player);
	bool FindViableRecord( player_t *player, LagRecord* record);
	void FinishLagCompensation( player_t *player);

	int GetPriorityLevel( player_t *player, LagRecord* lag_record);
	void SimulateMovement(Vector &velocity, Vector &origin, player_t *player, int &flags, bool was_in_air);
	void FakelagFix( player_t *player);
	void UpdateAnimations( player_t *player);

	void SetOverwriteTick( player_t *player, Vector angles, float_t correct_time);

	bool IsTickValid(int tick);
	bool IsPlayerValid( player_t *player);
	float GetLerpTime();

	template<class T, class U>
	T clamp(T in, U low, U high);
};