# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 10:08:15 by bbrahim           #+#    #+#              #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CXX = c++

FLAGS =  -Wall -Wextra -Werror -std=c++98 -fsanitize=address

HEADERS = server client channel bot Utils Guest Message
MANDATORY_HEADERS := $(addprefix headers/, $(addsuffix .hpp, $(HEADERS)))

MAIN := main.cpp


CLASSES = Bot Channel Server Client Message Command Errors_replies Command_responses Split Guest Authentication ChannelCmd ModeCmd ChannelCommands

SRC := $(addprefix srcs/, $(addsuffix .cpp, $(CLASSES)))

OBJ = $(SRC:.cpp=.o)

%.o: %.cpp $(MANDATORY_HEADERS)
	$(CXX) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(MAIN) $(MANDATORY_HEADERS) $(OBJ)
	$(CXX) $(FLAGS) $(MAIN) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:		all clean fclean re