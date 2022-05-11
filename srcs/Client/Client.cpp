/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:23:56 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/11 13:46:38 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "../Server/Server.hpp"

		Client::Client(int fd, struct sockaddr_in address) : fd(fd), _address(address), _registered(false)
{
	return;
}

		Client::~Client()
{
    close(fd);
}

void    Client::send_message() //Fonction juste pour montrer comment envoyer un message
{
    std::string message = "blip bloup\n";

    if (send(fd, message.c_str(), message.size(), 0) == -1)
        std::cout << "Error: envois message" << std::endl;

}

void    Client::get_message()
{
    char    buff[BUFFER_SIZE + 1];
    ssize_t    size;
    size_t  rn;

    if ((size = recv(fd, &buff, BUFFER_SIZE, 0)) == -1) //?? Should be a while? Need to check max size IRC REQUEST
        return;
    if (!size)
        return;
    buff[size] = 0;
    buffer += buff;

    while ((rn = buffer.find("\r\n")) != std::string::npos)
    {
        std::string command = buffer.substr(0, rn);
        buffer.erase(0, rn + 2);
        if (command.size())
        {
            std::cout << "In get message " << command << std::endl;
            send_message(); // test de la fonction send_message()
            // Traiter la commande, a voir comment, quels structures etc...
        } 
    }
}

int		Client::get_fd()
{
	return (this->fd);
}

bool	Client::get_registered() {return (_registered);}
void	Client::set_registered(bool status)
{
	_registered = status;
}