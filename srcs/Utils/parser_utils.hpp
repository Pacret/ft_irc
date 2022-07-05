/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:59:10 by tmerrien          #+#    #+#             */
/*   Updated: 2022/06/28 21:39:17 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_HPP
# define PARSER_UTILS_HPP

# include <string>
# include <vector>
# include <iostream>

using namespace std;

struct parse_t
{
	string original_msg;
	string cmd;
	string prefix;
	string msg_to_send;
	vector<string> args;
};


// Fill the structure, args are sequencial and separated by every space found, except when entering a trailling,
// if trailling is found then all the rest of the string is put into it. Function throw and error if partial data is found.
parse_t		*fill_parse_t(string &msg);
string		get_command(const string& msg);
void		print_parse_t(const parse_t& p);



#endif