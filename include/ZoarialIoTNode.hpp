// ZoarialIoT.hpp

#ifndef ZOARIALIOTNODE_HPP
#define ZOARIALIOTNODE_HPP

#include "Server.hpp"
#include <string>
#include <iostream>
#include <config4cpp/Configuration.h>

namespace ZoarialIoT {

	class ZoarialIoTNode {

		private:
		//Inizalizing Variables

			//Server should reset if any of these change
			std::string 	_hostname;
			int 			_ipAddr;
			bool 			_nodeType;
			bool 			_isVolatile;
			std::string 	_configFileName;
	
			//Can change in run time
			int 			_messageTimeout;
			int 			_pingTimeout;
			std::string 	_logFileName;
			int 			_loggingLevel;

		//Constants
			const char * DEVICE = 		"ZoarialIoT.device";
			const char * LOGGING = 		"ZoarialIoT.logging";
			
			const std::string CONFIG_VERSION = "0.1";
			const std::string DEFAULT_CONFIG_FILE = "/etc/ZoarialIoT/default.cfg";

		//Variables
		
		//Members
			config4cpp::Configuration * _cfg;
			//Server         _server;

		//Functions
			/*
			 * Configuration Functions
			 *
			 * Used to handle some interations with config4cpp
			 *
			 *
			**/
			bool openConfigFile();
			bool openConfigFile(const std::string& file);
			bool fileExists(const std::string& file);
			bool readConfigFile();

		public:

		//Functions
			ZoarialIoTNode();	
			~ZoarialIoTNode();

			bool setConfigFile(const std::string& file);
			bool initServerConfiguration();

	}; //ZoarialIoTNode
} //ZoarialIoT
#endif //ZOARIALIOTNODE_HPP
