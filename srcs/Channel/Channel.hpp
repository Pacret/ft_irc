/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:50:08 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/18 08:54:34 by tmerrien         ###   ########.fr       */
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

class Channel
{
    private:
        Client _owner;
        std::string _channel_name;

        std::vector<Client *> operators;
        std::vector<Client *> clients;


    public:
        Channel(const Client &owner, const std::string &channel_name);
        ~Channel();

        void demote(Client& client);
        void promote(Client& client);

		std::string get_name();
		std::string get_mode();
		std::string get_mode_params();
		std::string get_nbrUsr();
		std::string get_topic();
};

#endif
