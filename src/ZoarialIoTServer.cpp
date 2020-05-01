#include "ZoarialIoTNode.hpp"
#include "Exception.hpp"
#include "Server.hpp"

#include <libconfig.h++>

#include <iostream>
#include <locale.h>
#include <clocale>
#include <string>
#include <memory>

using namespace ZoarialIoT;

//Constructor
ZoarialIoTNode::ZoarialIoTNode() :
	_configFileName(NORMAL_CONFIG_FILE) {
	std::setlocale(LC_ALL, "");
	std::cout << "Constructing Node" << std::endl;
}

ZoarialIoTNode::~ZoarialIoTNode() {
	std::cout << "Deconstructing Node...";

	std::cout << "Success" << std::endl;
}

int ZoarialIoTNode::initServerConfiguration() noexcept {
	int status = initConfiguration();
	if(status != 0) {
		return status;
	}

	status = initServer();
	if(status != 0) {
		return status;
	}
	return 0;
}

int ZoarialIoTNode::initConfiguration() noexcept {

	std::cout << "Attempting To Set Configuration File...";
	int status = setConfigFile(_configFileName);
	if(status == 0) {
		std::cout << "Success" << std::endl;
	} else {
		std::cerr << "Failed" << std::endl;
		return status;
	}

	bool configFileFailed = false;
	std::cout << "Attempting To Open Config File...";
	status = openConfigFile();
	
	//	If the file failed to open, use the default config file, or fail.
	if(status != 0) {
		configFileFailed = true;
		if(!_useDefaultConfigOnInvalidConfig) {
			std::cerr << "Failed\n";
			return status;
		} else {
			std::cout << "Failed but continuing" << std::endl;
		}
	} else {
		std::cout << "Success" << std::endl;
	}


	std::cout << "Attempting To Set Configuration Fallback...";

	status = openDefaultConfigFile();
	if(!configFileFailed) {
		status -= 10;
	}
	if(status != 6110 && status != 6120) {
		std::cerr << "Failed\n";
		return status;
	}

	std::cout << "Success" << std::endl;
	std::cout << "Attempting To Read Config File...";

	status = readConfigFile();
	if(status != 0) {
		std::cerr << "Failed\n";
		return status;
	}
	std::cout << "Success" << std::endl;

	status = verifyServerConfigOptions();
	std::cout << "Attempting To Verify Server Options...";
	if(status != 0 ) {
		std::cerr << "Failed\n";
		return status;
	}
	std::cout << "Success" << std::endl;
	return 0;	
}

int ZoarialIoTNode::initServer() noexcept {
	_server = std::make_unique<Server>(_hostname, _ipAddr, _nodeType, _isVolatile, _port, "eth0", _messageTimeout, _pingTimeout);
	return 0;
}

void ZoarialIoTNode::start() noexcept {
	std::cout << "Starting node...\n";
}
