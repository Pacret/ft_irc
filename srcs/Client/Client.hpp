/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:19:41 by pbonilla          #+#    #+#             */
/*   Updated: 2022/03/21 15:18:18 by pbonilla         ###   ########.fr       */
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
        std::string buffer;

    public:
        Client(int fd, struct sockaddr_in address);
        ~Client();

        void get_message();
        void send_message();
};