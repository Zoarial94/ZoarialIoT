#include "ZoarialIoTNode.hpp"

#include <fstream>
#include <unistd.h>
#include <cstdio>
#include <ctime>
#include <sstream>

using namespace ZoarialIoT;

bool ZoarialIoTNode::fileExists(const std::string& fileName) {

	std::ifstream f(fileName.c_str());
	return f.good();

}

bool ZoarialIoTNode::setConfigFile(const std::string& file) {

	if(fileExists(file)) {

		_configFileName = file;
		return true;
	
	} else {
		return false;
	}

}

bool ZoarialIoTNode::openConfigFile() {

		try {
			_cfg->parse(_configFileName.c_str());
			
			try {

				
				if(fileExists(DEFAULT_CONFIG_FILE)) {
					
					config4cpp::Configuration * fallback = config4cpp::Configuration::create();
					fallback->parse(DEFAULT_CONFIG_FILE.c_str());
					_cfg->setFallbackConfiguration(fallback);	

				} else {
		
					std::cout << "WARNING: NO FALLBACK FOR CONFIGURATION" << std::endl; 

				}

			} catch(const config4cpp::ConfigurationException & ex) {

				std::cerr << "ERROR MAKING FALLBACK CONFIG: " << ex.c_str() << std::endl;

			}

			return true;
		} catch(const config4cpp::ConfigurationException & ex) {

			std::cerr << "CONFIGURATION FILE COULD NOT BE PARSED: " << ex.c_str() << std::endl;

			time_t now = time(0);
			std::tm * ltm= localtime(&now);
			std::stringstream newFileName;
			newFileName << "/etc/ZoarialIoT/";
			int nameStart = _configFileName.rfind("/") + 1;
			int nameEnd = _configFileName.rfind(".");
			
			newFileName << _configFileName.substr(nameStart, nameEnd-nameStart);
			newFileName << "-fail(";
			newFileName << 1 + ltm->tm_mon << "-" << ltm->tm_mday << "-" << 1900 + ltm->tm_year << " ";
			newFileName << 1 + ltm->tm_hour << ":" << 1 + ltm->tm_min << ":" << 1 + ltm->tm_sec << ")";
			newFileName << ".cfg";

			std::cout << newFileName.str() << std::endl;

			rename(_configFileName.c_str(), newFileName.str().c_str());

			/*if(fileExists(DEFAULT_CONFIG_FILE)) {
				
				std::cerr << "USING DEFAULT CONFIG FILE..." << std::endl;
			
				if(openConfigFile(DEFAULT_CONFIG_FILE)) {
					return true;
				}

			} else {

				std::cerr << "NO CONFIGURATION FILES" << std::endl;
				
			}*/
			return false;
		}

}

bool ZoarialIoTNode::openConfigFile(const std::string& file) {

	if(setConfigFile(file)) {
		return openConfigFile();
	} else {
		return false;
	}

}

bool ZoarialIoTNode::readConfigFile() {
	
	try {

		/*char hostname[1024];
		gethostname(hostname, 1024);

		_cfg->insertString("", "version", "0.1");

		_cfg->insertString(DEVICE.c_str(), "hostname", hostname);
		_cfg->insertString(DEVICE.c_str(), "node_type", "1");
		_cfg->insertString(DEVICE.c_str(), "is_volatile", "false");
		_cfg->insertString(DEVICE.c_str(), "message_timeout", "500");
		_cfg->insertString(DEVICE.c_str(), "ping_timeout", "90");

		_cfg->insertString(LOGGING.c_str(), "log_file_name", "/etc/ZoarialIoT/logging.log");
		_cfg->insertString(LOGGING.c_str(), "loggging_level", "3");
		
		std::cout << "Configurations added, attempting to write to file..." << std::endl;

		std::ofstream configFile;
		configFile.open(_configFileName, std::fstream::out | std::fstream::trunc);
		config4cpp::StringBuffer buf;

		_cfg->dump(buf, false);

		configFile << buf.c_str();
		
		std::cout << "File successfully written too." << std::endl;

		configFile.close();*/

		if(_cfg->lookupString("", "version") != CONFIG_VERSION) {
			std::cerr << "CONFIG FILE IS NOT CORRECT VERSION" << std::endl;
			return false;
		}


		_hostname = _cfg->lookupString(DEVICE, "hostname", "");
		_nodeType = _cfg->lookupInt(DEVICE, "node_type", -1);
		_isVolatile = _cfg->lookupBoolean(DEVICE, "is_volatile", false);
		_messageTimeout = _cfg->lookupInt(DEVICE, "message_timeout", -1);
		_pingTimeout = _cfg->lookupInt(DEVICE, "ping_timeout", -1);
		_logFileName = _cfg->lookupString(DEVICE, "log_file_name", "/etc/ZoarialIoT/log.log");
		_loggingLevel = _cfg->lookupInt(DEVICE, "logging_level", 3);

		return true;

	} catch(const config4cpp::ConfigurationException & ex) {
		std::cerr << "CONFIG DATA COULD NOT BE READ PROPERLY: " << ex.c_str() << std::endl;
		return false;
	}
}

bool ZoarialIoTNode::verifyServerConfigOptions() {

	if(_hostname == "") {

		char hostname[1024];
		gethostname(hostname, 1024);
		_hostname = hostname;
	}

	if(_nodeType != BASIC_NODE || _nodeType != RECV_NODE) {
		std::cerr << "NODE TYPE IS INVALID: " << _nodeType std::endl;
		return false;
	}

	if(_messageTimeout < -1) {
		_messageTimeout = -1;
	}

	if(_pingTimeout < -1) {
		_pingTimeout = -1;
	}

	return true;
}
