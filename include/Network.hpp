
#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <tins/tins.h>


namespace ZoarialIoT {
	class Server {

		private:
			Tins::PacketSender sender;

		public:
			Server();
			~Server();

	}; //Server
} //ZoairalIoT

#endif //NETWORK_HPP
