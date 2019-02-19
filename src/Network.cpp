#include "Network/Network.hpp"
#include <tins/tins.h>

using namespace ZoarialIoT;

Server::Server() {

	sender = Tins::PacketSender("eth0");

}

Server::~Server() {

}
