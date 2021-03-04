#include "NetworkedVariables.h"


CStaticOffsets StaticOffsets;



uint32_t StaticOffset::GetOffset() const
{

	return Offset ^ GetDecryptionKey();

}


CStaticOffsets::CStaticOffsets()
{
	m_bAlreadyAdded = false;
}

void CStaticOffsets::AddOffset(const StaticOffset& fulloffset)
{
	//Add the offset if it hasn't been added already.
	auto &dest = Offsets.at(fulloffset.GetName());
	if (dest.GetName() == StaticOffsetName::INVALID_STATIC_OFFSET)
		dest = fulloffset;
	//else
	//	DebugBreak();
}

CStaticOffsets::CachedStaticOffsetsHandle CStaticOffsets::HandleToCachedHandle(HANDLE handle)
{
	if (handle == ClientHandle)
		return CStaticOffsets::CachedStaticOffsetsHandle::CACHE_CLIENTDLL;
	else if (handle == EngineHandle)
		return CStaticOffsets::CachedStaticOffsetsHandle::CACHE_ENGINEDLL;
	else if (handle == VGUIMatSurfaceHandle)
		return CStaticOffsets::CachedStaticOffsetsHandle::CACHE_VGUIMATSURFACE;
	else if (handle == SHADERAPIDX9Handle)
		return CStaticOffsets::CachedStaticOffsetsHandle::CACHE_SHADERAPIDX9;
	else if (handle == ServerHandle)
		return CStaticOffsets::CachedStaticOffsetsHandle::CACHE_SERVERDLL;
	else
		return CStaticOffsets::CachedStaticOffsetsHandle::CACHE_UNKNOWN;
}

HANDLE CStaticOffsets::HandleToCachedHandle(CStaticOffsets::CachedStaticOffsetsHandle dll)
{
	if (dll == CStaticOffsets::CachedStaticOffsetsHandle::CACHE_CLIENTDLL)
	{
		return ClientHandle;
	}
	else if (dll == CStaticOffsets::CachedStaticOffsetsHandle::CACHE_ENGINEDLL)
	{
		return EngineHandle;
	}
	else if (dll == CStaticOffsets::CachedStaticOffsetsHandle::CACHE_VGUIMATSURFACE)
	{
		return VGUIMatSurfaceHandle;
	}
	else if (dll == CStaticOffsets::CachedStaticOffsetsHandle::CACHE_SHADERAPIDX9)
	{
		return SHADERAPIDX9Handle;
	}
	else if (dll == CStaticOffsets::CachedStaticOffsetsHandle::CACHE_SERVERDLL)
	{
		return ServerHandle;
	}
	return 0;
}

