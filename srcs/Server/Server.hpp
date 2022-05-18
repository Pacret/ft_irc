/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:50:08 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/17 09:49:25 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <sys/socket.h>
# include <sys/types.h>
# include <fcntl.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <poll.h>
# include <map>
# include <vector>

# ifndef DEBUG
#  define DEBUG 0
# endif

# include "../Utils/Utils.hpp"
# include "../Client/Client.hpp"
# include "../Utils/defines.h"
# include "../Channel/Channel.hpp"

class Channel;

class Server
{
    private:
        int    fd_socket;
        std::vector<struct pollfd> pollfds;

        std::map<int, Client *> clients;
        std::vector<Channel> channels;

        std::string port;
        std::string password;

		std::ofstream log_file;
    public:
        Server();
        Server(const std::string &port, const std::string &password);
        ~Server();

        void    init();
        void    process();
        void    addClient();

		void	send_message(Client& client, const std::string& msg);
		void	register_client(Client& client, const std::string& msg_rcv);

        void    setPort(const std::string &port);
        void    setPassword(const std::string &password);

		std::string get_name();
		std::string get_info();

};

#endif
