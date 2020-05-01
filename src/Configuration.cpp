#include "ZoarialIoTNode.hpp"
#include "Exception.hpp"
#include <libconfig.h++>

#include <fstream>
#include <unistd.h>
#include <cstdio>
#include <ctime>
#include <sstream>

using namespace ZoarialIoT;

bool ZoarialIoTNode::fileExists(const std::string& fileName) noexcept {

	std::ifstream f(fileName.c_str());
	return f.good();

}

void ZoarialIoTNode::openConfigFile(const std::string& file = "") {

	if(file != "" && _configFileName == "") {
		if(fileExists(file)) {
			_configFileName = file;
		} else {
			throw new ZoarialExcept("Unable to open config file: " + file);
		}
	} else if(file == "" && _configFileName == "") {
		//	TODO: Log this
		throw new ZoarialExcept("Tried opening a config file, but no file was given");
	}


	try {
		_cfg.readFile(_configFileName);
		return 0;
	} catch(const libconfig::ParseException &e) {

		//	There was a parse error
		//	Get the time and date and add it to the file name
		time_t now = time(0);
		std::tm * ltm= localtime(&now);
		std::stringstream newFileName;
		newFileName << "/etc/ZoarialIoT/";
		int nameStart = _configFileName.rfind("/") + 1;
		int nameEnd = _configFileName.rfind(".");

		//	Construct the file name
		newFileName << _configFileName.substr(nameStart, nameEnd-nameStart);
		newFileName << "-fail(";
		newFileName << 1 + ltm->tm_mon << "-" << ltm->tm_mday << "-" << 1900 + ltm->tm_year << " ";
		newFileName << 1 + ltm->tm_hour << ":" << 1 + ltm->tm_min << ":" << 1 + ltm->tm_sec << ")";
		newFileName << ".cfg";

		//std::cout << newFileName.str() << std::endl;

		//	Rename the file
		rename(_configFileName.c_str(), newFileName.str().c_str());
		
		std::cerr << "CONFIGURATION FILE COULD NOT BE SET: " << _configFileName << std::endl;
		
		throw new ZoarialExcept("Config file could not be parsed.");
		//	TODO: Log this
	}

}

void ZoarialIoTNode::readConfigFile() noexcept {
	try {
		if(_cfg.lookup("app").c_str() != APP) {
			throw new ZoarialExcept("CONFIG FILE IS NOT FOR ZOARIALIOT - Wrong Specifier");
			//	TODO: Log this
		}
	} catch(const libconfig::SettingNotFoundException & ex) {
		throw new ZoarialExcept("CONFIG FILE IS NOT FOR ZOARIALIOT - Missing Specifier);
		std::cerr << " << std::endl;
		//	TODO: Log this
	}

	try {
		if(_cfg.lookup("version").c_str() != CONFIG_VERSION) {
			throw new ZoarialExcept("CONFIG FILE IS NOT CORRECT VERSION");
			//	TODO: Log this
		}
	} catch(const libconfig::SettingNotFoundException & ex) {
		throw new ZoarialExcept("CONFIG FILE DOES NOT HAVE VERSION NUMBER");
		//	TODO: Log this
	} 
	
	int i = 0;
	if( _cfg.lookupValue(DEVICE + "hostname", _hostname) && i++, true &&
		_cfg.lookupValue(DEVICE + "node_type", _nodeType) && i++, true &&
		_cfg.lookupValue(DEVICE + "is_volatile", _isVolatile) && i++, true &&
		_cfg.lookupValue(DEVICE + "message_timeout", _messageTimeout) && i++, true &&
		_cfg.lookupValue(DEVICE + "ping_timeout", _pingTimeout) && i++, true &&
		_cfg.lookupValue(DEVICE + "port", _port) && i++, true &&
		_cfg.lookupValue(LOGGING + "log_file_name", _logFileName) && i++, true &&
		_cfg.lookupValue(LOGGING + "logging_level", _loggingLevel) )
	{ 
		return
	} else {
		//	TODO: Log this
		throw new ZoarialExcept("Failed to read config file on count: " + std::to_string(i));
	}
}

void ZoarialIoTNode::verifyServerConfigOptions() noexcept {

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

}

void ZoarialIoTNode::generateDefaultConfigFile(std::string file) noexcept {
	
}
