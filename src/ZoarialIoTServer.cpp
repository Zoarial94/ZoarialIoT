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

void ZoarialIoTNode::initServerConfiguration() noexcept {
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

void ZoarialIoTNode::initConfiguration()  {

	std::cout << "Attempting To Open Config File...";
	status = openConfigFile(_configFileName);
	std::cout << "Success" << std::endl;

	std::cout << "Attempting To Read Config File...";
	status = readConfigFile();
	std::cout << "Success" << std::endl;

	std::cout << "Attempting To Verify Server Options...";
	status = verifyServerConfigOptions();
	std::cout << "Success" << std::endl;
}

void ZoarialIoTNode::initServer() noexcept {
	_server = std::make_unique<Server>(_hostname, _ipAddr, _nodeType, _isVolatile, _port, "eth0", _messageTimeout, _pingTimeout);
}

void ZoarialIoTNode::start() noexcept {
	std::cout << "Starting node...\n";
}
