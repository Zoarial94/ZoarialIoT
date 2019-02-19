#include <iostream>
#include <sstream>
#include "ZoarialIoTServer/ZoarialIoTServer.hpp"

int main(int argc, char const *argv[]) 
{ 

	bool daemonize = false;

	if(daemonize) {
		//daemonize
	}


	std::cout << "Creating Server From main()" << std::endl;
	ZoarialIoT::ZoarialIoTServer server();
	std::cout << "Server Created" << std::endl;



	//Turn argument into int
	/*if (argc < 2) {
		std::cerr << "ERROR, no port provided\n";
		return 1;
	} else {
		std::istringstream ss(argv[1]);
		if (!(ss >> port)) {
			std::cerr << "Invalid number: " << argv[1] << '\n';
		} else if (!ss.eof()) {
			std::cerr << "Trailing characters after number: " << argv[1] << '\n';
		}
		std::cout << port << std::endl;
	}*/

	return 0; 
} 

