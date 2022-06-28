/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:23:56 by pbonilla          #+#    #+#             */
/*   Updated: 2022/06/28 15:41:23 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "../Utils/defines.h"

using namespace std;

		Client::Client( int fd, struct sockaddr_in address) : _statut(NONE), _address(address), fd(fd)
{
	return;
}

		Client::~Client()
{
    close(fd);
}

void	Client::set_nick(std::string nick)
{
	_nick = nick;
}

void	Client::set_user(std::string user)
{
	_username = user;
}

void	Client::set_rn(std::string rn)
{
	_real_name = rn;
}

int		Client::get_fd() {return (this->fd);}

string Client::get_ip() {return (ft_irc::to_string(_address.sin_addr.s_addr));}

string	Client::get_nick() {return (_nick);}

string	Client::get_username() {return (_username);}

string Client::get_rn() {return (_real_name);}

Statut	Client::get_statut() {return (_statut);}

void	Client::set_statut(Statut statut)
{
	_statut = statut;
}
