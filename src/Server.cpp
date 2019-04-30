#include "Server.hpp"

#include <tins/tins.h>

#include <string>
#include <iostream>

using namespace ZoarialIoT;

Server::Server(std::string& hostname, int ipAddr, bool nodeType, bool isVolatile, int port, int messageTimeout, int pingTimeout) : 
HOSTNAME(hostname), IP_ADDR(ipAddr), NODE_TYPE(nodeType), IS_VOLATILE(isVolatile), PORT(port), _messageTimeout(messageTimeout), _pingTimeout(pingTimeout)
{

	std::cout << "Constructing Server...";
	sender = std::make_unique<Tins::PacketSender>("eth0");
	std::cout << "Success" << std::endl;
}

Server::~Server() {
	std::cout << "Deconstructing Server...";

	std::cout << "Success" << std::endl;
}
