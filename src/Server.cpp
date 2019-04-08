#include "Server.hpp"

#include <tins/tins.h>

#include <string>
#include <iostream>

using namespace ZoarialIoT;

Server::Server(std::string& hostname, int ipAddr, bool nodeType, bool isVolatile, int messageTimeout, int pingTimeout) : 
HOSTNAME(hostname), IP_ADDR(ipAddr), NODE_TYPE(nodeType), IS_VOLATILE(isVolatile), _messageTimeout(messageTimeout), _pingTimeout(pingTimeout)
{

	std::cout << "Constructing Server..." << std::endl;
	sender = Tins::PacketSender("eth0");

}

Server::~Server() {

}
