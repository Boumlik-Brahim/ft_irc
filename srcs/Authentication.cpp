/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Authentication.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void Server::handlePassCmd(Message &msg, int newSocketFd)
{
	Guest *tmpGuest = _mapGuest[newSocketFd];
			
	if (!msg.getArgument().size())
		errorHandler(newSocketFd, 461, "PASS");
	else
	{
		if (msg.getArgument().at(0).compare(getPassword()))
			errorHandler(newSocketFd, 464);
		else
			tmpGuest->setPassValid(true);
	}
}

void Server::handleNickCmd(Message &msg, int newSocketFd)
{
	Guest *tmpGuest = _mapGuest[newSocketFd];
	
    if (!msg.getArgument().size())
		errorHandler(newSocketFd, 431);	
	else if (tmpGuest->getPassValid())
	{
		for (std::map<int, Client*>::iterator it = _mapClients.begin(); it != _mapClients.end(); ++it)
		{
			if (!it->second->getNickName().compare(msg.getArgument().at(0)))
			{
				errorHandler(newSocketFd, 436 ,it->second->getNickName());
				return ;
			}
		}
		if (!isalpha(msg.getArgument().at(0).at(0)) || msg.getArgument().at(0).size() > 8)
			errorHandler(newSocketFd, 432, msg.getArgument().at(0));
		else{
			if (!_mapClients[newSocketFd]->getNickName().compare(""))
			{
				tmpGuest->setGuestNick(msg.getArgument().at(0));
				if (_mapGuest[newSocketFd]->getUserValid())
					guestToClient(tmpGuest, newSocketFd);
			}
			else
				_mapClients[newSocketFd]->setNickName(msg.getArgument().at(0));
			tmpGuest->setNickValid(true);
		}		
	}
	else
		errorHandler(newSocketFd, 464);
}

void Server::guestToClient(Guest *tmpGuest, int newSocketFd)
{
	Client *tmpClient = _mapClients[newSocketFd];
	
	tmpClient->setNickName(tmpGuest->getGuestNick()); 
	tmpClient->setUserName(tmpGuest->getGuestUser()); 
	tmpClient->setRealName(tmpGuest->getGuestRealName()); 
    tmpClient->setAuthValid(true);
}

void Server::handleUserCmd(Message &msg, int newSocketFd)
{
	Guest *tmpGuest = _mapGuest[newSocketFd];
	
	if (msg.getArgument().size() < 4)
		errorHandler(newSocketFd, 461, "USER");
	else if (!tmpGuest->getPassValid())
		errorHandler(newSocketFd, 464);
	else
	{
		if (!isalpha(msg.getArgument().at(0).at(0)) && !isnumber(msg.getArgument().at(0).at(0)))
			errorHandler(newSocketFd, 432, msg.getArgument().at(0));
		else{
			if (!_mapClients[newSocketFd]->getUserName().compare("")){
				tmpGuest->setGuestUser(msg.getArgument().at(0));
				tmpGuest->setGuestRealName(msg.getArgument().at(3));
				if (_mapGuest[newSocketFd]->getNickValid())
					guestToClient(tmpGuest, newSocketFd);
			}
			else{
				_mapClients[newSocketFd]->setUserName(msg.getArgument().at(0));
				_mapClients[newSocketFd]->setRealName(msg.getArgument().at(3));
			}
			tmpGuest->setUserValid(true);
		}
	}
}

void Server::handleWhoIsCmd(Message &msg, int newSocketFd)
{
	if (!msg.getArgument().size())
		errorHandler(newSocketFd, 431);
	else
	{
		if (_mapClients[newSocketFd]->getIsAuthValid())
		{
			for (std::map<int, Client*>::iterator it = _mapClients.begin(); it != _mapClients.end(); ++it)
			{
				if (!msg.getArgument().at(0).compare(it->second->getNickName()))
				{
					cmd_Resp_Handler(newSocketFd, 311, it->second->getNickName(),\
						it->second->getUserName(), it->second->getRealName());
					break;
				}
				if (it == --_mapClients.end() && msg.getArgument().at(0).compare(it->second->getNickName())) 
					errorHandler(newSocketFd, 401, msg.getArgument().at(0));
			}
		}	
		else
        	errorHandler(newSocketFd , 451);
	}

}