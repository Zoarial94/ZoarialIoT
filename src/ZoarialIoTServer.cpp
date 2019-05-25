#include "ZoarialIoTNode.hpp"
#include "Exception.hpp"
#include "Server.hpp"

#include <config4cpp/Configuration.h>

#include <iostream>
#include <locale.h>
#include <clocale>
#include <string>
#include <memory>

using namespace ZoarialIoT;

//Constructor
ZoarialIoTNode::ZoarialIoTNode() :
	_configFileName("/etc/ZoarialIoT/config.cfg")
{

	std::setlocale(LC_ALL, "");
	std::cout << "Constructing Node" << std::endl;

	_cfg = config4cpp::Configuration::create();
	_defaultCfg = config4cpp::Configuration::create();
}

ZoarialIoTNode::~ZoarialIoTNode() {
	std::cout << "Deconstructing Node...";

	_cfg->destroy();
	_defaultCfg->destroy();

	std::cout << "Success" << std::endl;
}

int ZoarialIoTNode::initServerConfiguration() {
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

int ZoarialIoTNode::initConfiguration() {

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

	try {
		status = readConfigFile();
		if(status != 0) {
			std::cerr << "Failed\n";
			return status;
		}
	} catch(const ZoarialConfigExcept & ex) {
		std::cerr << "Failed\n";
		std::cerr << "ERROR READING LOCALNAME: " << ex.getLocal() << " | IN SCOPE: " << ex.getScope() << "\n";
		return ex.getErrorCode();
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

int ZoarialIoTNode::initServer() {
	int status = 0;
	_server = std::make_unique<Server>(_hostname, _ipAddr, _nodeType, _isVolatile, _port, "eth0", _messageTimeout, _pingTimeout);
	return 0;
}
