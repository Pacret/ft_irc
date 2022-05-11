# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 20:59:10 by pbonilla          #+#    #+#              #
#    Updated: 2022/05/11 09:01:27 by tmerrien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ircserv

SRCS		=	srcs/main.cpp 			\
				srcs/Server/Server.cpp	\
				srcs/Utils/Utils.cpp	\
				srcs/Client/Client.cpp	\

COMP		= c++

FLAGS		= -Wall -Wextra -Werror -std=c++98

OBJS		= $(SRCS:.cpp=.o)

RM			= rm -rf

all: $(NAME)

$(NAME): ${OBJS}
	 $(COMP) $(FLAGS) $(OBJS) -o $(NAME) 

debugflag:
		$(eval FLAGS=-D DEBUG)

debug: debugflag run

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
