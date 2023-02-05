# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 11:27:59 by bbrahim           #+#    #+#              #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CXX = c++

FLAGS =  -Wall -Wextra -Werror -std=c++98

HEADERS = server client channel bot Utils Guest
MANDATORY_HEADERS := $(addprefix headers/, $(addsuffix .hpp, $(HEADERS)))

MAIN := main.cpp

CLASSES = Bot Channel Server Client Message Command Errors_replies Command_responses Split Guest Authentication
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