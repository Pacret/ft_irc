/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:59:10 by tmerrien          #+#    #+#             */
/*   Updated: 2022/06/24 15:22:56 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_HPP
# define PARSER_UTILS_HPP

# include "../Client/Client.hpp"

# include <string>
# include <vector>

using namespace std;

//pr_ means the function is used for parsing
//Functions that return pointers, return NULL means the information wasn't found

Client *pr_get_client(string& msg);

struct parse_t
{
	string original_msg;
	string cmd;
	string prefix;
	vector<string> args;
};


#endif