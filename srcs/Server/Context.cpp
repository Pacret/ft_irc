#include "Context.hpp"

Context::Context(std::string & servname, const std::string &port, const std::string &password)
{
	this->server_name = servname;
	this->port = port;
	this->_password = password;

	// TEMP PART, FILL THE MOTD
	_motd.push_back("une ligne de MOTD");
	_motd.push_back("une deuxieme");
	_motd.push_back("et c'est tout");

	_commands["CAP"] = &Context::capls_command;
	_commands["JOIN"] = &Context::join_command;
	_commands["PASS"] = &Context::pass_command;
	_commands["NICK"] = &Context::nick_command;
	_commands["USER"] = &Context::user_command;
	_commands["OPER"] = &Context::oper_command;
	_commands["QUIT"] = &Context::quit_command;
	_commands["TOPIC"] = &Context::topic_command;
	_commands["NAMES"] = &Context::names_command;
	_commands["LIST"] = &Context::list_command;

	_commands["KICK"] = &Context::kick_command;
	_commands["PART"] = &Context::part_command;
	_commands["PRIVMSG"] = &Context::priv_msg_command;
//	_commands["MODE"] = &Context::mode_command_dummy;

	_commands["WHOIS"] = &Context::whois_command;
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
	if ((client->get_statut() == NONE && (command->cmd == "PASS" || command->cmd == "CAP")) || 
		(client->get_statut() == REGISTERED && (command->cmd == "USER" || command->cmd == "NICK")) ||
		(client->get_statut() == CONNECTED && (_commands.count(command->cmd) && command->cmd != "PASS" && command->cmd != "USER")))
	{
		return (this->*_commands[command->cmd])(client, command);
	}
	else
		sendToClient(client->fd, std::string(ft_irc::ERR_UNKNOWNCOMMAND(server_name, client->nick, command->cmd)));
	return NOPE;
}

Action		Context::capls_command(Client *client, struct parse_t *command)
{
	(void)client;
	(void)command;
	return NOPE;
}

