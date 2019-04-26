// ZoarialIoT.hpp

#ifndef ZOARIALIOTNODE_HPP
#define ZOARIALIOTNODE_HPP

#include "Server.hpp"
#include <string>
#include <iostream>
#include <config4cpp/Configuration.h>
#include <exception>

namespace ZoarialIoT {

	class ZoarialIoTNode {

		private:
		//Arguments/Options

			//Should the default config be used on the failure to parse the given config file
			bool _useDefaultConfigOnInvalidConfig;

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
			
			const int RECV_NODE = 	0;
			const int BASIC_NODE = 	1;
			const int SATELLITE =   2;
			
			const char * APP = "ZoarialIoT";
			
			const char * DEVICE = 		"ZoarialIoT.device";
			const char * LOGGING = 		"ZoarialIoT.logging";
			
			const std::string CONFIG_VERSION = "0.1";
			const std::string DEFAULT_CONFIG_FILE = "/etc/ZoarialIoT/default.cfg";

		//Variables
		
		//Members
			config4cpp::Configuration * _cfg;
			config4cpp::Configuration * _defaultCfg;
			//Server         _server;

		//Functions
			/*
			 * Configuration Functions
			 *
			 * Used to handle some interations with config4cpp
			 *
			 *
			**/
			int openConfigFile();
			int openConfigFile(const std::string& file);
			int verifyServerConfigOptions();
			bool fileExists(const std::string& file);
			int readConfigFile();
			int openDefaultConfigFile();

			const char* readStringFromConfigFile(const char* scope, const char* localName, const char* defaultVal);
			int readIntFromConfigFile(const char* scope, const char* localName, int defaultVal);
			bool readBoolFromConfigFile(const char* scope, const char* localName, bool defaultVal);

		public:

		//Functions
			ZoarialIoTNode();	
			~ZoarialIoTNode();

			int setConfigFile(const std::string& file);
			int initServerConfiguration();
			void useDefaultConfigOnInvalidConfig(bool use);

	}; //ZoarialIoTNode

	class ZoarialExcept;
	class ZoarialConfigExcept;

} //ZoarialIoT
#endif //ZOARIALIOTNODE_HPP
