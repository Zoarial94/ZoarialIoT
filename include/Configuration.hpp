
#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <iostream>
#include <config4cpp/Configuration.h>
#include <clocale>
#include <string>

namespace ZoarialIoT {
	class Configuration {

		private:
			//Members
			config4cpp::Configuration * cfg; 
			
			//Functions
			bool fileExists(std::string& fileName);

		public: 
			//Functions
			Configuration();
			~Configuration();

	}; //Configuration
} //ZoarialIoT

#endif //CONFIGURATION_HPP
