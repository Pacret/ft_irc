/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:59:10 by tmerrien          #+#    #+#             */
/*   Updated: 2022/06/25 19:55:28 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_HPP
# define PARSER_UTILS_HPP

# include "../Client/Client.hpp"

# include <string>
# include <vector>

using namespace std;

struct parse_t
{
	string original_msg;
	string cmd;
	string prefix;
	vector<string> args;
};

parse_t *fill_parse_t(string &msg);


#endif