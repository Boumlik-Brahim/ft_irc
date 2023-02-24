#include "../../headers/Server.hpp"

void Server::handleLogTime(Message &msg, int newSocketFd)
{
	std::stringstream 	sHour;
	std::stringstream 	sMin;
	std::stringstream 	sSec;
	std::string 		rpl;
	int 				duration;
	int 				hours;
	int 				minutes; 
	int 				seconds;
	int					tmpFd;
	
	if (msg.getArguments().size() >= 2)
	{
		tmpFd = findFdClientByNick(msg.getArguments().at(1));
		std::string	receiver = findNickClientByFd(tmpFd);
		std::map<int, Client*>::iterator it = _mapClients.find(tmpFd);
		if (it != _mapClients.end())
		{
			time_t 		currentTime = time(NULL);
			
			duration = currentTime - it->second->getLoginTime();
			hours = duration / 3600;
			minutes = (duration % 3600) / 60;
			seconds = duration % 60;
			sHour << hours;
			sMin << minutes;
			sSec << seconds;
			rpl += ":BOT NOTICE " + receiver + " : " + receiver  + " Logged " + sHour.str() + ":" + sMin.str() + ":" + sSec.str() + "\r\n";
			sendReplay(newSocketFd, rpl);
		}
		else{
			errorHandler(401, msg.getArguments().at(1)); //User doesn't exist
		}
	}
	else
	{
		errorHandler(461, msg.getCommand()); //Need More Arguments
	}
}

void  Server::handleBotCmd(Message &msg, int senderFd)
{
	std::string receiver;
	std::string message = "";

	receiver = findNickClientByFd(senderFd);
	if (!_mapClients[senderFd]->getIsAuthValid())	
		errorHandler(451);
	if (msg.getArguments().empty())
	{
		message  = ":BOT NOTICE " + receiver + " :" + "*************************************BOT*************************************\r\n";
		message += ":BOT NOTICE " + receiver + " :" + "*     BOT: Used to interpret and execute commands given by users.           *\r\n";
		message += ":BOT NOTICE " + receiver + " :" + "*     BOT <help>: Used to display information about available commands      *\r\n";
		message += ":BOT NOTICE " + receiver + " :" + "*     BOT <logtime>: Used to track the amount of time spent on a server.    *\r\n";
		message += ":BOT NOTICE " + receiver + " :" + "*     BOT <search> <nickname> : Used to get informations about a user.      *\r\n";
		message += ":BOT NOTICE " + receiver + " :" + "*************************************BOT*************************************\r\n";
		sendReplay(senderFd, message);
	}
	else if (!msg.getArguments().empty())
	{
		if (msg.getArguments().at(0) == "help")
		{
			message  = ":BOT NOTICE " + receiver + " :" + "**********************************************************BOT*********************************************************\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     PASS: Used to set a 'connection password'.                                                                     *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     NICK: Used to give user a nickname or change the existing one.                                                 *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     USER: Used at the beginning of connection to specify the username, hostname and realname of a new user.        *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     QUIT: A client session is terminated with a quit message.                                                      *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     JOIN: Used by a user to request to start listening to the specific channel.                                    *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     PART: Causes the user sending the message to be removed from the list of active members for all given channels.*\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     MODE: Is provided so that users may query and change the characteristics of a channel.                         *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     TOPIC: Used to change or view the topic of a channel.                                                          *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     NAMES: Used to list all nicknames that are visible to user.                                                    *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     LIST: Used to list channels and their topics.                                                                  *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     INVITE: Used to invite a user to a channel.                                                                    *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     KICK: Used to request the forced removal of a user from a channel.                                             *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     PRIVMSG: Used to send private messages between users, as well as to send messages to channels.                 *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     NOTICE: Used similarly to PRIVMSG.                                                                             *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     WHOIS: Used to query information about particular user.                                                        *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     BOT: Used to interpret and execute commands given by users.                                                    *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     BOT <help>: Used to display information about available command                                                *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     BOT <logtime>: Used to track the amount of time spent on a server.                                             *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     BOT <search> <nickname> : Used to get informations about <nickname> user.                                      *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "**********************************************************BOT*********************************************************\r\n";
			sendReplay(senderFd, message);
		}
		else if (msg.getArguments().at(0) == "search" && msg.getArguments().size() == 2)
		{
			std::map<int, Client *>::iterator    it;
			std::string channels= "";
			int clientFd;
			int nbrSecretChannel = 0;
			int nbrPrivateChannel = 0;
			int nbrPublicChannel = 0;

			clientFd = findFdClientByNick(msg.getArguments().at(1));
			it = _mapClients.find(clientFd);
			if (findFdClientByNick(msg.getArguments().at(1),senderFd) == -1)
				return ;
			for (size_t i = 0; i < it->second->getJoinedChannels().size() ; i++)
			{
				Channel     &tmpChannel = findChannel(it->second->getJoinedChannels().at(i));
				if (tmpChannel.getIsMode_s())
					nbrSecretChannel++;
				else if (tmpChannel.getIsMode_p())
					nbrPrivateChannel++;
				else
				{
					nbrPublicChannel++;
					channels = channels.append(" ") + tmpChannel.getChannelName();
				}
			}
			if (nbrPublicChannel == 0)
				channels = "There is no Channel for this user";
			message =  ":BOT NOTICE " + receiver + " :" + " **************************** CLIENT INFORMATION *****************************\r\n";
			message += ":BOT NOTICE " + receiver + " :" + " *    NICK NAME : " + it->second->getNickName() + "                            \r\n";
			message += ":BOT NOTICE " + receiver + " :" + " *    REAL NAME : " + it->second->getRealName() + "                            \r\n";
			message += ":BOT NOTICE " + receiver + " :" + " *    USER NAME : " + it->second->getUserName() + "                            \r\n";
			message += ":BOT NOTICE " + receiver + " :" + " *****************************************************************************\r\n";
			message += ":BOT NOTICE " + receiver + " :" + " ***************************** CLIENT CHANNELS *******************************\r\n";
			message += ":BOT NOTICE " + receiver + " :" + " *    PRIVATE CHANNELS * : " + std::to_string(nbrPrivateChannel) + "          \r\n";
			message += ":BOT NOTICE " + receiver + " :" + " *    SECRET  CHANNELS @ : " + std::to_string(nbrSecretChannel)+ "            \r\n";
			message += ":BOT NOTICE " + receiver + " :" + " *    PUBLIC  CHANNELS = : " + channels + "                                   \r\n";
			message += ":BOT NOTICE " + receiver + " :" + " *****************************************************************************\r\n";
			sendReplay(senderFd, message);
		}
		else if (msg.getArguments().at(0) == "logtime"){
			handleLogTime(msg, senderFd);
		}
		else
		{
			message  = ":BOT NOTICE " + receiver + " :" + "*************************************BOT*************************************\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     BOT: Used to interpret and execute commands given by users.           *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     BOT <help>: Used to display information about available commands      *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     BOT <logtime>: Used to track the amount of time spent on a server.    *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*     BOT <search> <nickname> : Used to get informations about a user.      *\r\n";
			message += ":BOT NOTICE " + receiver + " :" + "*************************************BOT*************************************\r\n";
			sendReplay(senderFd, message);
		}
	}
}