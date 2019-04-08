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

bool ZoarialIoTNode::initServerConfiguration() {

	std::cout << "Attempting To Set Config File To: " << _configFileName << std::endl;
	if(setConfigFile(_configFileName)) {
		std::cout << "Attempting To Read Config File..." << std::endl;
		if(openConfigFile()) {
			std::cout << "Configration File Successfully Opened" << std::endl;
		} else {
			if(fileExists(DEFAULT_CONFIG_FILE)) {

				std::cerr << "USING DEFAULT CONFIG FILE..." << std::endl;

				if(openConfigFile(DEFAULT_CONFIG_FILE)) {
					//return true;
				}

			} else {

				std::cerr << "NO CORRECT CONFIGURATION FILES" << std::endl;
				return false;
			}
		}
	} else {
		std::cerr << "CONFIGURATION FILE COULD NOT BE SET: " << _configFileName << std::endl;
		
		if(fileExists(DEFAULT_CONFIG_FILE)) {

			std::cerr << "USING DEFAULT CONFIG FILE..." << std::endl;

			if(openConfigFile(DEFAULT_CONFIG_FILE)) {
				//return true;
			}

		} else {

			std::cerr << "NO CORRECT CONFIGURATION FILES" << std::endl;
			return false;
		}
	}

	return readConfigFile();

}

ZoarialIoTNode::~ZoarialIoTNode() {

	std::cout << "Deconstructing Server" << std::endl;

}
