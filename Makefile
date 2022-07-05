# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 20:59:10 by pbonilla          #+#    #+#              #
#    Updated: 2022/07/04 15:13:21 by pbonilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ircserv

SRCS		=	srcs/main.cpp 				\
				srcs/Server/Server.cpp		\
				srcs/Server/Context.cpp		\
				srcs/Client/Client.cpp		\
				srcs/Channel/Channel.cpp	\
				srcs/Utils/parser_utils.cpp \
				srcs/Utils/defines.cpp		\
				srcs/Utils/utils.cpp		
	
COMP		= c++

FLAGS		= -Wall -Wextra -Werror -fsanitize=address -std=c++98 

OBJS		= $(SRCS:.cpp=.o)

.cpp.o:
			$(COMP) -c $(FLAGS) $(FLAG) $< -o $(<:.cpp=.o)

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
