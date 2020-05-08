#include "Server.hpp"

#include <tins/tins.h>

#include <iostream>

using namespace ZoarialIoT;
using namespace Tins;

Server::Server(std::string& hostname, int ipAddr, bool nodeType, bool isVolatile, int port, std::string interface, int messageTimeout, int pingTimeout) : 
HOSTNAME(hostname), IP_ADDR(ipAddr), NODE_TYPE(nodeType), IS_VOLATILE(isVolatile), PORT(port), INTERFACE(interface), _messageTimeout(messageTimeout), _pingTimeout(pingTimeout),
_sender(INTERFACE), _UDPSniffer(INTERFACE, _UDPSnifferConfig), _TCPSniffer(INTERFACE, _TCPSnifferConfig) 
{

	std::cout << "Constructing Server" << std::endl;
	std::cout << "Using Port Number: " << PORT <<std::endl;
	
	_UDPSnifferConfig.set_filter("udp and broadcast and port " + std::to_string(PORT));
	_TCPSnifferConfig.set_filter("tcp and port " + std::to_string(PORT));
	
	//_sender = std::make_unique<Tins::PacketSender>(INTERFACE);
	//_UDPsniffer = std::make_unique<Tins::Sniffer>(INTERFACE, _UDPSnifferConfig);
	//_TCPsniffer = std::make_unique<Tins::Sniffer>(INTERFACE, _TCPSnifferConfig);
	
	//	TODO: Do this in its own thread	
	_UDPSniffer.sniff_loop(make_sniffer_handler(this, &Server::UDPpacketHandler));
	
	std::cout << "Server Constructed" << std::endl;
}

Server::~Server() {
	std::cout << "Deconstructing Server...";
	
	std::cout << "Success" << std::endl;
}


bool Server::UDPpacketHandler(Tins::PDU& pdu) {
	
    const EthernetII &eth = pdu.rfind_pdu<EthernetII>();
    const IP &ip = pdu.rfind_pdu<IP>();
    const UDP &udp = pdu.rfind_pdu<UDP>();
    const RawPDU raw = pdu.rfind_pdu<RawPDU>();
    
    std::cout << "\tMAC Addr: " << eth.dst_addr() << "\n";
    std::cout << "\tIP Addr: " << ip.src_addr() << "\n";
  	std::cout << "\tUDP Src Port: " << udp.sport() << "\n";
  	std::cout << "\tUDP Dst Port: " << udp.dport() << "\n";
  	std::cout << "\t" << std::string(raw.payload().begin(), raw.payload().end()) << "\n\n";
  	return false;
    
}

bool Server::TCPpacketHandler(Tins::PDU& pdu) {
	return false;
}
