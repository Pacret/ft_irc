/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:36:14 by tmerrien          #+#    #+#             */
/*   Updated: 2022/06/28 21:37:21 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.hpp"

std::string get_command(const std::string& msg)
{
	size_t i = 0;

	if (msg[i] == ':')
		i = msg.find(' ') + 1;
	return (msg.substr(i, msg.find(' ', i)));
}

// get_prefix does not include the ':' starting the prefix.
std::string get_prefix(std::string &msg)
{
	size_t i = msg.find(" ");
	return (msg.substr(1, i));
}

parse_t *fill_parse_t(std::string &msg)
{
	std::cout << msg << std::endl;
	parse_t *p = new parse_t;

	p->original_msg = msg;
	if (msg[0] == ':')
	{
		p->prefix = get_prefix(msg);
		msg.erase(0, p->prefix.size() + 1);
	}
	p->cmd = get_command(msg);
	msg.erase(0, p->cmd.size());

	std::string end_set = "\r\n\0";
	while (msg[0] != '\0')
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
	//if (msg.size() < 2 || msg[0] != '\r' || msg[1] != '\n')
	//	throw runtime_error("Bad data: Partial Data received");
	print_parse_t(*p);
	return (p);
}

void	print_parse_t(const parse_t & p)
{
	std::vector<std::string>::const_iterator it = p.args.begin();
	std::vector<std::string>::const_iterator ite = p.args.end();

	std::cout << "============== print parse_t ===============" << std::endl;
	std::cout << "-> Original msg {" << p.original_msg << "}" << std::endl;
	std::cout << "-> cmd {"<< p.cmd << "}" << std::endl;
	std::cout << "-> prefix {" << p.prefix << "}" << std::endl;
	std::cout << "-> msg_to_send {" << p.msg_to_send << "}" << std::endl;

	for (int i = 0; it != ite; it++, i++)
		std::cout << "-> args[" << i << "] {" << *it << "}" << std::endl;
	std::cout << "=========== print parse_t end ==============" << std::endl;

}
