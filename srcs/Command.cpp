/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:22:27 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/03 10:45:55 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void sendMessage(int fd, std::string message)
{
	size_t i = 0;
	while (i != message.length())
		i += send(fd, message.c_str(), message.length() - i, 0);
}

// void checkPrivateMsg(int senderFd, Message &msg)
// {
// 	// (void)senderFd;

// 	std::string receiver = msg.getArgument()[0];
// 	// std::cout << "Receiver == " << receiver << std::endl;
// 	/* check if receiver is a client */
// 	// std::cout << "size --" << msg.getArgument().size() << std::endl;
// 	/* reply sender with ERR_NOTEXTTOSEND message */
// 	if (msg.getArgument().size() < 2)
// 		sendMessage(senderFd, ERR_NOTEXTTOSEND);

// 	for (unsigned long i = 1; i < msg.getArgument().size(); i++)
// 		std::cout << "-- " << msg.getArgument()[i] << std::endl;

// 	std::string newMessage;
// 	// char **newMessage;
// 	std::cout << "--------" << msg.getArgument()[1][0] << std::endl;
// 	// if (msg.getArgument()[1].c_str() == ":")
// 	// {
// 	//     int n = 0;

// 	// }
// }

// void checkNotice(Message &msg, int sender_fd)
// {
// 	(void)sender_fd;
// 	std::vector<std::string> clients;
// 	std::string msgtarget;

// 	msgtarget = msg.getArgument()[0];
// 	std::cout << "msgtarget is ====>" << msgtarget << std::endl;
// 	for (std::map<int, Client *>::iterator it = mapClients.begin(); it != mapClients.end(); ++it)
// 	{
// 		std::cout << "msgargument is ====>" << it->second << std::endl;
// 		if (msgtarget != it->second->getNickName())
// 		{
// 			std::cout << "makaynch";
// 			sendMessage(sender_fd, ERR_NORECIPIENT);
// 			break;
// 		}
// 	}
// 	if (msg.getArgument().size() < 2)
// 	{
// 		sendMessage(sender_fd, ERR_NOTEXTTOSEND);
// 		return;
// 	}
// }

void parseMessageFormat(Message &msg, char **data)
{
	std::vector<std::string> args;
	std::string tmp;

	msg.setCommand(data[0]);
	for (int i = 1; data[i]; i++)
	{
		if (data[i][0] == ':')
		{
			for (; data[i]; i++)
			{
				tmp += data[i];
				if (data[i + 1])
					tmp += ' ';
			}
			args.push_back(tmp);
			break;
		}
		else
			args.push_back(data[i]);
	}
	msg.setArguments(args);
}

void Server::backBone(std::string buffer, int new_socket_fd)
{
	(void)new_socket_fd;
	Message msg;
	char **data;

	data = ft_split(buffer.c_str(), ' ');
	parseMessageFormat(msg, data);
	// if (!msg.getCommand().compare("PASS"))
	// {
	//     std::cout << "i got the pass" << std::endl;
	// }
	// if (!msg.getCommand().compare("NICK"))
	// {
	//     std::cout << "i got the nick" << std::endl;
	// }
	// if (!msg.getCommand().compare("USER"))
	// {
	//     std::cout << "i got the user" << std::endl;
	// }
	// if (!msg.getCommand().compare("NOTICE"))
	// {
	// }
	// if (!msg.getCommand().compare("PRIVMSG"))
	// {
	// }
	// else
	// {
	// }
}