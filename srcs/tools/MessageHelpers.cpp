#include "../../headers/Server.hpp"

void sendMessage(int fd, std::string message)
{
	size_t i = 0;
	message += "\r\n";
	while (i != message.length())
		i += send(fd, message.c_str(), message.length() - i, 0);
}

void sendReplay(int fd, std::string message)
{
	size_t i = 0;
	while (i != message.length())
		i += send(fd, message.c_str(), message.length() - i, 0);
}