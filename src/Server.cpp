#include "Server.hpp"

#include <tins/tins.h>

#include <iostream>

using namespace ZoarialIoT;

Server::Server(std::string& hostname, int ipAddr, bool nodeType, bool isVolatile, int port, std::string interface, int messageTimeout, int pingTimeout) : 
HOSTNAME(hostname), IP_ADDR(ipAddr), NODE_TYPE(nodeType), IS_VOLATILE(isVolatile), PORT(port), INTERFACE(interface), _messageTimeout(messageTimeout), _pingTimeout(pingTimeout)
{

	std::cout << "Constructing Server" << std::endl;
	std::cout << "Using Port Number: " << PORT <<std::endl;
	_sender = std::make_unique<Tins::PacketSender>(INTERFACE);
	_UDPsniffer = std::make_unique<Tins::Sniffer>(INTERFACE);
	_TCPsniffer = std::make_unique<Tins::Sniffer>(INTERFACE);
	_UDPSnifferConfig.set_filter("udp and broadcast and port " + std::to_string(PORT));
	_TCPSnifferConfig.set_filter("tcp and port " + std::to_string(PORT));
	std::cout << "Server Constructed" << std::endl;
}

Server::~Server() {
	std::cout << "Deconstructing Server...";
	
	std::cout << "Success" << std::endl;
}
