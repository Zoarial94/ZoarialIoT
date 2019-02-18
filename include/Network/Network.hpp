
#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "ZoarialIoTServer/ZoarialIoTServer.hpp"
#include <iostream>
#include <tins/tins.h>

class ZoarialIoTServer::Server {
	
	private:
		Tins::PacketSender sender;

	public:
		Server::Server();

}

#endif //NETWORK_HPP
