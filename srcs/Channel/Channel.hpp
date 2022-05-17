/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:50:08 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/17 13:19:24 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <fstream>
# include <stdlib.h>
# include <vector>

# include "../Utils/Utils.hpp"
# include "../Server/Server.hpp"
# include "../Client/Client.hpp"
# include "../Utils/defines.h"

class Server;

class Channel
{
    private:
        Server &_server;
        Client _owner;
        std::string _channel_name;

        std::vector<Client *> operators;
        std::vector<Client *> clients;


    public:
        Channel(Server &server, const Client &owner, const std::string &channel_name);
        ~Channel();

        
        int get_users_count();
        int get_ops_count();

        void demote(Client& client);
        void promote(Client& client);

        std::string get_name();
};

#endif
