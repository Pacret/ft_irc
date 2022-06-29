/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:47:26 by pbonilla          #+#    #+#             */
/*   Updated: 2022/06/29 20:29:11 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "../Utils/parser_utils.hpp"
#include "../Utils/defines.h"
#include "../Utils/parser_utils.hpp"
#include <string>

		Server::Server()
{
    
}

		Server::Server(const std::string &port, const std::string &password) : port(port), password(password)
{
	server_name = "paco.com";
}

		Server::~Server()
{
    std::cout << "Fermeture du serveur" << std::endl;
    for (std::map<int, Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
        delete it->second;
    close(fd_socket);
	log_file.close();
}

void    Server::addClient()
{
    int fd_client;
    struct sockaddr_in client_adress;
    socklen_t len = sizeof(client_adress);

    if ((fd_client = accept(fd_socket, (struct sockaddr *)&client_adress, &len)) == -1)
        close_server("Error: accept");
    if (fcntl(fd_client, F_SETFL, O_NONBLOCK) == -1) // Non blocking socket
        close_server("Error: fcntl client");

    struct pollfd pfd;
	
    pfd.fd = fd_client;
    pfd.events = POLLIN;
    pfd.revents = 0;
    pollfds.push_back(pfd);

    clients[fd_client] = new Client(fd_client, client_adress);

	log_file << "Client " << inet_ntoa(client_adress.sin_addr) << ":" << ntohs(client_adress.sin_port) << " fd: " << fd_client << std::endl; 
}

void    Server::init()
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
    server_address.sin_port = htons(std::atoi(port.c_str()));
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

	// TEMP PART, FILL THE MOTD
	motd.push_back("une ligne de MOTD");
	motd.push_back("une deuxieme");
	motd.push_back("et c'est tout");

	commands["JOIN"] = &Server::join_command;
	commands["MODE"] = &Server::mode_command_dummy;
	commands["KICK"] = &Server::kick_command;
	commands["PASS"] = &Server::pass_command;
	commands["NICK"] = &Server::nick_command;
	commands["USER"] = &Server::user_command;
}

void Server::mode_command_dummy(Client *c, struct parse_t* p)
{
	c->get_ip();
	p->prefix.size();
	return;
}

void    Server::send_message(int fd, const std::string &message) //Fonction juste pour montrer comment envoyer un message
{
	std::string msg(message + "\r\n");
    std::cout << "Envois :" << msg << std::endl;
    if (send(fd, msg.c_str(), msg.size(), 0) == -1)
        std::cout << "Error: envois message" << std::endl;
}

std::string	Server::get_pwd()
{
	return (password);
}

std::string format_msg(numeric_replies_e num, Client& client)
{
	return (":paco.com " + ft_irc::to_string(num) + " " + client.get_nick());
}

void    Server::join_command(Client *client, struct parse_t *command)
{
	std::string channel_name = command->args[0];

	if (channels.find(channel_name) == channels.end())
		channels[channel_name] = new Channel(client, channel_name);
	std::vector<Client *> usrs = channels[channel_name]->get_users();
	for(unsigned long int i = 0; i < usrs.size(); i++)
		send_message(usrs[i]->get_fd(), std::string(":" + client->get_nick() + "!" +  client->get_username() + "@" + server_name + " JOIN :" + channel_name));
	send_message(client->get_fd(), std::string(format_msg(RPL_TOPIC, *client) + " " + ft_irc::RPL_TOPIC(*channels[channel_name])));
	send_message(client->get_fd(), std::string(format_msg(RPL_NAMREPLY, *client) + " " + ft_irc::RPL_NAMREPLY(channels[channel_name]->get_name(), channels[channel_name]->get_users_names())));
	send_message(client->get_fd(), std::string(format_msg(RPL_ENDOFNAMES, *client) + " " + ft_irc::RPL_ENDOFNAMES(channels[channel_name]->get_name())));
}

void	Server::kick_command(Client *client, struct parse_t *command)
{
	(void)client;
	(void)command;
}


void    Server::send_motd(Client *client)
{
	if (motd.empty())
		return;
	send_message(client->get_fd(), format_msg(RPL_MOTDSTART, *client) + ft_irc::RPL_MOTDSTART(server_name));
	for(unsigned long int i = 0; i < motd.size(); i++)
		send_message(client->get_fd(), format_msg(RPL_MOTD, *client) + ft_irc::RPL_MOTD(motd[i]));
	send_message(client->get_fd(), format_msg(RPL_ENDOFMOTD, *client) + ft_irc::RPL_ENDOFMOTD());
}

void	Server::priv_msg(Client *client, const string &command)
{
	// NOT FINISHED
	//vector<string> destinators;
	//if (parsed->args.size() != 2)
		//ERROR
	client->get_fd();
	string p = command;
}

void    Server::pass_command(Client *client, struct parse_t *command)
{
	if (command->args[0] != get_pwd())
	{
		kill_connection(client);
		return;
	}
	client->set_statut(REGISTERED);
}

void    Server::nick_command(Client *client, struct parse_t *command)
{
	std::map<clientSocket, Client *>::iterator it;
	for (it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second->get_nick() == command->args[0])
			send_message(client->get_fd(), format_msg(ERR_NICKNAMEINUSE, *client) + ft_irc::ERR_NICKNAMEINUSE(command->args[0]));
		else
			client->set_nick(command->args[0]);
	}
}

void    Server::user_command(Client *client, struct parse_t *command)
{
	client->set_user(command->args[0]);
	if (client->get_nick() != "")
	{
		client->set_statut(CONNECTED);
		send_message(client->get_fd(), format_msg(RPL_WELCOME, *client) + ft_irc::RPL_WELCOME(client->get_nick(), "127.0.0.1"));
		send_message(client->get_fd(), format_msg(RPL_LUSERCLIENT, *client) + ft_irc::RPL_LUSERCLIENT("0", "0"));
		send_message(client->get_fd(), format_msg(RPL_LUSERUNKNOWN, *client) + ft_irc::RPL_LUSERUNKNOWN(" 0 "));
		send_message(client->get_fd(), format_msg(RPL_LUSERCHANNELS, *client) + ft_irc::RPL_LUSERCHANNELS(ft_irc::to_string(channels.size())));
		send_message(client->get_fd(), format_msg(RPL_LUSERME, *client) + ft_irc::RPL_LUSERME(ft_irc::to_string(clients.size())));
		send_motd(client);
	}
}

void    Server::parse_command(Client *client, struct parse_t *command)
{
	if ((client->get_statut() == NONE && command->cmd == "PASS") || 
		(client->get_statut() == REGISTERED && (command->cmd == "USER" || command->cmd == "NICK")) ||
		(client->get_statut() == CONNECTED && (commands.count(command->cmd) && command->cmd != "PASS" && command->cmd != "USER")))
	{
		(this->*commands[command->cmd])(client, command);
	}
	else
		std::cout << "	/!\\ ERROR COMMAND /!\\" << std::endl;
}

void	Server::get_message(Client *client)
{
    char    buff[BUFFER_SIZE + 1];
    ssize_t    size;
    size_t  rn;

    if ((size = recv(client->get_fd(), &buff, BUFFER_SIZE, 0)) == -1) //?? Should be a while? Need to check max size IRC REQUEST
        return;
    if (!size)
        return;
    buff[size] = 0;
    client->buffer += buff;

    while (client->buffer.size())
    {
		parse_t *p;
		rn = client->buffer.find("\r\n");
		if (rn == std::string::npos)
			throw ("Bad data: Partial Data received");
		std::string command = client->buffer.substr(0, rn);
		p = fill_parse_t(command);
        client->buffer.erase(0, rn + 2);
        if (p->original_msg.size())
        {
            std::cout << std::endl;
            parse_command(client, p);
        } 
    }
}

void    Server::process()
{
	// int test = 0;

    while (1)
    {
        if (poll(&pollfds[0], pollfds.size(), -1) == -1)
            close_server("Error: poll");
        if (pollfds[0].revents == POLLIN)
            addClient();
        else
        {
            for (std::vector<struct pollfd>::iterator it = pollfds.begin(); it != pollfds.end(); ++it)
                if ((*it).revents == POLLIN)
                    get_message(clients[(*it).fd]);

        }
        std::cout << pollfds[0].revents << std::endl;
		std::cout << "here\n" << std::endl;
    }
}

void    Server::setPort(const std::string &port)
{
    this->port = port;
}

void    Server::setPassword(const std::string &password)
{
    this->password = password;
}

void	Server::kill_connection(Client *client)
{
	std::vector<struct pollfd>::iterator it = pollfds.begin();

	while ((*it).fd != client->get_fd())
		++it;
	pollfds.erase(it);
	close(client->get_fd());
	delete client;
	return;
}

// void	Server::register_client(Client& client, const std::string& msg_rcv)
// {
	
// 	if (password.length() == 0)
// 	{
// 		client.set_statut(REGISTERED);
// 		return;
// 	}
// 	//if (())
// }

void	Server::sendToClient(int clientSocket, std::string msg)
{
	if (send(clientSocket, msg.c_str(), msg.size() + 1, 0) == -1)
	{
		//error handler
	}
}

bool	Server::_isOperator(Client * client) const
{
	std::set<Client *>::const_iterator	it;

	it = _operatorList.find(client);
	if (it != _operatorList.end())
		return (true);
	return false;
}

void	Server::_removeOperator(Client * client)
{
	_operatorList.erase(client);
}

void	Server::_addOperator(Client * client)
{
	_operatorList.insert(client);
}