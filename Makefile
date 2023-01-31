# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 11:27:59 by bbrahim           #+#    #+#              #
#    Updated: 2023/01/31 17:27:34 by bbrahim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CXX = c++

FLAGS =  -Wall -Wextra -Werror -std=c++98

HEADERS = server client channel bot
MANDATORY_HEADERS := $(addprefix headers/, $(addsuffix .hpp, $(HEADERS)))

MAIN := main.cpp

CLASSES = Bot Channel Server Client Message
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