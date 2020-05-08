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

//	Load config and initialize the server
void ZoarialIoTNode::initServerConfiguration() noexcept {
	initConfiguration();
	initServer();
}

//	Open the file and read the contents
//	Will verify proper arguments in initServer()
void ZoarialIoTNode::initConfiguration()  {

	std::cout << "Attempting To Open Config File...";
	openConfigFile(_configFileName);
	std::cout << "Success" << std::endl;

	std::cout << "Attempting To Read Config File...";
	readConfigFile();
	std::cout << "Success" << std::endl;
}

//	Verify the arguments and then start the server
void ZoarialIoTNode::initServer() noexcept {

	std::cout << "Attempting To Verify Server Options...";
	verifyServerConfigOptions();
	std::cout << "Success" << std::endl;

	_server = std::make_unique<Server>(_hostname, _ipAddr, _nodeType, _isVolatile, _port, "eth0", _messageTimeout, _pingTimeout);
}

void ZoarialIoTNode::start() noexcept {
	std::cout << "Starting node...\n";
	std::cin.get();
}
