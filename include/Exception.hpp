#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

class ZoarialIoT::ZoarialExcept : virtual public std::exception {

	int _errorCode;          
	std::string _msg; 

	public:

	explicit ZoarialExcept(const std::string& msg, int errNum);

	explicit ZoarialExcept();

	virtual ~ZoarialExcept();

	virtual const char* what();

}; //ZoarialExcept

class ZoarialIoT::ZoarialConfigExcept : ZoarialIoT::ZoarialExcept {

	std::string _msg; 
	std::string _scope;
	std::string _localName;
	std::string _configFileName;
	int _errorCode;

	public:
	
	explicit ZoarialConfigExcept(const std::string& msg, const std::string& file, const std::string& scope, const std::string& localName, int errorCode);

	virtual ~ZoarialConfigExcept();

	virtual const char* what();

	const char* configWhat() const;

	const char* getFile() const;

	const char* getScope() const;

	const char* getLocal() const;

	int getErrorCode() const;
};



#endif //EXCEPTION_HPP
