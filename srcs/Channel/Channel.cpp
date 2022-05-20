/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:47:26 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/20 13:31:05 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

		Channel::Channel(Client *owner, const std::string &channel_name): _owner(owner), _channel_name(channel_name)
{
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

int		Channel::get_nbrClients()
{
	return (clients.size());
}

int		Channel::get_nbrOps()
{
	return (operators.size());
}
int		Channel::get_nbrUsers()
{
	return (get_nbrOps() + get_nbrClients() + 1);
}

std::vector<Client *>	Channel::get_Users()
{
	std::vector<Client *> users = clients;
	users.insert(users.end(), operators.begin(), operators.end());
	users.push_back(_owner);
	return (users);
}