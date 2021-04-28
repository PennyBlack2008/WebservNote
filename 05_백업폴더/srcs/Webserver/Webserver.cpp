#include "Webserver.hpp"

Webserver::Webserver(int argc, char** argv, char** envp)
{
	Server s1; s1.ip = INADDR_ANY; s1.port = 80;

	// if (argc > 2)
	// {
	// 	std::cout << "Usage: " << argv[0] << " [configfile]" << std::endl;
	// 	return ;
	// }
	// std::deque<std::string>	token(1);
	// config_parser(token, argv[1]);
	// server_create(token);
	// set_path_cgi_bin(env);
	// set_status_code();
	// set_map_method();
}

void			Webserver::start_server(void)
{

}