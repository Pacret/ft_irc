/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:36:14 by tmerrien          #+#    #+#             */
/*   Updated: 2022/06/26 16:57:43 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

#include "../Client/Client.hpp"
#include "../Channel/Channel.hpp"
#include "parser_utils.hpp"

using namespace std;


string get_comand(const string& msg)
{
	size_t i = 0;

	if (msg[i] == ':')
		i = msg.find(' ') + 1;
	return (msg.substr(i, msg.find(' ', i)));
}

// get_prefix does not include the ':' starting the prefix.
string get_prefix(string &msg)
{
	size_t i = msg.find(" ");
	return (msg.substr(1, i));
}

parse_t *fill_parse_t(string &msg)
{
	parse_t *p = new parse_t;

	p->original_msg = msg;
	if (msg[0] == ':')
	{
		p->prefix = get_prefix(msg);
		msg.erase(0, p->prefix.size() + 1);
	}
	p->cmd = get_comand(msg);
	msg.erase(0, p->cmd.size());

	string end_set = "\r\n\0";
	while (msg[0] != '\0' && msg[0] != '\r' && msg[0] != '\n')
	{
		msg.erase(0, 1);
		if (msg[0] == ':')
		{
			p->args.push_back(msg.substr(0, msg.find_first_of(end_set)));
			msg.erase(0, p->args.back().size());
			break;
		}
		p->args.push_back(msg.substr(0, msg.find_first_of(" " + end_set)));
		msg.erase(0, p->args.back().size());
	}
	if (msg.size() < 2 || msg[0] != '\r' || msg[1] != '\n')
		throw runtime_error("Bad data: Partial Data received");
	return (p);
}
