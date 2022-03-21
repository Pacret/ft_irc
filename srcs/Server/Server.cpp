/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:47:26 by pbonilla          #+#    #+#             */
/*   Updated: 2022/03/21 15:37:41 by pbonilla         ###   ########.fr       */
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
    for (std::map<int, Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
        delete it->second;
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
}

void    Server::init()
{
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

void    Server::process()
{
    while (1)
    {
        if (poll(&pollfds[0], pollfds.size(), 1000) == -1)
            close_server("Error: poll");
        if (pollfds[0].revents == POLLIN)
            addClient();
        else
        {
            for (std::vector<struct pollfd>::iterator it = pollfds.begin(); it != pollfds.end(); ++it)
                if ((*it).revents == POLLIN)
                    clients[(*it).fd]->get_message();
        }
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