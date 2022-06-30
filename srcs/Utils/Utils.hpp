/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:51:49 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/18 13:40:58 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <stdlib.h>
# include <vector>
# include <string>

enum Statut
{
	NONE,
    REGISTERED,
    CONNECTED
};

void	close_server(const std::string &msg_error);

std::vector<std::string>	string_split(std::string str, std::string const& delim);

#endif