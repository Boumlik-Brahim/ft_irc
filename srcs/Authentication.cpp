/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Authentication.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:30:17 by iomayr            #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void Server::handlePassCmd(Message &msg, int newSocketFd)
{
	Guest *tmpGuest = _mapGuest[newSocketFd];
			
	if (!msg.getArguments().size())
		errorHandler(newSocketFd, 461, "PASS");
	else
	{
		if (msg.getArguments().at(0).compare(getPassword()))
		{
			std::cout << msg.getArguments().at(0).size() << std::endl;	
			errorHandler(newSocketFd, 464);
		}
		else
			tmpGuest->setPassValid(true);
	}
}

void Server::handleNickCmd(Message &msg, int newSocketFd)
{
	Guest *tmpGuest = _mapGuest[newSocketFd];
	
    if (!msg.getArguments().size())
		errorHandler(newSocketFd, 431);	
	else if (tmpGuest->getPassValid())
	{
		for (std::map<int, Client*>::iterator it = _mapClients.begin(); it != _mapClients.end(); ++it)
		{
			if (!it->second->getNickName().compare(msg.getArguments().at(0)))
				errorHandler(newSocketFd, 436 ,it->second->getNickName());
		}
		if (!isalpha(msg.getArguments().at(0).at(0)) || msg.getArguments().at(0).size() > 8)
			errorHandler(newSocketFd, 432, msg.getArguments().at(0));
		else{
			if (!_mapClients[newSocketFd]->getNickName().compare(""))
			{
				tmpGuest->setGuestNick(msg.getArguments().at(0));
				tmpGuest->setNickValid(true);
				if (_mapGuest[newSocketFd]->getUserValid())
					guestToClient(tmpGuest, newSocketFd);
			}
			else{
				_mapClients[newSocketFd]->setNickName(msg.getArguments().at(0));
				tmpGuest->setNickValid(true);
			}
		}		
	}
	else
	{
		errorHandler(newSocketFd, 464);	
	}
}

void Server::guestToClient(Guest *tmpGuest, int newSocketFd)
{
	Client *tmpClient = _mapClients[newSocketFd];
	std::map<int, Guest*>::iterator it;
	
	tmpClient->setNickName(tmpGuest->getGuestNick()); 
	tmpClient->setUserName(tmpGuest->getGuestUser()); 
	tmpClient->setRealName(tmpGuest->getGuestRealName()); 
  tmpClient->setAuthValid(true);
  WelcomeMsg(newSocketFd);
	it = _mapGuest.find(newSocketFd);
	if (it != _mapGuest.end()){
		delete it->second;
		_mapGuest.erase(it);
	}
}

void Server::handleUserCmd(Message &msg, int newSocketFd)
{
	Guest *tmpGuest = _mapGuest[newSocketFd];
	
	if (msg.getArguments().size() < 4)
		errorHandler(newSocketFd, 461, "USER");
	else if (!tmpGuest->getPassValid()){
		errorHandler(newSocketFd, 464);
	}
	else{
		if (!isalpha(msg.getArguments().at(0).at(0)) && !isnumber(msg.getArguments().at(0).at(0)))
			errorHandler(newSocketFd, 432, msg.getArguments().at(0));
		else{
			if (!_mapClients[newSocketFd]->getUserName().compare("")){
				tmpGuest->setGuestUser(msg.getArguments().at(0));
				tmpGuest->setGuestRealName(msg.getArguments().at(3));
				tmpGuest->setUserValid(true);
				if (_mapGuest[newSocketFd]->getNickValid())
					guestToClient(tmpGuest, newSocketFd);
			}
			else{
				_mapClients[newSocketFd]->setUserName(msg.getArguments().at(0));
				_mapClients[newSocketFd]->setRealName(msg.getArguments().at(3));
				tmpGuest->setUserValid(true);
			}
		}
	}
}

void Server::handleWhoIsCmd(Message &msg, int newSocketFd)
{
	if (!msg.getArguments().size())
		errorHandler(newSocketFd, 431);
	else
	{
		if (_mapClients[newSocketFd]->getIsAuthValid())
		{
			for (std::map<int, Client*>::iterator it = _mapClients.begin(); it != _mapClients.end(); ++it)
			{
				if (!msg.getArguments().at(0).compare(it->second->getNickName()))
				{
					cmd_Resp_Handler(newSocketFd, 311, it->second->getNickName(),\
						it->second->getUserName(), it->second->getRealName());
					break;
				}
				if (it == --_mapClients.end() && msg.getArguments().at(0).compare(it->second->getNickName())) 
					errorHandler(newSocketFd, 401, msg.getArguments().at(0));
			}
		}	
		else
        	errorHandler(newSocketFd , 451);
	}
                                                                                              
}

void Server::handleQuitCmd(int newSocketFd)
{
	std::map<int, Client*>::iterator	itClient = _mapClients.find(newSocketFd);
	std::string 						clientNick = itClient->second->getNickName();
	std::vector<std::string> 			chnlVec = itClient->second->getJoinedChannels();
	
	for (std::vector<std::string>::iterator	it = chnlVec.begin(); it != chnlVec.end(); it++)
	{
		Channel &tmpChnl = findChannel(*it);
		for (std::vector<std::string>::iterator	it = tmpChnl.getChannelMembers().begin(); it != tmpChnl.getChannelMembers().end(); it++){
			if (*it == clientNick){
				tmpChnl.getChannelMembers().erase(it);
				break;
			}
		}
		for (std::vector<std::string>::iterator	it = tmpChnl.getChannelOperators().begin(); it != tmpChnl.getChannelOperators().end(); it++){
			if (*it == clientNick){
				tmpChnl.getChannelOperators().erase(it);
				break;
			}
		}
		for (std::vector<std::string>::iterator	it = tmpChnl.getInvitedMembers().begin(); it != tmpChnl.getInvitedMembers().end(); it++){
			if (*it == clientNick){
				tmpChnl.getInvitedMembers().erase(it);
				break;
			}
		}
	}
	if (itClient != _mapClients.end()){
		delete itClient->second;
		_mapClients.erase(itClient);
	}
	close(newSocketFd);
}