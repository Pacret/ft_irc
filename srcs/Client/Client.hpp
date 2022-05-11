/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:19:41 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/11 13:46:28 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

class Client
{
    private:
        int fd;
		bool _registered;
        std::string buffer;
		std::string _nick;
		std::string _username;
		struct sockaddr_in _address;

    public:
        Client(int fd, struct sockaddr_in address);
        ~Client();

        void get_message();
        void send_message();

		int	get_fd();
		bool get_registered();
		void set_registered(bool status);
};