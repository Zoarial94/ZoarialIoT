#include <iostream>
#include <sstream>
#include "ZoarialIoTNode.hpp"

int main(int argc, char const *argv[]) 
{ 

	bool daemonize = false;

	if(daemonize) {
		//daemonize
	}


	std::cout << "Creating Node From main()" << std::endl;
	ZoarialIoT::ZoarialIoTNode server;
	std::cout << "Node Created... Initializing Server Configuration" << std::endl;
	
	int status = server.initServerConfiguration();

	if(status == 0) {
		std::cout << "Node Initialized" << std::endl;
	} else {
		std::cerr << "Node Incorrectly Initialized: " << status << std::endl;
	}

	std::cout << "Starting Server" << std::endl;

	server.start();


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

