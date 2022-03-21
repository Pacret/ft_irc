/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:23:56 by pbonilla          #+#    #+#             */
/*   Updated: 2022/03/21 15:37:36 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int fd, struct sockaddr_in address) : fd(fd)
{
    (void)address;
}

Client::~Client()
{
    close(fd);
}

void    Client::get_message()
{
    char    buff[BUFFER_SIZE + 1];
    ssize_t    size;
    size_t  rn;

    if ((size = recv(fd, &buff, BUFFER_SIZE, 0)) == -1)
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
            std::cout << command << std::endl;
            send_message(); // test de la fonction send_message()
            // Traiter la commande, a voir comment, quels structures etc...
        } 
    }
}

void    Client::send_message() //Fonction juste pour montrer comment envoyer un message
{
    std::string message = "Message de test\r\n";

    if (send(fd, message.c_str(), message.size(), 0) == -1)
        std::cout << "Error: envois message" << std::endl;

}