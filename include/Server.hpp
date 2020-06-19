
#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <memory>
#include <atomic>

//	Sockets
#include <cstdint>
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses
#include <sys/epoll.h>
 
namespace ZoarialIoT {
	class Server {

	private:
	//Constants
		const std::string 	HOSTNAME;
		const int 			IP_ADDR;
		const bool 			NODE_TYPE;
		const bool			IS_VOLATILE;
		const int 			PORT;
		const std::string 	INTERFACE;
		
		//  Sockets
		static const int MAX_EVENTS = 10;
		static const int MAX_BUF_SIZE = 1024;

	//Variables
		//In milliseconds
		int _messageTimeout;
		//In Seconds
		int _pingTimeout;

	//Members
		//	For sockets
        struct epoll_event ev, events[MAX_EVENTS];
        
		int listen_sock, conn_sock;
		//	Number of file descriptors
		int nfds;
		int epollfd;
		
		int status, addrlen;
		//	buffer for data         buffer for ip addresses
		char sockBuf[MAX_BUF_SIZE], paddr[INET_ADDRSTRLEN];
		struct sockaddr_in localAddr, clientAddr;
		
		int flags, bytesRead;
		
		std::atomic<bool> shutdownFlag = false;

	//Functions
		bool UDPpacketHandler(int fd);
		bool TCPpacketHandler();
		
	//Sockets
		bool setNonblocking(int fd);

	public:
		Server(std::string& hostname, int ipAddr, bool nodeType, bool isVolatile, int port, std::string interface, int messageTimeout, int pingTimeout);
		~Server();
		
		void start();

	}; //Server
} //ZoairalIoT

#endif //SERVER_HPP
