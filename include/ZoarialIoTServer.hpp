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
			//Members
			Configuration  _config;
			Server         _server;
			int test;

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
