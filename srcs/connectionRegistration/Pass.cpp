
#include "../../headers/Server.hpp"

void Server::handlePassCmd(Message &msg, int newSocketFd)
{
	Guest *tmpGuest = _mapGuest[newSocketFd];
			
	if (msg.getArguments().size())
	{
		if (msg.getArguments().at(0).compare(getPassword())){
			errorHandler(464);
		}
		else
			tmpGuest->setPassValid(true);
	}
	else
		errorHandler(461, "PASS");
}