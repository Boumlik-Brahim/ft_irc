
#include "../../headers/Server.hpp"

void Server::guestToClient(Guest *tmpGuest, int newSocketFd)
{
	Client *tmpClient = _mapClients[newSocketFd];
	time_t login_time = time(NULL);
	
	tmpClient->setNickName(tmpGuest->getGuestNick()); 
	tmpClient->setUserName(tmpGuest->getGuestUser()); 
	tmpClient->setRealName(tmpGuest->getGuestRealName()); 
  	tmpClient->setAuthValid(true);
	tmpClient->setLoginTime(login_time);
  	WelcomeMsg(newSocketFd);
}