void CStaticOffsets::AddAllOffsets()
{
	if (m_bAlreadyAdded)
		return;

#ifdef USE_CACHED_STATIC_OFFSETS
	if (ReadOffsetsFromFile())
		return;
#endif

	//AddOffset(StaticOffset(_IsPlayer, 0x26C / 4)); //fixed correct 4/30/19
	//AddOffset(StaticOffset(_LocalAngles, 0xD0)); //fixed
	//AddOffset(StaticOffset(_SetAbsAnglesDirect, 0xC4)); //fixed
	//AddOffset(StaticOffset(_OldOrigin, 0x3A4 + 8)); //fixed
	//AddOffset(StaticOffset(_MoveType, 0x25C)); //fixed
	//AddOffset(StaticOffset(_MoveCollide, 0x25D)); //fixed
	//AddOffset(StaticOffset(_m_iEFlags, 0xE8));  //fixed
	//AddOffset(StaticOffset(_m_nWaterType, 0xEC)); //fixed
	//AddOffset(StaticOffset(_m_BoneSetupLock, 9908)); //fixed
	//AddOffset(StaticOffset(_m_bIsToolRecording, 0x291)); //fixed correct 4/30/19
	//AddOffset(StaticOffset(_m_EntClientFlags, 104)); //fixed
	//AddOffset(StaticOffset(_GetPredictable, 0x2EE)); //fixed correct 4/30/19
	//AddOffset(StaticOffset(_m_pIK_offset, 9840)); //fixed correct 4/30/19
	//AddOffset(StaticOffset(_m_flLastBoneSetupTime, 0x2924)); //fixed correct 4/30/19
	//AddOffset(StaticOffset(_LastBoneChangedTime_Offset, (968 / 4))); //fixed correct 4/30/19
	//AddOffset(StaticOffset(_m_iPrevBoneMask, 0x269C)); //fixed
	//AddOffset(StaticOffset(_m_iAccumulatedBoneMask, 0x26A0)); //fixed
	//AddOffset(StaticOffset(_LastSetupBonesFrameCount, 0xA68)); //fixed
	//AddOffset(StaticOffset(_m_iMostRecentModelBoneCounter, 0x2690)); //fixed correct 4/30/19
	//AddOffset(StaticOffset(_BoneAccessor, 0x26A4)); //fixed correct 4/30/19
	//AddOffset(StaticOffset(_m_pStudioHdr, 0x294C)); //fixed
	//AddOffset(StaticOffset(_StandardBlendingRules, 0x32C / 4)); //fixed correct 4/30/19
	//AddOffset(StaticOffset(_BuildTransformations, 0x2EC / 4)); //fixed correct 4/30/19
	//AddOffset(StaticOffset(_UpdateIKLocks, (0x2F4 / 4))); //fixed correct 4/30/19
	//AddOffset(StaticOffset(_CalculateIKLocks, (0x2F8 / 4))); //fixed
	//AddOffset(StaticOffset(_ControlMouth, (0x308 / 4))); //fixed correct 4/30/19
	AddOffset(StaticOffset(_UnknownOffset1, (32 / 4))); // nit; not used anymore
	//AddOffset(StaticOffset(_DoExtraBoneProcessing, (0x30C / 4))); //fixed correct 4/30/19
	//AddOffset(StaticOffset(_m_CachedBoneData, 0x2910)); //fixed correct 4/30/19
	//AddOffset(StaticOffset(_Weapon_ShootPosition, 279)); //277  fixed
	//AddOffset(StaticOffset(_Weapon_ShootPosition_Base, 656 / 4)); //NOT correct
	//AddOffset(StaticOffset(_m_flEncodedController, 0x0A54)); //fixed correct 4/30/19
	AddOffset(StaticOffset(_IsTransparent, 50));	// nit; not used anymore?
	//AddOffset(StaticOffset(_GetBaseAnimating, 0xB0));
	AddOffset(StaticOffset(_GetAbsOriginVMT, 10)); // nit; this will never change and too generic to make a sig
	//m_bIsLocalPlayer = 0x3620 = 74  ??  8A  83  ??  ??  ??  ??  88

	//NOTE: FIX  int CBaseEntity::GetNumAnimOverlays()
	//NOTE: FIX CUtlVectorSimple* CBaseEntity::GetAnimOverlayStruct() const

	//AddOffset(StaticOffset(_DeadFlag, 0, "8B 41 04 80 B8 ?? ?? ?? ?? ?? 74 03", ClientHandle, 1, 5, 0, 0));
	//AddOffset(StaticOffset(_RenderAngles, GetOffsetValue(_DeadFlag) + 4));

	//decrypts(0)
	AddOffset(StaticOffset(_StriderMuzzleEffect, 0, ("55  8B  EC  83  EC  ??  F3  0F  10  0D  ??  ??  ??  ??  8D  45  ??  56  8B  F2  89  45  ??  8D  45  ??  57  8B  F9"), ClientHandle));
	AddOffset(StaticOffset(_GunshipMuzzleEffect, 0, ("55  8B  EC  83  EC  ??  53  56  57  8B  F9  8B  DA  8B  0D  ??  ??  ??  ??  8B  81  ??  ??  ??  ??  89  45  ??"), ClientHandle));
	AddOffset(StaticOffset(_CS_Bloodspray, 0, ("55  8B  EC  8B  4D  08  F3  0F  10  51  ??  8D"), ClientHandle));
	AddOffset(StaticOffset(_Tesla, 0, ("55  8B  EC  81  EC  ??  ??  ??  ??  56  57  8B  F9  8B  47  18"), ClientHandle));
	AddOffset(StaticOffset(_ViewRender, 0, ("8B  0D  ??  ??  ??  ??  D9  1D  ??  ??  ??  ??"), ClientHandle, 0, 0, 0, 2));
	AddOffset(StaticOffset(_ParseEventDelta, 0, ("55  8B  EC  83  E4  ??  53  57  8B  F9  8B  DA  51  8B  4D  ??  E8  ??  ??  ??  ??  8B  4D  ??  83  C4  ??  8B  D3  6A  ??  57  E8  ??  ??  ??  ??  83  C4  ??  5F  5B  8B  E5  5D"), EngineHandle));
	AddOffset(StaticOffset(_GetPlayerResource, 0, ("A1  ??  ??  ??  ??  85  C0  74  ??  5  ??  ??  ??  ??  C3  33  C0  C3"), ClientHandle));
	AddOffset(StaticOffset(_CalcPlayerView, 0, ("84  C0  75  08  57  8B  CE  E8  ??  ??  ??  ??  8B  06"), ClientHandle));
	AddOffset(StaticOffset(_InvalidatePhysicsRecursive, 0, ("55  8B  EC  83  E4  F8  83  EC  0C  53  8B  5D  08  8B  C3  56  83  E0  04"), ClientHandle));
	AddOffset(StaticOffset(_GetShotgunSpread, 0, ("55  8B  EC  83  EC  10  56  8B  75  08  8D"), ClientHandle));
	AddOffset(StaticOffset(_NoClipEnabled, 0, ("80  3D  ??  ??  ??  ??  00  75  0E  47"), EngineHandle, 1, 2, 0, 0));
	AddOffset(StaticOffset(_CanUseFastPath, 0, ("8B  07  8B  CF  C6  87  ??  ??  ??  ??  00  FF  90"), ClientHandle, 1, 6));
	AddOffset(StaticOffset(_SetAbsAngles, 0, ("55  8B  EC  83  E4  F8  83  EC  64  53  56  57  8B  F1  E8"), ClientHandle));
	AddOffset(StaticOffset(_SetAbsOrigin, 0, ("55  8B  EC  83  E4  F8  51  53  56  57  8B  F1  E8  ??  ??  ??  ??  8B  7D  08"), ClientHandle));
	AddOffset(StaticOffset(_OverridePostProcessingDisable, 0, ("80  3D  ??  ??  ??  ??  00  53  56  57  0F  85"), ClientHandle, 1, 2, 0, 0));
	AddOffset(StaticOffset(_LastOcclusionCheckTime, 0, ("A1  ??  ??  ??  ??  8B  B7  ??  ??  ??  ??  89  75"), ClientHandle, 1, 7, 0, 0));
	AddOffset(StaticOffset(_InvalidateBoneCache, 0, ("CC  80  3D  ??  ??  ??  ??  00  74  16  A1"), ClientHandle, 0, 0, 0, 1));  //fixme
	AddOffset(StaticOffset(_EntityGlowIndex, 0, ("F3  0F  11  45  ??  8B  B7"), ClientHandle, 1, 7, 0, 0));
	AddOffset(StaticOffset(_UpdateClientSideAnimation, 0, ("74  0B  8B  0C  F0  8B  01  FF  90"), ClientHandle, 1, 9, 4, 0));
	AddOffset(StaticOffset(_LastOutgoingCommand, 0, ("8B  98  ??  ??  ??  ??  56  "), EngineHandle, 1, 2, 0, 0));
	AddOffset(StaticOffset(_DeltaTick, 0, ("83  BF  ??  ??  ??  ??  ??  0F  84  ??  ??  ??  ??  8D  "), EngineHandle, 1, 2, 0, 0));
	AddOffset(StaticOffset(_pClientState, 0, ("8B  3D  ??  ??  ??  ??  8A  F9  F3  0F  11  45  FC"), EngineHandle, 2, 2, 0, 0));
	AddOffset(StaticOffset(_FinishDrawing, 0, ("8B  0D  ??  ??  ??  ??  56  C6  05  ??  ??  ??  ??  00  8B  01  FF  90"), VGUIMatSurfaceHandle));
	AddOffset(StaticOffset(_StartDrawing, 0, ("55  8B  EC  83  E4  ??  83  EC  ??  80  3D  ??  ??  ??  ??  00  56  57  8B  F9"), VGUIMatSurfaceHandle));
	AddOffset(StaticOffset(_UTIL_TraceLineIgnoreTwoEntities, 0, ("53  8B  DC  83  EC  ??  83  E4  ??  83  C4  04  55  8B  6B  04  89  6C  24  04  8B  EC  81  EC  8C"), ClientHandle));
	AddOffset(StaticOffset(_UTIL_ClipTraceToPlayers, 0, ("53  8B  DC  83  EC  08  83  E4  F0  83  C4  04  55  8B  6B  04  89  6C  24  04  8B  EC  81  EC  D8  00  00  00  0F  57  C9  89  55  E4"), ClientHandle));
	AddOffset(StaticOffset(_UTIL_ClipTraceToPlayers2, 0, ("55  8B  EC  A1  ??  ??  ??  ??  83  EC  08  D1  E8  56  57  A8  01  74  59  8B  0D  ??  ??  ??  ??  8B  C1  8B  35  ??  ??  ??  ??  85  C9  75  03  8B  46  08  8B  40  30  C1  E8  04  A8  01  74  3A"), ClientHandle));
	AddOffset(StaticOffset(_IsEntityBreakable, 0, ("55  8B  EC  51  56  8B  F1  85  F6  74  ??  83  BE"), ClientHandle));
	AddOffset(StaticOffset(_IsBaseCombatWeaponIndex, 0, ("85  F6  74  ??  8B  06  8B  80"), ClientHandle, 1, 8));
	AddOffset(StaticOffset(_LineGoesThroughSmoke, 0, ("55  8B  EC  83  EC  08  8B  15  ??  ??  ??  ??  0F"), ClientHandle));
	AddOffset(StaticOffset(_RevealRanks, 0, ("55  8B  EC  8B  0D  ??  ??  ??  ??  68"), ClientHandle));
	AddOffset(StaticOffset(_Spread, 0, ("8B  CB  8B  80  ??  ??  ??  ??  FF  D0  8B  45  EC"), ClientHandle, 1, -0xC, 4, 0));
	AddOffset(StaticOffset(_Cone, 0, ("8B  CB  8B  80  ??  ??  ??  ??  FF  D0  8B  45  EC"), ClientHandle, 1, 0x4, 4, 0));
	AddOffset(StaticOffset(_UpdateAccuracyPenalty, 0, ("83  C4  14  85  DB  0F  84  ??  ??  ??  ??  8B  17  8B  CF  FF  92  ??  ??  ??  ??"), ClientHandle, 1, 17, 4, 0));
	AddOffset(StaticOffset(_GameResources, 0, ("0F  85  ??  ??  ??  ??  8B  3D  ??  ??  ??  ??  85  FF  0F  84  ??  ??  ??  ??  81  C7"), ClientHandle, 1, 8, 0, 0));
	AddOffset(StaticOffset(_GlowObjectManager, 0, ("0F  11  05  ??  ??  ??  ??  83  C8  01"), ClientHandle, 0, 0, 0, 3));
	AddOffset(StaticOffset(_KeyValues_LoadFromBuffer, 0, ("55  8B  EC  83  E4  F8  83  EC  34  53  8B  5D  0C  89"), ClientHandle));
	AddOffset(StaticOffset(_ChangeClantag, 0, ("53  56  57  8B  DA  8B  F9  FF  15"), EngineHandle));
	AddOffset(StaticOffset(_KeyValues_Constructor, 0, ("55  8B  EC  51  33  C0  C7  45  FC  ??  ??  ??  ??  56  8B  F1"), ClientHandle));
	AddOffset(StaticOffset(_CalcAbsoluteVelocity, 0, ("55  8B  EC  83  E4  F8  83  EC  1C  53  56  57  8B  F9  F7  87  ??  00  00  00  00  10  00  00"), ClientHandle));//"55  8B  EC  83  E4  F8  83  EC  1C  53  56  57  8B  F9  F7  87  E4  00  00  00  00  10  00  00"), ClientHandle));
	AddOffset(StaticOffset(_CalcAbsolutePosition, 0, ("55  8B  EC  83  E4  F0  83  EC  68  80  3D"), ClientHandle));
	AddOffset(StaticOffset(_InThreadedBoneSetup, 0, ("80  3D  ??  ??  ??  ??  00  8D  8F"), ClientHandle, 1, 2, 0, 0));
	AddOffset(StaticOffset(_GetSolid, 0, ("FF  90  ??  ??  00  00  8B  56  04  8D  4E  04  8B  F8  FF  52  ??  8B  0D"), ClientHandle, 1, 2, 4, 0)); //fixed
	AddOffset(StaticOffset(_g_iModelBoneCounter, 0, ("0F  84  ??  ??  ??  ??  8B  47  FC  8D  4F  FC  F3  0F  10  87  ??  ??  ??  ??"), ClientHandle, 1, -4, 0, 0));
	//AddOffset(StaticOffset(_PhysicsSolidMaskForEntityVMT, 0, ("8B  06  8B  CE  FF  90  ??  ??  00  00  A9  00  00  01  00  74  27"), ClientHandle, 1, 6, 4, 0));
	AddOffset(StaticOffset(_SetDormant, 0, ("55  8B  EC  53  8B  5D  08  56  8B  F1  88  9E  ??  ??  00  00"), ClientHandle));
	AddOffset(StaticOffset(_LockStudioHdr, 0, ("55  8B  EC  51  53  8B  D9  56  57  8D  B3"), ClientHandle));
	AddOffset(StaticOffset(_GetPunchAngleVMT, 0, ("8B  01  8D  54  24  14  52  FF  90  ??  ??  00  00"), ClientHandle, 1, 9, 4, 0));
	AddOffset(StaticOffset(_SetPunchAngleVMT, 0, ("55  8B  EC  56  57  8B  7D  08  8D  B1  ??  ??  ??  ??  F3  0F  10  07"), ClientHandle));
	AddOffset(StaticOffset(_SpawnTime, 0, ("F3  0F  5C  88  ??  ??  ??  ??  0F  2F  C1  73  ??  80  BE  ??  ??  00  00  00"), ClientHandle, 1, 4, 0, 0));
	AddOffset(StaticOffset(_m_dwObserverTargetVMT, 0, ("8B  4E  ??  8B  01  8B  80  ??  ??  00  00  FF  D0  8B  F8"), ClientHandle, 1, 7, 4, 0));
	AddOffset(StaticOffset(_ReevaluateAnimLod, 0, ("53  8B  DC  83  EC  08  83  E4  F8  83  C4  04  55  8B  6B  04  89  6C  24  04  8B  EC  83  EC  30  56  57  8B  F9  8B  0D  ??  ??  ??  ??  8B  01  8B  80  74  01  00  00"), ClientHandle));
	AddOffset(StaticOffset(_AllowBoneAccessForViewModels, 0, ("0F  B6  0D  ??  ??  ??  ??  0F  45  D1  84  D2"), ClientHandle, 1, 3, 0, 0));
	AddOffset(StaticOffset(_AllowBoneAccessForNormalModels, 0, ("0F  B6  15  ??  ??  ??  ??  84  C0  0F  B6  0D"), ClientHandle, 1, 3, 0, 0));
	AddOffset(StaticOffset(_IsViewModel, 0, ("8B  47  FC  8D  4F  FC  8B  80  ??  ??  00  00  FF  D0  0F  B6  15"), ClientHandle, 1, 8, 4, 0));
	AddOffset(StaticOffset(_MarkForThreadedBoneSetup, 0, ("55  8B  EC  51  80  3D  ??  ??  ??  ??  00  56  8B  F1  0F  84"), ClientHandle));
	AddOffset(StaticOffset(_SequencesAvailableVMT, 0, ("8B  0D  ??  ??  ??  ??  52  8B  01  8B  40  68"), ClientHandle, 1, 2, 0, 0));
	AddOffset(StaticOffset(_SequencesAvailableCall, 0, ("55  8B  EC  53  8B  5D  08  56  8B  F1  85  DB  74  ??  57  89  5E  04"), ClientHandle));
	AddOffset(StaticOffset(_CreateIK, 0, ("53  8B  D9  F6  C3  03  74  0B  FF  15  ??  ??  ??  ??  84  C0  74  01  CC  C7  83  F0  0F  00  00  00  00  00  00"), ClientHandle));
	AddOffset(StaticOffset(_Teleported, 0, ("8B  91  ??  ??  ??  ??  83  FA  FF  74  17  0F  B7  C2  C1  E0  04  05  ??  ??  ??  ??  C1  EA  10  39  50  04  75  04  8B  00  EB  02  33  C0  56"), ClientHandle));
	AddOffset(StaticOffset(_IKInit, 0, ("55  8B  EC  83  EC  08  8B  45  08  56  57  8B  F9  8D  8F"), ClientHandle));
	//AddOffset(StaticOffset(_ShouldSkipAnimFrame, 0, ("57  8B  F9  8B  07  8B  80  ??  ??  ??  ??  FF  D0  84  C0  75  02"), ClientHandle));
	AddOffset(StaticOffset(_UpdateTargets, 0, ("55  8B  EC  83  E4  F0  81  EC  ??  ??  ??  ??  33  D2"), ClientHandle));
	AddOffset(StaticOffset(_AttachmentHelper, 0, ("55  8B  EC  83  EC  48  53  8B  5D  08  89  4D  F4"), ClientHandle));
	AddOffset(StaticOffset(_Wrap_SolveDependencies, 0, ("55  8B  EC  83  E4  F0  81  EC  ??  ??  ??  ??  8B  81  ??  ??  ??  ??"), ClientHandle));
	AddOffset(StaticOffset(_g_VecRenderOrigin, 0, ("8B  45  08  F3  0F  7E  04  8D"), ClientHandle, 1, 8, 0, 0));
	AddOffset(StaticOffset(_CacheVehicleView, 0, ("A1  ??  ??  ??  ??  56  8B  F1  8B  96  ??  ??  ??  ??  3B  50  04  74  67  8B  8E  ??  ??  ??  ??  83  F9  FF  74  5C  0F  B7  C1  C1  E0  04  05  ??  ??  ??  ??  C1  E9  10  39  48  04  75  49  8B  08  85  C9  74  43  8B  01  57  FF  90  ??  ??  ??  ??"), ClientHandle));
	//AddOffset(StaticOffset(_IsInAVehicle, 0, ("8B  89  ??  ??  ??  ??  83  F9  FF  74  1B  0F  B7  C1  C1  E0  04  05  ??  ??  ??  ??  C1  E9  10  39  48  04  75  08  8B  00  85  C0  0F  95  C0  C3  33  C0  85  C0  0F  95  C0  C3  CC  CC  56"), ClientHandle));
	AddOffset(StaticOffset(_GetObserverModeVMT, 0, ("56  8B  F1  80  BE  ??  ??  ??  ??  00  0F  84  ??  ??  ??  ??  8B  06  FF  90  ??  ??  00  00  85  C0  74  ??  B0  01"), ClientHandle, 1, 20, 4));//"56  8B  F1  80  BE  ??  ??  00  00  00  74  7D  8B  06  FF  90  ??  ??  00  00"), ClientHandle, 1, 16, 4, 0));
	AddOffset(StaticOffset(_BaseCalcView, 0, ("55  8B  EC  56  8B  F1  57  8B  8E  ??  ??  ??  ??  83  F9  FF  74  3E  0F  B7  C1  C1  E0  04  05  ??  ??  ??  ??  C1  E9  10  39  48  04  75  2B  8B  08  85  C9  74  25  8B  01"), ClientHandle));
	AddOffset(StaticOffset(_m_bThirdPerson, 0, ("80  BE  ??  ??  ??  ??  ??  74  ??  8B  06  8B  CE  8B  80  ??  ??  ??  ??  FF  D0  84  C0  75  ??  38"), ClientHandle, 1, 2, 0, 0));
	AddOffset(StaticOffset(_LookupBone, 0, ("55  8B  EC  53  56  8B  F1  57  83  BE  ??  ??  ??  ??  ??  75  14  8B  46  04  8D  4E  04  FF  50  20"), ClientHandle));
	AddOffset(StaticOffset(_m_rgflCoordinateFrame, 0, ("F3  0F  59  C4  F3  0F  58  D0  F3  0F  10  83  ??  ??  00  00"), ClientHandle, 1, 0xC, 0, 0));
	AddOffset(StaticOffset(_GameRules, 0, ("8B  0D  ??  ??  ??  ??  FF  B3  ??  ??  00  00  FF  77  08"), ClientHandle, 1, 2));//"8B  0D  ??  ??  ??  ??  FF  B3  70  04  00  00  FF  77  08  8B  01  8B  40  70  FF  D0  84  C0  74  14  8B  47  0C  85  C0  74  16  FF  75  0C  56  FF  D0  83  C4  08  84  C0"), ClientHandle, 1, 2, 0, 0));
	AddOffset(StaticOffset(_PlayFootstepSound, 0, ("05  ??  00  00  00  51  C7  04  24  00  00  80  3F  FF  B1  ??  ??  00  00  50  FF  92  ??  ??  00  00"), ClientHandle, 1, 22, 4));//"05  ??  00  00  00  C7  04  24  00  00  80  3F  FF  B1  ??  ??  00  00  50  FF  92  ??  ??  00  00"), ClientHandle, 1, 21, 4, 0));
	AddOffset(StaticOffset(_VehicleViewOrigin, 0, ("F3  0F  7E  87  ??  ??  00  00  66  0F  D6  00"), ClientHandle, 1, 4, 0, 0));
	AddOffset(StaticOffset(_GetClientVehicle, 0, ("8B  01  FF  90  ??  ??  00  00  85  C0  74  10  8B  CE"), ClientHandle, 1, 4, 4, 0));
	AddOffset(StaticOffset(_SplitScreenPlayerSlot, 0, ("8B  87  ??  ??  00  00  5F  8D  0C  40"), ClientHandle, 1, 2, 0, 0));
	AddOffset(StaticOffset(_m_bUseAnimationEyeOffset, 0, ("55  8B  EC  56  8B  75  08  57  8B  F9  56  8B  07  FF  90  ??  ??  00  00  80  BF  ??  ??  00  00  00"), ClientHandle, 1, 21, 0, 0));
	AddOffset(StaticOffset(_m_pRagdoll, 0, ("83  B9  ??  ??  00  00  00  74  0D  80  B9  ??  ??  00  00  00  0F  85"), ClientHandle, 1, 2, 0, 0));
	AddOffset(StaticOffset(_LookupPoseParameter, 0, ("55  8B  EC  57  8B  7D  08  85  FF  75  08  83  C8  FF  5F  5D  C2  08  00"), ClientHandle));
	AddOffset(StaticOffset(_GetPoseParameterRange, 0, ("55  8B  EC  56  8B  F1  83  BE  ??  ??  00  00  00  75  14  8B  46  04  8D  4E  04  FF  50  20  85  C0  74  07  8B  CE  E8  ??  ??  ??  ??  8B  8E  ??  ??  00  00  85  C9  74  49  83  39  00  74  44  8B  55  08  85  D2"), ClientHandle));//"55  8B  EC  56  8B  F1  83  BE  3C  29  00  00  00  75  14  8B  46  04  8D  4E  04  FF  50  20  85  C0  74  07  8B  CE  E8  ??  ??  ??  ??  8B  8E  3C  29  00  00  85  C9  74  49  83  39  00  74  44  8B  55  08  85  D2  78  3D  8B  41  04  85  C0  75  12  8B  01  85  C0  74  08  8B  80  2C  01  00  00  EB  07"), ClientHandle));
	AddOffset(StaticOffset(_SetGroundEntity, 0, ("55  8B  EC  56  8B  F1  57  8B  8E  ??  ??  00  00  83  F9  FF  74  17"), ClientHandle));//"55  8B  EC  56  8B  F1  57  8B  8E  4C  01  00  00"), ClientHandle));
	AddOffset(StaticOffset(_SurfaceFriction, 0, ("F3  0F  59  45  FC  F3  0F  59  80  ??  ??  00  00  F3  0F  5C  D0"), ClientHandle, 1, 9, 0, 0));
	AddOffset(StaticOffset(_m_chTextureType, 0, ("8B  81  ??  ??  00  00  8A  40  ??  88  81  ??  ??  00  00  5D  C2  04  00"), ClientHandle, 1, 11, 0, 0));
	AddOffset(StaticOffset(_m_flWaterJumpTime, 0, ("F3  0F  10  80  ??  ??  00  00  0F  2E  C6  9F  F6  C4  44  0F  8A"), ClientHandle, 1, 4, 0, 0));
	AddOffset(StaticOffset(_m_hPlayerAnimState, 0, ("83  BE  ??  ??  ??  ??  ??  0F  84  ??  ??  ??  ??  F6  86  ??  ??  ??  ??  ??  0F  85"), ClientHandle, 1, 2, 0, 0));
	AddOffset(StaticOffset(_GetCompetitiveMatchID, 0, ("55  8B  EC  A1  ??  ??  ??  ??  83  EC  08  D1  E8  56  57  A8  01  74  59  8B  0D  ??  ??  ??  ??  8B  C1  8B  35  ??  ??  ??  ??  85  C9  75  03  8B  46  08  8B  40  30  C1  E8  04  A8  01  74  3A"), ClientHandle));
	AddOffset(StaticOffset(_IsPaused, 0, ("80  B9  ??  ??  00  00  00  75  62  80  3D  ??  ??  ??  ??  00  74  28  83  3D  ??  ??  ??  ??  02  7C  0C  83  3D  ??  ??  ??  ??  01  0F  9E  C0  EB  0F"), EngineHandle));
	AddOffset(StaticOffset(_host_tickcount, 0, ("A1  ??  ??  ??  ??  33  D2  8B  3D  ??  ??  ??  ??  8B  D8"), EngineHandle, 1, 1));
	AddOffset(StaticOffset(_predictionrandomseed, 0, ("8B  0D  ??  ??  ??  ??  BA  ??  ??  ??  ??  E8  ??  ??  ??  ??  83  C4  04"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_predictionplayer, 0, ("83  3D  ??  ??  ??  ??  00  74  ??  51  8B  0D"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_MD5PseudoRandom, 0, ("55  8B  EC  83  E4  F8  83  EC  70  6A  58"), ClientHandle));
	AddOffset(StaticOffset(_IsPausedExtrapolateReturnAddress, 0, ("FF  D0  A1  ??  ??  ??  ??  B9  ??  ??  ??  ??  D9  1D  ??  ??  ??  ??  FF  50  34  85  C0  74  22  8B  0D  ??  ??  ??  ??"), ClientHandle, 1, 0x29));
	AddOffset(StaticOffset(_g_pClientLeafSystem, 0, ("E8  ??  ??  ??  ??  85  C0  74  0B  8D  48  04  8B  01  FF  50  1C"), ClientHandle, 1, 0x15));
	AddOffset(StaticOffset(_StandardFilterRulesCallOne, 0, ("8B  89  4C  01  00  00  83  F9  FF  74  16  0F  B7  C1  C1  E0  04  05  ??  ??  ??  ??  C1  E9  10  39  48  04  75  03  8B  00  C3  33  C0  C3"), ClientHandle));
	AddOffset(StaticOffset(_SetAbsVelocity, 0, ("55  8B  EC  83  E4  F8  83  EC  0C  53  56  57  8B  7D  08  8B  F1  F3  0F  10  07  0F  2E  86  94  00  00  00  9F  F6  C4  44  7A  28  F3  0F  10  47  04  0F  2E  86  98  00  00  00  9F  F6  C4  44  7A  16  F3  0F  10  47  08  0F  2E  86  9C  00  00  00  9F  F6  C4  44  0F  8B  72  01  00  00  6A  04"), ClientHandle));
	AddOffset(StaticOffset(_UpdateClientSideAnimationFunction, 0, ("55  8B  EC  51  56  8B  F1  80  BE  ??  ??  00  00  00  74  36  8B  06  FF  90  ??  ??  00  00"), ClientHandle));
	AddOffset(StaticOffset(_frametime1, 0, ("F3  0F  10  05  ??  ??  ??  ??  F3  0F  10  1D  ??  ??  ??  ??  F3  0F  10  15  ??  ??  ??  ??  51  F3  0F  11  04  24  8D  4D  A8"), EngineHandle, 1, 4));
	AddOffset(StaticOffset(_frametime2, 0, ("F3  0F  10  05  ??  ??  ??  ??  F3  0F  10  1D  ??  ??  ??  ??  F3  0F  10  15  ??  ??  ??  ??  51  F3  0F  11  04  24  8D  4D  A8"), EngineHandle, 1, 12));
	AddOffset(StaticOffset(_frametime3, 0, ("F3  0F  10  05  ??  ??  ??  ??  F3  0F  10  1D  ??  ??  ??  ??  F3  0F  10  15  ??  ??  ??  ??  51  F3  0F  11  04  24  8D  4D  A8"), EngineHandle, 1, 20));
	AddOffset(StaticOffset(_ClientSideAnimationList, 0, ("A1  ??  ??  ??  ??  F6  44  F0  04  01  74  0B"), ClientHandle, 1, 1));
	AddOffset(StaticOffset(_EnableInvalidateBoneCache, 0, ("C6  05  ??  ??  ??  ??  00  F3  0F  5F  05  ??  ??  ??  ??  F3  0F  11  47  74"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_RadarBase, 0, ("A1  ??  ??  ??  ??  ??  3C  B0  85  FF  74  62  80  3B  00"), ClientHandle, 1, 1));
	AddOffset(StaticOffset(_IsEntityBreakable_FirstCall_Arg1, 0, ("6A  00  68  ??  ??  ??  ??  68  ??  ??  ??  ??  6A  00  56  E8  ??  ??  ??  ??  83  C4  14  85  C0  74  12  8B  10  8B  C8  FF  12"), ClientHandle, 1, 8));
	AddOffset(StaticOffset(_IsEntityBreakable_FirstCall_Arg2, 0, ("6A  00  68  ??  ??  ??  ??  68  ??  ??  ??  ??  6A  00  56  E8  ??  ??  ??  ??  83  C4  14  85  C0  74  12  8B  10  8B  C8  FF  12"), ClientHandle, 1, 3));
	AddOffset(StaticOffset(_IsEntityBreakable_SecondCall_Arg1, 0, ("6A  00  68  ??  ??  ??  ??  68  ??  ??  ??  ??  6A  00  56  E8  ??  ??  ??  ??  8B  C8  83  C4  14  85  C9  74  17  8B  01  8B  40  0C  FF  D0"), ClientHandle, 1, 8));
	AddOffset(StaticOffset(_IsEntityBreakable_SecondCall_Arg2, 0, ("6A  00  68  ??  ??  ??  ??  68  ??  ??  ??  ??  6A  00  56  E8  ??  ??  ??  ??  8B  C8  83  C4  14  85  C9  74  17  8B  01  8B  40  0C  FF  D0"), ClientHandle, 1, 3));
	AddOffset(StaticOffset(_IsEntityBreakable_ActualCall, 0, ("6A  18  68  ??  ??  ??  ??  E8  ??  ??  ??  ??  8B  7D  08"), ClientHandle));
	AddOffset(StaticOffset(_WeaponScriptPointer, 0, ("B9  ??  ??  ??  ??  50  FF  56  08  8B  F8  85  FF"), ClientHandle, 1, 1));
	AddOffset(StaticOffset(_WeaponScriptPointerCall, 0, ("55  8B  EC  51  53  8B  D9  8B  0D  ??  ??  ??  ??  56  57  8B  B9  0C  10  00  00"), ClientHandle));
	AddOffset(StaticOffset(_GetWeaponSystem, 0, ("B9  ??  ??  ??  ??  50  FF  56  08  5E"), ClientHandle, 1, 1, 0, 0));
	AddOffset(StaticOffset(_Input, 0, ("A1  ??  ??  ??  ??  B9  ??  ??  ??  ??  FF  90  8C"), ClientHandle, 1, 1));
	AddOffset(StaticOffset(_oSetupBones, 0, ("55  8B  EC  56  8B  F1  51  8D  4E  FC"), ClientHandle));
	AddOffset(StaticOffset(_host_interval_per_tick, 0, ("F3  0F  10  05  ??  ??  ??  ??  84  C0"), EngineHandle, 1, 4));
	AddOffset(StaticOffset(_GetSequenceName, 0, ("55  8B  EC  83  7D  08  FF  56  8B  F1  75"), ClientHandle));
	AddOffset(StaticOffset(_GetSequenceActivity, 0, ("55  8B  EC  53  8B  5D  08  56  8B  F1  83  FB  FF"), ClientHandle));
	AddOffset(StaticOffset(_GetSequenceActivityNameForModel, 0, ("85  C9  74  61  85  D2  78  22  8B  41  04  85  C0  75  0A  8B  01  8B  80  ??  ??  ??  ??  EB  03  8B  40  ??  3B  D0  7D  0A  52  E8  ??  ??  ??  ??  03  40  08"), ClientHandle));
	AddOffset(StaticOffset(_ActivityListNameForIndex, 0, ("56  8B  35  ??  ??  ??  ??  33  C0  85  F6  7E  ??  8B  15  ??  ??  ??  ??"), ClientHandle));
	AddOffset(StaticOffset(_pSeqDesc, 0, ("55  8B  EC  83  79  04  00  75  25"), ClientHandle));
	AddOffset(StaticOffset(_svtable, 0, ("8B  0D  ??  ??  ??  ??  8B  01  8B  40  10  FF  D0  84  C0  75  ??  A1  ??  ??  ??  ??  83  F8  02"), EngineHandle, 1, 2));
	AddOffset(StaticOffset(_hoststate, 0, ("8B  0D  ??  ??  ??  ??  8B  01  8B  40  10  FF  D0  84  C0  75  ??  A1  ??  ??  ??  ??  83  F8  02"), EngineHandle, 1, 0x12));
	//AddOffset(StaticOffset(_CL_Move, 0, ("55  8B  EC  81  EC  64  01  00  00  53  56  57"), EngineHandle));
	AddOffset(StaticOffset(_WriteUserCmd, 0, ("55  8B  EC  83  E4  F8  51  53  56  8B  D9"), ClientHandle));
	AddOffset(StaticOffset(_pCommands, 0, ("B8  ??  ??  ??  ??  F7  EE  8B  CE"), ClientHandle, 1, 1));
	AddOffset(StaticOffset(_SetupVelocityReturnAddress, 0, ("84  C0  75  38  8B  0D  ??  ??  ??  ??  8B  01  8B  80"), ClientHandle));
	AddOffset(StaticOffset(_CL_FireEvents, 0, ("55  8B  EC  83  EC  08  53  8B  1D  ??  ??  ??  ??  56  57  83  BB  ??  ??  00  00  06"), EngineHandle));
	AddOffset(StaticOffset(_AbsRecomputationEnabled, 0, ("0F  B6  0D  ??  ??  ??  ??  33  D2  84  C0  0F  45  CA  88  0D  ??  ??  ??  ??  FF  D6  0F  B6  0D  ??  ??  ??  ??  33  D2"), ClientHandle, 1, 3));
	AddOffset(StaticOffset(_AbsQueriesValid, 0, ("0F  B6  0D  ??  ??  ??  ??  33  D2  84  C0  0F  45  CA  88  0D  ??  ??  ??  ??  FF  D6  0F  B6  0D  ??  ??  ??  ??  33  D2"), ClientHandle, 1, 25));
	AddOffset(StaticOffset(_ResetAnimationState, 0, ("56  6A  01  68  ??  ??  ??  ??  8B  F1"), ClientHandle));
	AddOffset(StaticOffset(_ProcessOnDataChangedEvents, 0, ("55  8B  EC  51  8B  0D  ??  ??  ??  ??  53  56  57  8B  01"), ClientHandle));
	AddOffset(StaticOffset(_pTempEnts, 0, ("A1  ??  ??  ??  ??  B9  ??  ??  ??  ??  FF  50  14  A1"), ClientHandle, 1, 1));
	AddOffset(StaticOffset(_pBeams, 0, ("A1  ??  ??  ??  ??  B9  ??  ??  ??  ??  FF  50  14  A1"), ClientHandle, 1, 0xE));
	AddOffset(StaticOffset(_Net_Time, 0, ("F2  0F  10  05  ??  ??  ??  ??  8B  CF"), EngineHandle, 1, 4));
	AddOffset(StaticOffset(_SequenceDuration, 0, ("55  8B  EC  56  8B  F1  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  83  C4  04  5E  5D  C2  04  00  52  68  ??  ??  ??  ??  6A  02"), ClientHandle));
	AddOffset(StaticOffset(_GetFirstSequenceAnimTag, 0, ("55  8B  EC  56  8B  F1  83  BE  ??  ??  00  00  00  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  FF  75  0C  E8  ??  ??  ??  ??  83  C4  08  5E  5D  C2  0C  00"), ClientHandle));
	AddOffset(StaticOffset(_GameTypes, 0, ("8B  0D  ??  ??  ??  ??  8B  01  FF  50  20  83  F8  04  75  13  8B  0D"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_SurpressLadderChecks, 0, ("55  8B  EC  83  EC  0C  A1  ??  ??  ??  ??  56  57  8B  F9  F3  0F  10  48  10"), ClientHandle));
	AddOffset(StaticOffset(_s_nTraceFilterCount, 0, ("8B  15  ??  ??  ??  ??  83  FA  08  7C  06  33  C0"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_s_TraceFilter, 0, ("8B  15  ??  ??  ??  ??  83  FA  08  7C  06  33  C0"), ClientHandle, 1, 0x19));
	AddOffset(StaticOffset(_IsCarryingHostage, 0, ("55  8B  EC  8B  09  83  F9  FF"), ClientHandle));
	AddOffset(StaticOffset(_EyeVectors, 0, ("55  8B  EC  56  8B  F1  8B  96  ??  ??  ??  ??  83  FA  FF  74  48"), ClientHandle));
	AddOffset(StaticOffset(_CreateStuckTable, 0, ("55  8B  EC  83  EC  0C  83  3D  ??  ??  ??  ??  00  0F  84  ??  ??  ??  ??  68  ??  ??  ??  ??"), ClientHandle));
	AddOffset(StaticOffset(_rgv3tStuckTable, 0, ("55  8B  EC  83  EC  0C  83  3D  ??  ??  ??  ??  00  0F  84  ??  ??  ??  ??  68  ??  ??  ??  ??"), ClientHandle, 1, 0x1B));
	AddOffset(StaticOffset(_LevelShutdownPreEntity, 0, ("8B  0D  ??  ??  ??  ??  8B  0C  B9  E8  ??  ??  ??  ??  83  EF  01  79  ED  8B  06  8B  CE  5F  5E  FF  A0  88  00  00  00"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_LevelInitPreEntity, 0, ("A1  ??  ??  ??  ??  8B  3D  ??  ??  ??  ??  8B  1C  88  8B  CF"), ClientHandle, 1, 1));
	AddOffset(StaticOffset(_RenderViewTrap1, 0, ("A1  ??  ??  ??  ??  89  0D  ??  ??  ??  ??  8B  08  8B  C1  81  F1  15  23  1A  30  35  33  0D  50  AE  09  05  ??  ??  ??  ??  89  0D  ??  ??  ??  ??"), ClientHandle, 1, 28));
	AddOffset(StaticOffset(_RenderViewTrap2, 0, ("A1  ??  ??  ??  ??  89  0D  ??  ??  ??  ??  8B  08  8B  C1  81  F1  15  23  1A  30  35  33  0D  50  AE  09  05  ??  ??  ??  ??  89  0D  ??  ??  ??  ??"), ClientHandle, 1, 34));
	AddOffset(StaticOffset(_CHLClientTrap2, 0, ("A1  ??  ??  ??  ??  35  2C  E5  C2  46  A3  ??  ??  ??  ??  A1  ??  ??  ??  ??  5F  8B  00  35  00  25  88  E9  A3  ??  ??  ??  ??"), ClientHandle, 1, 11));
	AddOffset(StaticOffset(_EngineClientTrap2, 0, ("A1  ??  ??  ??  ??  35  2C  E5  C2  46  A3  ??  ??  ??  ??  A1  ??  ??  ??  ??  5F  8B  00  35  00  25  88  E9  A3  ??  ??  ??  ??"), ClientHandle, 1, 29));
	AddOffset(StaticOffset(_LevelShutdownCHLClientTrap, 0, ("A1  ??  ??  ??  ??  35  DA  BD  D8  A4  09  05  ??  ??  ??  ??  A1  ??  ??  ??  ??  8B  00  35  05  9E  CD  C7  09  05  ??  ??  ??  ??"), ClientHandle, 1, 12));
	AddOffset(StaticOffset(_LevelShutdownEngineClientTrap, 0, ("A1  ??  ??  ??  ??  35  DA  BD  D8  A4  09  05  ??  ??  ??  ??  A1  ??  ??  ??  ??  8B  00  35  05  9E  CD  C7  09  05  ??  ??  ??  ??"), ClientHandle, 1, 30));
	AddOffset(StaticOffset(_LocalPlayerEntityTrap, 0, ("8B  06  35  D4  2D  14  39  09  05"), ClientHandle, 1, 9));
	AddOffset(StaticOffset(_ModelRenderGlow, 0, ("8B  0D  ??  ??  ??  ??  53  8B  01  FF  90  B0  00  00  00"), ClientHandle, 1, 2)); //NOTE: FIX HookModelRenderGlow VFUNC INDEX IF THIS CHANGES
	AddOffset(StaticOffset(_ModelRenderGlowTrap, 0, ("A1  ??  ??  ??  ??  89  0D  ??  ??  ??  ??  8B  08  8B  C1  35  AC  14  F5  08  81  F1  81  99  CD  BC  09  05  ??  ??  ??  ??  A1  ??  ??  ??  ??  89  0D  ??  ??  ??  ??"), ClientHandle, 1, 28));
	AddOffset(StaticOffset(_ModelRenderGlowTrap2, 0, ("A1  ??  ??  ??  ??  89  0D  ??  ??  ??  ??  8B  08  8B  C1  35  AC  14  F5  08  81  F1  81  99  CD  BC  09  05  ??  ??  ??  ??  A1  ??  ??  ??  ??  89  0D  ??  ??  ??  ??"), ClientHandle, 1, 39));
	AddOffset(StaticOffset(_PredictionUpdateHLTVCall, 0, ("55  8B  EC  83  E4  F8  81  EC  ??  ??  ??  ??  53  8B  1D  ??  ??  ??  ??  56  57  85  DB  0F  84  ??  ??  ??  ??  8B  CB  E8  ??  ??  ??  ??  84  C0  0F  84  ??  ??  ??  ??  A1  ??  ??  ??  ??  8B  40  1C"), ClientHandle));
	AddOffset(StaticOffset(_GetBonePosition, 0, ("55  8B  EC  83  E4  F8  56  8B  F1  57  83  BE  ??  ??  ??  ??  ??  75  14  8B  46  04  8D  4E  04  FF  50  20  85  C0  74  07  8B  CE  E8  ??  ??  ??  ??  8B  86"), ClientHandle));
	AddOffset(StaticOffset(_LookupBone, 0, ("55  8B  EC  53  56  8B  F1  57  83  BE  ??  ??  ??  ??  ??  75  14  8B  46  04  8D  4E  04  FF  50  20"), ClientHandle));
	//AddOffset(StaticOffset(_GetNetChannelInfoCvarCheck, 0, ("8B  C8  85  C9  0F  84  ??  ??  ??  ??  8B  01  8B  40  ??  FF  D0  6A  ??  50  8D  4C  24  ??  E8  ??  ??  ??  ??  8D  44  24  ??  50"), ClientHandle));
	AddOffset(StaticOffset(_IClientEntityList, 0, ("A1  ??  ??  ??  ??  FF  10  A1  ??  ??  ??  ??  8D  8B"), ClientHandle, 1, 1));
	AddOffset(StaticOffset(_RenderBeams, 0, ("A1  ??  ??  ??  ??  56  8B  F1  B9  ??  ??  ??  ??  FF  50  08"), ClientHandle, 1, 1));
	//AddOffset(StaticOffset(_DirectXPrePointer, 0, ("A1  ??  ??  ??  ??  50  8B  08  FF  51  0C"), SHADERAPIDX9Handle, 1, 1));
	AddOffset(StaticOffset(_TE_EffectDispatch, 0, ("B8  ??  ??  ??  ??  C3  CC  CC  CC  CC  CC  CC  CC  CC  CC  CC  55  8B  EC  83  E4  F8  83  EC  20"), ClientHandle, 1, 1));
	AddOffset(StaticOffset(_MoveHelperClient, 0, ("8B  0D  ??  ??  ??  ??  8B  46  08  68"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_FormatViewModelAttachment, 0, ("FF  90  ??  ??  00  00  8D  45  ??  46  50  56  8B  CF"), ClientHandle, 1, 2, 4));
	AddOffset(StaticOffset(_GroupStudioHdr, 0, ("55  8B  EC  56  8B  F1  57  85  F6"), ClientHandle));
	AddOffset(StaticOffset(_Attachments, 0, ("8B  92  ??  ??  00  00  8D  0C  80  53  8B  1D"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_AnimOverlay, 0, ("8B  87  ??  ??  00  00  39  54  F0  18  0F  8D"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_GetPlayerMaxSpeedVMT, 0, ("8B  80  ??  ??  00  00  FF  D0  8B  47  08"), ClientHandle, 1, 2, 4));
	AddOffset(StaticOffset(_PlayClientJumpSound, 0, ("FF  90  ??  ??  00  00  8B  8F  ??  ??  00  00  80  B9  ??  ??  00  00  00  75  0F"), ClientHandle, 1, -12, 4)); //FF  90  ??  ??  00  00  8B  8E  54  0E  00  00  80  B9  ??  ??  00  00  00
	AddOffset(StaticOffset(_PlayClientUnknownSound, 0, ("FF  90  ??  ??  00  00  8B  8F  ??  ??  00  00  80  B9  ??  ??  00  00  00  75  0F"), ClientHandle, 1, 2, 4)); //FF  90  ??  ??  00  00  8B  8E  54  0E  00  00  80  B9  ??  ??  00  00  00
	AddOffset(StaticOffset(_DoAnimationEvent1, 0, ("8B  89  ??  ??  00  00  6A  00  6A  08  8B  01  FF  50  ?? "), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_DoAnimationEvent2, 0, ("8B  89  ??  ??  00  00  6A  00  6A  08  8B  01  FF  50  ?? "), ClientHandle, 0, 0, 0, 14));
	AddOffset(StaticOffset(_ResetLatched, 0, ("FF  90  ??  ??  00  00  46  3B  B7  ??  ??  ??  ??  7C  E2"), ClientHandle, 1, 2, 4));
	AddOffset(StaticOffset(_GetDefaultFOV, 0, ("8B  06  8B  CE  FF  90  ??  ??  00  00  8B  CF  66  0F  6E  C0  0F  5B  C0"), ClientHandle, 1, 6, 4));
	AddOffset(StaticOffset(_UpdateStepSound, 0, ("FF  96  ??  ??  ??  ??  8B  07  8B  CF  FF  90  ??  ??  ??  ??  8B  07  8B  CF  FF  90  ??  ??  ??  ??  8B  47  04  5E  80  B8  ??  ??  ??  ??  ??  75  38  F6  80  ??  ??  ??  ??  ??  75  2F  8B  07  8B  CF  8B  80  ??  ??  ??  ??  "), ClientHandle, 1, 2, 4));
	AddOffset(StaticOffset(_IsTaunting, 0, ("8D  4E  FC  8B  80  ??  ??  00  00  FF  D0  84  C0  75  ??  8B  06"), ClientHandle, 1, 5, 4));
	AddOffset(StaticOffset(_IsInThirdPersonTaunt, 0, ("8B  80  ??  ??  00  00  FF  D0  84  C0  74  ??  8B  45  0C  32  DB  C7"), ClientHandle, 1, 2, 4));
	AddOffset(StaticOffset(_IsBotPlayerResourceOffset, 0, ("8D  B8  ??  ??  ??  ??  85  FF  74  1D  8B  41  08  83  C1  08  56  8B  37  FF  50  28  50  8B  46  18"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_StepSoundTime, 0, ("F3  0F  5F  05  ??  ??  ??  ??  57  6A  00  C7  80  ??  ??  00  00  00  00  C8  43"), ClientHandle, 1, 13));
	AddOffset(StaticOffset(_m_StuckLast, 0, ("8D  46  01  89  81  ??  ??  00  00  B8"), ClientHandle, 1, 5));
	AddOffset(StaticOffset(_m_VPhysicsObject, 0, ("8B  91  ??  ??  00  00  85  D2  74  12  8B  02  8B  CA"), ClientHandle, 1, 2));//"8B  88  ??  ??  00  00  85  C9  74  0D  8B  01  FF  50  4C"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_m_vecWaterJumpVel, 0, ("F3  0F  5C  C1  F3  0F  11  80  ??  ??  00  00  F3  0F  10  4D  90"), ClientHandle, 1, 8));
	AddOffset(StaticOffset(_m_flSwimSoundTime, 0, ("C7  80  ??  ??  00  00  00  00  7A  44  8B  46  08"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_m_SurfaceProps, 0, ("0F  BF  52  40  89  91  ??  ??  00  00"), ClientHandle, 1, 6));
	AddOffset(StaticOffset(_m_iSurfaceData, 0, ("05  ??  00  00  00  51  C7  04  24  00  00  80  3F  FF  B1  ??  ??  00  00  50  FF  92  ??  ??  00  00"), ClientHandle, 1, 0xF));//"05  ??  00  00  00  C7  04  24  00  00  80  3F  FF  B1  ??  ??  00  00  50  FF  92  ??  ??  00  00"), ClientHandle, 1, 14));
	AddOffset(StaticOffset(_m_flTimeNotOnLadder, 0, ("0F  2F  81  ??  ??  ??  ??  0F  82  ??  ??  ??  ??  F3  0F  10  0D"), ClientHandle, 1, 3));
	AddOffset(StaticOffset(_m_vecDuckingOrigin, 0, ("F3  0F  10  89  ??  ??  00  00  F3  0F  10  81  ??  ??  00  00  F3  0F  5C  40  04  F3  0F  5C  08"), ClientHandle, 1, 4));
	AddOffset(StaticOffset(_m_duckUntilOnGround, 0, ("80  B8  ??  ??  00  00  00  74  0D  F6  41  ??  04"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_m_bServerSideJumpAnimation, 0, ("80  B9  ??  ??  ??  ??  00  75  0F  8B  89  ??  ??  ??  ??  6A  00"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_m_bSlowMovement, 0, ("80  B9  ??  ??  00  00  00  0F  85  ??  ??  ??  ??  8B  46  08"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_m_bHasWalkMovedSinceLastJump, 0, ("C6  81  ??  ??  00  00  00  8B  4E  04"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_GetWeaponMaxSpeedVMT, 0, ("8B  07  8B  CF  8B  80  ??  ??  00  00  FF  D0  8B  07  8B  CF  D8  4C  24  ??"), ClientHandle, 1, 6, 4));
	AddOffset(StaticOffset(_GetWeaponMaxSpeed2VMT, 0, ("8B  80  ??  ??  00  00  FF  D0  D8  4C  24  24  D9  5C  24  24"), ClientHandle, 1, 2, 4));
	//AddOffset(StaticOffset(_WeaponOnJumpVMT, 0, ("8B  C8  F3  0F  11  04  24  FF  92  ??  ??  00  00  8B  E5  5D  C2  04  00"), ClientHandle, 1, 9, 4));
	AddOffset(StaticOffset(_WeaponOnJumpVMT, 0, ("8B  10  F3  0F  ??  ??  ??  ??  51  8B  C8  F3  ??  ??  ??  ??  FF  92  ??  ??  ??  ??  80  BE"), ClientHandle, 1, 18, 4));
	AddOffset(StaticOffset(_WeaponGetZoomLevelVMT, 0, ("8B  80  ??  ??  00  00  D9  5C  24  1C  FF  D0  F3  0F  10  54  24  ??  F3  0F  11  54  24  ??"), ClientHandle, 1, 2, 4));
	AddOffset(StaticOffset(_WeaponGetNumZoomLevelsVMT, 0, ("8B  07  8B  CF  8B  80  ??  ??  00  00  FF  D0  F3  0F  10  54  24  ??  83  F8  01"), ClientHandle, 1, 6, 4));//"8B  80  ??  ??  00  00  FF  D0  83  F8  01  7E  2D  8B  07"), ClientHandle, 1, 2, 4));
	AddOffset(StaticOffset(_m_bInReload, 0, ("F6  41  24  01  74  2E  80  BA  ??  ??  00  00  00  75  25"), ClientHandle, 1, 8));
	AddOffset(StaticOffset(_ParallelProcess, 0, ("55  8B  EC  83  EC  08  53  8B  5D  0C  56  8B  F1  57  85  DB  0F  84  ??  ??  ??  ??  A1  ??  ??  ??  ??  8B  55  08  8B  CA  C7  46  ??  ??  ??  ??  ??  8B  38  8D  46  0C  89  7D  FC  87  08  8D  04  9A  4B  89  46  10  85  FF  0F  84  ??  ??  ??  ??  8B  07  8B  CF  FF  50  1C  3B  D8  0F  4F  D8  89  5D  F8  85  DB"), EngineHandle));
	AddOffset(StaticOffset(_ParallelQueueVT1, 0, ("55  8B  EC  83  EC  08  53  8B  5D  0C  56  8B  F1  57  85  DB  0F  84  ??  ??  ??  ??  A1  ??  ??  ??  ??  8B  55  08  8B  CA  C7  46  ??  ??  ??  ??  ??  8B  38  8D  46  0C  89  7D  FC  87  08  8D  04  9A  4B  89  46  10  85  FF  0F  84  ??  ??  ??  ??  8B  07  8B  CF  FF  50  1C  3B  D8  0F  4F  D8  89  5D  F8  85  DB"), EngineHandle, 1, 0x8E));
	AddOffset(StaticOffset(_ParallelQueueVT2, 0, ("55  8B  EC  83  EC  08  53  8B  5D  0C  56  8B  F1  57  85  DB  0F  84  ??  ??  ??  ??  A1  ??  ??  ??  ??  8B  55  08  8B  CA  C7  46  ??  ??  ??  ??  ??  8B  38  8D  46  0C  89  7D  FC  87  08  8D  04  9A  4B  89  46  10  85  FF  0F  84  ??  ??  ??  ??  8B  07  8B  CF  FF  50  1C  3B  D8  0F  4F  D8  89  5D  F8  85  DB"), EngineHandle, 1, 0x95));
	AddOffset(StaticOffset(_DoExecute, 0, ("55  8B  EC  83  EC  08  53  8B  5D  0C  56  8B  F1  57  85  DB  0F  84  ??  ??  ??  ??  A1  ??  ??  ??  ??  8B  55  08  8B  CA  C7  46  ??  ??  ??  ??  ??  8B  38  8D  46  0C  89  7D  FC  87  08  8D  04  9A  4B  89  46  10  85  FF  0F  84  ??  ??  ??  ??  8B  07  8B  CF  FF  50  1C  3B  D8  0F  4F  D8  89  5D  F8  85  DB"), EngineHandle, 1, 0x9C));
	AddOffset(StaticOffset(_AbortJob, 0, ("57  8B  F9  8B  47  ??  83  F8  01  74  ??  83  F8  02  74  ??  83  F8  04  75  ??  53"), EngineHandle));
	AddOffset(StaticOffset(_ShotgunSpread, 0, ("55  8B  EC  83  EC  10  56  8B  75  08  8D  45  F4  50  B9  ??  ??  ??  ??"), ClientHandle));
	AddOffset(StaticOffset(_GetClassnameVMT, 0, ("74  36  8B  01  FF  90  ??  ??  00  00"), ClientHandle, 1, 6, 4));
	AddOffset(StaticOffset(_GetMaxHealthVMT, 0, ("FF  90  ??  ??  00  00  85  C0  0F  8F  ??  ??  ??  ??  80  BE  ??  ??  00  00  02"), ClientHandle, 1, 2, 4));
	AddOffset(StaticOffset(_TakeDamage, 0, ("FF  90  ??  ??  00  00  85  C0  0F  8F  ??  ??  ??  ??  80  BE  ??  ??  00  00  02"), ClientHandle, 1, 16));
	AddOffset(StaticOffset(_PhysicsSolidMaskForEntityVMT, 0, ("8B  06  8B  CE  FF  90  ??  ??  00  00  A9  00  00  01  00  74  27"), ClientHandle, 1, 6, 4));
	AddOffset(StaticOffset(_WorldSpaceCenter, 0, ("68  ??  ??  00  00  F3  0F  11  44  24  ??  FF  90  ??  ??  00  00"), ClientHandle, 1, 13, 4));
	AddOffset(StaticOffset(_EstimateAbsVelocity, 0, ("FF  90  ??  ??  00  00  F3  0F  10  4C  24  18"), ClientHandle, 1, 2, 4));
	AddOffset(StaticOffset(_GetActiveCSWeapon, 0, ("FF  90  ??  ??  00  00  85  C0  74  ??  8B  98  ??  ??  00  00  85  DB"), ClientHandle, 1, 2, 4)); //11/28/2018 sig: FF  90  ??  ??  ??  ??  85  C0  74  4E  8B  B8  ??  ??  ??  ??  85  FF  74  44  80  3F  00  74  3F
	AddOffset(StaticOffset(_AbsVelocityDirect, 0, ("F3  0F  10  A6  ??  00  00  00  F3  0F  10  54  24  ??  F3  0F  10  5C  24  ??  F3  0F  59  C8  F3  0F  59  D0  F3  0F  59  D8  F3  0F  58  E1"), ClientHandle, 1, 4));
	AddOffset(StaticOffset(_GetAbsAnglesVMT, 0, ("FF  50  ??  8D  54  24  1C  8B  C8"), ClientHandle, 0, 0, 0, 2));
	AddOffset(StaticOffset(_EyeAnglesVMT, 0, ("8B  80  ??  ??  00  00  FF  D0  F3  0F  10  0D  ??  ??  ??  ??  F3  0F  7E  00"), ClientHandle, 1, 2, 4));
	AddOffset(StaticOffset(_LocalOrigin, 0, ("89  87  ??  00  00  00  8B  41  04  89  87  ??  00  00  00  8B  41  08  89  87  ??  00  00  00  6A  01"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_AbsOriginDirect, 0, ("89  87  ??  00  00  00  8B  41  04  89  87  ??  00  00  00  8B  41  08  89  87  ??  00  00  00  6A  01"), ClientHandle, 1, 2, 0, -12));
	AddOffset(StaticOffset(_GetAliveVMT, 0, ("80  BE  ??  ??  ??  ??  ??  74  ??  8B  06  8B  CE  8B  80  ??  ??  ??  ??  FF  D0  84  C0  75  ??  38"), ClientHandle, 1, 0xF, 4));
	//AddOffset(StaticOffset(_GameTypes, 0, ("80  BE  ??  ??  ??  ??  ??  74  ??  8B  06  8B  CE  8B  80  ??  ??  ??  ??  FF  D0  84  C0  75  ??  38"), ClientHandle, 1, 0xF, 4));
	AddOffset(StaticOffset(_SurvivalCalcView, 0, ("55  8B  EC  83  E4  F8  81  EC  C0  00  00  00  56  8B  75  08  89  4C  24  14"), ClientHandle));
	AddOffset(StaticOffset(_SurvivalModeOrigin, 0, ("F3  0F  10  87  ??  ??  ??  ??  83  C4  08  F3  0F  10  9F"/*"F3 0F 10 8F ? ? ? ? 0F 28 D0 F3 0F 10 9F ? ? ? ? 8B CE"*/), ClientHandle, 1, 4));
	//AddOffset(StaticOffset(_UnknownSurvivalBool, 0, ("80  BE  ??  ??  00  00  00  74  33  C6  86  ??  ??  00  00  00"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_GetHudPlayer, 0, ("56  8B  35  ??  ??  ??  ??  57  85  F6  74  56  8B  06"), ClientHandle));
	//AddOffset(StaticOffset(_UselessCalcViewSurvivalBool, 0, ("C6  05  ??  ??  ??  ??  00  FF  90  ??  00  00  00  8B  06"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_ThirdPersonSwitchVMT, 0, ("74  0A  8B  01  6A  00  FF  90  ??  ??  00  00  8B  0D  ??  ??  ??  ??  6A  00"), ClientHandle, 1, 8, 4));
	AddOffset(StaticOffset(_CanWaterJumpVMT, 0, ("8B  80  ??  ??  ??  ??  FF  D0  84  C0  0F  84  ??  ??  ??  ??  8B  4F  04"), ClientHandle, 1, 2, 4));
	AddOffset(StaticOffset(_GetEncumberance, 0, ("55  8B  EC  A1  ??  ??  ??  ??  83  EC  10  F3  0F  10  05  ??  ??  ??  ??  F3  0F  10  50  ??"), ClientHandle));
	AddOffset(StaticOffset(_Weapon_ShootPosition, 0, ("50  8B  01  52  FF  90  ??  ??  00  00  50  8D  46  ??"), ClientHandle, 1, 6, 4));
	AddOffset(StaticOffset(_C_CSPlayer_CalcView, 0, ("FF  90  ??  ??  ??  ??  8B  0D  ??  ??  ??  ??  8B  01  FF  90  ??  ??  ??  ??  89  45  F4  E8  ??  ??  ??  ??  8B  D0  85  D2  74  40"), ClientHandle, 1, 2, 4));
	AddOffset(StaticOffset(_ShouldInterpolate, 0, ("8B  06  8B  CE  8B  80  ??  ??  00  00  FF  D0  84  C0  74  5C"), ClientHandle, 1, 6, 4));
	AddOffset(StaticOffset(_ShouldCollide, 0, ("FF  75  0C  FF  77  08  8B  80  ??  ??  00  00  FF  D0  84  C0"), ClientHandle, 1, 8, 4));
	AddOffset(StaticOffset(_Simulate, 0, ("F6  87  ??  00  00  00  01  75  ??  8B  07  8B  CF  8B  80  ??  ??  00  00  FF  D0"), ClientHandle, 1, 15, 4));
	AddOffset(StaticOffset(_PhysicsSimulate, 0, ("74  ??  8B  06  8B  CE  FF  90  ??  ??  00  00  8B  06  8B  CE  6A  ??  FF  90"), ClientHandle, 1, 8, 4));
	AddOffset(StaticOffset(_RenderHandle, 0, ("8D  4E  04  FF  50  ??  0F  B7  10"), ClientHandle, 1, 5, 4));
	AddOffset(StaticOffset(_MoveType, 0, ("80  BE  ??  ??  00  00  07  75  ??  5F"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_MoveCollide, 0, ("80  BE  ??  ??  00  00  07  75  ??  5F"), ClientHandle, 1, 2, 0, 1));
	AddOffset(StaticOffset(_TE_FireBullets, 0, ("C7  05  ??  ??  ??  ??  ??  ??  ??  ??  C7  05  ??  ??  ??  ??  ??  ??  ??  ??  66  A3  ??  ??  ??  ??  C7  05"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_UserCmd_GetChecksum, 0, ("53  8B  D9  83  C8  FF  56  57  BF  ??  ??  ??  ??  8D  73  04  FF  24  BD  ??  ??  ??  ??"), ClientHandle));
	AddOffset(StaticOffset(_CL_SendMove, 0, ("55  8B  EC  A1  ??  ??  ??  ??  81  EC  ??  ??  ??  ??  B9  ??  ??  ??  ??  53  8B  98"), EngineHandle));
	AddOffset(StaticOffset(_SplitScreenMgr, 0, ("55  8B  EC  A1  ??  ??  ??  ??  81  EC  ??  ??  ??  ??  B9  ??  ??  ??  ??  53  8B  98"), EngineHandle, 1, 0xF));
	AddOffset(StaticOffset(_CCLCMsg_Move_vtable1, 0, ("55  8B  EC  A1  ??  ??  ??  ??  81  EC  ??  ??  ??  ??  B9  ??  ??  ??  ??  53  8B  98"), EngineHandle, 1, 0x76));
	AddOffset(StaticOffset(_CCLCMsg_Move_vtable2, 0, ("55  8B  EC  A1  ??  ??  ??  ??  81  EC  ??  ??  ??  ??  B9  ??  ??  ??  ??  53  8B  98"), EngineHandle, 1, 0x82));
	AddOffset(StaticOffset(_CL_SendMove_DefaultMemory, 0, ("55  8B  EC  A1  ??  ??  ??  ??  81  EC  ??  ??  ??  ??  B9  ??  ??  ??  ??  53  8B  98"), EngineHandle, 1, 0x7B));
	AddOffset(StaticOffset(_CCLCMsg_Move_Deconstructor_relative, 0, ("55  8B  EC  A1  ??  ??  ??  ??  81  EC  ??  ??  ??  ??  B9  ??  ??  ??  ??  53  8B  98"), EngineHandle, 0, 0, 0, 0x1B8));
	AddOffset(StaticOffset(_CCLCMsg_Move_UnknownCall, 0, ("55  8B  EC  53  8B  5D  08  56  8B  F1  85  DB  74  57  8B  4E  14"), EngineHandle));
	AddOffset(StaticOffset(_UnknownAnimationFloat, 0, ("8B  4E  60  0F  2F  99  ??  ??  ??  ??  0F  82  ??  ??  ??  ??  F3  0F  10  0D  ??  ??  ??  ??  81  C1  ??  ??  ??  ??  E8  ??  ??  ??  ??"), ClientHandle, 1, 6));
	AddOffset(StaticOffset(_UnknownAnimationCall, 0, ("0F  57  D2  C6  81"), ClientHandle));
	AddOffset(StaticOffset(_PlayerFilterRules, 0, ("55  8B  EC  83  EC  ??  56  57  8B  F9  8B  F2  8B  0D  ??  ??  ??  ??  81  F9  ??  ??  ??  ??  75  ??  A1  ??  ??  ??  ??"), ClientHandle));
	AddOffset(StaticOffset(_GetViewOffsetVMT, 0, ("8B  4E  04  8B  01  FF  90  ??  ??  00  00  F3  0F  10  40  08"), ClientHandle, 1, 7, 4));
	AddOffset(StaticOffset(_GetSolidFlagsVMT, 0, ("C2  08  00  8B  01  FF  90  ??  ??  00  00  C0  E8  05  24  01  5D  C2  08  00"), ClientHandle, 1, 7, 4)); //0x148
	AddOffset(StaticOffset(_PhysicsCheckWaterTransition, 0, ("55  8B  EC  83  E4  F8  83  EC  10  56  8B  F1  57  8A  96  ??  ??  ??  ??  0F  B6  C2  83  E0  01  C1  E0  05  8B  F8  83  CF  10  80  E2  02  0F  44  F8  E8  ??  ??  ??  ??  8A  8E  ??  ??  ??  ??  0F  B6  C1  83  E0  01  C1  E0  05  8B  D0  83  CA  10  80  E1  02  8B  8E  ??  ??  ??  ??  0F  44  D0  83  F9  FF  74  18  0F  B7  C1"), ClientHandle));
	AddOffset(StaticOffset(_PhysicsPushEntity, 0, ("55  8B  EC  83  EC  0C  56  8B  F1  57  8B  06  FF  50  28  8B  7D  0C  8B  CE  57  FF  75  08  F3  0F  10  00  F3  0F  11  45  ??  F3  0F  10  40  ??  F3  0F  11  45  ??  F3  0F  10  40  ??  8D  45  F4  50  F3  0F  11  45  ??  E8  ??  ??  ??  ??  F3  0F  10  47  ??  0F  2E  05  ??  ??  ??  ??  9F  F6  C4  44  7B  0B"), ClientHandle));
	AddOffset(StaticOffset(_GetUnknownEntity, 0, ("8B  80  ??  ??  00  00  FF  D0  85  C0  8B  46  04  74"), ClientHandle, 1, 2, 4, 0));
	AddOffset(StaticOffset(_DesiredCollisionGroup, 0, ("5E  8B  81  ??  ??  00  00  89  81  ??  ??  00  00"), ClientHandle, 1, 9));
	AddOffset(StaticOffset(_EyePositionVMT, 0, ("8B  01  F3  0F  11  44  24  ??  8B  80  ??  ??  ??  ??  FF  D0  F3  0F  10  74  24  ??  F3  0F  10  6C  24  ??  0F  28  CE  F3  0F  59  4C  24  ??  F3  0F  10  10  F3  0F  10  58  ??  0F  28  C2  F3  0F  10  60  ??  F3  0F  58  CA  F3  0F  5C  25  ??  ??  ??  ??  0F  14  C3"), ClientHandle, 1, 10, 4));
	AddOffset(StaticOffset(_MaintainSequenceTransitionsReturnAddress, 0, ("84  C0  74  17  8B  87"), ClientHandle));
	AddOffset(StaticOffset(_AccumulateLayersVMT, 0, ("56  51  8D  4C  24  ??  51  8B  CF  FF  90  ??  ??  00  00"), ClientHandle, 1, 11, 4));
	AddOffset(StaticOffset(_boneFlagsOffset, 0, ("8B  41  ??  F6  04  B0  04  74  ??  8B  09"), ClientHandle, 1, 2, 0, 0, sizeof(int8_t)));
	AddOffset(StaticOffset(_ClientEntityListArray, 0, ("05  ??  ??  ??  ??  03  C0  8B  0C  C1  85  C9  74  09"), ClientHandle, 1, 1));
	AddOffset(StaticOffset(_m_pPlayerCommand, 0, ("8D  8E  ??  ??  00  00  89  5C  24  ??  89  BE  ??  ??  00  00  E8  ??  ??  ??  ??  85  FF"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_m_pCurrentCommand, 0, ("8D  8E  ??  ??  00  00  89  5C  24  ??  89  BE  ??  ??  00  00  E8  ??  ??  ??  ??  85  FF"), ClientHandle, 1, 12));
	AddOffset(StaticOffset(_m_pPredictionPlayer, 0, ("89  35  ??  ??  ??  ??  F3  0F  10  48  ??  F3  0F  59  C1"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_CacheSequences, 0, ("55  8B  EC  83  E4  F8  83  EC  34  53  56  8B  F1  57  8B  46  60  85  C0  75"), ClientHandle));
	AddOffset(StaticOffset(_HasC4, 0, ("56  8B  F1  85  F6  74  31  8B  06  8B  80  ??  ??  ??  ??  FF  D0  84  C0  74  ??"), ClientHandle));
	AddOffset(StaticOffset(_FlashbangTime, 0, ("8B  80  ??  ??  ??  ??  FF  D0  84  C0  0F  84  ??  ??  ??  ??  A1  ??  ??  ??  ??  F3  0F  10  86  ??  ??  ??  ??  0F"), ClientHandle, 1, 25));	AddOffset(StaticOffset(_CacheSequences, 0, ("55  8B  EC  83  E4  F8  83  EC  34  53  56  8B  F1  57  8B  46  60  85  C0  75"), ClientHandle));
	AddOffset(StaticOffset(_SetupLean, 0, ("55  8B  EC  83  E4  F8  A1  ??  ??  ??  ??  83  EC  20  F3  0F  10  48  10  56  57  8B  F9"), ClientHandle));
	AddOffset(StaticOffset(_SetupWeaponAction, 0, ("55  8B  EC  51  53  56  57  8B  F9  8B  77  60  83  BE  ??  ??  ??  ??  ??  0F  84  ??  ??  ??  ??  8B  86"/*"55  8B  EC  51  53  56  8B  F1  0F  57  C9  57  8B  46  60  83  B8  ??  ??  00  00  00  74  ??"*/), ClientHandle));
	AddOffset(StaticOffset(_SetupAimMatrix, 0, ("55  8B  EC  81  EC  ??  00  00  00  53  56  57  8B  3D  ??  ??  ??  ??  8B  D9  8B  CF  8B  07  FF  90  ??  00  00  00"), ClientHandle));
	AddOffset(StaticOffset(_SetupMovement, 0, ("55  8B  EC  83  E4  F8  81  EC  ??  ??  ??  ??  56  57  8B  3D  ??  ??  ??  ??  8B  F1  8B  CF  89  74  24  24  8B  07  FF  90  ??  ??  ??  ??"), ClientHandle));
	AddOffset(StaticOffset(_SetSequenceVMT, 0, ("6A  00  8B  01  FF  90  ??  ??  00  00  8B  47  ??  C7  44  24  10  00  00  00  00"), ClientHandle, 1, 6, 4));
	AddOffset(StaticOffset(_WeaponGetZoomFOVVMT, 0, ("8B  06  51  FF  B6  ??  ??  ??  ??  8B  CE  FF  90  ??  ??  ??  ??  F3  0F  10  1D"), ClientHandle, 1, 13, 4));
	//AddOffset(StaticOffset(_m_bInReload, 0, ("FF  92  ??  ??  ??  ??  8B  17  8B  CF  FF  92  ??  ??  ??  ??  80  BF  ??  ??  ??  ??  00"), ClientHandle, 1, 18));
	AddOffset(StaticOffset(_WeaponHasBurstVMT, 0, ("C6  87  ??  ??  ??  ??  00  8B  06  8B  CE  8B  80  ??  ??  ??  ??  FF  D0  84  C0  74"), ClientHandle, 1, 13, 4));
	AddOffset(StaticOffset(_m_Activity, 0, ("F3  0F  11  8E  ??  ??  ??  ??  81  BE  ??  ??  ??  ??  D0"), ClientHandle, 1, 10));
	AddOffset(StaticOffset(_GetMaxClip1VMT, 0, ("F7  C1  ??  ??  ??  ??  74  ??  8B  07  8B  CF  FF  90  ??  ??  ??  ??"), ClientHandle, 1, 14, 4));
	AddOffset(StaticOffset(_IsFullAutoVMT, 0, ("83  BF  ??  ??  ??  ??  00  7E  ??  8B  06  8B  CE  8B  80  ??  ??  ??  ??  FF  D0  84  C0"), ClientHandle, 1, 15, 4));
	AddOffset(StaticOffset(_GetCycleTimeVMT, 0, ("8B  06  8B  CE  6A  01  8B  80  ??  ??  ??  ??  FF  D0  D8  0D  ??  ??  ??  ??"), ClientHandle, 1, 8, 4));
	AddOffset(StaticOffset(_GetReserveAmmoCount, 0, ("8B  D8  83  FB  FF  7E  ??  8B  4D  08  53  E8  ??  ??  ??  ??  85  C0  74  ??  8B  4D  08  53"), ClientHandle, 0, 0, 0, -96));
	AddOffset(StaticOffset(_m_bFireOnEmpty, 0, ("E8  ??  ??  ??  ??  85  C0  75  ??  C6  86  ??  ??  ??  ??  01  83"), ClientHandle, 1, 11));
	AddOffset(StaticOffset(_m_bIsCustomPlayer, 0, ("85  C0  0F  95  C0  83  BF  ??  ??  00  00  00  88  87  ??  ??  00  00  75  14"), ClientHandle, 1, 14));
	AddOffset(StaticOffset(_UpdateViewModelAddonsSub, 0, ("55  8B  EC  83  E4  F8  83  EC  2C  53  8B  D9  56  57  8B  03  FF  90"), ClientHandle));
	AddOffset(StaticOffset(_UpdateViewModelAddonsVT, 0, ("6A  20  FF  92  ??  ??  00  00  5E  8B  E5  5D  C3"), ClientHandle, 1, 4, 4));
	AddOffset(StaticOffset(_ViewModelLabelHandle, 0, ("74  ??  8B  CF  E8  ??  ??  ??  ??  8B  8F  ??  ??  00  00  83  F9  FF  74  ??"), ClientHandle, 1, 11));
	AddOffset(StaticOffset(_ViewModelStatTrackHandle, 0, ("8B  08  85  C9  74  ??  E8  ??  ??  ??  ??  8B  8F  ??  ??  00  00  83  F9  FF"), ClientHandle, 1, 13));
	AddOffset(StaticOffset(_RemoveViewModelStickers, 0, ("53  56  8B  D9  57  33  FF  39  BB  ??  ??  00  00  0F  8E  ??  ??  ??  ??  8B  83  ??  ??  ??  ??"), ClientHandle));
	AddOffset(StaticOffset(_RemoveViewModelArmModels, 0, ("51  56  57  8B  F9  8B  B7  ??  ??  00  00  83  EE  01  78  ??  8B  87  ??  ??  ??  ??  8B  0C  B0  83  F9  FF"), ClientHandle));
	AddOffset(StaticOffset(_RemoveEntity, 0, ("56  8B  F1  F6  86  ??  00  00  00  01  75  ??  83  8E  ??  00  00  00  01"), ClientHandle));
	AddOffset(StaticOffset(_OnLatchInterpolatedVariables, 0, ("74  ??  8B  06  8B  CE  6A  01  FF  90  ??  ??  00  00  80  BE"), ClientHandle, 1, 0xA, 4));
	AddOffset(StaticOffset(_FrameAdvance, 0, ("8B  06  51  C7  04  24  00  00  00  00  8B  80  ??  ??  00  00  FF  D0  DD  D8"), ClientHandle, 1, 12, 4));
	AddOffset(StaticOffset(_HandleTaserAnimation, 0, ("55  8B  EC  83  EC  08  56  8B  F1  80  BE  ??  ??  ??  ??  00  0F  84  ??  ??  ??  ??  80  BE  ??  ??  ??  ??  00  0F  84  ??  ??  ??  ??  A1  ??  ??  ??  ??"), ClientHandle));
	AddOffset(StaticOffset(_GetViewModel, 0, ("55  8B  EC  8B  45  08  53  8B  D9  56  8B  84  83  ??  ??  00  00"), ClientHandle));
	AddOffset(StaticOffset(_IsBaseCombatWeapon, 0, ("85  FF  74  6F  8B  07  8B  CF  FF  90  ??  ??  ??  ??  8B  F0  85  F6"), ClientHandle, 1, 10, 4));
	AddOffset(StaticOffset(_FileSystemStringVMT, 0, ("68  ??  ??  ??  ??  50  8B  11  8D  46  48  50  8B  82  ??  ??  ??  ??  FF  D0"), EngineHandle, 1, 14, 4));
	AddOffset(StaticOffset(_SetSky, 0, ("55  8B  EC  81  EC  ??  ??  ??  ??  56  57  8B  F9  C7  45"), EngineHandle));
	AddOffset(StaticOffset(_FindElement, 0, ("55  8B  EC  53  8B  5D  08  56  57  8B  F9  33  F6  39  77  28"), ClientHandle));
	AddOffset(StaticOffset(_Hud, 0, ("8B  07  8B  CF  68  ??  ??  ??  ??  FF  ??  ??  C6  ??  ??  ??"), ClientHandle, 1, 5));
	AddOffset(StaticOffset(_ClearDeathNotices, 0, ("55  8B  EC  83  EC  0C  53  56  8B  71  58"), ClientHandle));
	AddOffset(StaticOffset(_IsInIronsight, 0, ("53  56  8B  F1  57  8B  4E  3C  85  C9  0F  84  ??  ??  ??  ??  8B  81"), ClientHandle));
	AddOffset(StaticOffset(_SetupVelocity, 0, ("55  8B  EC  83  E4  F8  83  EC  30  56  57  8B  3D  ??  ??  ??  ??  8B  F1  8B  CF  89  74  24  14  8B  07  FF  90  ??  ??  ??  ??  8B  0D  ??  ??  ??  ??  F3  0F  7E  86  ??  ??  ??  ??  8B  86  ??  ??  ??  ??  89  44  24  28  66  0F  D6  44  24  ??  8B  01  8B  80  ??  ??  ??  ??  FF  D0  84  C0  75  38  8B  0D  ??  ??  ??  ??  8B  01  8B  80  ??  ??  ??  ??"), ClientHandle));
	AddOffset(StaticOffset(_UpdatePartition, 0, ("55  8B  EC  83  EC  18  57  8B  F9  8B  4F  04  8B  81  ??  ??  ??  ??  C1  E8  0F"), ClientHandle));
	AddOffset(StaticOffset(_CAM_ToThirdPerson, 0, ("A1  ??  ??  ??  ??  B9  ??  ??  ??  ??  FF  90  8C"), ClientHandle));
	AddOffset(StaticOffset(_CAM_ToFirstPerson, 0, ("A1  ??  ??  ??  ??  B9  ??  ??  ??  ??  FF  90  90"), ClientHandle));
	AddOffset(StaticOffset(_IronSightController, 0, ("8B  98  ??  ??  00  00  85  DB  74  ??  80  3B  00  74"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_OnLand, 0, ("55  8B  EC  83  E4  F8  81  EC  28  02  00  00  56  8B  F1  F3  0F  11  4C  24  08"), ClientHandle));
	AddOffset(StaticOffset(_NetSetConVar_Constructor, 0, ("FF  CC  CC  CC  CC  CC  CC  CC  CC  CC  CC  CC  CC  CC  CC  56  8B  F1  C7  06  ??  ??  ??  ??  8D"), EngineHandle, 1, 15));
	AddOffset(StaticOffset(_NetSetConVar_Init, 0, ("55  8B  EC  56  8B  F1  83  4E  14  01  83  7E  0C  00"), EngineHandle));
	AddOffset(StaticOffset(_NetSetConVar_Destructor, 0, ("00  CC  CC  CC  CC  CC  CC  CC  CC  CC  CC  CC  CC  CC  53  8B  D9  56  57"), EngineHandle, 1, 14));
	AddOffset(StaticOffset(_NetIsMultiplayer, 0, ("80  3D  ??  ??  ??  ??  00  0F  84  64  01  00  00  8B  46  48"), EngineHandle, 1, 2));
	AddOffset(StaticOffset(_CNetMsg_Tick_Constructor, 0, ("55  8B  EC  83  EC  08  56  57  F3  0F  11  5D  F8"), EngineHandle));
	AddOffset(StaticOffset(_CNetMsg_Tick_Destructor, 0, ("53  56  57  8B  F9  8D  77  2C  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  C7  46  14  0F  00  00  00  83  7E  14  10  C7  46  10  00  00  00  00  72  02  8B  36  C6  06  00  8D  4F  08  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  8D  4F  04  E8  ??  ??  ??  ??  C7  07  ??  ??  ??  ??  5F  5E  5B  C3  83  E9  04"), EngineHandle));
	AddOffset(StaticOffset(_CNetMsg_Tick_Setup, 0, ("53  56  57  8B  F9  8D  77  2C  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  C7  46  14  0F  00  00  00  83  7E  14  10  C7  46  10  00  00  00  00  72  02  8B  36  C6  06  00  8D  4F  08  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  ??  8D  4F  04  E8  ??  ??  ??  ??  C7  07  ??  ??  ??  ??  5F  5E  5B  C3  83  E9  04"), EngineHandle));
	AddOffset(StaticOffset(_CNetMsg_Tick_MiscAdr, 0, ("F3  0F  10  05  ??  ??  ??  ??  F3  0F  10  1D  ??  ??  ??  ??  F3  0F  10  15  ??  ??  ??  ??  51  F3  0F  11  04  24  8D  4D  A8"), EngineHandle));
	AddOffset(StaticOffset(_NET_SendPacketSig, 0, ("55  8B  EC  B8  ??  ??  00  00  E8  ??  ??  ??  ??  53  8B  D9  56  57  8B  FA"), EngineHandle));
	AddOffset(StaticOffset(_ViewMatrixPtr, 0, ("B9  ??  ??  ??  ??  A1  ??  ??  ??  ??  FF  60  38"), EngineHandle, 1, 1));
	AddOffset(StaticOffset(_IsPlayer, 0, ("FF  90  ??  ??  ??  ??  8B  47  FC  8D  4F  FC  8B  80  ??  ??  ??  ??  FF  D0  84  C0  0F"), ClientHandle, 1, 14, 4));
	AddOffset(StaticOffset(_LocalAngles, 0, ("F3  0F  11  86  ??  ??  ??  ??  F3  0F  10  45  EC  0F  2E  86  ??  ??  ??  ??  9F"), ClientHandle, 1, 16));
	AddOffset(StaticOffset(_SetAbsAnglesDirect, 0, ("83  EC  ??  53  56  57  8B  F1  E8  ??  ??  ??  ??  8B  7D  08  F3  ??  ??  ??  0F  2E  86  ??  ??  ??  ??  9F  F6  C4  44"), ClientHandle, 1, 23));
	AddOffset(StaticOffset(_OldOrigin, 0, ("32  FF  F3  0F  10  86  ??  ??  ??  ??  0F  2E  86  ??  ??  ??  ??  9F  F6  C4  44  7A"), ClientHandle, 1, 13, 0, 8));
	AddOffset(StaticOffset(_m_iEFlags, 0, ("89  ??  ??  ??  0F  86  ??  ??  ??  ??  8B  87  ??  ??  ??  ??  C1  E8  03"), ClientHandle, 1, 12));
	AddOffset(StaticOffset(_m_nWaterType, 0, ("8A  B1  ??  ??  ??  ??  80  FE  01  ??  ??  8A  91  ??  ??  ??  ??  0F  B6  CA"), ClientHandle, 1, 13));
	AddOffset(StaticOffset(_m_BoneSetupLock, 0, ("EB  35  FF  15  ??  ??  ??  ??  8D  97  ??  ??  ??  ??  89  44  ??  ??  3B  02"), ClientHandle, 1, 10, 0, 4));
	AddOffset(StaticOffset(_m_bIsToolRecording, 0, ("81  CE  00  FF  0F  00  80  BF  ??  ??  ??  ??  00  0F  44  F1"), ClientHandle, 1, 8, 0, 4));
	AddOffset(StaticOffset(_m_EntClientFlags, 0, ("8B  06  83  B8  ??  ??  ??  ??  00  7E  2E  F6  47  ??  02  75"), ClientHandle, 1, 13, 0, 4, 1));
	AddOffset(StaticOffset(_GetPredictable, 0, ("75  F7  89  ??  ??  ??  80  BF  ??  ??  ??  ??  00  74  1D"), ClientHandle, 1, 8, 0, 4));
	AddOffset(StaticOffset(_m_pIK_offset, 0, ("83  BF  ??  ??  ??  ??  00  75  3C  8B  06  83  B8  ??  ??  ??  ??  00"), ClientHandle, 1, 2, 0, 4));
	AddOffset(StaticOffset(_m_flLastBoneSetupTime, 0, ("80  3D  ??  ??  ??  ??  ??  74  16  A1  ??  ??  ??  ??  48  C7  81"), ClientHandle, 1, 17));
	AddOffset(StaticOffset(_LastBoneChangedTime_Offset, 0, ("8D  4F  FC  F3  0F  ??  ??  ??  ??  00  00  F3  0F  ??  ??  ??  ??  8B  80  ??  ??  ??  ??  FF  D0  F3"), ClientHandle, 1, 19, 4));
	AddOffset(StaticOffset(_m_iPrevBoneMask, 0, ("0F  84  ??  ??  ??  ??  83  FE  FF  75  06  8B  B7  ??  ??  ??  ??  8B  0D"), ClientHandle, 1, 13, 0, 4));
	AddOffset(StaticOffset(_m_iAccumulatedBoneMask, 0, ("8B  87  ??  ??  ??  ??  89  87  ??  ??  ??  ??  8D  47  FC  C7  ??  ??  ??  ??  00"), ClientHandle, 1, 2, 0, 4));
	AddOffset(StaticOffset(_LastSetupBonesFrameCount, 0, ("A1  ??  ??  ??  ??  8B  40  ??  89  87  ??  ??  ??  ??  EB  68"), ClientHandle, 1, 10, 0, 4));
	AddOffset(StaticOffset(_m_iMostRecentModelBoneCounter, 0, ("80  3D  ??  ??  ??  ??  ??  74  16  A1  ??  ??  ??  ??  48  C7  81"), ClientHandle, 1, 27));
	AddOffset(StaticOffset(_BoneAccessor, 0, ("8D  81  ??  ??  ??  ??  50  8D  84  24"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_m_pStudioHdr, 0, ("8B  86  ??  ??  ??  ??  89  44  24  10  85  C0"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_StandardBlendingRules, 0, ("8D  94  ??  ??  ??  ??  ??  52  56  FF  90  ??  ??  ??  ??  8B  47  FC"), ClientHandle, 1, 11, 4));
	AddOffset(StaticOffset(_BuildTransformations, 0, ("8D  94  ??  ??  ??  ??  ??  52  56  FF  90  ??  ??  ??  ??  A1  ??  ??  ??  ??"), ClientHandle, 1, 11, 4));
	AddOffset(StaticOffset(_UpdateIKLocks, 0, ("8B  01  F3  0F  ??  ??  ??  ??  51  F3  ??  ??  ??  ??  FF  90  ??  ??  ??  ??  8B  8F  ??  ??  ??  ??  8D"), ClientHandle, 1, 16, 4));
	AddOffset(StaticOffset(_CalculateIKLocks, 0, ("8D  4F  FC  F3  ??  ??  ??  ??  ??  51  F3  ??  ??  ??  ??  FF  90  ??  ??  ??  ??  8B  8F  ??  ??  ??  ??  8D"), ClientHandle, 1, 17, 4));
	AddOffset(StaticOffset(_ControlMouth, 0, ("83  ??  ??  00  00  00  F7  8D  4F  FC  8B  01  56  FF  90  ??  ??  ??  ??  80"), ClientHandle, 1, 15, 4));
	AddOffset(StaticOffset(_DoExtraBoneProcessing, 0, ("8D  94  ??  ??  ??  ??  ??  52  56  FF  90  ??  ??  ??  ??  8D  4F  FC"), ClientHandle, 1, 11, 4));
	AddOffset(StaticOffset(_m_CachedBoneData, 0, ("8B  55  ??  85  D2  74  23  8B  87  ??  ??  ??  ??  8B  4D  ??  3B  C8"), ClientHandle, 1, 9, 0, -8));
	AddOffset(StaticOffset(_m_flEncodedController, 0, ("50  F3  0F  10  84  B7  ??  ??  ??  ??  F3  0F  11  45  ??  E8"), ClientHandle, 1, 6));
	AddOffset(StaticOffset(_GetBaseAnimating, 0, ("8B  01  8B  80  ??  ??  ??  ??  FF  D0  89  ??  ??  ??  85  C0  0F  84  ??  ??  ??  ??  FF  76  ??"), ClientHandle, 1, 4));
	AddOffset(StaticOffset(_GetWeaponMaxSpeed3VMT, 0, ("8B  01  8B  80  ??  ??  ??  ??  FF  D0  F3  0F  ??  ??  ??  ??  ??  ??  D9  ??  ??  ??  F3  ??  ??  ??  ??  ??  0F  2F  C3"), ClientHandle, 1, 4, 4));
	AddOffset(StaticOffset(_LookupSequence, 0, ("55  8B  EC  56  8B  F1  83  BE  ??  ??  ??  ??  ??  75  14  8B  46  04  8D  4E  04  FF  50  20  85  C0  74  07  8B  CE  E8  ??  ??  ??  ??  8B  B6  ??  ??  ??  ??  85  F6  74  48  83  3E  00  74  43  8B  CE  E8  ??  ??  ??  ??  84  C0  74  38  FF  75  08  8B  CE  E8"), ClientHandle));
	AddOffset(StaticOffset(_GetWeaponMoveAnimation, 0, ("53  56  57  8B  F9  33  F6  8B  4F  60  8B  01  FF  90"), ClientHandle));
	AddOffset(StaticOffset(_GetSequenceLinearMotion, 0, ("55  8B  EC  83  EC  0C  56  8B  F1  57  8B  FA  85  F6  75  14  68"), ClientHandle));
	AddOffset(StaticOffset(_UpdateLayerOrderPreset, 0, ("55  8B  EC  51  53  56  57  8B  F9  83  7F  60  00  0F  84"), ClientHandle));
	AddOffset(StaticOffset(_UnknownSetupMovementFloat, 0, ("0F  2F  89  ??  ??  ??  ??  72  ??  F3  0F"), ClientHandle, 1, 3));
	AddOffset(StaticOffset(_GetLayerIdealWeightFromSeqCycle, 0, ("55  8B  EC  83  EC  08  53  56  8B  35  ??  ??  ??  ??  57  8B  F9  8B  CE  8B  06  FF  90"), ClientHandle));
	AddOffset(StaticOffset(_GetSequenceCycleRate, 0, ("52  8B  01  8B  80  ??  ??  00  00  FF  D0  F3  0F  10  46  ??  F3  0F  10  4C  24  ??"), ClientHandle, 1, 5, 4));
	AddOffset(StaticOffset(_GetLayerSequenceCycleRate, 0, ("8B  80  ??  ??  00  00  FF  D0  D9  5F  ??  8B  4F  ??  0F  57  C9"), ClientHandle, 1, 2, 4));
	AddOffset(StaticOffset(_GetAnySequenceAnimTag, 0, ("55  8B  EC  51  56  8B  F1  0F  28  C3  F3  0F  11  45  ??  83  BE  ??  ??  ??  ??  ??  75"), ClientHandle));
	AddOffset(StaticOffset(_GetPoseParameter, 0, ("55  8B  EC  56  8B  F1  83  BE  ??  ??  ??  ??  ??  75  14  8B  46  04  8D  4E  04  FF  50  20  85  C0  74  07  8B  CE  E8  ??  ??  ??  ??  8B  8E  ??  ??  ??  ??  85  C9  74  1F  83  39  00  74  1A  8B  55  08  85  D2  78  13  F3  0F  10  94  96  ??  ??  ??  ??  E8  ??  ??  ??  ??  5E"), ClientHandle));
	AddOffset(StaticOffset(_FindKey, 0, ("55  8B  EC  83  EC  1C  53  8B  D9  85  DB  75  09  33  C0  5B  8B  E5  5D  C2  08  00"), ClientHandle));
	AddOffset(StaticOffset(_GetInt, 0, ("55  8B  EC  6A  00  FF  75  08  E8  ??  ??  ??  ??  85  C0  74  45  0F"), ClientHandle));
	AddOffset(StaticOffset(_CActivityToSequenceMapping_Reinitialize, 0, ("55  8B  EC  56  8B  F1  8B  06  85  C0  74  11  6A  ??  50  E8"), ClientHandle));
	AddOffset(StaticOffset(_GetActivityListVersion, 0, ("57  8B  F9  8B  47  04  85  C0  75  0A  8B  07  5F  8B  80"), ClientHandle));
	AddOffset(StaticOffset(_g_nActivityListVersion, 0, ("3B  05  ??  ??  ??  ??  7D  07  8B  CE  E8  ??  ??  ??  ??  8B  46  04  85  C0"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_IndexModelSequences, 0, ("57  8B  F9  85  FF  74  6E  E8  ??  ??  ??  ??  84  C0  74  65  56  8B  CF"), ClientHandle));
	AddOffset(StaticOffset(_g_ActivityModifiersTable, 0, ("B9  ??  ??  ??  ??  50  E8  ??  ??  ??  ??  8B  55  F4  8B  75  E0"), ClientHandle, 1, 1));
	AddOffset(StaticOffset(_m_afButtonLast, 0, ("89  86  ??  ??  ??  ??  8B  C1  89  96  ??  ??  ??  ??  23  C2  F7  D2  89  86"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_m_nButtons, 0, ("89  86  ??  ??  ??  ??  8B  C1  89  96  ??  ??  ??  ??  23  C2  F7  D2  89  86"), ClientHandle, 1, 10));
	AddOffset(StaticOffset(_m_afButtonPressed, 0, ("89  86  ??  ??  ??  ??  8B  C1  89  96  ??  ??  ??  ??  23  C2  F7  D2  89  86"), ClientHandle, 1, 20));
	AddOffset(StaticOffset(_m_afButtonReleased, 0, ("89  86  ??  ??  ??  ??  8B  C1  89  96  ??  ??  ??  ??  23  C2  F7  D2  89  86"), ClientHandle, 1, 37));
	AddOffset(StaticOffset(_symbolsInitialized, 0, ("80  3D  ??  ??  ??  ??  ??  75  50  A1  ??  ??  ??  ??  56  6A  40  8B  08  8B  01  FF  50  04  8B  F0  85  F6  74  29  6A  00  6A  20"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_s_pSymbolTable, 0, ("89  35  ??  ??  ??  ??  C6  05  ??  ??  ??  ??  ??  5E  C3  C7  05  ??  ??  ??  ??  ??  ??  ??  ??  C6  05  ??  ??  ??  ??  ??  5E  C3"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_AddString, 0, ("55  8B  EC  83  EC  0C  53  8B  5D  0C  57  8B  F9  89  7D  F4  85  DB  75  13  B9"), ClientHandle));
	AddOffset(StaticOffset(_FindString, 0, ("55  8B  EC  83  EC  0C  56  8B  75  0C  57  8B  F9  85  F6"/*"55  8B  EC  56  8B  F1  8B  4D  0C  85  C9  75  10  8B  45  08  B9  ??  ??  ??  ??  5E  66  89  08  5D  C2  08  00  80  7E  1C  00"*/), ClientHandle));
	AddOffset(StaticOffset(_FindFieldByName, 0, ("55  8B  EC  83  EC  0C  53  56  8B  F2  8B  D1  89  55  FC"), ClientHandle));
	AddOffset(StaticOffset(_GetPredDescMap, 0, ("C6  87  ??  00  00  00  01  8B  CE  8B  06  8B  40"), ClientHandle, 1, 13, 4, 0, 1));
	AddOffset(StaticOffset(_GetPredictedFrame, 0, ("55  8B  EC  57  8B  F9  83  BF  ??  ??  00  00  00  75  07  33  C0  5F  5D  C2  04  00"), ClientHandle));
	AddOffset(StaticOffset(_g_Predictables, 0, ("39  3C  9D  ??  ??  ??  ??  0F  8E  CE  00  00  00  8B  75  F8  8B  04  9D  ??  ??  ??  ??"), ClientHandle, 1, 3, 1, -12, 4));
	AddOffset(StaticOffset(_touchStamp, 0, ("FF  80  ??  ??  ??  ??  C1  E9  18  F6  C1  01  75  0C  81  CA"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_doLocalPlayerPrePrediction, 0, ("55  8B  EC  83  E4  F0  81  EC  ??  ??  ??  ??  56  57  51  51  8D  8C  24  ??  ??  ??  ??  E8  ??  ??  ??  ??  8B  BC  24  ??  ??  ??  ??  85  FF  0F  84  ??  ??  ??  ??  0F  1F  44  00  ??  8B  47  08  8D  4F  08  8B  40  24  FF  D0  84  C0  0F  85  ??  ??  ??  ??  8B  07  8B  CF  8B  40  0C  FF  D0  8B  F0  8B  CE  8B  16  8B  52  30  FF  D2  84  C0  79  4F  8B  16"), ClientHandle));
	AddOffset(StaticOffset(_PhysicsCheckForEntityUntouch, 0, ("55  8B  EC  51  56  8B  F1  8B  86  ??  ??  ??  ??  D1  E8  A8  01  0F  84  ??  ??  ??  ??  8B  0D  ??  ??  ??  ??  85  C9  0F  84  ??  ??  ??  ??  8B  01  53  56  FF  50  04"), ClientHandle));
	AddOffset(StaticOffset(_PhysicsTouchTriggers, 0, ("55  8B  EC  83  E4  F0  81  EC  ??  ??  ??  ??  56  57  51  51  8D  8C  24  ??  ??  ??  ??  E8  ??  ??  ??  ??  8B  BC  24  ??  ??  ??  ??  85  FF  0F  84  ??  ??  ??  ??  0F  1F  44  00  ??  8B  47  08  8D  4F  08  8B  40  24  FF  D0  84  C0  0F  85  ??  ??  ??  ??  8B  07  8B  CF  8B  40  0C  FF  D0  8B  F0  8B  CE  8B  16  8B  52  30  FF  D2  8B  94  24  ??  ??  ??  ??  85  D2  74  0C  8B  C8  23  CA  3B  CA  0F  84  ??  ??  ??  ??  84  C0  79  4F  8B  06  8D  4C  24  10  51  8D  4C  24  24  51  8B  CE  FF  50  0C  0F  28  05  ??  ??  ??  ??  8D  44  24  30  0F  29  44  24  ??  8D  54  24  40  0F  10  44  24  ??  50  8D  84  24  ??  ??  ??  ??  0F  29  44  24  ??  8D  4C  24  54  0F  10  44  24  ??  50  0F  29  44  24  ??  E8  ??  ??  ??  ??  84  C0  EB  37  8B  0D  ??  ??  ??  ??  8D  94  24  ??  ??  ??  ??  52  56  C7  84  24  ??  ??  ??  ??  ??  ??  ??  ??  8D  94  24  ??  ??  ??  ??  8B  01  68  ??  ??  ??  ??  52  FF  50  10"), ClientHandle));
	AddOffset(StaticOffset(_MoveToLastReceivedPosition, 0, ("55  8B  EC  51  53  56  8B  F1  32  DB  8B  06  8B  80  ??  ??  ??  ??  FF  D0  84  C0  74  09  38  9E  ??  ??  ??  ??  0F  95  C3  80  7D  08  00  75  11  80  BE  ??  ??  ??  ??  ??  74  08  84  DB  0F  84"), ClientHandle));
	AddOffset(StaticOffset(_UnknownEntityPredictionBool, 0, ("8B  04  88  85  C0  74  07  C6  80"), ClientHandle, 1, 9));
	AddOffset(StaticOffset(_StorePredictionResults, 0, ("55  8B  EC  83  EC  08  8B  45  08  53  56  57  8D  1C  C5  ??  ??  ??  ??  89  4D  F8  2B  D8  33  FF  8B  34  9D  ??  ??  ??  ??  89  75  FC  85  F6  0F  8E  ??  ??  ??  ??  8B  C6  66  90  8B  34  9D  ??  ??  ??  ??  8B  34  BE  85  F6  74  6E  80  BE"), ClientHandle));
	AddOffset(StaticOffset(_m_nFinalPredictedTick, 0, ("89  81  ??  ??  ??  ??  8B  4D  18"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_m_pFirstPredictedFrame, 0, ("FF  90  ??  ??  ??  ??  47  3B  3C  9D  ??  ??  ??  ??"), ClientHandle, 1, -4));
	AddOffset(StaticOffset(_VPhysicsCompensateForPredictionErrorsVMT, 0, ("FF  90  ??  ??  ??  ??  47  3B  3C  9D  ??  ??  ??  ??"), ClientHandle, 1, 2, 4));
	AddOffset(StaticOffset(_ComputeFirstCommandToExecute, 0, ("55  8B  EC  83  EC  08  53  56  8B  75  08  57  8B  F9  6B  DE  34  80  7D  0C  00  89  7D  F8  C7  45"), ClientHandle));
	AddOffset(StaticOffset(_physenv, 0, ("8B  0D  ??  ??  ??  ??  66  0F  6E  80  ??  ??  ??  ??  A1  ??  ??  ??  ??  0F  5B  C0"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_g_BoneAccessStack, 0, ("8B  0D  ??  ??  ??  ??  52  8B  04  D1  A3  ??  ??  ??  ??  8B  44  D1  04"), ClientHandle, 1, 2));
	AddOffset(StaticOffset(_g_BoneAcessBase, 0, ("8B  0D  ??  ??  ??  ??  52  8B  04  D1  A3  ??  ??  ??  ??  8B  44  D1  04"), ClientHandle, 1, 11));
	AddOffset(StaticOffset(_RestoreOriginalEntityState, 0, ("55  8B  EC  8B  45  08  53  56  33  F6  8D  1C  C5"), ClientHandle));
	AddOffset(StaticOffset(_RunSimulation, 0, ("55  8B  EC  83  EC  08  53  8B  5D  10  56  57  FF  75  0C  8B  F1  F3  0F  11  55"), ClientHandle));
	AddOffset(StaticOffset(_RestoreEntityToPredictedFrame, 0, ("55  8B  EC  A1  ??  ??  ??  ??  56  8B  75  08  83  FE  FF  74  07  8B  04  B5  ??  ??  ??  ??  85  C0  74  67  A1"), ClientHandle));
	AddOffset(StaticOffset(_ShiftIntermediateDataForward, 0, ("55  8B  EC  B8  ??  ??  ??  ??  83  38  00  75  0E  83  C0  04  3D  ??  ??  ??  ??  74  F1  5D  C2  0C  00  A1"), ClientHandle));
	AddOffset(StaticOffset(_ShiftFirstPredictedIntermediateDataForward, 0, ("55  8B  EC  53  8B  5D  0C  85  DB  74  7A  81  FB"), ClientHandle));
	AddOffset(StaticOffset(_SaveData, 0, ("55  8B  EC  83  E4  F8  83  EC  40  56  8B  75  0C  57  8B  F9  83  FE  FF  75  08  8B  8F"), ClientHandle));
	AddOffset(StaticOffset(_ListLeavesInBox_ReturnAddrBytes, 0, ("FF  50  18  89  44  24  14  EB"), ClientHandle, 1, 3));
	AddOffset(StaticOffset(_IsVoiceRecording_Ptr, 0, ("83  B8  ??  ??  ??  ??  06  75  ??  80  3D  ??  ??  ??  ??  00  74"), EngineHandle, 1, 11));
	AddOffset(StaticOffset(_Interpolate, 0, ("55  8B  EC  83  EC  20  56  8B  F1  83  BE  ??  ??  00  00  00  0F  85"), ClientHandle));
	AddOffset(StaticOffset(_InterpolationVarMap, 0, ("8B  7E  ??  8B  4C  1F  ??  89  ??  ??  8B  01"), ClientHandle, 1, 2, 0, 0, 1));
	AddOffset(StaticOffset(_DelayUnscope, 0, ("55  8B  EC  A1  ??  ??  ??  ??  57  8B  F9  B9  ??  ??  ??  ??  FF  50  ??  85  C0  75  ??  32  C0"), ClientHandle));
	AddOffset(StaticOffset(_SelectWeightedSequence, 0, ("55  8B  EC  83  E4  F8  83  EC  14  53  56  8B  75  08  57  8B  F9  8B  16  83  BA"), ClientHandle));
	AddOffset(StaticOffset(_InitPose, 0, ("55  8B  EC  83  EC  10  53  8B  D9  89  55"), ServerHandle));
	AddOffset(StaticOffset(_AccumulatePose, 0, ("B8  ??  ??  ??  ??  E8  ??  ??  ??  ??  A1  ??  ??  ??  ??  56  57  8B  F9  B9"), ServerHandle));
	AddOffset(StaticOffset(_CalcAutoplaySequences, 0, ("55  8B  EC  83  EC  10  53  56  57  8B  7D  10"), ServerHandle));
	AddOffset(StaticOffset(_CalcBoneAdj, 0, ("55  8B  EC  83  E4  F8  81  EC  ??  ??  ??  ??  8B  C1  89"), ServerHandle));
	AddOffset(StaticOffset(_IKConstruct, 0, ("53  8B  D9  F6  C3"), ServerHandle));
	AddOffset(StaticOffset(_IKDestruct, 0, ("56  8B  F1  57  8D  8E  ??  ??  ??  ??  E8  ??  ??  ??  ??  8D  8E  ??  ??  ??  ??  E8  ??  ??  ??  ??  83  BE  ??  ??  ??  ??  00"), ServerHandle));
	AddOffset(StaticOffset(_ParticleProp, 0, ("0F  44  C1  8D  8F  ??  ??  ??  ??  6A  01  50  E8  ??  ??  ??  ??  8B  8F"), ClientHandle, 1, 5));
	AddOffset(StaticOffset(_SUB_Remove, 0, ("56  8B  F1  83  BE  ??  ??  00  00  00  7E  ??  68"), ClientHandle));
	AddOffset(StaticOffset(_Spawn, 0, ("8B  47  F8  8D  4F  F8  FF  90  ??  ??  00  00  8B  06"), ClientHandle, 1, 8, 4));
	AddOffset(StaticOffset(_Precache, 0, ("8B  06  8B  CE  FF  90  ??  ??  00  00  83  EC  10"), ClientHandle, 1, 6, 4));
	//AddOffset(StaticOffset(_PostThinkVPhysics, 0, ("55  8B  EC  83  E4  F8  81  EC  ??  ??  ??  ??  53  8B  D9  56  57  83  BB"), ClientHandle));
	//encrypts(0)
#ifdef DUMP_SIGS_FOR_BLACKBOOK
	g_Security.setup_data_for_server();
	g_Security.dump();
#endif


#if 0
	if (Global::IsPanorama)
	{
		AddOffset(StaticOffset(_LobbyScreen_Scaleform, 0));
		AddOffset(StaticOffset(_ChangeTeammateColor, 0));
		AddOffset(StaticOffset(_IsReady, 0));
		AddOffset(StaticOffset(_AcceptMatch, 0));
		AddOffset(StaticOffset(_GetWeaponDataIndex, 0));
	}
	else
	{
		AddOffset(StaticOffset(_LobbyScreen_Scaleform, 0, "74 1C FF 75 18 8B C8 FF 75 14 FF 75 10 FF 75 0C", ClientHandle, 1, -0x1B, 0, 0));
		AddOffset(StaticOffset(_ChangeTeammateColor, 0, "55 8B EC 83 EC 08 56 57 6A 00 68 ? ? ? ? 8D 4D F8", ClientHandle));
		AddOffset(StaticOffset(_IsReady, 0, "55 8B EC 83 E4 F8 83 EC 08 56 8B 35 ? ? ? ? 57 83 BE", ClientHandle));
		AddOffset(StaticOffset(_AcceptMatch, 0, "51 83 3D ? ? ? ? 00 74 ? C7 81 ? ? ? ? 01 00 00 00 8B 0D", ClientHandle));
		AddOffset(StaticOffset(_GetWeaponDataIndex, 0, "8B 03 83 C4 10 8B CB C7", ClientHandle, 1, 0x10, 4, 0));
	}
#endif
	m_bAlreadyAdded = true;
}

bool CStaticOffsets::ReadOffsetsFromFile()
{
#ifdef USE_CACHED_STATIC_OFFSETS
	//decrypts(0)
	std::ifstream file(("sig.txt"), std::ifstream::binary);
	//encrypts(0)
	
	if (!file.is_open())
		return false;

	//read api version from file
	char version;
	file.read(&version, sizeof(version));
	if (version != API_VERSION)
	{
		file.close();
		//decrypts(0)
		MessageBoxA(NULL, ("Warning: cached offsets file api invalid! Running sig scan anyway"), "", MB_OK);
		//encrypts(0)
		return false;
	}

	//read game version from file
	unsigned int gameversion;
	file.read((char*)&gameversion, sizeof(gameversion));

	//verify max offsets from file
	int numoffsets;
	file.read((char*)&numoffsets, sizeof(int));

	if (numoffsets != MAX_STATIC_OFFSETS || gameversion != Interfaces::EngineClient->GetEngineBuildNumber())
	{
		file.close();
		//decrypts(0)
		MessageBoxA(NULL, ("Warning: cached offsets outdated! Running sig scan anyway"), "", MB_OK);
		//encrypts(0)
		return false;
	}

	for (int i = 0; i < MAX_STATIC_OFFSETS; i++)
	{
		StaticOffsetName name;
		file.read((char*)&name, sizeof(name));

		if (name != StaticOffsetName::INVALID_STATIC_OFFSET)
		{
			bool ishardcoded;
			uint32_t decryptionkey;
			file.read((char*)&ishardcoded, sizeof(ishardcoded));
			file.read((char*)&decryptionkey, sizeof(decryptionkey));

			if (ishardcoded)
			{
				uint32_t offset;
				file.read((char*)&offset, sizeof(offset));
				AddOffset(StaticOffset(name, offset ^ decryptionkey, decryptionkey));
			}
			else
			{
				CachedStaticOffsetsHandle dll;
				uint32_t delta;
				int dereferencetimes;
				int addbeforedereference;
				int divideafterdereference;
				int addatend;
				int sizeofvalue;
				file.read((char*)&dll, sizeof(dll));
				file.read((char*)&delta, sizeof(delta));
				file.read((char*)&dereferencetimes, sizeof(dereferencetimes));
				file.read((char*)&addbeforedereference, sizeof(addbeforedereference));
				file.read((char*)&divideafterdereference, sizeof(divideafterdereference));
				file.read((char*)&addatend, sizeof(addatend));
				file.read((char*)&sizeofvalue, sizeof(sizeofvalue));
				HANDLE handle = HandleToCachedHandle(dll);
				if (dll != CachedStaticOffsetsHandle::CACHE_UNKNOWN)
					AddOffset(StaticOffset(name, ((uint32_t)handle + delta) ^ decryptionkey, handle, dereferencetimes, addbeforedereference, divideafterdereference, addatend, sizeofvalue, decryptionkey));
				else
					DebugBreak();
			}
		}
	}

	file.close();
	return true;
#endif
	return true;
}

void CStaticOffsets::DumpOffsetsToFile()
{
#ifdef DUMP_STATIC_OFFSETS
	//decrypts(0)
	std::ofstream file(("sig.txt"), std::ofstream::binary|std::ofstream::trunc);
	//encrypts(0)

	if (!file.is_open())
		return;

	//write api version
	char version = API_VERSION;
	file.write(&version, sizeof(version));

	//write game version
	unsigned int gamever = Interfaces::EngineClient->GetEngineBuildNumber();
	file.write((char*)&gamever, sizeof(gamever));

	//write max offsets
	int numoffsets = MAX_STATIC_OFFSETS;
	file.write((char*)&numoffsets, sizeof(int));
	StaticOffsetName invalidname = StaticOffsetName::INVALID_STATIC_OFFSET;

	//write each offset
	for (auto& iter : Offsets)
	{
		if (iter.GetName() == invalidname)
		{
			file.write((char*)&invalidname, sizeof(invalidname));
			continue;
		}

		auto ishardcoded = iter.IsHardCoded();
		uint32_t decryptionkey = iter.GetDecryptionKey();
		if (ishardcoded)
		{
			auto name = iter.GetName();
			auto offset = iter.GetOffset() ^ iter.GetDecryptionKey();
			file.write((char*)&name, sizeof(name));
			file.write((char*)&ishardcoded, sizeof(ishardcoded));
			file.write((char*)&decryptionkey, sizeof(decryptionkey));
			file.write((char*)&offset, sizeof(offset));
		}
		else
		{
			auto dll = HandleToCachedHandle(iter.GetHandle());

			if (dll != CachedStaticOffsetsHandle::CACHE_UNKNOWN)
			{
				auto name = iter.GetName();
				auto dereferencetimes = iter.GetDereferenceTimes();
				auto addbeforedereference = iter.GetAddBeforeDereference();
				auto divideafterdereference = iter.GetDivideAfterDereference();
				auto addatend = iter.GetAddAtEnd();
				auto sizeofvalue = iter.GetSizeOfValue();

				file.write((char*)&name, sizeof(name));
				file.write((char*)&ishardcoded, sizeof(ishardcoded));
				file.write((char*)&decryptionkey, sizeof(decryptionkey));
				file.write((char*)&dll, sizeof(dll));
				auto delta = iter.GetRawAddress() - (uint32_t)iter.GetHandle();
				file.write((char*)&delta, sizeof(delta));
				file.write((char*)&dereferencetimes, sizeof(dereferencetimes));
				file.write((char*)&addbeforedereference, sizeof(addbeforedereference));
				file.write((char*)&divideafterdereference, sizeof(divideafterdereference));
				file.write((char*)&addatend, sizeof(addatend));
				file.write((char*)&sizeofvalue, sizeof(sizeofvalue));
			}
			else
			{
				DebugBreak();

				//Handle not added here yet, just force a sig scan
				file.write((char*)&invalidname, sizeof(invalidname));
				continue;
			}
		}
	}

	file.close();
#endif
}

#pragma optimize("", off)





size_t GetModuleSize(HANDLE ModuleHandle)
{
	MODULEINFO dllinfo;
	GetModuleInformation(GetCurrentProcess(), (HMODULE)ModuleHandle, &dllinfo, sizeof(MODULEINFO));
	return dllinfo.SizeOfImage;
}
#include "console.hpp"

uint32_t FindPattern(HANDLE Module, std::string Pattern, uint32_t StartAddress, bool UseStartAddressAsStartPoint, bool SubtractBaseAddressFromStart, bool Dereference, uint32_t AddBeforeDereference, int DereferenceTimes, uint32_t* rawadr, int sizeofvalue)
{
	auto Start = ((uint32_t)Module + StartAddress);

	if (UseStartAddressAsStartPoint)
		Start = StartAddress;

	if (SubtractBaseAddressFromStart)
		Start -= (uint32_t)Module;

	struct sSignature {
		sSignature() {
			Index = 0;
			Byte = 0;
			IsWildcard = false;
		}

		sSignature(int _Index, uint8_t _Byte, bool _IsWildcard) {
			Index = _Index;
			Byte = _Byte;
			IsWildcard = _IsWildcard;
		}

		int Index;
		uint8_t Byte;
		bool IsWildcard;
	};

	std::vector<sSignature> vecSig;
	int TotalBytes = 0;

	auto _patternLength = Pattern.length();

	for (size_t i = 0; i < _patternLength; i++)
	{
		if (Pattern.data()[i] == ' ')
			continue;

		if (Pattern.data()[i] != '?')
			vecSig.emplace_back(sSignature(TotalBytes, (uint8_t)std::strtoul(Pattern.data() + i, nullptr, 16), false));
		else {
			if (i + 1 < _patternLength && Pattern.data()[i + 1] == '?')
				++i; //Fix patterns with double wide wildcards

			vecSig.emplace_back(sSignature(TotalBytes, 0, true));
		}

		TotalBytes++;
		i++;
	}

	auto CompareBytes = [](uint32_t _Address, std::vector<sSignature>& _vecSig)
	{
		auto _sigSize = _vecSig.size();
		for (size_t i = 0; i < _sigSize; ++i)
		{
			auto it = _vecSig.at(i);

			if (it.IsWildcard)
				continue;

			if (it.Byte != *reinterpret_cast<uint8_t*>(_Address + it.Index))
				return false;
		}

		return true;
	};

	size_t ModuleSize = GetModuleSize(Module);

	for (uint32_t idx = 0; idx < ModuleSize; ++idx)
	{
		auto retn = Start + idx;

		if (CompareBytes(retn, vecSig))
		{
			//decrypts(0)
			logger::add(LSUCCESS, "Found Signature: 0x%x", retn);
			//encrypts(0)

			if (rawadr)
				*rawadr = retn;

			if (Dereference)
			{
				retn += AddBeforeDereference;

				for (int i = 0; i < DereferenceTimes; ++i)
				{
					switch (sizeofvalue)
					{
					case 4:
						retn = *reinterpret_cast<uint32_t*>(retn);
						break;
					case 2:
						retn = *reinterpret_cast<uint16_t*>(retn);
						break;
					case 1:
						retn = *reinterpret_cast<uint8_t*>(retn);
						break;
					default:
						//not supported! retn is 32 bit
						DebugBreak();
						break;
					}
				}
			}

			return retn;
		}
	}

	//decrypts(0)
	logger::add(LWARN, "WARNING! Signature not found.");

	//encrypts(0)

	if (rawadr)
		*rawadr = 0;

	return 0;
}











void CStaticOffsets::UpdateAllOffsets()
{
	for (auto& iter : Offsets)
	{
		if (iter.GetName() != INVALID_STATIC_OFFSET)
		{
			if (!iter.IsHardCoded())
			{
				uint32_t rawadr;
				uint32_t tostore;
				uint32_t sizeofvalue = iter.GetSizeOfValue();

				if (iter.ShouldUseRawHandle())
				{
					rawadr = iter.GetRawAddress();
					tostore = iter.GetRawAddress();
					if (iter.ShouldDereference())
					{
						tostore += iter.GetAddBeforeDereference();
						auto dereftimes = iter.GetDereferenceTimes();
						for (int i = 0; i < dereftimes; ++i)
						{
							switch (sizeofvalue)
							{
							case 4:
								tostore = *reinterpret_cast<uint32_t*>(tostore);
								break;
							case 2:
								tostore = *reinterpret_cast<uint16_t*>(tostore);
								break;
							case 1:
								tostore = *reinterpret_cast<uint8_t*>(tostore);
								break;
							default:
								//not supported! tostore is 32 bit
								DebugBreak();
								break;
							}
						}
					}
				}
				else
				{
					tostore = FindPattern(iter.GetHandle(), iter.GetSignature(), 0, false, false, iter.ShouldDereference(), iter.GetAddBeforeDereference(), iter.GetDereferenceTimes(), &rawadr, sizeofvalue);

					if (!tostore)
					{
						char msg[256];
#ifdef IMI_MENU
						//decrypts(0)
						//sprintf(msg, ("Failed to find signature for StaticOffsetName %i"), (int)iter.GetName());
						//MessageBoxA(NULL, msg, ("Error"), MB_OK);
						//encrypts(0)
#else
#ifdef MUTINY_FRAMEWORK
						//decrypts(0)
						THROW_ERROR(("CSGO UPDATED, WAIT FOR NEW CHEAT UPDATE"));
						//encrypts(0)
#else
						//decrypts(0)
						sprintf(msg, ("Failed to find signature for StaticOffsetName %i"), (int)iter.GetName());
						MessageBoxA(NULL, msg, ("Error"), MB_OK);
						//encrypts(0)
#endif
#endif
					}
				}

				if (tostore)
				{
					if (iter.ShouldDivideAfterDereference())
						tostore /= iter.GetDivideAfterDereference();
					tostore += iter.GetAddAtEnd();

					iter.SetFound(true);
				}

				iter.SetOffset(tostore);
				iter.SetRawAddress(rawadr);
			}
			
			iter.SetOffset(iter.GetOffset());
			iter.SetRawAddress(iter.GetRawAddress());
		}
	}

	//Interfaces::GameRules = GetOffsetValueByType<C_CSGameRules**>(_GameRules);
	TE_FireBullets = GetOffsetValueByType<C_TEFireBullets*>(_TE_FireBullets);
	TE_EffectDispatch = GetOffsetValueByType<C_TEEffectDispatch*>(_TE_EffectDispatch);
	//uint32_t* RelativeAdr = GetOffsetValueByType<uint32_t*>(_CCLCMsg_Move_Deconstructor_relative);
	//CCLCMsg_Move_Deconstructor = (CCLCMsg_Move_Deconstructor_Fn)((uint32_t)RelativeAdr + 4 + *RelativeAdr);
	//g_SplitScreenMgr = GetOffsetValueByType<CSplitScreen*>(_SplitScreenMgr);
	//g_ActivityModifiersTable = GetOffsetValueByType<CUtlSymbolTable*>(_g_ActivityModifiersTable);
	//CUtlSymbol::s_pSymbolTable = GetOffsetValueByType<CUtlSymbolTableMT**>(_s_pSymbolTable);

	//update the CStudioHdr struct for m_boneFlags if this changes!
	if (GetOffsetValue(_boneFlagsOffset) != 48)
		DebugBreak();

	//std::ofstream out("f:\\static_offsets.txt");
	//for (int i = 0; i < MAX_STATIC_OFFSETS; ++i)
	//{
	//	out << std::dec << i << " 0x" << std::hex << StaticOffsets.GetOffsetValue((StaticOffsetName)i) << "\n";
	//}
	//out.flush();

	DumpOffsetsToFile();
	HideStaticOffsets();
}
#pragma optimize("", on)

void CStaticOffsets::HideStaticOffsets()
{
#ifndef _DEBUG
	for (auto& iter : Offsets)
	{
		iter.ClearIdentifiableData();	
	}
#endif
}

StaticOffset &CStaticOffsets::GetOffset(StaticOffsetName name)
{
	return Offsets.at(name);
}

uint32_t CStaticOffsets::GetOffsetValue(StaticOffsetName name)
{
	return Offsets.at(name).GetOffset();
}