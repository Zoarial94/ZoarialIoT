#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

class ZoarialIoT::ZoarialExcept : virtual public std::exception {
      
	std::string _msg; 

public:

	explicit ZoarialExcept(const std::string& msg);

	explicit ZoarialExcept();

	virtual ~ZoarialExcept();

	virtual const std::string what();

}; //ZoarialExcept

class ZoarialIoT::ZoarialConfigExcept : ZoarialIoT::ZoarialExcept {

	std::string _msg; 
	std::string _scope;
	std::string _localName;
	std::string _configFileName;

public:
	
	explicit ZoarialConfigExcept(const std::string& msg, const std::string& file, const std::string& scope, const std::string& localName);

	virtual ~ZoarialConfigExcept();

	virtual const char* what();

	const std::string configWhat() const;

	const std::string getFile() const;

	const std::string getScope() const;

	const std::string getLocal() const;

	int getErrorCode() const;
};



#endif //EXCEPTION_HPP
