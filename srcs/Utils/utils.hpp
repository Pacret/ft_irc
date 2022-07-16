/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:51:49 by pbonilla          #+#    #+#             */
/*   Updated: 2022/07/04 15:18:08 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <stdlib.h>
# include <vector>
# include <string>
# include <sstream>

std::vector<std::string>	string_split(std::string str, std::string const& delim);
std::string	&				string_to_lower(std::string &);
std::string					int_to_string(int code);

#endif