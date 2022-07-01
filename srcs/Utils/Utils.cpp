/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:53:10 by pbonilla          #+#    #+#             */
/*   Updated: 2022/03/19 14:20:07 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

void    close_server(const std::string &msg_error)
{
    std::cerr << msg_error << std::endl;
    exit(EXIT_FAILURE);
}

std::vector<std::string>	string_split(std::string str, std::string const& delim)
{
	std::vector<std::string>	ret;
	size_t						pos;

	while ((pos = str.find(delim)) != std::string::npos)
	{
		ret.push_back(str.substr(0, pos));
		str.erase(0, pos + delim.size());
	}
	if (!str.empty())
		ret.push_back(str);
	return ret;
}