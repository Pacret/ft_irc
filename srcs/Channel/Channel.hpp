/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:50:08 by pbonilla          #+#    #+#             */
/*   Updated: 2022/07/15 16:35:05 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <fstream>
# include <stdlib.h>
# include <vector>
# include <set>
# include <map>
# include <sstream>
# include <stdexcept>

# include "../Utils/utils.hpp"
# include "../Client/Client.hpp"

typedef struct chan_mode_s
{
	bool	o; // give channel operator privileges;
	bool	i; // invite-only channel flag;
	bool	t; // topic settable by channel operator only flag;

	chan_mode_s(): o(false), i(false), t(false) {}
}	chan_mode_t;

class Channel
{
    private:

		std::string	_channel_name;
		std::string	_topic;

		std::set<Client *>	_clients;
		std::set<Client *>	_operatorList;

    public:
		typedef unsigned long int	clientSize;
		chan_mode_t					mode;

        Channel(Client *owner, const std::string &channel_name);
        ~Channel();

        int get_nbrNormalClients();
        int get_nbrOps();
        int get_nbrUsers();

        std::vector<Client *>	get_users();
        //std::string			get_users_names();
        std::string				get_users_nicks();

        // void demote(Client& client);
        // void promote(Client& client);

		std::string get_name();
		std::string get_mode() const;
		std::string get_mode_params();
		std::string get_topic();

		bool		isChannelMember(std::string nickname) const;
		Client*		getClientByNick(std::string nickname);
		void		addClient(Client * client);
		clientSize	deleteClient(Client * client);
		void	set_topic(const std::string &new_topic);

		bool	isOperator(Client * client) const;
		void	removeOperator(Client * client);
		void	addOperator(Client * client);

		void	sendToClient(Client * client, std::string msg);
		void	broadcastToClients(Client * client, std::string msg);
};

#endif
