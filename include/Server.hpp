
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
		//const bool 			CAN_BE_HEAD_NODE;
		
		//  Sockets
		static const int MAX_UDP_EPOLL_EVENTS = 2;
		static const int MAX_BUF_SIZE = 1024;

	//Variables
		//In milliseconds
		int _messageTimeout;
		//In Seconds
		int _pingTimeout;
		//
		//bool _isHeadNode;
		
	//Structs and others
		enum NetworkingType {
			BLANK, UDP, TCP
		};

	 	//Mostly just used to prevent allocs and frees while calling functions to handle sockets
		struct SocketHelper {
			int fd = -1;                //  File descriptor used
			int addrlen = -1;
			struct sockaddr_in clientAddr;  //  Used for UDP connection
			enum NetworkingType type = BLANK;       //  UDP or TCP
			int bytesRead = -1;              //  Bytes used in the buffer
			char sockBuf[MAX_BUF_SIZE];   //  Buffer holding the TCP/UDP packet
			char paddr[INET_ADDRSTRLEN];	// Buffer to hold string version of ip addresses
		};
		
	//Members
		//	For sockets
		std::atomic<bool> _shutdownFlag = false;
		//	Make file descriptors class member to make sure they are closed during deconstruction
		int epollfd = -1, UDP_listen_sock = -1;

	//Functions
		bool UDPPacketHandler(SocketHelper helper);
		bool TCPPacketHandler(SocketHelper helper);
		
		void UDPMainThreadFunc();
		
	//Sockets
		bool setNonblocking(int fd);
			

	public:
		Server(std::string& hostname, int ipAddr, bool nodeType, bool isVolatile, int port, std::string interface, int messageTimeout, int pingTimeout);
		~Server();
		
		void start();

	}; //Server
} //ZoairalIoT

#endif //SERVER_HPP
