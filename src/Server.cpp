#include "Server.hpp"

#include <iostream>
#include <thread>

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

#include <cstdio>
#include <sys/epoll.h>
#include <fcntl.h>
#include <netdb.h>

using namespace ZoarialIoT;
Server::Server(std::string& hostname, int ipAddr, bool nodeType, bool isVolatile, int port, std::string interface, int messageTimeout, int pingTimeout) : 
HOSTNAME(hostname), IP_ADDR(ipAddr), NODE_TYPE(nodeType), IS_VOLATILE(isVolatile), PORT(port), INTERFACE(interface), _messageTimeout(messageTimeout), _pingTimeout(pingTimeout)
{

	std::cout << "Constructing Server" << std::endl;
	std::cout << "Using Port Number: " << PORT <<std::endl;
	
	std::cout << "Server Constructed" << std::endl;
}

Server::~Server() {
	std::cout << "Deconstructing Server...";
	
	if(UDP_listen_sock != -1) {
		std::cout << "Closing UDP_listen_sock in dctor\n";
		close(UDP_listen_sock);
	}
	
	if(epollfd != -1) {
		std::cout << "Closing epollfd in dctor\n";
		close(epollfd);
	}
	
	std::cout << "Success" << std::endl;
}


bool Server::UDPPacketHandler(SocketHelper helper) {

	if(helper.type != UDP) {
		std::cerr << "Wrong type of SocketHelper received in UDPPacketHandler\n";
	}
  	
  	helper.addrlen = sizeof(helper.clientAddr);
  	helper.bytesRead = recvfrom(helper.fd, helper.sockBuf, sizeof(helper.sockBuf), 0, (struct sockaddr*) &(helper.clientAddr), (socklen_t*)&(helper.addrlen));
  	//	Try and null terminate
  	helper.sockBuf[helper.bytesRead & (MAX_BUF_SIZE-1)] = 0;
  	
  	if(inet_ntop(AF_INET, &(helper.clientAddr.sin_addr), helper.paddr, sizeof(helper.paddr)) == nullptr) {
  		std::cerr << "Unable to translate address into a string\n";
  	}
  	
  	std::printf("From %s:\t%s", helper.paddr, helper.sockBuf);
  	
  	if(strncmp(helper.sockBuf, "shutdown", 8) == 0) {
  		std::cout << "Recieved shutdown signal...\n";
  		_shutdownFlag = true;
  	}
  	
  	return false;
    
}

bool Server::TCPPacketHandler(SocketHelper helper) {
	return false;
}

bool Server::setNonblocking(int fd) {

	int flags, status;
	//	Set fd to non-blocking
	//	First get the current flags, then add the non-blocking flag and save it.
	flags = fcntl(fd, F_GETFL, 0);
  	if (flags == -1) {
      	std::cerr << "Error getting flags from fd " << fd << "\n";
      	exit(EXIT_FAILURE);
	}

	flags |= O_NONBLOCK;
	status = fcntl(fd, F_SETFL, flags);
	if (status == -1) {
		std::cerr << "Error setting flags for fd " << fd << "\n";
		exit(EXIT_FAILURE);
	}
	return true;
}

void Server::start() {
	
	std::cout << "Starting networking threads...\n";

	std::thread UDPMainThread(&Server::UDPMainThreadFunc, this);
	UDPMainThread.join();

}

void Server::UDPMainThreadFunc() {

	std::cout << "UDP Main Thread started.\n";

    struct epoll_event ev, events[MAX_UDP_EPOLL_EVENTS];
    
    struct SocketHelper UDPHelper;

	//	Number of file descriptors
	int nfds;

	int status;
	struct sockaddr_in localAddr;
	
	
	//	Clear some structs
	memset(&localAddr, '0', sizeof(localAddr));
	
	UDPHelper.type = UDP;
	
	//	Create the socket
	UDP_listen_sock = socket(AF_INET, SOCK_DGRAM, 0);
	UDPHelper.fd = UDP_listen_sock;
	if(UDP_listen_sock == -1) {
		std::cerr << "There was an error creating the socket.\n";
		exit(EXIT_FAILURE);
	}
	
	//	Requirements for incoming connections
	localAddr.sin_family = AF_INET;					//	IPv4
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);	//	INADDR_ANY means 'from any address'
	localAddr.sin_port = htons(PORT);				//	Use port 'PORT'

	
	//	Bind the socket to the requirements in localAddr
	status = bind(UDP_listen_sock, (struct sockaddr*)&localAddr , sizeof(localAddr));
	if(status == -1) {
		std::cerr << "There was an error binding to the socket.\n";
		exit(EXIT_FAILURE);
	}
	
	//	Create the epoll.
	//	Used to trigger events when data is arriving
	epollfd = epoll_create1(0);
	if (epollfd == -1) {
		std::cerr << "There was an error creating the epoll.\n";
		exit(EXIT_FAILURE);
	}

	//	Set epoll to poll UDP_listen_sock
	ev.events = EPOLLIN;
	ev.data.fd = UDP_listen_sock;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, UDP_listen_sock, &ev) == -1) {
		std::cerr << "There was an error adding UDP_listen_sock to the epoll.\n";
		exit(EXIT_FAILURE);
	}
	
	//
	setNonblocking(UDP_listen_sock);
	
	//
	for (;;) {
	
		if(_shutdownFlag.load()) {
			std::cout << "Shutting down\n";
			break;		
		}
	
       	nfds = epoll_wait(epollfd, events, MAX_UDP_EPOLL_EVENTS, 5000);
       	
       	//	0 means timeout
       	if(nfds == 0) {
       		std::cout << "Timeout in UDP loop...\n";
       		continue;
       	} else if (nfds == -1) {
           	perror("epoll_wait");
           	exit(EXIT_FAILURE);
       	} 

       	for (int n = 0; n < nfds; ++n) {
       		//	New incoming UDP socket
           	if (events[n].data.fd == UDP_listen_sock) {
               	/*setNonblocking(fd);
               	ev.events = EPOLLIN | EPOLLET;
               	ev.data.fd = conn_sock;
               	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
                   	perror("epoll_ctl: conn_sock");
                   	exit(EXIT_FAILURE);
               	}*/
               	UDPPacketHandler(UDPHelper);
           	} else {
               	//	uh oh
               	std::cout << "Recieved an event from an unexpected socket. Exiting...\n";
               	exit(-1);
           	}
       	}
   	}
   	//	We only have to worry about one socket with UDP
   	if(UDP_listen_sock) {
   		close(UDP_listen_sock);
   		UDP_listen_sock = -1;
   	}
   	if(epollfd) {
   		close(epollfd);
   		epollfd = -1;
   	}

}


