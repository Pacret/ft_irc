/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:47:26 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/20 14:05:51 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

		Server::Server()
{
    
}

		Server::Server(const std::string &port, const std::string &password) : port(port), password(password)
{
    
}

		Server::~Server()
{
    std::cout << "Fermeture du serveur" << std::endl;
    for (std::map<int, Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
        delete it->second;
    close(fd_socket);
}

void    Server::addClient()
{
    int fd_client;
    struct sockaddr_in client_adress;
    socklen_t len = sizeof(client_adress);

    if ((fd_client = accept(fd_socket, (struct sockaddr *)&client_adress, &len)) == -1)
        close_server("Error: accept");
    if (fcntl(fd_client, F_SETFL, O_NONBLOCK) == -1) // Non blocking socket
        close_server("Error: fcntl client");

    struct pollfd pfd;
	
    pfd.fd = fd_client;
    pfd.events = POLLIN;
    pfd.revents = 0;
    pollfds.push_back(pfd);

    clients[fd_client] = new Client(fd_client, client_adress);

	log_file << "Client " << inet_ntoa(client_adress.sin_addr) << ":" << ntohs(client_adress.sin_port) << " fd: " << fd_client << std::endl; 
}

void    Server::init()
{
	log_file.open("lol");
	if (!log_file)
		close_server("Error: Log file couldn't be created");
    if ((fd_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        close_server("Error: Open socket");
    if (fcntl(fd_socket, F_SETFL, O_NONBLOCK) == -1) // Non blocking socket
        close_server("Error: fcntl");

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(std::atoi(port.c_str()));
    server_address.sin_addr.s_addr = INADDR_ANY;

    if ((bind(fd_socket, (struct sockaddr *)&server_address, sizeof(server_address))) == -1)
        close_server("Error: Port already used please choose another one");
    if (listen(fd_socket, 128) == -1)
        close_server("Error: listen");
    
    struct pollfd pfd;
    pfd.fd = fd_socket;
    pfd.events = POLLIN;
    pfd.revents = 0;

    pollfds.push_back(pfd);
}

void    Server::send_message(int fd, const std::string &message) //Fonction juste pour montrer comment envoyer un message
{
    std::cout << "Envois :" << message << std::endl;
    if (send(fd, message.c_str(), message.size(), 0) == -1)
        std::cout << "Error: envois message" << std::endl;
}

std::string	Server::get_pwd()
{
	return (password);
}

void	Server::check_passwd(Client &client, const std::string &command)
{
	//size_t pos = command.find(" ");
	std::string	pass_sent;

	if (!command.find("PASS"))
		pass_sent = command.substr(5);
	else
		return;
	if (pass_sent != get_pwd())
	{
		kill_connection(client);
		return;
	}
	client.set_statut(REGISTERED);
	
	return ;
}

void    Server::join_channel(Client *client, const std::string &channel_name)
{
    if (channels.find(channel_name) == channels.end())
    {
        channels[channel_name] = new Channel(client, channel_name);
        std::vector<Client *> usrs = channels[channel_name]->get_Users();
    
        for(unsigned long int i = 0; i < usrs.size(); i++)
        {
            send_message(usrs[i]->get_fd(), std::string(":" + client->_nick + "!" +  client->_nick + "@127.0.0.1 JOIN :" + channel_name + "\r\n"));
        }

    }
}

void    Server::parse_command(Client *client, const std::string &command)
{
	if (client->get_statut() == NONE)
		check_passwd(*client, command);
    else if (client->_statut == REGISTERED)
    {
        size_t  pos = command.find(" ");

        if (!command.find("NICK "))
            client->_nick = command.substr(5);
        else if (!command.find("USER "))
        {
            client->_username = command.substr(5, (command.find(" ", pos + 1)) - 5);
            if (client->_nick != "") // todo: verifier qu'il n'y a pas un client ayant le meme nick
            {
                // Verifie t'on le hostname du client comme inspircd ?
                // send_message(":paco.com NOTICE * :*** Looking up your hostname...\r\n");
                client->set_statut(CONNECTED);
                send_message(client->get_fd(), std::string(":paco.com 001 ") + client->_nick + std::string(" :Welcome to the Internet Relay Network ") + client->_nick + std::string("!") + client->_nick + std::string("@127.0.0.1\r\n"));
                send_message(client->get_fd(), std::string(":paco.com 251 ") + client->_nick + std::string(" :There a users\r\n"));
                send_message(client->get_fd(), std::string(":paco.com 253 ") + client->_nick + std::string(" :There a users\r\n"));
                send_message(client->get_fd(), std::string(":paco.com 254 ") + client->_nick + std::string(" :There a users\r\n"));
                send_message(client->get_fd(), std::string(":paco.com 255 ") + client->_nick + std::string(" :There a users\r\n"));
                send_message(client->get_fd(), std::string(":paco.com 265 ") + client->_nick + std::string(" :There a users\r\n"));
                send_message(client->get_fd(), std::string(":paco.com 266 ") + client->_nick + std::string(" :There a users\r\n"));
                send_message(client->get_fd(), std::string(":paco.com 375 ") + client->_nick + std::string(" :paco.com message of the day\r\n"));
                send_message(client->get_fd(), std::string(":paco.com 372 ") + client->_nick + std::string(" :message of the day\r\n"));
                send_message(client->get_fd(), std::string(":paco.com 372 ") + client->_nick + std::string(" :message of the day\r\n"));
                send_message(client->get_fd(), std::string(":paco.com 376 ") + client->_nick + std::string(" :End of message of the day\r\n"));
            }
        }
    }
    if (client->_statut == CONNECTED)
    {
        if (!command.find("PING "))
            std::cout << std::endl;
        else if (!command.find("JOIN "))
            join_channel(client, command.substr(5));

        std::cout << command << std::endl;
    }
}

void    Server::get_message(Client *client)
{
    char    buff[BUFFER_SIZE + 1];
    ssize_t    size;
    size_t  rn;

    std::cout << "crasp" << std::endl;
    if ((size = recv(client->get_fd(), &buff, BUFFER_SIZE, 0)) == -1) //?? Should be a while? Need to check max size IRC REQUEST
        return;
    if (!size)
        return;
    buff[size] = 0;
    client->buffer += buff;
    std::cout << "crsdefklhjesadf" << std::endl;

    while ((rn = client->buffer.find("\r\n")) != std::string::npos)
    {
        std::string command = client->buffer.substr(0, rn);
        client->buffer.erase(0, rn + 2);
        if (command.size())
        {
            std::cout << std::endl;
            parse_command(client, command);
        } 
    }
}

void    Server::process()
{
	// int test = 0;

    while (1)
    {
        if (poll(&pollfds[0], pollfds.size(), -1) == -1)
            close_server("Error: poll");
        if (pollfds[0].revents == POLLIN)
            addClient();
        else
        {
            for (std::vector<struct pollfd>::iterator it = pollfds.begin(); it != pollfds.end(); ++it)
                if ((*it).revents == POLLIN)
                    get_message(clients[(*it).fd]);

        }
        std::cout << pollfds[0].revents << std::endl;
		std::cout << "here\n" << std::endl;
    }
}

void    Server::setPort(const std::string &port)
{
    this->port = port;
}

void    Server::setPassword(const std::string &password)
{
    this->password = password;
}

void	Server::kill_connection(Client& client)
{
	std::vector<struct pollfd>::iterator it = pollfds.begin();

	while ((*it).fd != client.get_fd())
		++it;
	pollfds.erase(it);
	close(client.get_fd());
	client.~Client();
	return;
}

// void	Server::register_client(Client& client, const std::string& msg_rcv)
// {
	
// 	if (password.length() == 0)
// 	{
// 		client.set_statut(REGISTERED);
// 		return;
// 	}
// 	//if (())
// }
