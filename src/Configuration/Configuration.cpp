#include "Configuration/Configuration.hpp"
#include <iostream>
#include <string>
#include <locale.h>
#include <config4cpp/Configuration.h>
#include <clocale>
#include <fstream>

using namespace ZoairalIoT::Configuration;

Configuration() {

	cfg = config4cpp::Configuration::create();
	
}

bool fileExists(std::string& fileName) {

	ifstream f(fileName.c_str());
	return f.good();

}
