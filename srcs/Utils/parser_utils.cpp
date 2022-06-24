/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:36:14 by tmerrien          #+#    #+#             */
/*   Updated: 2022/06/24 14:36:36 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

#include "../Client/Client.hpp"
#include "../Channel/Channel.hpp"

using namespace std;


string get_comand(string& msg)
{
	size_t i = 0;

	if (msg[i] == ':')
		i = msg.find(' ') + 1;
	return (msg.substr(i, msg.find(' ', i)));
}
