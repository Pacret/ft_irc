/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:23:56 by pbonilla          #+#    #+#             */
/*   Updated: 2022/07/02 16:58:47 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

using namespace std;

		Client::Client( int fd, struct sockaddr_in address)
			: _statut(NONE), _address(address), fd(fd), nick_inuse(false)
{}

		Client::~Client()
{}

void	Client::set_nick(std::string nick)
{
	this->nick = nick;
}

void	Client::set_user(std::string user)
{
	_username = user;
}

void	Client::set_rn(std::string rn)
{
	_real_name = rn;
}

string Client::get_ip() const {return (int_to_string(_address.sin_addr.s_addr));}

string	Client::get_username() {return (_username);}

string Client::get_rn() {return (_real_name);}

Statut	Client::get_statut() {return (_statut);}

void	Client::set_statut(Statut statut)
{
	_statut = statut;
}

//Nickmask standard basic format: <nick>!<username>@<host>
std::string	Client::get_nickmask() const
{
	return (nick + "!" + _username + "@" + get_ip()); //How to get hostname instead of ip?
}
