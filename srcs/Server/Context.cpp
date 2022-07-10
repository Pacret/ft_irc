#include "Context.hpp"

#include <ctime>

Context::Context(std::string & servname, const std::string &port, const std::string &password)
{
	this->server_name = servname;
	this->port = port;
	this->_password = password;

	// TEMP PART, FILL THE MOTD
	_motd.push_back("une ligne de MOTD");
	_motd.push_back("une deuxieme");
	_motd.push_back("et c'est tout");

	_commands["JOIN"] = &Context::join_command;
	_commands["PASS"] = &Context::pass_command;
	_commands["NICK"] = &Context::nick_command;
	_commands["USER"] = &Context::user_command;
	_commands["OPER"] = &Context::oper_command;
	_commands["QUIT"] = &Context::quit_command;

	_commands["KICK"] = &Context::kick_command;
	_commands["PART"] = &Context::part_command;
	_commands["PRIVMSG"] = &Context::priv_msg_command;
	_commands["PING"] = &Context::ping_command;
	_commands["PONG"] = &Context::pong_command;
//	_commands["MODE"] = &Context::mode_command_dummy;
}

Context::~Context()
{
	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		delete it->second;
	// Delete channels
}

void	Context::sendToClient(int fd, const std::string & msg)
{
	std::cout << "Send: {" << msg << "}" << std::endl;
	if (send(fd, msg.c_str(), msg.size(), 0) == -1)
		std::cout << "Error: send message" << std::endl; //Add an error handler
}

std::string	 Context::_format_response(std::string sender, parse_t & command)
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

Action		Context::parse_command(Client *client, struct parse_t *command)
{
	if ((client->get_statut() == NONE && command->cmd == "PASS") || 
		(client->get_statut() == REGISTERED && (command->cmd == "USER" || command->cmd == "NICK")) ||
		(client->get_statut() == CONNECTED && (_commands.count(command->cmd) && command->cmd != "PASS" && command->cmd != "USER")))
	{
		return (this->*_commands[command->cmd])(client, command);
	}
	else
		std::cout << "	/!\\ ERROR COMMAND /!\\" << std::endl;
	return NOPE;
}

// Action		Context::Ping(Client *client, struct parse_t *command)
// {

// 	return NOPE;
// }

Action		Context::join_command(Client *client, struct parse_t *command)
{
	std::string channel_name = command->args[0];

	if (command->args[0].size() > 200)
	{
		sendToClient(client->fd, ft_irc::ERR_BADCHANMASK(server_name, client->nick, channel_name));
		return NOPE;
	}

	if (_channels.find(channel_name) == _channels.end())
		_channels[channel_name] = new Channel(client, channel_name);
	else
		_channels[channel_name]->addClient(client);
	std::vector<Client *> usrs = _channels[channel_name]->get_users();
	_channels[channel_name]->broadcastToClients(NULL, std::string(":" + client->nick + "!" +  client->nick + "@" + server_name + " JOIN :" + channel_name + "\r\n"));
	sendToClient(client->fd, std::string(ft_irc::RPL_TOPIC(server_name, client->nick, *_channels[channel_name])));
	sendToClient(client->fd, std::string(ft_irc::RPL_NAMREPLY(server_name, client->nick, _channels[channel_name]->get_name(), _channels[channel_name]->get_users_nicks())));
	sendToClient(client->fd, std::string(ft_irc::RPL_ENDOFNAMES(server_name, client->nick, _channels[channel_name]->get_name())));
	return NOPE;
}

//KICK <channel> <user> [<comment>] 
Action		Context::kick_command(Client *client, struct parse_t *command)
{
	//Check if there's enough parameters 
	if (_not_enough_params(*client, command, 2))
		return NOPE;

	//Check if channel exists
	std::string channel_name = command->args[0];
	if (_no_such_channel(*client, channel_name))
		return NOPE;

	//Check if victim exists on given channel
	Channel *	channel = _channels[channel_name];
	std::cout << "(" + channel->get_users_nicks() + ")" << std::endl;
	Client *	victim = channel->getClientByNick(command->args[1]);
	if (!victim)
	{
		sendToClient(client->fd, ft_irc::ERR_USERNOTINCHANNEL(server_name, client->nick, command->args[1], channel_name));
		std::cout << "Victim not on channel" << std::endl;	
		return NOPE;
	}

	//Check if client exists on given channel
	if (!_channels[channel_name]->isChannelMember(client->nick))
	{
		sendToClient(client->fd, ft_irc::ERR_NOTONCHANNEL(server_name, client->nick, channel_name));
		std::cout << "Client not on channel" << std::endl;
		return NOPE;
	}

	//Check if client has operator's privilege
	if (!channel->isOperator(client))
	{
		sendToClient(client->fd, ft_irc::ERR_CHANOPRIVSNEEDED(server_name, client->nick, channel_name));
		std::cout << "Need op priv" << std::endl;
		return NOPE;
	}

	//Broadcast to channel members
	channel->broadcastToClients(0, _format_response(client->get_nickmask(), *command));

	//Remove victim from channel and cleanup
	removeClientFromChannel(victim, channel);
	return NOPE;
}

