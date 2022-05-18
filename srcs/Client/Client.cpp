/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:23:56 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/18 13:41:55 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

		Client::Client( int fd, struct sockaddr_in address) : fd(fd), _address(address), _statut(REGISTERED)
{
	return;
}

		Client::~Client()
{
    close(fd);
}

void		Client::check_passwd(const std::string &command)
{
	size_t pos = command.find(" ");
	std::string	pass_sent;

	if (!command.find("PASS"))
		pass_sent = command.substr(5);
	else
		return;
	if (pass_sent != )
		return;
	_statut = REGISTERED;
	
	return ;
}

void    Client::parse_command(const std::string &command)
{
	if (_statut == NONE)
		return (check_passwd(command));
    else if (_statut == REGISTERED)
    {
        size_t  pos = command.find(" ");

        if (!command.find("NICK"))
            _nick = command.substr(5);
        else if (!command.find("USER"))
        {
            _username = command.substr(5, (command.find(" ", pos + 1)) - 5);
            if (_nick != "") // todo: verifier qu'il n'y a pas un client ayant le meme nick
            {
                // Verifie t'on le hostname du client comme inspircd ?
                // send_message(":paco.com NOTICE * :*** Looking up your hostname...\r\n");
                set_statut(CONNECTED);
                send_message(std::string(":paco.com 001 ") + _nick + std::string(" :Welcome to the Internet Relay Network ") + _nick + std::string("!") + _nick + std::string("@127.0.0.1\r\n"));
                send_message(std::string(":paco.com 251 ") + _nick + std::string(" :There a users\r\n"));
                send_message(std::string(":paco.com 253 ") + _nick + std::string(" :There a users\r\n"));
                send_message(std::string(":paco.com 254 ") + _nick + std::string(" :There a users\r\n"));
                send_message(std::string(":paco.com 255 ") + _nick + std::string(" :There a users\r\n"));
                send_message(std::string(":paco.com 265 ") + _nick + std::string(" :There a users\r\n"));
                send_message(std::string(":paco.com 266 ") + _nick + std::string(" :There a users\r\n"));
                send_message(std::string(":paco.com 375 ") + _nick + std::string(" :paco.com message of the day\r\n"));
                send_message(std::string(":paco.com 372 ") + _nick + std::string(" :message of the day\r\n"));
                send_message(std::string(":paco.com 372 ") + _nick + std::string(" :message of the day\r\n"));
                send_message(std::string(":paco.com 376 ") + _nick + std::string(" :End of message of the day\r\n"));
            }
        }
    }
    if (_statut == CONNECTED)
    {
        std::cout << command << std::endl;
    }
}

void    Client::send_message(const std::string &message) //Fonction juste pour montrer comment envoyer un message
{
    std::cout << "Envois :" << message << std::endl;
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
            parse_command(command);
            //std::cout << "In get message " << command << "|" << std::endl;
            //send_message(); // test de la fonction send_message()
            // Traiter la commande, a voir comment, quels structures etc...
        } 
    }
}

int		Client::get_fd()
{
	return (this->fd);
}

Statut	Client::get_statut() {return (_statut);}

void	Client::set_statut(Statut statut)
{
	_statut = statut;
}
