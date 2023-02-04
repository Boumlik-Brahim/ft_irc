/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:22:27 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/04 17:17:33 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void Server::handlePassCmd(Message &msg, int newSocketFd)
{
	Guest *tmpGuest = _mapGuest[newSocketFd];
			
	if (msg.getArgument().size() > 1)
		std::cout << "A lot of Arguments" << std::endl;
	else if (!msg.getArgument().size())
		std::cout << "Need more Arguments" << std::endl;
	else
	{
		if (msg.getArgument().at(0).compare(getPassword()))
			std::cout << "Invalid password" << std::endl;
		else
			tmpGuest->setPassValid(true);
	}
}

void Server::handleNickCmd(Message &msg, int newSocketFd)
{
	Guest *tmpGuest = _mapGuest[newSocketFd];
			
	if (tmpGuest->getPassValid())
	{
		for (std::map<int, Client*>::iterator it = mapClients.begin(); it != mapClients.end(); ++it)
		{
			std::cout << "--------> " << it->second->getNickName() << std::endl;
			if (!it->second->getNickName().compare(msg.getArgument().at(0)))
			{
				std::cout << "This Nick Already Used" << std::endl;
				return ;
			}
		}
		if (msg.getArgument().at(0).size() > 8 || msg.getArgument().at(0).size() < 1)
			std::cout << "check the Lenght of the Nickname" << std::endl;
		else if (!isalpha(msg.getArgument().at(0).at(0)))
			std::cout << "First character in Nickname Invalid " << std::endl;
		else
		{
			tmpGuest->setGuestNick(msg.getArgument().at(0));
			tmpGuest->setNickValid(true);
		}		
	}
	else
		std::cout << "You Need To Enter Pass First" << std::endl;
}

void Server::guestToClient(Guest *tmpGuest, int newSocketFd)
{
	Client *tmpClient = mapClients[newSocketFd];
	
	tmpClient->setNickName(tmpGuest->getGuestNick()); 
	tmpClient->setUserName(tmpGuest->getGuestUser()); 
	tmpClient->setRealName(tmpGuest->getGuestRealName()); 
}

void Server::handleUserCmd(Message &msg, int newSocketFd)
{
	Guest *tmpGuest = _mapGuest[newSocketFd];
	
	if (msg.getArgument().size() < 4)
		std::cout << "Need more arguments" << std::endl;
	else if (!tmpGuest->getPassValid() || !tmpGuest->getNickValid())
		std::cout << "You Need to enter Pass and Nick First" << std::endl;
	else
	{
		if (!isalpha(msg.getArgument().at(0).at(0)) && !isnumber(msg.getArgument().at(0).at(0)))
			std::cout << "First character in UserName Invalid " << std::endl;
		else{
			tmpGuest->setGuestUser(msg.getArgument().at(0));
			tmpGuest->setGuestRealName(msg.getArgument().at(3));
			tmpGuest->setAuthValid(true);
			guestToClient(tmpGuest, newSocketFd);
		}
	}
	std::cout << tmpGuest->getGuestRealName() << std::endl;
	std::cout << tmpGuest->getGuestUser() << std::endl;
}


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

void Server::backBone(std::string buffer, int newSocketFd)
{
	(void)new_socket_fd;
	Message msg;
	char **data;

	data = ft_split(buffer.c_str(), ' ');
	parseMessageFormat(msg, data);
	if (!msg.getCommand().compare("PASS"))
	{
	    // std::cout << "i got the pass" << std::endl;
		handlePassCmd(msg, newSocketFd);
	}
	if (!msg.getCommand().compare("NICK"))
	{
	    // std::cout << "i got the nick" << std::endl;
		handleNickCmd(msg, newSocketFd);
	}
	if (!msg.getCommand().compare("USER"))
	{
	    std::cout << "i got the user" << std::endl;
		handleUserCmd(msg, newSocketFd);
		std::cout << "this is the Size ----> " << mapClients[newSocketFd]->getNickName() << std::endl;
	}
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