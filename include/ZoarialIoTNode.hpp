// ZoarialIoT.hpp

#ifndef ZOARIALIOTNODE_HPP
#define ZOARIALIOTNODE_HPP

#include "Server.hpp"
#include <string>
#include <iostream>
#include <exception>
#include <libconfig.h++>
#include <cstdint>

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
		int 			_nodeType;
		bool 			_isVolatile;
		std::string 	_configFileName;
		int 			_port;

	//Can change in run time
		int 			_messageTimeout;
		int 			_pingTimeout;
		std::string 	_logFileName;
		int 			_loggingLevel;

	//Constants
		
		const static int RECV_NODE  =	0;
		const static int BASIC_NODE = 	1;
		const static int SATELLITE  =	2;
		
		const static inline std::string APP = "ZoarialIoT";
		
		const static inline std::string DEVICE = 		APP + ".device.";
		const static inline std::string LOGGING = 		APP + ".logging.";
		
		const static inline std::string CONFIG_VERSION = "0.1";
		const static inline std::string CONFIG_LOCATION = "/etc/zoarial/";
		const static inline std::string DEFAULT_CONFIG_FILE = CONFIG_LOCATION + "default.cfg";
		const static inline std::string NORMAL_CONFIG_FILE = CONFIG_LOCATION + "config.cfg";

	//Variables
	
	//Members
		libconfig::Config _cfg;
		std::unique_ptr<Server>     _server;

	/*
	 * Configuration Functions
	 *
	 * Used to handle some interations with config4cpp
	 *
	 *
	**/
	//	Open a file
		int openConfigFile(const std::string& file) noexcept;
		int openConfigFile() noexcept;

	//	Verify the server options are valid	
		int verifyServerConfigOptions() noexcept;

	//	Check to see a file exists
		bool fileExists(const std::string& file) noexcept;

	//  Read the file
		int readConfigFile() noexcept;

	//	Open the default config file
		int openDefaultConfigFile() noexcept;

	//	Read string from config
		std::string readStringFromConfigFile(std::string localName) noexcept;

	// 	Read int from config
		int readIntFromConfigFile(std::string localName) noexcept;

	//  Read bool from config
		bool readBoolFromConfigFile(std::string localName) noexcept;

	//  Generate a default file
		void generateDefaultConfigFile(std::string file = DEFAULT_CONFIG_FILE) noexcept;


	//  Initialize variables from the configuration file
		int initConfiguration() noexcept;

	//	Initialize the server
		int initServer() noexcept;

	public:

	//Functions
		ZoarialIoTNode();	
		~ZoarialIoTNode();

	//  Set the config file
		int setConfigFile(const std::string& file) noexcept;

	// 	Init the server
		int initServerConfiguration() noexcept;

	//	Use default values if the normal file is invalid
		void useDefaultConfigOnInvalidConfig(bool use) noexcept;

	//	Start the server
		void start() noexcept;

	}; //ZoarialIoTNode

	class ZoarialExcept;
	class ZoarialConfigExcept;

} //ZoarialIoT
#endif //ZOARIALIOTNODE_HPP
