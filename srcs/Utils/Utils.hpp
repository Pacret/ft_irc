/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:51:49 by pbonilla          #+#    #+#             */
/*   Updated: 2022/05/17 14:36:45 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <stdlib.h>

enum Statut
{
    REGISTERED,
    CONNECTED
};

void    close_server(const std::string &msg_error);

#endif