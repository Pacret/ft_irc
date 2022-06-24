/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:47:26 by pbonilla          #+#    #+#             */
/*   Updated: 2022/06/23 14:20:33 by pbonilla         ###   ########.fr       */
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

std::vector<Client *>	Channel::get_users()
{
	std::vector<Client *> users = clients;
	users.insert(users.end(), operators.begin(), operators.end());
	users.push_back(_owner);
	return (users);
}

std::string		Channel::get_users_names()
{
	std::string users_names;
	std::vector<Client *> users = get_users();

	for(unsigned long int i = 0; i < users.size(); i++)
		users_names += users[i]->get_username();
	return (users_names);
}

std::string		Channel::get_topic()
{
	return (_topic);
}