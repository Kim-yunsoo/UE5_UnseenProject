﻿#include "pch.h"
#include <iostream>
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "GameSessionManager.h"
//#include "ClientPacketHandler.h"
#include <tchar.h>
#include "Job.h"
#include "Protocol.pb.h"
#include "Room.h"
#include "ObjectUtils.h"
#include "Thing.h"

enum
{
	WORKER_TICK = 64
};

void DoWorkerJob(ServerServiceRef& service)
{


	while (true)
	{
		LEndTickCount = ::GetTickCount64() + WORKER_TICK;

		// 네트워크 입출력 처리 -> 인게임 로직까지 (패킷 핸들러에 의해)
		service->GetIocpCore()->Dispatch(10);

		// 예약된 일감 처리
		ThreadManager::DistributeReservedJobs();

		// 글로벌 큐
		ThreadManager::DoGlobalQueueWork();
	}
}

int main()
{
	ServerPacketHandler::Init();

	ServerServiceRef service = make_shared<ServerService>(
		//NetAddress(L"192.168.1.21", 7777),
		NetAddress(L"127.0.0.1", 7777),
		// NetAddress(L"192.168.20.2", 7777),
		//NetAddress(L"192.168.1.27", 7777),
		//NetAddress(L"192.168.45.25", 7777),
		make_shared<IocpCore>(),
		[=]() { return make_shared<GameSession>(); }, // TODO : SessionManager 등
		100);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([&service]()
			{
				DoWorkerJob(service);
			});
	}

	// Main Thread
	// DoWorkerJob(service);

	


	while (true)
	{
		//Protocol::S_O_SPAWN pkt;
		//pkt.set_msg("HelloWorld");
		//auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);

		//GSessionManager.Broadcast(sendBuffer);
		//GRoom->updateTick();

		//Protocol::S_O_SPAWN pkt;

		//Protocol::PositionInfo* posInfo = new Protocol::PositionInfo();
		//posInfo->set_x(1.f);
		//posInfo->set_y(2.f);
		//posInfo->set_z(3.f);
		//posInfo->set_yaw(4.f);
		//posInfo->set_object_id(20);

		//pkt.set_allocated_objects(posInfo);
		//auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);

		//GSessionManager.Broadcast(sendBuffer);

		//Sleep(0.1);
	}

	

	GThreadManager->Join();
}