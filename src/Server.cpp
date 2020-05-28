#include "Server.hpp"

#include <pcap/pcap.h>

#include <iostream>

using namespace ZoarialIoT;
Server::Server(std::string& hostname, int ipAddr, bool nodeType, bool isVolatile, int port, std::string interface, int messageTimeout, int pingTimeout) : 
HOSTNAME(hostname), IP_ADDR(ipAddr), NODE_TYPE(nodeType), IS_VOLATILE(isVolatile), PORT(port), INTERFACE(interface), _messageTimeout(messageTimeout), _pingTimeout(pingTimeout)
{

	std::cout << "Constructing Server" << std::endl;
	std::cout << "Using Port Number: " << PORT <<std::endl;
	
	std::cout << "Server Constructed" << std::endl;
}

Server::~Server() {
	std::cout << "Deconstructing Server...";
	
	std::cout << "Success" << std::endl;
}


bool Server::UDPpacketHandler() {
    
    //std::cout << "\tMAC Addr: " << eth.dst_addr() << "\n";
    //std::cout << "\tIP Addr: " << ip.src_addr() << "\n";
  	//std::cout << "\tUDP Src Port: " << udp.sport() << "\n";
  	//std::cout << "\tUDP Dst Port: " << udp.dport() << "\n";
  	//std::cout << "\t" << std::string(raw.payload().begin(), raw.payload().end()) << "\n\n";
  	return false;
    
}

bool Server::TCPpacketHandler() {
	return false;
}

void Server::start() {
	
}
