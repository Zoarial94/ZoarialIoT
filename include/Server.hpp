
#ifndef SERVER_HPP
#define SERVER_HPP

#include <tins/tins.h>

#include <iostream>
#include <string>
#include <memory>

namespace ZoarialIoT {
	class Server {

	private:
	//Constants
		const std::string 	HOSTNAME;
		const int 			IP_ADDR;
		const bool 			NODE_TYPE;
		const bool			IS_VOLATILE;
		const int 			PORT;
		const std::string 	INTERFACE;

	//Variables
		//In milliseconds
		int _messageTimeout;
		//In Seconds
		int _pingTimeout;

	//Members
		Tins::SnifferConfiguration 	_UDPSnifferConfig;
		Tins::SnifferConfiguration 	_TCPSnifferConfig;
		Tins::PacketSender 			_sender;
		Tins::Sniffer 				_UDPSniffer;
		Tins::Sniffer				_TCPSniffer;

	//Functions
		bool UDPpacketHandler(Tins::PDU& pdu);
		bool TCPpacketHandler(Tins::PDU& pdu);

	public:
		Server(std::string& hostname, int ipAddr, bool nodeType, bool isVolatile, int port, std::string interface, int messageTimeout, int pingTimeout);
		~Server();

	}; //Server
} //ZoairalIoT

#endif //SERVER_HPP
