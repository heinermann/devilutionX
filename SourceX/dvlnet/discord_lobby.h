#pragma once

#include <cstdint>
#include <string>

#include "dvlnet/base.h"
#include "dvlnet/packet.h"


namespace discord {
class Core;
}

namespace dvl {
namespace net {

class discord_lobby : public base {
public:
	discord_lobby();

	int create(std::string addrstr, std::string passwd) override;

	// Unused - joining games will be done through Discord only
	int join(std::string addrstr, std::string passwd) override;

	void poll() override;
	void send(packet &pkt) override;

private:
	static constexpr std::int64_t NO_LOBBY = -1;

	discord::Core* discord;

	std::string secret;
	std::int64_t lobby_id = NO_LOBBY;
	bool connected = false;

	bool connect_network();
	bool open_channel();
};

} // namespace net
} // namespace dvl
