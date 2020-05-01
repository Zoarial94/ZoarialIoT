#include "ZoarialIoTNode.hpp"
#include "Exception.hpp"
#include <sstream>

ZoarialIoT::ZoarialExcept::ZoarialExcept(const std::string& msg): _msg(msg) { 
}

ZoarialIoT::ZoarialExcept::ZoarialExcept() {}

ZoarialIoT::ZoarialExcept::~ZoarialExcept() {}

const std::string ZoarialIoT::ZoarialExcept::what() {
	return _msg;
}




ZoarialIoT::ZoarialConfigExcept::ZoarialConfigExcept(const std::string& msg, const std::string& file, const std::string& scope, const std::string& localName) : _msg(msg), _scope(scope), _localName(localName), _configFileName(file) {
}

ZoarialIoT::ZoarialConfigExcept::~ZoarialConfigExcept() {}

const std::string ZoarialIoT::ZoarialConfigExcept::what() {
	return _msg.c_str();
}

const std::string ZoarialIoT::ZoarialConfigExcept::configWhat() const {
	std::stringstream ss;
	ss <<  "File: " << _configFileName << "\nScope: " << _scope << "\n Local: " << _localName << "\n"; 
	return ss.str();	
}

const std::string ZoarialIoT::ZoarialConfigExcept::getFile() const {
	return _configFileName;
}

const std::string ZoarialIoT::ZoarialConfigExcept::getScope() const {
	return _scope;
}

const std::string ZoarialIoT::ZoarialConfigExcept::getLocal() const {
	return _localName;
}
