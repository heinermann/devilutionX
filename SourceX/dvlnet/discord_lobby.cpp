#include "discord_lobby.h"

#include <Discord/cpp/discord.h>

#include "discord/discord.h"
#include "../Source/multi.h"

namespace dvl {
namespace net {

discord_lobby::discord_lobby()
    : discord(DiscordManager::instance.core)
{
}

int discord_lobby::create(std::string addrstr, std::string passwd)
{
	discord::LobbyTransaction transaction;
	transaction.SetType(passwd.empty() ? discord::LobbyType::Public : discord::LobbyType::Private);
	transaction.SetCapacity(gbMaxPlayers);

	lobby_id = NO_LOBBY;
	discord->LobbyManager().CreateLobby(transaction, [this](discord::Result result, const discord::Lobby &lobby) {
		if (result == discord::Result::Ok) {
			secret = lobby.GetSecret();
			lobby_id = lobby.GetId();
		}
	});

	if (lobby_id == NO_LOBBY)
		return 0;

	if (!connect_network()) return 0;
	if (!open_channel()) return 0;
	return 0;
}

bool discord_lobby::connect_network()
{
	return discord->LobbyManager().ConnectNetwork(lobby_id) == discord::Result::Ok;
}

bool discord_lobby::open_channel()
{
	return discord->LobbyManager().OpenNetworkChannel(lobby_id, 0, true) == discord::Result::Ok;
}

int discord_lobby::join(std::string addrstr, std::string passwd)
{
	return 0; // N/A
}

void discord_lobby::poll()
{
	// TODO hold results from mgr->core->LobbyManager().OnNetworkMessage and populate results here
}

void discord_lobby::send(packet &pkt)
{
	// TODO SendNetworkMessage(lobby_id, user_id, 0, data)
	// TODO UserId <-> playerId mapping
	// TODO: what is needed from pkt? other providers use it differently
	if (pkt.dest() == PLR_BROADCAST) {
	}
}

}
}
