/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:47:26 by pbonilla          #+#    #+#             */
/*   Updated: 2022/06/28 15:36:10 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

		Channel::Channel(Client *owner, const std::string &channel_name): _channel_name(channel_name)
{
	_clients.push_back(owner);
	addOperator(owner);
	return;
}

		Channel::~Channel()
{
    std::cout << "aurevoir channel" << std::endl;
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

std::vector<Client *>	Channel::get_users()
{
	return (_clients);
}

std::string		Channel::get_users_names()
{
	std::string users_names;

	for(unsigned long int i = 0; i < _clients.size(); i++)
		users_names += _clients[i]->get_username();
	return (users_names);
}

std::string		Channel::get_topic()
{
	return (_topic);
}

void	Channel::broadcastToClients(int sendingClient, std::string msg)
{
	for (unsigned long int i = 0; i < _clients.size(); i++)
	{
		if (_clients[i]->fd != sendingClient)
		{
			sendToClient(_clients[i]->fd, msg);
		}
	}
}

void	Channel::sendToClient(int clientSocket, std::string msg)
{
	if (send(clientSocket, msg.c_str(), msg.size() + 1, 0) == -1)
	{
		//error handler
	}
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
	_operatorList.insert(client);
}