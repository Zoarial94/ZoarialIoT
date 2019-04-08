
#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <iostream>
#include <config4cpp/Configuration.h>
#include <clocale>
#include <string>

namespace ZoarialIoT {
	class Configuration {

		private:
		//Constants

		//Members
			config4cpp::Configuration * _cfg; 

		//Functions
			bool fileExists(std::string& fileName);

		public: 
		//Functions
			Configuration();
			~Configuration();

			bool setFile(std::string file);

			bool openFile();
			bool openFile(std::string file);

			std::string getFileName();

			bool setString(std::string);


	}; //Configuration
} //ZoarialIoT

#endif //CONFIGURATION_HPP
