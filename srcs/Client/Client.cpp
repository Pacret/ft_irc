/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:23:56 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/18 14:15:42 by pbonilla         ###   ########.fr       */
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

void		Client::check_passwd(const std::string &command)
{
	size_t pos = command.find(" ");
	std::string	pass_sent;

	if (!command.find("PASS"))
		pass_sent = command.substr(5);
	else
		return;
	if (pass_sent != )
		return;
	_statut = REGISTERED;
	
	return ;
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
