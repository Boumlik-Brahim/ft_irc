/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Authentication.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 09:22:10 by iomayr            #+#    #+#             */
/*   Updated: 2023/02/05 11:45:06 by iomayr           ###   ########.fr       */
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
    tmpClient->setAuthValid(true);
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
			guestToClient(tmpGuest, newSocketFd);
		}
	}
}