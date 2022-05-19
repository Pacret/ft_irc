/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:23:56 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/18 14:34:51 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

		Client::Client( int fd, struct sockaddr_in address) : fd(fd), _address(address), _statut(REGISTERED)
{
	return;
}

		Client::~Client()
{
    close(fd);
}

int		Client::get_fd()
{
	return (this->fd);
}

Statut	Client::get_statut() {return (_statut);}

void	Client::set_statut(Statut statut)
{
	_statut = statut;
}
