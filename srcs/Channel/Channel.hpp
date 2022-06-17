/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:50:08 by pbonilla          #+#    #+#             */
/*   Updated: 2022/06/11 22:41:20 by pbonilla         ###   ########.fr       */
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
		std::string _topic;

        std::vector<Client *> operators;
        std::vector<Client *> clients;


    public:
        Channel(Client *owner, const std::string &channel_name);
        ~Channel();

        
        int get_nbrClients();
        int get_nbrOps();
        int get_nbrUsers();
    
        std::vector<Client *> get_Users();
    
        void demote(Client& client);
        void promote(Client& client);

		std::string get_name();
		std::string get_mode();
		std::string get_mode_params();
		std::string get_topic();
};

#endif
