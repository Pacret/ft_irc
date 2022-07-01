/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:19:41 by pbonilla          #+#    #+#             */
/*   Updated: 2022/06/29 16:28:04 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP


#include <netinet/in.h>
//#include "../Server/Server.hpp"
#include "../Utils/Utils.hpp"
#include <iostream>
#include <unistd.h>
#include <netdb.h>


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif


class Client
{
    private:
		std::string			_username;
		std::string			_real_name;
		Statut				_statut;
		struct sockaddr_in	_address;
		struct hostent 		_host;

    public:
        std::string buffer;
		int			fd;
		std::string	nick;

        Client(int fd, struct sockaddr_in address);
        ~Client();

		int	get_fd();

		std::string	get_nick();
		std::string	get_username();
		std::string	get_rn();
		std::string	get_ip();
		Statut		get_statut();
		
		void	set_nick(std::string nick);
		void	set_user(std::string user);
		void	set_rn(std::string rn);
		void	set_statut(Statut statut);
		void check_passwd(const std::string &command);
};

#endif