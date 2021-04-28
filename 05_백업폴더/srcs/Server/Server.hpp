#pragma once
#include <string>
#include <vector>
#include <list>
#include "Client.hpp"
#include "Config.hpp"

class Server
{
	// std::vector<Config>&	config_locations;		
	// std::list<Client>		clients;
	uint32_t ip;
	uint16_t port;
public:
	Server(uint32_t ip, uint16_t port);
};