Action		Context::join_command(Client *client, struct parse_t *command)
{
	std::string channel_name = command->args[0];

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

Action		Context::topic_command(Client *client, struct parse_t *command)
{
	std::string channel_name;

	if (command->args.size() < 1 || command->args[0] == "")
	{
		sendToClient(client->fd, ft_irc::ERR_NEEDMOREPARAMS(server_name, client->nick, command->cmd));
		return NOPE;
	}
	channel_name = command->args[0];
	if (_no_such_channel(*client, channel_name))
		return NOPE;
	else if (command->args.size() == 1)
	{
		if (_channels[channel_name]->get_topic() == "")
			sendToClient(client->fd, std::string(ft_irc::RPL_NOTOPIC(server_name, client->nick, channel_name)));
		else
			sendToClient(client->fd, std::string(ft_irc::RPL_TOPIC(server_name, client->nick, *_channels[channel_name])));
		return (NOPE);
	}
	else
	{
		std::string new_topic = command->args[1].substr(1);
		_channels[channel_name]->set_topic(new_topic);
		sendToClient(client->fd, std::string(ft_irc::RPL_TOPIC(server_name, client->nick, *_channels[channel_name])));
	}
	return NOPE;
}

Action		Context::names_command(Client *client, struct parse_t *command)
{
	// client->channelSet	
	// sendToClient(client->fd, std::string(ft_irc::RPL_NAMREPLY(server_name, client->nick, _channels[channel_name]->get_name(), _channels[channel_name]->get_users_nicks())));
	// sendToClient(client->fd, std::string(ft_irc::RPL_ENDOFNAMES(server_name, client->nick, _channels[channel_name]->get_name())));
	(void)client;
	(void)command;
	// sendToClient(client->fd, std::string(ft_irc::RPL_NAMREPLY(server_name, client->nick, _channels[channel_name]->get_name(), _channels[channel_name]->get_users_nicks())));
	// sendToClient(client->fd, std::string(ft_irc::RPL_ENDOFNAMES(server_name, client->nick, _channels[channel_name]->get_name())));
	return NOPE;
}

Action		Context::list_command(Client *client, struct parse_t *command)
{
	if (!command->args.size() || command->args[0] == "")
	{
		std::map<channelName, Channel *>::iterator it = _channels.begin();

		sendToClient(client->fd, std::string(ft_irc::RPL_LISTSTART(server_name, client->nick)));
		while(it != _channels.end())
    	{
			sendToClient(client->fd, std::string(ft_irc::RPL_LIST(server_name, client->nick, *it->second)));
        	it++;
    	}
		sendToClient(client->fd, std::string(ft_irc::RPL_LISTEND(server_name, client->nick)));
	}
	else
	{
		sendToClient(client->fd, std::string(ft_irc::RPL_LISTSTART(server_name, client->nick)));
		if (_channels.count(command->args[0]))
			sendToClient(client->fd, std::string(ft_irc::RPL_LIST(server_name, client->nick, *_channels[command->args[0]])));
		sendToClient(client->fd, std::string(ft_irc::RPL_LISTEND(server_name, client->nick)));
	}
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
	Client *	victim = channel->getClientByNick(command->args[1]);
	if (!victim)
	{
		sendToClient(client->fd, ft_irc::ERR_USERNOTINCHANNEL(server_name, client->nick, command->args[1], channel_name));
		return NOPE;
	}

	//Check if client exists on given channel
	if (!_channels[channel_name]->isChannelMember(client->nick))
	{
		sendToClient(client->fd, ft_irc::ERR_NOTONCHANNEL(server_name, client->nick, channel_name));
		return NOPE;
	}

	//Check if client has operator's privilege
	if (!channel->isOperator(client))
	{
		sendToClient(client->fd, ft_irc::ERR_CHANOPRIVSNEEDED(server_name, client->nick, channel_name));
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

//WHOIS [<server>] <nickmask>[,<nickmask>[,...]]
Action	Context::whois_command(Client *client, struct parse_t *command)
{
	//Check if there's any param
	if (command->args.empty())
	{
		sendToClient(client->fd, ft_irc::ERR_NONICKNAMEGIVEN(this->server_name, client->nick));
		return NOPE;
	}

	//Parse
	std::string					servname;
	std::vector<std::string>	nickmasks;
	int 						i = 0;
	if (command->args.size() == 2)
		servname = command->args[i++];
	nickmasks = string_split(command->args[i], ",");
	//TODO: nickmasks get rid of strings after ! and @
	
	//Check server name
	if (!servname.empty() && servname != this->server_name)
	{
		sendToClient(client->fd, ft_irc::ERR_NOSUCHSERVER(this->server_name, client->nick, servname));
		return NOPE;
	}

	//Return info for each nickname
	Client *		target;
	ostringstream	os;
	for (unsigned long i = 0; i < nickmasks.size(); i++)
	{
		if (!(target = _get_client_by_nickname(nickmasks[i])))
		{
			os << ft_irc::ERR_NOSUCHNICK(this->server_name, client->nick, nickmasks[i]);
		}
		else
		{
			os << ft_irc::RPL_WHOISUSER(server_name, client->nick, *target, "<host>");
			os << ft_irc::RPL_WHOISCHANNELS(server_name, client->nick, target->nick, _get_client_channellist(target));
			os << ft_irc::RPL_WHOISSERVER(server_name, client->nick, target->nick, server_name, "");
		}
	}
	os << ft_irc::RPL_ENDOFWHOIS(server_name, client->nick, nickmasks[0]);
	sendToClient(client->fd, os.str());
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
	
	// cout << "before for" << endl;

	for (vector<string>::iterator it = destinators.begin(); it != destinators.end(); it++)
	{
		string final_msg(start_msg);
		final_msg += *it;
		final_msg += " " + p->args[1] + "\r\n";

		// cout << "before if in for " << *it << endl;
		// _channels.find(*it);
		// cout << "channel cond" << endl;
		// get_client_by_nickname(*it);
		// cout << "by nickname" << endl;
		if (_channels.find(*it) == _channels.end() && _get_client_by_nickname(*it) == NULL)
		{
			// cout << "in if not found" << endl;
			return NOPE;
		}
		else if (_channels.find(*it) != _channels.end())
		{
			// cout << "before broadcast" << endl;
			_channels[*it]->broadcastToClients(client, final_msg);
			// cout << "after broadcast" << endl;
		}
		else
		{
			sendToClient(_get_client_by_nickname(*it)->fd, final_msg);
		}
	}
	return NOPE;
}

Action		Context::pass_command(Client *client, struct parse_t *command)
{

	if (!command->args.size())
		sendToClient(client->fd, ft_irc::ERR_NEEDMOREPARAMS(server_name, "*", command->cmd));
	else if (client->get_statut() != NONE)
		sendToClient(client->fd, ft_irc::ERR_ALREADYREGISTRED(server_name, client->nick));
	else if (command->args[0] == getPassword())
		client->set_statut(REGISTERED);
	else
	{
		deleteClient(client);
		return KILL_CONNECTION;
	}
	return NOPE;
}

Action		Context::nick_command(Client *client, struct parse_t *command)
{
	bool tmp = false;

	if (!command->args.size())
	{
		std::string name = "*";
		if (client->nick != "")
			name = client->nick;
		sendToClient(client->fd, ft_irc::ERR_NONICKNAMEGIVEN(server_name, name));
		return (NOPE);
	}
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
	if (!command->args.size())
	{
		sendToClient(client->fd, ft_irc::ERR_NEEDMOREPARAMS(server_name, "*", command->cmd));
		return NOPE;
	}
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

std::string	Context::_get_client_channellist(Client * client) const
{
	std::string							chan_list;
	std::set<Channel *>::const_iterator	it = client->channelSet.begin();
	std::set<Channel *>::const_iterator	ite = client->channelSet.end();
	
	for (; it != ite; it++)
	{
		if (chan_list != "")
			chan_list += " ";
		if ((*it)->isOperator(client))
			chan_list += "@";
		chan_list += (*it)->get_name();
	}
	std::cout << chan_list << std::endl;
	return (chan_list);
}

