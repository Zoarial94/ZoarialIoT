// ZoarialIoT.hpp

#ifndef ZOARIALIOTSERVER_HPP
#define ZOARIALIOTSERVER_HPP

#include "Configuration/Configuration.hpp"
#include "Network/Network.hpp"
#include <string>

namespace ZoarialIoT {

	class ZoarialIoTServer {

		private:
			//Members
			Configuration  _config;
			Server         _server;

			//Functions
			bool initConfiguration();

		public:

			//Functions
			ZoarialIoTServer();	
			~ZoarialIoTServer();

			bool setConfigFile(std::string&);

	}; //ZoarialIoTServer
} //ZoarialIoT
#endif //ZOARIALIOTSERVER_HPP
