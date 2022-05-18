/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:19:41 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/18 09:28:01 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <netinet/in.h>
#include "../Utils/Utils.hpp"
#include <iostream>
#include <unistd.h>


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

class Client
{
    private:

        int fd;
		Statut _statut;
        std::string buffer;
		std::string _nick;
		std::string _username;
		std::string _real_name;
		struct sockaddr_in _address;

        void parse_command(const std::string &command);
		void check_passwd(const std::string &command);

    public:
        Client(int fd, struct sockaddr_in address);
        ~Client();

        void get_message();
        void send_message(const std::string &message);

		int	get_fd();
		std::string get_nick();
		std::string get_user();
		std::string get_rn();

		Statut get_statut();
		void set_statut(Statut statut);
};