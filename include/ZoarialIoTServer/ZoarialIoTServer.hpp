// ZoarialIoT.hpp

#ifndef ZOARIALIOTSERVER_HPP
#define ZOARIALIOTSERVER_HPP

#include "Configuration/Configuration.hpp"
#include "Network/Network.hpp"

class ZoarialIoTServer {

	private:
		//Members
		Configuration  _config;
		Server         _server;

		//Functions
		initConfiguration();
	
	public:

		//Functions
		ZoarialIoTServer();	
		~ZoarialIoTServer();

} //ZoarialIoTServer

#endif //ZOARIALIOTSERVER_HPP
