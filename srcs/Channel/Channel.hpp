/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:50:08 by pbonilla          #+#    #+#             */
/*   Updated: 2022/06/23 14:20:44 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <fstream>
# include <stdlib.h>
# include <vector>
# include <set>

# include "../Utils/Utils.hpp"
# include "../Client/Client.hpp"

class Channel
{
    private:

        std::string	_channel_name;
		std::string	_topic;

        std::vector<Client *>	_clients;
		std::set<Client *>		_operatorList;

    public:
        Channel(Client *owner, const std::string &channel_name);
        ~Channel();

        int get_nbrNormalClients();
        int get_nbrOps();
        int get_nbrUsers();
    
        std::vector<Client *>	get_users();
        std::string				get_users_names();

        // void demote(Client& client);
        // void promote(Client& client);

		std::string get_name();
		std::string get_mode();
		std::string get_mode_params();
		std::string get_topic();

		bool	isOperator(Client * client) const;
		void	removeOperator(Client * client);
		void	addOperator(Client * client);

		void	sendToClient(int clientSocket, std::string msg);
		void	broadcastToClients(int sendingClient, std::string msg);
};

#endif
