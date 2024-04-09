#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "Spectrum.h"
#include "SpectrumGameInstance.h"
#include "SocketSubsystem.h"
#include "PacketSession.h"
#include "Protocol.pb.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	return false;
}

bool Handle_S_LOGIN(PacketSessionRef& session, Protocol::S_LOGIN& pkt)
{
	for (auto& Player : pkt.players())
	{
	}

	for (int32 i = 0; i < pkt.players_size(); i++)
	{
		const Protocol::ObjectInfo& Player = pkt.players(i);
	}

	// 나중에 로그인 DB에 없으면 회원가입되도록 수정
	Protocol::C_ENTER_GAME EnterGamePkt;
	EnterGamePkt.set_playerindex(0);
	SEND_PACKET(EnterGamePkt);


	return true;
}

bool Handle_S_ENTER_GAME(PacketSessionRef& session, Protocol::S_ENTER_GAME& pkt)
{

	if (auto* GameInstance = Cast<USpectrumGameInstance>(GWorld->GetGameInstance()))
	{
		GameInstance->HandleSpawn(pkt);
	}

	return true;
}

bool Handle_S_LEAVE_GAME(PacketSessionRef& session, Protocol::S_LEAVE_GAME& pkt)
{
	if (auto* GameInstance = Cast<USpectrumGameInstance>(GWorld->GetGameInstance()))
	{
		// 나중에 게임 종료할지 로비로 갈지 결정
	}

	return true;
}

bool Handle_S_SPAWN(PacketSessionRef& session, Protocol::S_SPAWN& pkt)
{
	if (auto* GameInstance = Cast<USpectrumGameInstance>(GWorld->GetGameInstance()))
	{
		GameInstance->HandleSpawn(pkt);
	}

	return true;
}

bool Handle_S_DESPAWN(PacketSessionRef& session, Protocol::S_DESPAWN& pkt)
{
	if (auto* GameInstance = Cast<USpectrumGameInstance>(GWorld->GetGameInstance()))
	{
		GameInstance->HandleDespawn(pkt);

	}	

	return true;
}

bool Handle_S_O_SPAWN(PacketSessionRef& session, Protocol::S_O_SPAWN& pkt)
{
	if (auto* GameInstance = Cast<USpectrumGameInstance>(GWorld->GetGameInstance()))
	{
		Protocol::PositionInfo posInfo = pkt.objects();
		posInfo.set_object_id(pkt.objects().object_id());

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%lld"), posInfo.object_id()));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%f %f %f"), 
			posInfo.x(), posInfo.y(), posInfo.z()));

		GameInstance->HandleOSpawn(posInfo, false);

	}

	//auto* GameInstance = Cast<USpectrumGameInstance>(GWorld->GetGameInstance());
	//Protocol::PositionInfo posInfo = pkt.objects();
	//posInfo.set_object_id(pkt.objects().object_id());

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%lld"), posInfo.object_id()));
	//GameInstance->HandleOSpawn(posInfo, false);

	return true;
}

bool Handle_S_O_DESPAWN(PacketSessionRef& session, Protocol::S_O_DESPAWN& pkt)
{
	return false;
}

bool Handle_S_MOVE(PacketSessionRef& session, Protocol::S_MOVE& pkt)
{
	if (auto* GameInstance = Cast<USpectrumGameInstance>(GWorld->GetGameInstance()))
	{
		GameInstance->HandleMove(pkt);
	}

	return true;
}

bool Handle_S_TURN(PacketSessionRef& session, Protocol::S_TURN& pkt)
{
	if (auto* GameInstance = Cast<USpectrumGameInstance>(GWorld->GetGameInstance()))
	{
		GameInstance->HandleTurn(pkt);
	}

	return true;
}

bool Handle_S_O_MOVE(PacketSessionRef& session, Protocol::S_O_MOVE& pkt) {

	if (auto* GameInstance = Cast<USpectrumGameInstance>(GWorld->GetGameInstance()))
	{
		GameInstance->HandleOMove(pkt);
	}

	return true;


}

bool Handle_S_O_BURST(PacketSessionRef& session, Protocol::S_O_BURST& pkt)
{
	if (auto* GameInstance = Cast<USpectrumGameInstance>(GWorld->GetGameInstance()))
	{
		GameInstance->HandleOBurst(pkt);
	}

	return true;
}

bool Handle_S_O_POTION(PacketSessionRef& session, Protocol::S_O_POTION& pkt)
{
	if (auto* GameInstance = Cast<USpectrumGameInstance>(GWorld->GetGameInstance()))
	{
		GameInstance->HandleOPotion(pkt);
	}

	return true;
}

bool Handle_S_CHAT(PacketSessionRef& session, Protocol::S_CHAT& pkt)
{
	auto Msg = pkt.msg();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Msg")));

	return true;
}
