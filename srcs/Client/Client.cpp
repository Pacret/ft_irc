/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:23:56 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/22 02:04:20 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "../Utils/defines.h"

using namespace std;

		Client::Client( int fd, struct sockaddr_in address) : fd(fd), _address(address), _statut(NONE)
{
	return;
}

		Client::~Client()
{
    close(fd);
}

int		Client::get_fd() {return (this->fd);}

string Client::get_ip() {return (ft_irc::to_string(_address.sin_addr.s_addr));}

string	Client::get_nick() {return (_nick);}

string	Client::get_user() {return (_username);}

string Client::get_rn() {return (_real_name);}

Statut	Client::get_statut() {return (_statut);}

void	Client::set_statut(Statut statut)
{
	_statut = statut;
}
