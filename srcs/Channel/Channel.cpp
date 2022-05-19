/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:47:26 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/18 14:47:56 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

		Channel::Channel(const Client &owner, const std::string &channel_name): _owner(owner), _channel_name(channel_name)
{
	return;
}

		Channel::~Channel()
{
    std::cout << "aurevoir channel" << std::endl;
}

std::string		Channel::get_name()
{
	return (_channel_name);
}