#include "ZoarialIoTNode.hpp"

#include <config4cpp/Configuration.h>

#include <iostream>
#include <locale.h>
#include <clocale>
#include <string>

using namespace ZoarialIoT;

//Constructor
ZoarialIoTNode::ZoarialIoTNode() :
	_configFileName("/etc/ZoarialIoT/config.cfg")
{

	std::setlocale(LC_ALL, "");
	std::cout << "Constructing Server" << std::endl;

	_cfg = config4cpp::Configuration::create();
}

int ZoarialIoTNode::initServerConfiguration() {

	int status = setConfigFile(_configFileName);
	std::cout << "Attempting To Set Configuration File...";
	if(status == 0) {
		std::cout << "Success" << std::endl;
	} else {
		std::cerr << "Failed" << std::endl;
		return status;
	}

	std::cout << "Attempting To Read Config File...";
	try {
	
		openConfigFile();
		std::cout << "Success" << std::endl;
		status = openDefaultConfigFile() - 10;
	
	} catch(const config4cpp::ConfigurationException & ex) {

		std::cerr << "CONFIGURATION FILE COULD NOT BE SET: " << _configFileName << std::endl;
		
		if(!_useDefaultConfigOnInvalidConfig) {
			return 6104;
		} 

		status = openDefaultConfigFile();
		if(status == 6124) {
			return status;
		}
	}
	
	status = readConfigFile();

	return -1;

}

ZoarialIoTNode::~ZoarialIoTNode() {

	std::cout << "Deconstructing Server" << std::endl;

}
