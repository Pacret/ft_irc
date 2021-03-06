/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:23:22 by pbonilla          #+#    #+#             */
/*   Updated: 2022/07/17 15:35:38 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Server.hpp"
#include <iostream>

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cout << "Usage : ./ircserv <port> <password>" << std::endl;
        return (1);
    }

    Server server(av[1], av[2]);
    server.init();
    server.process();
    return (0);
}