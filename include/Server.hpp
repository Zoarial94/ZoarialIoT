
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
			std::unique_ptr<Tins::PacketSender> _sender;
			std::unique_ptr<Tins::Sniffer> 		_UDPsniffer;
			std::unique_ptr<Tins::Sniffer> 		_TCPsniffer;
			Tins::SnifferConfiguration 			_UDPSnifferConfig;
			Tins::SnifferConfiguration 			_TCPSnifferConfig;

		//Functions
			bool packetHandler(const Tins::PDU& pkt);

		public:
			Server(std::string& hostname, int ipAddr, bool nodeType, bool isVolatile, int port, std::string interface, int messageTimeout, int pingTimeout);
			~Server();

	}; //Server
} //ZoairalIoT

#endif //SERVER_HPP
