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
			
	if (!msg.getArguments().size())
		errorHandler(461, "PASS");
	else
	{
		if (msg.getArguments().at(0).compare(getPassword()))
		{
			std::cout << msg.getArguments().at(0).size() << std::endl;	
			errorHandler(464);
		}
		else
			tmpGuest->setPassValid(true);
	}
}

void Server::handleNickCmd(Message &msg, int newSocketFd)
{
	Guest *tmpGuest = _mapGuest[newSocketFd];
	
    if (!msg.getArguments().size())
		errorHandler(431);	
	else if (tmpGuest->getPassValid())
	{
		for (std::map<int, Client*>::iterator it = _mapClients.begin(); it != _mapClients.end(); ++it)
		{
			if (!it->second->getNickName().compare(msg.getArguments().at(0)))
				errorHandler(436 ,it->second->getNickName());
		}
		if (!isalpha(msg.getArguments().at(0).at(0)) || msg.getArguments().at(0).size() > 8)
			errorHandler(432, msg.getArguments().at(0));
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
		errorHandler(464);	
	}
}

void Server::guestToClient(Guest *tmpGuest, int newSocketFd)
{
	Client *tmpClient = _mapClients[newSocketFd];
	
	tmpClient->setNickName(tmpGuest->getGuestNick()); 
	tmpClient->setUserName(tmpGuest->getGuestUser()); 
	tmpClient->setRealName(tmpGuest->getGuestRealName()); 
  	tmpClient->setAuthValid(true);
  	WelcomeMsg(newSocketFd);

}

void Server::handleUserCmd(Message &msg, int newSocketFd)
{
	Guest *tmpGuest = _mapGuest[newSocketFd];
	
	if (msg.getArguments().size() < 4)
		errorHandler(461, "USER");
	else if (!tmpGuest->getPassValid()){
		errorHandler(464);
	}
	else{
		if (!isalpha(msg.getArguments().at(0).at(0)) && !isnumber(msg.getArguments().at(0).at(0)))
			errorHandler(432, msg.getArguments().at(0));
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
	std::string	rpl;
	char		hostname[256];

	if (!msg.getArguments().size())
		errorHandler(431);
	else
	{
		if (_mapClients[newSocketFd]->getIsAuthValid())
		{
			for (std::map<int, Client*>::iterator it = _mapClients.begin(); it != _mapClients.end(); ++it)
			{
				if (!msg.getArguments().at(0).compare(it->second->getNickName()))
				{
					gethostname(hostname, sizeof(hostname));
					rpl = ":irc 311 " + it->second->getNickName() + " " + it->second->getUserName() + " ~" + it->second->getUserName() + " " + hostname + " * :" + it->second->getRealName() + "\r\n"
							+ ":irc" + " 318 " + it->second->getNickName() + " " + it->second->getUserName() + " :End of /WHOIS list.\r\n";
					sendReplay(newSocketFd, rpl);
					break;
				}
				if (it == --_mapClients.end() && msg.getArguments().at(0).compare(it->second->getNickName())) 
					errorHandler(401, msg.getArguments().at(0));
			}
		}	
		else
        	errorHandler(451); //You have not registred
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