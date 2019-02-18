
#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include "ZoarialIoTServer/ZoarialIoTServer.hpp"
#include <iostream>
#include <config4cpp/Configuration.h>
#include <clocale>
#include <string>

class ZoarialIoT::Configuration {

	pirvate:
		config4cpp::Configuration * cfg; 
		bool fileExists(std::string& fileName);

	public: 
		Configuration();
		~Configuration();

}

#endif //CONFIGURATION_HPP
