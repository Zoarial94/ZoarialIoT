#include "ZoarialIoTServer.hpp"
#include <iostream>


using namespace ZoarialIoT;

//Constructor
ZoarialIoTServer::ZoarialIoTServer() :
_configFile("/etc/ZoarialIoT/config.cfg")
{

	std::cout << "Constructing Server" << std::endl;

}

bool ZoarialIoTServer::initServerConfiguration() {
	bool status = false;

	std::cout << "Initializing Configuration" << std::endl;
	status = setConfigFile(_configFile);
	return status;

}

bool ZoarialIoTServer::setConfigFile(std::string& file) {
	bool status = false;

	status = _config.setFile(file);
	return false;

}

ZoarialIoTServer::~ZoarialIoTServer() {

	std::cout << "Deconstructing Server" << std::endl;

}
