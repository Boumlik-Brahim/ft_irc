/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:22:27 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/05 11:59:33 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void Server::handleWhoIsCmd(Message &msg, int newSocketFd)
{
	(void)newSocketFd;
	if (!msg.getArgument().size())
		std::cout << "NO Nick Name Given" << std::endl;
	else
	{
		if (mapClients[newSocketFd]->getIsAuthValid())
		{
			for (std::map<int, Client*>::iterator it = mapClients.begin(); it != mapClients.end(); ++it)
			{
				if (!msg.getArgument().at(0).compare(it->second->getNickName()))
				{
					std::cout << "User     : " << it->second->getUserName() << std::endl;
					std::cout << "realName : " << it->second->getRealName() << std::endl;
				}
				else
					std::cout << "NO Nick Name found" << std::endl;
			}
		}	
		else
			std::cout << "You Need To register First" << std::endl;
	}
}

void parseMessageFormat(Message &msg, char **data)
{
	std::vector<std::string> args;
	std::string tmp;

	msg.setCommand(data[0]);
	free(data[0]);
	for (int i = 1; data[i]; i++)
	{
		if (data[i][0] == ':')
		{
			for (; data[i]; i++)
			{
				tmp += data[i];
				free(data[i]);
				if (data[i + 1])
					tmp += ' ';
			}
			args.push_back(tmp);
			break;
		}
		else
		{
			args.push_back(data[i]);
			free(data[i]);
		}
	}
	free(data);
	msg.setArguments(args);
}

void Server::backBone(std::string buffer, int newSocketFd)
{
	Message msg;
	char 	**data;

	data = ft_split(buffer.c_str(), ' ');
	parseMessageFormat(msg, data);
	if (!msg.getCommand().compare("PASS"))
		handlePassCmd(msg, newSocketFd);
	if (!msg.getCommand().compare("NICK"))
		handleNickCmd(msg, newSocketFd);
	if (!msg.getCommand().compare("USER"))
		handleUserCmd(msg, newSocketFd);
	if (!msg.getCommand().compare("WHOIS"))
	{
		handleWhoIsCmd(msg, newSocketFd);
	}
	// if (!msg.getCommand().compare("PRIVMSG"))
	// {
	// }
	// else
	// {
	// }
}