/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:47:26 by pbonilla          #+#    #+#             */
/*   Updated: 2022/07/15 16:35:19 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

		Channel::Channel(Client *owner, const std::string &channel_name): _channel_name(channel_name)
{
	if (owner)
		addOperator(owner);
}

		Channel::~Channel()
{
	//std::cout << "aurevoir channel" << std::endl;
}

std::string		Channel::get_name()
{
	return (_channel_name);
}

int		Channel::get_nbrNormalClients()
{
	return (_clients.size() - _operatorList.size());
}

int		Channel::get_nbrOps()
{
	return (_operatorList.size());
}

int		Channel::get_nbrUsers()
{
	return (_clients.size());
}

//This functions needs to be deleted
std::vector<Client *>	Channel::get_users()
{
	std::vector<Client *>	ret;
	std::set<Client *>::iterator it = _clients.begin();
	std::set<Client *>::iterator ite = _clients.end();
	
	for (; it != ite; it++)
		ret.push_back(*it);
	return (ret);
}

std::string		Channel::get_users_nicks()
{
	std::string						user_nicks;
	std::set<Client *>::iterator	it = _clients.begin();
	std::set<Client *>::iterator	ite = _clients.end();
	
	for (; it != ite; it++)
	{
		if (user_nicks != "")
			user_nicks += " ";
		if (isOperator(*it))
			user_nicks += "@";
		user_nicks += (*it)->nick;
	}
	std::cout << user_nicks << std::endl;
	return (user_nicks);
}

void			Channel::set_topic(const std::string &new_topic)
{
	_topic = new_topic;
}

std::string		Channel::get_topic()
{
	return (_topic);
}

void	Channel::broadcastToClients(Client * client, std::string msg)
{
	std::set<Client *>::iterator it = _clients.begin();
	std::set<Client *>::iterator ite = _clients.end();
	
	std::cout << "Broadcast: {" << msg << "}" << std::endl;
	for (; it != ite; it++)
	{
		if (client == NULL || (*it)->fd != client->fd)
		{
			sendToClient((*it), msg);
		}
	}
}

void	Channel::sendToClient(Client * client, std::string msg)
{
	//Bot has negative fd -1
	if (!client || client->fd < 0) 
		return ;

	if (send(client->fd, msg.c_str(), msg.size(), 0) == -1)
	{
		//error handler
	}
}

bool	Channel::isChannelMember(std::string nickname) const
{
	std::set<Client *>::const_iterator it = _clients.begin();
	std::set<Client *>::const_iterator ite = _clients.end();
	
	for (; it != ite; it++)
	{
		if ((*it)->nick == nickname)
			return (true);
	}
	return (false);
}

Client *	Channel::getClientByNick(std::string nickname)
{
	std::set<Client *>::iterator it = _clients.begin();
	std::set<Client *>::iterator ite = _clients.end();
	
	for (; it != ite; it++)
	{
		if ((*it)->nick == nickname)
			return (*it);
	}
	return 0;
}

Channel::clientSize	Channel::deleteClient(Client * client)
{
	if (client && client->channelSet.find(this) != client->channelSet.end())
		client->channelSet.erase(this);
	_clients.erase(client);
	_operatorList.erase(client);
	return (_clients.size());
}

void	Channel::addClient(Client * client)
{
	if (isChannelMember(client->nick))
		return ; // send an err ?
	_clients.insert(client);
	if (client->channelSet.find(this) == client->channelSet.end())
		client->channelSet.insert(this);
}

bool	Channel::isOperator(Client * client) const
{
	std::set<Client *>::const_iterator	it;

	it = _operatorList.find(client);
	if (it !=_operatorList.end())
		return (true);
	return false;
}

void	Channel::removeOperator(Client * client)
{
	_operatorList.erase(client);
}

void	Channel::addOperator(Client * client)
{
	if (!isChannelMember(client->nick))
		addClient(client);
	_operatorList.insert(client);
}

std::string Channel::get_mode() const
{
	std::ostringstream	os;

	os << "+";
	if (mode.i)
		os << "i";
	if (mode.t)
		os << "t";
	return (os.str());
}
