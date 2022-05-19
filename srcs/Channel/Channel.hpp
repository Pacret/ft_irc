/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:50:08 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/20 00:28:18 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <fstream>
# include <stdlib.h>
# include <vector>

# include "../Utils/Utils.hpp"
# include "../Client/Client.hpp"

class Channel
{
    private:

        Client *_owner;
        std::string _channel_name;

        std::vector<Client *> operators;
        std::vector<Client *> clients;


    public:
        Channel(Client *owner, const std::string &channel_name);
        ~Channel();

        
        int get_users_count();
        int get_ops_count();

        void demote(Client& client);
        void promote(Client& client);

		std::string get_name();
		std::string get_mode();
		std::string get_mode_params();
		int get_nbrUsers();
		std::string get_topic();
};

#endif
