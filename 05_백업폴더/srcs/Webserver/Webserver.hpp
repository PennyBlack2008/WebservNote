#pragma once
// #include "ConfigWebserver.hpp"
// #include "Path.hpp"
#include "Server.hpp"
#include <sys/select.h>
#include <vector>

class Webserver
{
	// ConfigWebserver			config;
	fd_set					to_be_checked;
	fd_set					to_be_checked_read;
	fd_set					to_be_checked_write;
	std::vector<Server>		servers;

	public:
					Webserver(int argc, char** argv, char** envp);
	void			create_server(const std::vector<Config>& config_locations);
	void			start_server(void);				// 서버 시작

	private:
	void			parse_config(const Path& path_config);			// config 파일 해석
};