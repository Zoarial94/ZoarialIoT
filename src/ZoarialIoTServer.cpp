#include "ZoarialIoTServer/ZoarialIoTServer.hpp"
#include <iostream>


using namespace ZoarialIoT;

//Constructor
ZoarialIoTServer::ZoarialIoTServer() {

	std::cout << "Constructing Server" << std::endl;
	initConfiguration();

}

bool ZoarialIoTServer::initConfiguration() {

	std::cout << "Initializing Configuration" << std::endl;
	return false;

}

bool setConfigFile(std::string& file) {
	
	return false;

}
