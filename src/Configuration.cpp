#include "Configuration.hpp"
#include <config4cpp/Configuration.h>
#include <string>
#include <fstream>

using namespace ZoarialIoT;

Configuration::Configuration() {

	_cfg = config4cpp::Configuration::create();
	
}

Configuration::~Configuration() {
	
	_cfg->destroy();	

}

bool Configuration::fileExists(std::string& fileName) {

	std::ifstream f(fileName.c_str());
	return f.good();

}

bool Configuration::setFile(std::string file) {

	if(fileExists(file)) {

		_fileName = file;
		return true;
	
		/*try {
			cfg->parse(file.c_str());
			return true;
		} catch(const config4cpp::ConfigurationException & ex) {
			std::cerr << "CONFIGURATION FILE COULD NOT BE PARSED: " << ex.c_str() << std::endl;
			return false;
		}*/

	} else {
		return false;
	}

}
