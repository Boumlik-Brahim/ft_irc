#include "../../headers/Server.hpp"

void  Server::handlePrivmsgCmd(Message &msg, int senderFd)
{
    std::string 				sender;
    std::string 				cmd = msg.getCommand();
    std::vector<std::string> 	receivers;
    std::string 				message;
    std::string 				messageFormat;
    std::vector<int>			receiversFd;
	std::string					channelName;
	int							fd;
	char						hostname[256];
	std::map<int, Client *>::iterator	it;

	int 						channelExist;

	if (!_mapClients[senderFd]->getIsAuthValid())
		errorHandler(451);
	sender = findNickClientByFd(senderFd);
	
	//411
	if (msg.getArguments().empty())
		errorHandler(411, cmd);
	//412
	if (msg.getArguments().size() < 2)
		errorHandler(412);
	it = _mapClients.find(senderFd);
	gethostname(hostname, sizeof(hostname));
	checkMultiArgs(msg);
	if (msg.getMultiArgs().size())
	{
		receivers = msg.getMultiArgs();
		for (size_t i = 0; i < receivers.size(); i++)
		{
			receiversFd.push_back(findFdClientByNick(receivers.at(i), senderFd));
			message = msg.getArguments().at(0);
			messageFormat = ":"+ sender+ " " +cmd + " " + receivers.at(i) + " " + message;
			sendMessage(receiversFd.at(i), messageFormat);
		}
	}
	else if (msg.getArguments().size())
	{
		if (msg.getArguments()[0].at(0) == '#')
		{
			channelName = msg.getArguments()[0];
			channelExist = findChannelByName(channelName);
			if (channelExist)
			{
				Channel &tmpChannel = findChannel(channelName);
				if (tmpChannel.getIsMode_n())
				{
					if (checkIfClientIsMember(tmpChannel, sender) == true)
					{
						message = msg.getArguments()[1];
						std::string rpl = ":" + it->second->getNickName() + "!~" + it->second->getUserName() + "@" + hostname + " PRIVMSG " + tmpChannel.getChannelName() + " " + message + "\r\n";
						for (size_t i = 0; i < tmpChannel.getChannelMembers().size(); i++)
						{
							if (tmpChannel.getChannelMembers().at(i) == it->second->getNickName())
								continue;
							fd = findFdClientByNick(tmpChannel.getChannelMembers().at(i));
							sendReplay(fd, rpl);
						}
					}
					else
						errorHandler(404, tmpChannel.getChannelName());
				}
				else
				{
					for (size_t i = 0; i < tmpChannel.getChannelMembers().size(); i++)
					{
						receivers.push_back(tmpChannel.getChannelMembers().at(i));
						receiversFd.push_back(findFdClientByNick(tmpChannel.getChannelMembers().at(i), senderFd));
						message = msg.getArguments()[1];
						messageFormat = ":"+ sender+ " " + cmd + " " + receivers.at(i) + " " + message;
						sendMessage(receiversFd.at(i), messageFormat);
					}
				}
			}
			else
				errorHandler(403, channelName);
		}
		else if (msg.getArguments()[0].at(0) != '#')
		{
			receivers.push_back(msg.getArguments()[0]);
			receiversFd.push_back(findFdClientByNick(msg.getArguments()[0], senderFd));
			message = msg.getArguments()[1];
			if (message.at(0) != ':')
				message.insert(0,1,':');
			messageFormat = ":"+ sender+ " " +cmd + " " + receivers.at(0) + " " + message;
			sendMessage(receiversFd.at(0), messageFormat);
		}
	}
}