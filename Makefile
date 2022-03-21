# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 20:59:10 by pbonilla          #+#    #+#              #
#    Updated: 2022/03/20 17:22:14 by pbonilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ircserv

SRCS		=	srcs/main.cpp \
				srcs/Server/Server.cpp \
				srcs/Utils/Utils.cpp \
				srcs/Client/Client.cpp

CXX		= c++

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

OBJS		= $(SRCS:.cpp=.o)

RM		= rm -rf

all: $(NAME)

$(NAME): ${OBJS}
	 $(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
