
#include "../../headers/Server.hpp"

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