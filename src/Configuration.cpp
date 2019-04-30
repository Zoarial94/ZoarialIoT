#include "ZoarialIoTNode.hpp"
#include "Exception.hpp"

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

int ZoarialIoTNode::setConfigFile(const std::string& file) {

	if(fileExists(file)) {

		_configFileName = file;
		return 0;

	} else {
		_configFileName = "";
		return 1301;
	}

}

int ZoarialIoTNode::openConfigFile() {

	try {

		_cfg->parse(_configFileName.c_str());
		return 0;

	} catch(const config4cpp::ConfigurationException & ex) {

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
		
		std::cerr << "CONFIGURATION FILE COULD NOT BE SET: " << _configFileName << std::endl;

		return 6104;
	}

}

int ZoarialIoTNode::openConfigFile(const std::string& file) {

	int stat = setConfigFile(file);

	if(stat == 0) {
		return openConfigFile();
	} else {
		return stat;
	}

}

int ZoarialIoTNode::readConfigFile() {

	/*char hostname[1024];
	  gethostname(hostname, 1024);

	  _cfg->insertString("", "version", "0.1");

	  _cfg->insertString(DEVICE.c_str(), "hostname", hostname);
	  _cfg->insertString(DEVICE.c_str(), "node_type", "1");
	  _cfg->insertString(DEVICE.c_str(), "is_volatile", "false");
	  _cfg->insertString(DEVICE.c_str(), "message_timeout", "500");
	  _cfg->insertString(DEVICE.c_str(), "ping_timeout", "90");

	  _cfg->insertString(LOGGING.c_str(), "log_file_name", "/etc/ZoarialIoT/logging.log");
	  _cfg->insertString(LOGGING.c_str(), "logging_level", "3");

	  std::cout << "Configurations added, attempting to write to file..." << std::endl;

	  std::ofstream configFile;
	  configFile.open(_configFileName, std::fstream::out | std::fstream::trunc);
	  config4cpp::StringBuffer buf;

	  _cfg->dump(buf, false);

	  configFile << buf.c_str();

	  std::cout << "File successfully written too." << std::endl;

	  configFile.close();*/

	try {
		if(_cfg->lookupString("", "app") != std::string(APP)) {
			std::cerr << "CONFIG FILE IS NOT FOR ZOARIALIOT - Missing Specifier" << std::endl;
			return 6104;
		}
	} catch(const config4cpp::ConfigurationException & ex) {
		std::cerr << "CONFIG FILE IS NOT FOR ZOARIALIOT - Missing Specifier" << std::endl;
		return 6104;
	}

	try {
		if(_cfg->lookupString("", "version") != CONFIG_VERSION) {
			std::cerr << "CONFIG FILE IS NOT CORRECT VERSION" << std::endl;
			return 6103;
		}
	} catch(const config4cpp::ConfigurationException & ex) {
		std::cerr << "CONFIG FILE DOES NOT HAVE VERSION NUMBER: " << ex.c_str() << "\n";
		return 6104;
	} 

		_hostname = readStringFromConfigFile(DEVICE, "hostname");
		_nodeType = readIntFromConfigFile(DEVICE, "node_type");
		_isVolatile = readBoolFromConfigFile(DEVICE, "is_volatile");
		_messageTimeout = readIntFromConfigFile(DEVICE, "message_timeout");
		_pingTimeout = readIntFromConfigFile(DEVICE, "ping_timeout");
		_logFileName = readStringFromConfigFile(LOGGING, "log_file_name");
		_loggingLevel = readIntFromConfigFile(LOGGING, "logging_level");
		_port = readIntFromConfigFile(DEVICE, "port");

	return 0;
}

int ZoarialIoTNode::verifyServerConfigOptions() {

	if(_hostname == "") {

		char hostname[1024];
		gethostname(hostname, 1024);
		_hostname = hostname;
	}

	if(_nodeType != BASIC_NODE && _nodeType != RECV_NODE) {
		std::cerr << "NODE TYPE IS INVALID: " << _nodeType << std::endl;
		return 1112;
	}

	if(_messageTimeout < -1) {
		_messageTimeout = -1;
	}

	if(_pingTimeout < -1) {
		_pingTimeout = -1;
	}

	return 0;
}

void ZoarialIoTNode::useDefaultConfigOnInvalidConfig(bool use) {
	_useDefaultConfigOnInvalidConfig = use;
}

int ZoarialIoTNode::openDefaultConfigFile() {

	if(fileExists(DEFAULT_CONFIG_FILE)) {
		try {

			_defaultCfg->parse(_configFileName.c_str());
			_cfg->setFallbackConfiguration(_defaultCfg);
			return 6120;

		} catch(const config4cpp::ConfigurationException & ex) {

			std::string configFileName = _defaultCfg->fileName();
			time_t now = time(0);
			std::tm * ltm= localtime(&now);
			std::stringstream newFileName;
			newFileName << "/etc/ZoarialIoT/";
			int nameStart = configFileName.rfind("/") + 1;
			int nameEnd = configFileName.rfind(".");

			newFileName << configFileName.substr(nameStart, nameEnd-nameStart);
			newFileName << "-fail(";
			newFileName << 1 + ltm->tm_mon << "-" << ltm->tm_mday << "-" << 1900 + ltm->tm_year << " ";
			newFileName << 1 + ltm->tm_hour << ":" << 1 + ltm->tm_min << ":" << 1 + ltm->tm_sec << ")";
			newFileName << ".cfg";

			std::cout << newFileName.str() << std::endl;

			rename(configFileName.c_str(), newFileName.str().c_str());
			
			std::cerr << "DEFAULT CONFIG FILE IS INVALID";
			return 6124;
		}
	} else {
		std::cerr << "DEFAULT FILE DOES NOT EXISTS" << std::endl;
		return 6121;
	}
}

const char* ZoarialIoTNode::readStringFromConfigFile(const char* scope, const char* localName) {
	try {
		return _cfg->lookupString(scope, localName);
	} catch(const config4cpp::ConfigurationException & ex) {
		throw ZoarialConfigExcept(ex.c_str(), _cfg->fileName(), scope, localName, -1);
	}
}

int ZoarialIoTNode::readIntFromConfigFile(const char* scope, const char* localName) {
	try {
		return _cfg->lookupInt(scope, localName);
	} catch(const config4cpp::ConfigurationException & ex) {
		throw ZoarialConfigExcept(ex.c_str(), _cfg->fileName(), scope, localName, -1);
	}
}

bool ZoarialIoTNode::readBoolFromConfigFile(const char* scope, const char* localName) {
	try {
		return _cfg->lookupBoolean(scope, localName);
	} catch(const config4cpp::ConfigurationException & ex) {
		throw ZoarialConfigExcept(ex.c_str(), _cfg->fileName(), scope, localName, -1);
	}
}
