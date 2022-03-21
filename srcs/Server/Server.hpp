/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:50:08 by pbonilla          #+#    #+#             */
/*   Updated: 2022/03/20 17:39:19 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <poll.h>
#include <map>
#include <vector>

#include "../Utils/Utils.hpp"
#include "../Client/Client.hpp"

class Server
{
    private:
        int    fd_socket;
        std::vector<struct pollfd> pollfds;

        std::map<int, Client *> clients;

        std::string port;
        std::string password;
    public:
        Server();
        Server(const std::string &port, const std::string &password);
        ~Server();

        void    init();
        void    process();
        void    addClient();

        void    setPort(const std::string &port);
        void    setPassword(const std::string &password);

};