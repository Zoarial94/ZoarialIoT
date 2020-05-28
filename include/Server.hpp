
#ifndef SERVER_HPP
#define SERVER_HPP

#include <pcap/pcap.h>

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
	

	//Functions
		bool UDPpacketHandler();
		bool TCPpacketHandler();

	public:
		Server(std::string& hostname, int ipAddr, bool nodeType, bool isVolatile, int port, std::string interface, int messageTimeout, int pingTimeout);
		~Server();
		
		void start();

	}; //Server
} //ZoairalIoT

#endif //SERVER_HPP
