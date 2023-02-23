
#include "../../headers/Server.hpp"

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