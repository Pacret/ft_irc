/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:47:26 by pbonilla          #+#    #+#             */
/*   Updated: 2022/07/02 17:42:16 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "../Utils/parser_utils.hpp"
#include "../Utils/defines.h"
#include "../Utils/parser_utils.hpp"
#include <string>
#include <netdb.h>

		Server::Server()
{
    
}

		Server::Server(const std::string &port, const std::string &password) : port(port), password(password)
{
	server_name = "paco.com";
	_prefixServer = ":" + server_name + " ";
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

	//struct hostent *host;



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
	commands["PART"] = &Server::part_command;
	commands["PRIVMSG"] = &Server::priv_msg_command;
	commands["OPER"] = &Server::oper_command;
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
	else
		channels[channel_name]->addClient(client);
	std::vector<Client *> usrs = channels[channel_name]->get_users();
	channels[channel_name]->broadcastToClients(NULL, std::string(":" + client->get_nick() + "!" +  client->get_username() + "@" + server_name + " JOIN :" + channel_name + "\r\n"));
	send_message(client->get_fd(), std::string(" " + ft_irc::RPL_TOPIC(server_name, client->get_nick(), *channels[channel_name])));
	send_message(client->get_fd(), std::string(" " + ft_irc::RPL_NAMREPLY(server_name, client->get_nick(), channels[channel_name]->get_name(), channels[channel_name]->get_users_names())));
	send_message(client->get_fd(), std::string(" " + ft_irc::RPL_ENDOFNAMES(server_name, client->get_nick(), channels[channel_name]->get_name())));
}

//KICK <channel> <user> [<comment>] 
void	Server::kick_command(Client *client, struct parse_t *command)
{
	//Check if there's enough parameters 
	if (_not_enough_params(*client, command, 2))
		return ;

	//Check if channel exists
	std::string channel_name = command->args[0];
	if (_no_such_channel(*client, channel_name))
		return ;

	//Check if victim exists on given channel
	Channel *	channel = channels[channel_name];
	std::cout << "(" + channel->get_users_nicks() + ")" << std::endl;
	Client *	victim = channel->getClientByNick(command->args[1]);
	if (!victim)
	{
		sendToClient(client->fd, ft_irc::ERR_USERNOTINCHANNEL(server_name, client->get_nick(), command->args[1], channel_name) + "\r\n");
		std::cout << "Victim not on channel" << std::endl;	
		return ;
	}

	//Check if client exists on given channel
	if (!channels[channel_name]->isChannelMember(client->nick))
	{
		sendToClient(client->fd, ft_irc::ERR_NOTONCHANNEL(server_name, client->get_nick(), channel_name) + "\r\n");
		std::cout << "Client not on channel" << std::endl;
		return ;
	}

	//Check if client has operator's privilege
	if (!channel->isOperator(client))
	{
		sendToClient(client->fd, ft_irc::ERR_CHANOPRIVSNEEDED(server_name, client->get_nick(), channel_name) + "\r\n");
		std::cout << "Need op priv" << std::endl;
		return ;
	}

	//Broadcast to channel members
	std::cout << "{" << _format_response(client->nick, *command) << "}" << std::endl;
	channel->broadcastToClients(0, _format_response(client->nick, *command));

	//Delete victim from channel
	//Delete channel if there's no one left
	if (channel->deleteClient(victim) == 0)
		channels.erase(channel->get_name());
}

std::string	Server::_format_response(std::string sender, parse_t & command)
{
	std::ostringstream	os;

	os << ":" << sender << " ";
	if (command.prefix.empty())
		os << command.original_msg;
	else
	{
		os << command.cmd;
		for (unsigned long i = 0; i < command.args.size(); i++)
		{
			os << " " << command.args[i];
		}
	}
	os << "\r\n";
	return (os.str());
}

void	Server::part_command(Client *client, struct parse_t *command)
{
	//Check if there's enough parameters 
	if (_not_enough_params(*client, command, 1))
		return ;

	//Check if each channel exists
	std::vector<std::string>	channel_names;
	channel_names = string_split(command->args[0], ",");
	for (unsigned long i = 0; i < channel_names.size(); i++)
	{
		if (_no_such_channel(*client, channel_names[i]))
			return ;
	}

	Channel *			chan;
	for (unsigned long i = 0; i < channel_names.size(); i++)
	{
		//Check if client exists on each channel
		chan = channels[channel_names[i]];
		if (!chan->isChannelMember(client->nick))
		{
			sendToClient(client->fd, ft_irc::ERR_NOTONCHANNEL(server_name, client->get_nick(), chan->get_name()) + "\r\n");
		}
		//Broadcast PART msg, delete client
		else
		{
			chan->broadcastToClients(client, _format_response(client->nick, *command));
			if (chan->deleteClient(client) == 0)
				channels.erase(chan->get_name());
		}
	}
}

void	Server::oper_command(Client *client, struct parse_t *command)
{
	//Check if there's enough parameters 
	if (_not_enough_params(*client, command, 2))
		return ;

	//Check if client has aleady op status
	// if (client->mode.o)
	//RPL_YOUREOPER

	//Load config file
	if (_load_server_config() && (_servOpConfig.host == client->get_ip()
				||  _servOpConfig.host != "" || _servOpConfig.host != "*" ))
	{
		if (_servOpConfig.password != command->args[1]
			|| _servOpConfig.username != command->args[0])
		{
			// ERR_PASSWDMISMATCH
			return ;
		}
		//client->mode.o = 1
		//Send user mode change to irc client
	}
	else
	{
		//ERR_NOOPERHOST
		return ;
	}
}


bool	Server::_not_enough_params(Client & client, struct parse_t * command, unsigned int minSize)
{
	if (command->args.size() < minSize)
	{
		sendToClient(client.fd, ft_irc::ERR_NEEDMOREPARAMS(server_name, client.get_nick(), command->cmd) + "\r\n");
		std::cout << "Not enough param" << std::endl;
		return true;
	}
	return false;
}

bool	Server::_no_such_channel(Client & client, std::string & chanName)
{
	std::map<channelName, Channel *>::iterator	it;
	it = channels.find(chanName);
	if (it == channels.end())
	{
		sendToClient(client.fd, ft_irc::ERR_NOSUCHCHANNEL(server_name, client.get_nick(), chanName) + "\r\n");
		std::cout << "No such channel" << std::endl;
		return true;
	}
	return false;
}

void    Server::send_motd(Client *client)
{
	send_message(client->get_fd(), ft_irc::RPL_WELCOME(server_name, client->get_nick(), client->get_nick(), "127.0.0.1"));
	send_message(client->get_fd(), ft_irc::RPL_LUSERCLIENT(server_name, client->get_nick(), "0", "0"));
	send_message(client->get_fd(), ft_irc::RPL_LUSERUNKNOWN(server_name, client->get_nick(), " 0"));
	send_message(client->get_fd(), ft_irc::RPL_LUSERCHANNELS(server_name, client->get_nick(), ft_irc::to_string(channels.size())));
	send_message(client->get_fd(), ft_irc::RPL_LUSERME(server_name, client->get_nick(), ft_irc::to_string(clients.size())));
	if (motd.empty())
		return;
	send_message(client->get_fd(), ft_irc::RPL_MOTDSTART(server_name, client->get_nick(), server_name));
	for(unsigned long int i = 0; i < motd.size(); i++)
		send_message(client->get_fd(), ft_irc::RPL_MOTD(server_name, client->get_nick(), motd[i]));
	send_message(client->get_fd(), ft_irc::RPL_ENDOFMOTD(server_name, client->get_nick()));
}

Client*	Server::get_client_by_nickname(string &nick_name)
{
	std::map<clientSocket, Client *>::iterator it = clients.begin();
	for(; it != clients.end(); it++)
	{
		if (it->second->get_nick() == nick_name)
			return (it->second);
	}
	return (NULL);
}

void	Server::priv_msg_command(Client *client, struct parse_t *p)
{
	// NOT FINISHED
	//vector<string> destinators;
	//if (parsed->args.size() != 2)
		//ERROR
	string start_msg;
	vector<string> destinators;
	string buff = p->args[0];
	size_t i = 0;
	vector<Client *> client_vector;

	start_msg = ":" + client->get_nick() + " " + "PRIVMSG ";
	while (!buff.empty() && buff[i] != '\0')
	{
		if ((i = buff.find(',')) == string::npos)
			i = buff.size() + 1;
		destinators.push_back(buff.substr(0, i - 1));
		buff.erase(0, i);
		i = 0;
	}
	
	// cout << "before for" << endl;

	for (vector<string>::iterator it = destinators.begin(); it != destinators.end(); it++)
	{
		string final_msg(start_msg);
		final_msg += *it;
		final_msg += " " + p->args[1];

		// cout << "before if in for " << *it << endl;
		// channels.find(*it);
		// cout << "channel cond" << endl;
		// get_client_by_nickname(*it);
		// cout << "by nickname" << endl;
		if (channels.find(*it) == channels.end() && get_client_by_nickname(*it) == NULL)
		{
			// cout << "in if not found" << endl;
			return;
		}
		else if (channels.find(*it) != channels.end())
		{
			// cout << "before broadcast" << endl;
			channels[*it]->broadcastToClients(client, final_msg);
			// cout << "after broadcast" << endl;
		}
		else
		{
			send_message(get_client_by_nickname(*it)->fd, final_msg);
		}
	}
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
	bool tmp = false;

	client->set_nick(command->args[0]);

	std::map<clientSocket, Client *>::iterator it;
	for (it = clients.begin(); it != clients.end(); it++)
	{
		std::cout << it->second->get_nick() << std::endl;
		if (it->second->get_fd() != client->get_fd() && it->second->get_nick() == client->get_nick())
		{
			client->nick_inuse = true;
			tmp = true;
			if (client->get_statut() == CONNECTED)
				send_message(client->get_fd(), ft_irc::ERR_NICKNAMEINUSE(server_name, "*", client->get_nick()));
		}
	}
	if (client->get_statut() == CONNECTED && tmp == false)
	{
		client->nick_inuse = false;
		send_motd(client);
	}
}

void    Server::user_command(Client *client, struct parse_t *command)
{
	client->set_user(command->args[0]);
	client->set_statut(CONNECTED);

	if (client->nick_inuse)
	{
		send_message(client->get_fd(), ft_irc::ERR_NICKNAMEINUSE(server_name, "*", client->get_nick()));
		return ;
	}
	send_motd(client);
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

bool	Server::_load_server_config()
{
	std::ifstream				ifs("config");
	std::stringstream			buffer;
	std::vector<std::string>	tmp;

	//Get config file's content into a string and split into lines 
  	if (!ifs.good())
	{
		std::cout << "Error: open config file failed" << std::endl;
		return (false);
	}
	buffer << ifs.rdbuf();
	tmp = string_split(buffer.str(), "\n");

	//Get lines that are not comments
	for (unsigned long int i = 0; i < tmp.size(); i++)
	{
		if (tmp[i][0] != '#')
			_config.push_back(tmp[i]);
	}

	//Parse O-lines for server operator, only the last line is accepted
	std::vector<std::string>	op_config;
	for (unsigned long int i = 0; i < _config.size(); i++)
	{
		if (_config[i][0] == 'O')
		{
			op_config = string_split(_config[i], ":");
			if (op_config.size() > 3)
			{
				_servOpConfig.host = op_config[1];
				_servOpConfig.password = op_config[2];
				_servOpConfig.username = op_config[3];
			}
		}
	}

	return (true);
}