Action		Context::part_command(Client *client, struct parse_t *command)
{
	//Check if there's enough parameters 
	if (_not_enough_params(*client, command, 1))
		return NOPE;

	//Check if each channel exists
	std::vector<std::string>	channel_names;
	channel_names = string_split(command->args[0], ",");
	for (unsigned long i = 0; i < channel_names.size(); i++)
	{
		if (_no_such_channel(*client, channel_names[i]))
			return NOPE;
	}

	Channel *	chan;
	for (unsigned long i = 0; i < channel_names.size(); i++)
	{
		//Check if client exists on each channel
		chan = _channels[channel_names[i]];
		if (!chan->isChannelMember(client->nick))
		{
			sendToClient(client->fd, ft_irc::ERR_NOTONCHANNEL(server_name, client->nick, chan->get_name()));
		}
		else
		{
			//Broadcast PART message
			chan->broadcastToClients(0, _format_response(client->get_nickmask(), *command));
			//Remove client from channel and cleanup
			removeClientFromChannel(client, chan);
		}
	}
	return NOPE;
}

//OPER <user> <password>
Action		Context::oper_command(Client *client, struct parse_t *command)
{
	//Check if there's enough parameters 
	if (_not_enough_params(*client, command, 2))
		return NOPE;

	//Check if client has aleady op status
	if (client->mode.o)
	{
		sendToClient(client->fd, ft_irc::RPL_YOUREOPER(
							server_name, client->nick));
		return NOPE;
	}

	//Compare params with op config
	if (!config.empty() && (opConfig.host == client->get_ip()
				|| opConfig.host == "" || opConfig.host == "*" ))
	{
		if (opConfig.username != command->args[0]
			|| opConfig.password != command->args[1])
		{
			sendToClient(client->fd, ft_irc::ERR_PASSWDMISMATCH(
							server_name, client->nick));
			return NOPE;
		}
		client->mode.o = true;
		_addOperator(client);
		sendToClient(client->fd, ft_irc::RPL_YOUREOPER(server_name, client->nick));
	}
	else
		sendToClient(client->fd, ft_irc::ERR_NOOPERHOST(server_name, client->nick));
	return NOPE;
}

Action		 Context::priv_msg_command(Client *client, struct parse_t *p)
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

	start_msg = ":" + client->nick + " " + "PRIVMSG ";
	while (!buff.empty() && buff[i] != '\0')
	{
		if ((i = buff.find(',')) == string::npos)
			i = buff.size() + 1;
		destinators.push_back(buff.substr(0, i - 1));
		buff.erase(0, i);
		i = 0;
	}
	for (vector<string>::iterator it = destinators.begin(); it != destinators.end(); it++)
	{
		string final_msg(start_msg);
		final_msg += *it;
		final_msg += " " + p->args[1] + "\r\n";

		if (_channels.find(*it) == _channels.end() && _get_client_by_nickname(*it) == NULL)
		{
			//RPL NEEDED
			return NOPE;
		}
		else if (_channels.find(*it) != _channels.end())
			_channels[*it]->broadcastToClients(client, final_msg);
		else
			sendToClient(_get_client_by_nickname(*it)->fd, final_msg);
	}
	return NOPE;
}

Action		Context::pass_command(Client *client, struct parse_t *command)
{
	if (command->args[0] != getPassword())
	{
		//client->set_statut(DELETE);
		deleteClient(client);
		return KILL_CONNECTION;
	}
	client->set_statut(REGISTERED);
	return NOPE;
}

Action		Context::nick_command(Client *client, struct parse_t *command)
{
	bool tmp = false;

	client->set_nick(command->args[0]);

	std::map<clientSocket, Client *>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); it++)
	{
		std::cout << it->second->nick << std::endl;
		if (it->second->fd != client->fd && it->second->nick == client->nick)
		{
			client->nick_inuse = true;
			tmp = true;
			if (client->get_statut() == CONNECTED)
				sendToClient(client->fd, ft_irc::ERR_NICKNAMEINUSE(server_name, "*", client->nick));
		}
	}
	if (client->get_statut() == CONNECTED && tmp == false)
	{
		client->nick_inuse = false;
		_send_motd(client);
	}
	return NOPE;
}

Action		Context::user_command(Client *client, struct parse_t *command)
{
	client->set_user(command->args[0]);
	client->set_statut(CONNECTED);

	if (client->nick_inuse)
	{
		sendToClient(client->fd, ft_irc::ERR_NICKNAMEINUSE(server_name, "*", client->nick));
		return NOPE;
	}
	_send_motd(client);
	return NOPE;
}

Action	Context::quit_command(Client *client, struct parse_t *command)
{
	std::string message;
	if (command->args.size())
		message = command->args[0];
	sendToClient(client->fd, std::string("ERROR :Closing link: (" + client->nick + "@127.0.0.1) [Quit: " + message + "]"));
	//client->set_statut(DELETE);
	deleteClient(client);
	return KILL_CONNECTION;
}

