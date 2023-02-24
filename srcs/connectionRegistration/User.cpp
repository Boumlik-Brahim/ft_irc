
#include "../../headers/Server.hpp"

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
			if (!_mapClients[newSocketFd]->getUserName().compare("")){ //check if the user already exist
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