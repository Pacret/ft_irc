/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:50:08 by pbonilla          #+#    #+#             */
/*   Updated: 2022/06/28 16:55:34 by tmerrien         ###   ########.fr       */
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
# include <set>
# include <string>

# ifndef DEBUG
#  define DEBUG 0
# endif

# include "../Utils/Utils.hpp"
# include "../Client/Client.hpp"
# include "../Channel/Channel.hpp"
# include "../Utils/parser_utils.hpp"



class Server
{
    private:
        int							fd_socket;
        std::vector<struct pollfd>	pollfds;

		typedef int							clientSocket;
        std::map<clientSocket, Client *>	clients;
        std::map<std::string, Channel *>	channels;

		std::string	server_name;
        std::string	port;
        std::string	password;

		std::ofstream				log_file;
		std::vector<std::string>	motd;

		void    send_motd(Client *client);

		std::set<Client *>		_operatorList;

		bool	_isOperator(Client * client) const;
		void	_removeOperator(Client * client);
		void	_addOperator(Client * client);

    public:
        Server();
        Server(const std::string &port, const std::string &password);
        ~Server();

        void    init();
        void    process();
        void    addClient();

        void    join_channel(Client *client, const std::string &channel_name);
		void	priv_msg(Client *client, const std::string& command);
        void    send_message(int fd, const std::string &message);
        void    parse_command(Client *client, const std::string &command);
        void    get_message(Client *client);

		void	register_client(Client& client, const std::string& msg_rcv);

        void    setPort(const std::string &port);
        void    setPassword(const std::string &password);
		std::string	get_pwd();

		void	kill_connection(Client *client);
		void	check_passwd(Client *client, const std::string &command);

		std::string get_name();
		std::string get_info();

		void	sendToClient(int clientSocket, const char* msg, int length);

};

#endif
