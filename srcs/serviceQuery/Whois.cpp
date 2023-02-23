#include "../../headers/Server.hpp"

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