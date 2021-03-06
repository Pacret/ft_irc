/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:50:08 by pbonilla          #+#    #+#             */
/*   Updated: 2022/07/12 13:36:49 by pbonilla         ###   ########.fr       */
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
# include <cstring>
# include <stdexcept>

# include "Context.hpp"

# ifndef DEBUG
#  define DEBUG 0
# endif


class Server
{
	private:
		int							fd_socket;
		std::vector<struct pollfd>	pollfds;
		Context *					context;
		std::ofstream				log_file;

		typedef int				clientFd;
		std::vector<clientFd>	_clients_to_kill;

		bool		_load_server_config(std::string config);

	public:
		Server();
		Server(const std::string &port, const std::string &password, std::string configFile = "config");
		~Server();

		void	init();
		void	process();
		void	addClient();

		void	get_message(Client *client);
		void	kill_connection(int clientFd);
		void	clean();
		void	close_server(const std::string &msg_error);
};

#endif
