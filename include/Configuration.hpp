
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
			config4cpp::Configuration * _cfg; 
			std::string _fileName;

			//Functions
			bool fileExists(std::string& fileName);

		public: 
			//Functions
			Configuration();
			~Configuration();

			bool setFile(std::string file);

	}; //Configuration
} //ZoarialIoT

#endif //CONFIGURATION_HPP
