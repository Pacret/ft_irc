/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:47:26 by pbonilla          #+#    #+#             */
/*   Updated: 2022/07/17 15:33:59 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

		Server::Server()
{

}

		Server::Server(const std::string &port, const std::string &password, std::string configFile)
{
	std::string server_name = "ft_irc.42.com";
 
	context = new Context(server_name, port, password);
	if (!configFile.empty())
		_load_server_config(configFile);
}

		Server::~Server()
{
	clean();
}

void	Server::addClient()
{
	int fd_client;
	struct sockaddr_in client_address;
	socklen_t len = sizeof(client_address);

	if ((fd_client = accept(fd_socket, (struct sockaddr *)&client_address, &len)) == -1)
		close_server("Error: accept");
	if (fcntl(fd_client, F_SETFL, O_NONBLOCK) == -1) // Non blocking socket
		close_server("Error: fcntl client");
	struct pollfd pfd;
	
	pfd.fd = fd_client;
	pfd.events = POLLIN;
	pfd.revents = 0;
	pollfds.push_back(pfd);

	context->addClient(fd_client, client_address);

	log_file << "Client " << inet_ntoa(client_address.sin_addr) << ":" << ntohs(client_address.sin_port) << " fd: " << fd_client << std::endl; 
}

void	Server::init()
{
	log_file.open("lol");
	if (!log_file)
		close_server("Error: Log file couldn't be created");
	if ((fd_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		close_server("Error: Open socket");
	if (fcntl(fd_socket, F_SETFL, O_NONBLOCK) == -1) // Non blocking socket
		close_server("Error: fcntl");

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(std::atoi(context->port.c_str()));
	server_address.sin_addr.s_addr = INADDR_ANY;

	if ((bind(fd_socket, (struct sockaddr *)&server_address, sizeof(server_address))) == -1)
		close_server("Error: Port already used please choose another one");
	if (listen(fd_socket, 128) == -1)
		close_server("Error: listen");
	

	struct pollfd pfd;
	pfd.fd = fd_socket;
	pfd.events = POLLIN;
	pfd.revents = 0;

	pollfds.push_back(pfd);
}

void	Server::process()
{
	while (1)
	{
		if (poll(&pollfds[0], pollfds.size(), -1) == -1)
			close_server("Error: poll");
		if (pollfds[0].revents == POLLIN)
			addClient();
		else
		{
			for (std::vector<struct pollfd>::iterator it = pollfds.begin(); it != pollfds.end(); ++it)
			{
				if ((*it).revents == POLLIN)
				{
					get_message(context->getClient((*it).fd));
				}
			}
		}

		for (std::vector<int>::iterator it = _clients_to_kill.begin(); it != _clients_to_kill.end(); ++it)
		{

			kill_connection(*it);
		}
		std::vector<Server::clientFd>().swap(_clients_to_kill);
	}
}

void	Server::get_message(Client *client)
{
	char	buff[BUFFER_SIZE + 1];
	ssize_t	size;
	size_t	rn;
	int		clientFd = client->fd;

	std::memset(buff, '\0', BUFFER_SIZE);
	if ((size = recv(client->fd, &buff, BUFFER_SIZE, 0)) == -1)
		return;
	if (!size)
	{
		context->deleteClient(client);
		_clients_to_kill.push_back(clientFd);
		return;
	}
	client->buffer += buff;

	while (client && client->buffer.size())
	{
		parse_t *p;
		rn = client->buffer.find("\r\n");
		if (rn == std::string::npos)
		{
			std::cout << "Partial message received..." << std::endl;
			break;
		}
		std::string command = client->buffer.substr(0, rn);
		p = fill_parse_t(command);
		client->buffer.erase(0, rn + 2);
		if (p->original_msg.size())
		{
			try
			{
				Action result = context->parse_command(client, p);
				if (result == KILL_CONNECTION)
				{
					_clients_to_kill.push_back(clientFd);
					delete p;
					return;
				}
				else if (result == CLOSE_SERVER)
				{
					delete p;
					std::cout << "Closing Server" << std::endl;
					close_server("");
				}
			}
			catch (const std::runtime_error& e)
			{
				delete p;
				close_server(e.what());
			}
		}
		delete p;
	}
}

void	Server::kill_connection(int clientFd)
{
	std::vector<struct pollfd>::iterator it = pollfds.begin();
	std::vector<struct pollfd>::iterator ite = pollfds.end();

	for (; it != ite; it++)
	{
		if ((*it).fd == clientFd)
		{
			pollfds.erase(it);
			close(clientFd);
			return ;
		}
	}
}

bool	Server::_load_server_config(std::string configFileNamepath)
{
	std::ifstream				ifs(configFileNamepath.c_str());
	std::stringstream			buffer;
	std::vector<std::string>	tmp;

	//Get config file's content into a string and split into lines 
  	if (!ifs.good())
	{
		std::cerr << "Error: open config file " << configFileNamepath << " failed" << std::endl;
		return (false);
	}
	buffer << ifs.rdbuf();
	tmp = string_split(buffer.str(), "\n");

	//Get lines that are not comments
	for (unsigned long int i = 0; i < tmp.size(); i++)
	{
		if (!(tmp[i].empty()) && tmp[i][0] != '#')
			context->config.push_back(tmp[i]);
	}

	//Parse O-lines for server operator, only the last line is accepted
	std::vector<std::string>	line_config;
	for (unsigned long int i = 0; i < context->config.size(); i++)
	{
		line_config = string_split(context->config[i], ":");
		if (context->config[i][1] == ':')
		{
			if (context->config[i][0] == 'O' && line_config.size() > 3)
			{
				context->opConfig.host = line_config[1];
				context->opConfig.password = line_config[2];
				context->opConfig.username = line_config[3];
			}
			else if (context->config[i][0] == 'H' && line_config.size() == 2)
				context->server_name = line_config[1];
			else if (context->config[i][0] == 'S' && line_config.size() == 2)
				context->version_name = line_config[1];
			else if (context->config[i][0] == 'M' && line_config.size() == 2)
				context->motd.push_back(line_config[1]);
		}
		else
		{
			std::vector<std::string> line = string_split(context->config[i], "=");
			if (line.size() == 2)
				context->conf_file[line[0]] = line[1];
		}
	}
	std::map<std::string, std::string>::iterator it;
	std::string inline_conf;

	for (it = context->conf_file.begin(); it != context->conf_file.end(); it++)
		inline_conf += " " + it->first + "=" + it->second;
	context->conf_file_inline = inline_conf;
	ifs.close();
	return (true);
}

void	Server::clean()
{
	//Close listen fd
	close(fd_socket);

	//Close all clients connection 
	for (std::size_t i = 0; i < pollfds.size(); i++)
		close(pollfds[i].fd);

	//LOL Nuking leaks since cpp98
	std::vector<pollfd>().swap(pollfds);
	
	delete context;
	log_file.close();
}

void	Server::close_server(const std::string &msg_error)
{
	if (!(msg_error.empty()))
		std::cerr << msg_error << std::endl;
	clean();
	exit(0);
}