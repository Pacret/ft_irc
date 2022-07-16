# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 20:59:10 by pbonilla          #+#    #+#              #
#    Updated: 2022/07/16 19:47:08 by tmerrien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ircserv

SRCS		=	srcs/main.cpp 				\
				srcs/Server/Server.cpp		\
				srcs/Server/Context.cpp		\
				srcs/Client/Client.cpp		\
				srcs/Channel/Channel.cpp	\
				srcs/Client/Bot.cpp			\
				srcs/Utils/parser_utils.cpp \
				srcs/Utils/defines.cpp		\
				srcs/Utils/utils.cpp		
	
COMP		= c++

FLAGS		= -Wall -Wextra -Werror -std=c++98 

VAL			=	valgrind

VALF		=	--tool=memcheck --leak-check=full --leak-resolution=high \
				--show-reachable=yes --track-origins=yes --log-file=valgrind_log \
				--xtree-memory=full

OBJS		= $(SRCS:.cpp=.o)

.cpp.o:
			$(COMP) -c $(FLAGS) $(FLAG) $< -o $(<:.cpp=.o)

RM			= rm -rf

all: $(NAME)

$(NAME): ${OBJS}
	 $(COMP) $(FLAGS) $(OBJS) -o $(NAME)

leaks: $(NAME)
		echo "Launching server with Valgrind all leaks enabled"
		$(VAL) $(VALF) ./$(NAME) 4241 mdp
		grep -A1 "valgrind" valgrind_log | grep $(NAME) || echo -n

debugflag:
		$(eval FLAGS=-D DEBUG)

debug: debugflag run

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
