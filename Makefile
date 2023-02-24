NAME = ircserv

CXX = c++

FLAGS =  -Wall -Wextra -Werror -std=c++98 

HEADERS = server client channel Utils Guest Message
MANDATORY_HEADERS := $(addprefix headers/, $(addsuffix .hpp, $(HEADERS)))

MAIN := main.cpp

SRC := 	srcs/channelOperations/Invite.cpp srcs/channelOperations/Join.cpp srcs/channelOperations/Kick.cpp srcs/channelOperations/List.cpp \
		srcs/channelOperations/Mode.cpp srcs/channelOperations/Names.cpp srcs/channelOperations/Part.cpp srcs/channelOperations/Topic.cpp \
		srcs/classes/Channel.cpp srcs/classes/Server.cpp srcs/classes/Client.cpp srcs/classes/Message.cpp srcs/classes/Guest.cpp \
		srcs/connectionRegistration/GuestToClient.cpp srcs/connectionRegistration/Nick.cpp srcs/connectionRegistration/Pass.cpp \
		srcs/connectionRegistration/User.cpp srcs/connectionRegistration/Quit.cpp \
		srcs/sendingMessages/Notice.cpp srcs/sendingMessages/Privmsg.cpp \
		srcs/serviceQuery/Whois.cpp \
		srcs/bot/BotCmd.cpp \
		srcs/replies/erros.cpp srcs/replies/response.cpp \
		srcs/tools/ArgsHelpers.cpp srcs/tools/ChannelHelpers.cpp srcs/tools/ClientHelpers.cpp srcs/tools/MessageHelpers.cpp srcs/tools/Split.cpp \
		srcs/Backbone.cpp

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