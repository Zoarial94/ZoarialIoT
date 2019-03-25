// ZoarialIoT.hpp

#ifndef ZOARIALIOTSERVER_HPP
#define ZOARIALIOTSERVER_HPP

#include "Configuration.hpp"
#include "Network.hpp"
#include <string>
#include <iostream>

namespace ZoarialIoT {

	class ZoarialIoTServer {

		private:
			//Constants n other info
			std::string _configFile;
			
			//Members
			Configuration  _config;
			Server         _server;
			int test;

			//Functions
			bool initServerConfiguration();

		public:

			//Functions
			ZoarialIoTServer();	
			~ZoarialIoTServer();

			bool setConfigFile(std::string&);

	}; //ZoarialIoTServer
} //ZoarialIoT
#endif //ZOARIALIOTSERVER_HPP