bool	Context::_not_enough_params(Client & client, struct parse_t * command, unsigned int minSize)
{
	if (command->args.size() < minSize)
	{
		sendToClient(client.fd, ft_irc::ERR_NEEDMOREPARAMS(server_name, client.nick, command->cmd));
		std::cout << "Not enough param" << std::endl;
		return true;
	}
	return false;
}

bool	Context::_no_such_channel(Client & client, std::string & chanName)
{
	std::map<channelName, Channel *>::iterator	it;
	it = _channels.find(chanName);
	if (it == _channels.end())
	{
		sendToClient(client.fd, ft_irc::ERR_NOSUCHCHANNEL(server_name, client.nick, chanName));
		std::cout << "No such channel" << std::endl;
		return true;
	}
	return false;
}

void	Context::_send_motd(Client *client)
{
	sendToClient(client->fd, ft_irc::RPL_WELCOME(server_name, client->nick, client->nick, "127.0.0.1"));
	sendToClient(client->fd, ft_irc::RPL_LUSERCLIENT(server_name, client->nick, "0", "0"));
	sendToClient(client->fd, ft_irc::RPL_LUSERUNKNOWN(server_name, client->nick, " 0"));
	sendToClient(client->fd, ft_irc::RPL_LUSERCHANNELS(server_name, client->nick, int_to_string(_channels.size())));
	sendToClient(client->fd, ft_irc::RPL_LUSERME(server_name, client->nick, int_to_string(_clients.size())));
	if (_motd.empty())
		return;
	sendToClient(client->fd, ft_irc::RPL_MOTDSTART(server_name, client->nick, server_name));
	for(unsigned long int i = 0; i < _motd.size(); i++)
		sendToClient(client->fd, ft_irc::RPL_MOTD(server_name, client->nick, _motd[i]));
	sendToClient(client->fd, ft_irc::RPL_ENDOFMOTD(server_name, client->nick));
}

Client*	 Context::_get_client_by_nickname(string &nick_name)
{
	std::map<clientSocket, Client *>::iterator it = _clients.begin();
	for(; it != _clients.end(); it++)
	{
		if (it->second->nick == nick_name)
			return (it->second);
	}
	return (NULL);
}

bool	 Context::_isOperator(Client * client) const
{
	std::set<Client *>::const_iterator	it;

	it = _operatorList.find(client);
	if (it != _operatorList.end())
		return (true);
	return false;
}

void	 Context::_removeOperator(Client * client)
{
	_operatorList.erase(client);
}

void	 Context::_addOperator(Client * client)
{
	_operatorList.insert(client);
}

std::string	 Context::getPassword() const
{
	return (_password);
}

Client *	Context::getClient(int clientFd)
{
	return (_clients[clientFd]);
}

void	Context::setPort(const std::string &port)
{
	this->port = port;
}

void	Context::setPassword(const std::string &password)
{
	this->_password = password;
}

void	Context::addClient(int fd, struct sockaddr_in address)
{
	_clients[fd] = new Client(fd, address);
	_clients[fd]->last_req = clock();
}

void	Context::deleteClient(Client * client)
{
	std::set<Channel *>::iterator it = client->channelSet.begin();
	std::set<Channel *>::iterator ite = client->channelSet.end();

	//Erase client from context's client lists
	_clients.erase(client->fd);

	//Remove client from all the channels that he joined
	for (; it != ite; it++)
		removeClientFromChannel(client, *it);

	delete client;
}

void	Context::removeClientFromChannel(Client *client, Channel *channel)
{
	client->channelSet.erase(channel);
	if (channel->deleteClient(client) == 0)
	{
		_channels.erase(channel->get_name());
		delete channel;
	}
}

Action	Context::pong_command(Client *client, parse_t *p)
{
	std::cout << "PONG Command received" << std::endl;
	client->ping_delta = 0;
	p->cmd.erase();
	return NOPE;
}

Action Context::ping_command(Client *client, parse_t *p)
{
	std::cout << "PING command sent by client" << std::endl;
	std::string msg = ":" + this->server_name + " PONG ";
	msg += this->server_name + " :" + this->server_name;

	sendToClient(client->fd, msg);
	p->cmd.erase();
	return NOPE;
}

Action	Context::check_alive(Client *client)
{
	
	if (client == NULL)
		return NOPE;
	float tsn_req = ((float)clock() - (float)(client->last_req)) / CLOCKS_PER_SEC;

	std::cout << "hello" << std::endl;
	if (tsn_req >= PING_DELTA && client->ping_delta == 0)
	{
		std::cout << "ping sent" << std::endl;
		std::string msg = "PING " + this->server_name + "\r\n";
		sendToClient(client->fd, msg);
		client->ping_delta = client->last_req;
		return NOPE;
	}
	// float ping_tsn = ((float)clock() - (float)(client->last_req)) / CLOCKS_PER_SEC; 
	if (tsn_req >= PING_DELTA && client->ping_delta >= PING_DELTA + PING_WAIT)
	{
		return KILL_CONNECTION;
	}
	return NOPE;
}

