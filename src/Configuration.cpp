#include "Configuration.hpp"
#include <config4cpp/Configuration.h>
#include <string>
#include <fstream>

using namespace ZoarialIoT;

Configuration::Configuration() {

	cfg = config4cpp::Configuration::create();
	
}

Configuration::~Configuration() {
	
	cfg->destroy();	

}

bool fileExists(std::string& fileName) {

	std::ifstream f(fileName.c_str());
	return f.good();

}
