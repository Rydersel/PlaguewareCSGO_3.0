#pragma once

#include <cstdint>

#include "..\math\Vector.hpp"
#include "..\misc\bf_write.h"

#define GenDefineVFunc(...) ( this, __VA_ARGS__ ); }
#define VFUNC( index, func, sig ) auto func { return call_virtual< sig >( this, index ) GenDefineVFunc

class CClockDriftMgr {
public:
	float m_ClockOffsets[ 17 ];   //0x0000
	uint32_t m_iCurClockOffset; //0x0044
	uint32_t m_nServerTick;     //0x0048
	uint32_t m_nClientTick;     //0x004C
}; 

class INetChannel
{
public:
	char pad_0x0000[ 0x18 ]; //0x0000
	__int32 m_nOutSequenceNr; //0x0018 
	__int32 m_nInSequenceNr; //0x001C 
	__int32 m_nOutSequenceNrAck; //0x0020 
	__int32 m_nOutReliableState; //0x0024 
	__int32 m_nInReliableState; //0x0028 
	__int32 m_nChokedPackets; //0x002C

	void Transmit(bool onlyreliable)
	{
		using Fn = bool(__thiscall*)(void*, bool);
		call_virtual<Fn>(this, 49)(this, onlyreliable);
	}

	void send_datagram()
	{
		using Fn = int(__thiscall*)(void*, void*);
		call_virtual<Fn>(this, 46)(this, 0);
	}

	void SetTimeOut(float seconds)
	{
		using Fn = void(__thiscall*)(void*, float);
		return call_virtual<Fn>(this, 4)(this, seconds);
	}

	int RequestFile(const char* filename)
	{
		using Fn = int(__thiscall*)(void*, const char*);
		return call_virtual<Fn>(this, 62)(this, filename);
	}
};

class INetMessage
{
public:
	virtual	~INetMessage() {};

	// Use these to setup who can hear whose voice.
	// Pass in client indices (which are their ent indices - 1).

	virtual void	SetNetChannel(INetChannel * netchan) = 0; // netchannel this message is from/for
	virtual void	SetReliable(bool state) = 0;	// set to true if it's a reliable message

	virtual bool	Process(void) = 0; // calles the recently set handler to process this message

	virtual	bool	ReadFromBuffer(bf_read &buffer) = 0; // returns true if parsing was OK
	virtual	bool	WriteToBuffer(bf_write &buffer) = 0;	// returns true if writing was OK

	virtual bool	IsReliable(void) const = 0;  // true, if message needs reliable handling

	virtual int				GetType(void) const = 0; // returns module specific header tag eg svc_serverinfo
	virtual int				GetGroup(void) const = 0;	// returns net message group of this message
	virtual const char		*GetName(void) const = 0;	// returns network message name, eg "svc_serverinfo"
	virtual INetChannel		*GetNetChannel(void) const = 0;
	virtual const char		*ToString(void) const = 0; // returns a human readable string about message content
};
class CEventInfo
{
public:
	uint16_t		classID;			//0x0
	char			pad_0[0x2];		//0x2 
	float			fire_delay;			//0x4
	char			pad_1[0x4];		//0x8
	ClientClass* pClientClass;		//0xC
	void* pData;				//0x10
	char			pad_2[0x30];		//0x14
};
class CClientState
{
	class CClockDriftManager {

	public:
		float clock_offsets[0x10];
		uint32_t cur_clock_offset;
		uint32_t m_server_tick;
		uint32_t m_client_tick;
	};

public:
	char            pad000[0x9C];
	INetChannel* m_net_channel;
	int                m_nChallengeNr;
	char            pad001[0x4];
	double            m_connect_time;
	int                m_retry_number;
	char            pad002[0x54];
	int                m_nSignonState;
	char            pad003[0x4];
	double            m_flNextCmdTime;
	int                m_nServerCount;
	int                m_current_sequence;
	char            pad004[0x8];

	CClockDriftManager clock_drift_mgr;

	int                m_delta_tick;
	char            pad005[0x4];
	int                m_nViewEntity;
	int                m_nPlayerSlot;
	bool            m_bPaused;
	char            pad006[0x3];
	char            m_szLevelName[0x104];
	char            m_szLevelNameShort[0x28];
	char            pad007[0xD4];
	int                m_nMaxClients;
	char            pad008[0x4994];
	int                oldtickcount;
	float            m_tickRemainder;
	float            m_frameTime;
	int                m_last_outgoing_command;
	int                m_choked_commands;
	int                m_last_command_ack;
	int                m_last_server_tick;
	int                m_command_ack;
	int                m_nSoundSequence;
	int                m_last_progress_percent;
	bool            m_is_hltv;
	char            pad009[0x4B];
	Vector            m_viewangles;
	char            pad010[0xCC];
	CEventInfo* m_events;
}; 