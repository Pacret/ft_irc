/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:19:41 by pbonilla          #+#    #+#             */
/*   Updated: 2022/07/02 16:58:37 by pbonilla         ###   ########.fr       */
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

typedef struct user_mode_s
{
	bool	i; // marks a users as invisible
	bool	o; // operator falg

	user_mode_s(): i(false), o(false) {}
}	user_mode_t;


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
		bool		nick_inuse;
		user_mode_t	mode;

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
		void	check_passwd(const std::string &command);
};

#endif