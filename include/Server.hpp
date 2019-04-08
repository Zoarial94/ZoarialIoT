
#ifndef SERVER_HPP
#define SERVER_HPP

#include <tins/tins.h>

#include <iostream>
#include <string>

namespace ZoarialIoT {
	class Server {

		private:
		//Constants
			const std::string 	HOSTNAME;
			const int 			IP_ADDR;
			const bool 			NODE_TYPE;
			const bool			IS_VOLATILE;

		//Variables
			//In milliseconds
			int _messageTimeout;
			//In Seconds
			int _pingTimeout;

		//Members
			Tins::PacketSender sender;
			
		//Functions

		public:
			Server(std::string& hostname, int ipAddr, bool nodeType, bool isVolatile, int messageTimeout, int pingTimeout);
			~Server();

	}; //Server
} //ZoairalIoT

#endif //SERVER_HPP
