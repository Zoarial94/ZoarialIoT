#include "ZoarialIoTNode.hpp"
#include "Exception.hpp"
#include <sstream>

ZoarialIoT::ZoarialExcept::ZoarialExcept(const std::string& msg, int errNum): _errorCode(errNum), _msg(msg) { 
}

ZoarialIoT::ZoarialExcept::ZoarialExcept() {}

ZoarialIoT::ZoarialExcept::~ZoarialExcept() {}

const char* ZoarialIoT::ZoarialExcept::what() {
	return _msg.c_str();
}

ZoarialIoT::ZoarialConfigExcept::ZoarialConfigExcept(const std::string& msg, const std::string& file, const std::string& scope, const std::string& localName, int errorCode) : _msg(msg), _scope(scope), _localName(localName), _configFileName(file), _errorCode(errorCode) {
}

ZoarialIoT::ZoarialConfigExcept::~ZoarialConfigExcept() {}

const char* ZoarialIoT::ZoarialConfigExcept::what() {
	return _msg.c_str();
}

const char* ZoarialIoT::ZoarialConfigExcept::configWhat() const {
	std::stringstream ss;
	ss <<  "File: " << _configFileName << "\nScope: " << _scope << "\n Local: " << _localName << "\n"; 
	return ss.str().c_str();	
}

const char* ZoarialIoT::ZoarialConfigExcept::getFile() const {
	return _configFileName.c_str();
}

const char* ZoarialIoT::ZoarialConfigExcept::getScope() const {
	return _scope.c_str();
}

const char* ZoarialIoT::ZoarialConfigExcept::getLocal() const {
	return _localName.c_str();
}

