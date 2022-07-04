/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:50:08 by pbonilla          #+#    #+#             */
/*   Updated: 2022/07/01 17:13:15 by tmerrien         ###   ########.fr       */
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

typedef struct servop_s
{
	std::string	host;
	std::string	password;
	std::string	username;
}	servop_t;

class Server
{
    private:
        int							fd_socket;
        std::vector<struct pollfd>	pollfds;

		typedef int			clientSocket;
		typedef std::string	channelName;
		typedef std::string	commandType;

        std::map<clientSocket, Client *>	clients;
        std::map<channelName, Channel *>	channels;
		std::map<commandType, void(Server::*)(Client *, struct parse_t *)> commands;

        std::string				port;
        std::string				password;
		servop_t				_servOpConfig;

		std::string					server_name;
		std::string					_prefixServer;
		std::ofstream				log_file;
		std::vector<std::string>	motd;
		std::vector<std::string>	_config;

		void    send_motd(Client *client);

		std::set<Client *>		_operatorList;

		bool	_isOperator(Client * client) const;
		void	_removeOperator(Client * client);
		void	_addOperator(Client * client);

		bool	_not_enough_params(Client & client, struct parse_t * command, unsigned int minSize);
		bool	_no_such_channel(Client & client, std::string & chanName);

		bool		_load_server_config();
		std::string	_format_response(std::string sender, parse_t & command);

    public:
        Server();
        Server(const std::string &port, const std::string &password);
        ~Server();

        void    init();
        void    process();
        void    addClient();

		void	pass_command(Client *client, struct parse_t *command);
		void	nick_command(Client *client, struct parse_t *command);
		void	user_command(Client *client, struct parse_t *command);
		void	join_command(Client *client, struct parse_t *command);
		void	kick_command(Client *client, struct parse_t *command);
		void	part_command(Client *client, struct parse_t *command);
		void	oper_command(Client *client, struct parse_t *command);


		void	priv_msg_command(Client *client, parse_t *p);
        void    send_message(int fd, const std::string &message);
        void    parse_command(Client *client, struct parse_t *command);
        void    get_message(Client *client);

		// DUMMY
		void	mode_command_dummy(Client *c, struct parse_t*p);

		void	register_client(Client& client, const std::string& msg_rcv);

        void    setPort(const std::string &port);
        void    setPassword(const std::string &password);

		std::string	get_pwd();
		void	kill_connection(Client *client);

		std::string get_name();
		std::string get_info();

		Client	*get_client_by_nickname(string &nick_name);

		void	sendToClient(int clientSocket, std::string msg);

};

#endif
