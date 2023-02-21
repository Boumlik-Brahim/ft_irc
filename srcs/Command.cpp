/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:57:58 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/21 14:12:19 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void sendMessage(int fd, std::string message)
{
	size_t i = 0;
	message += "\r\n";
	while (i != message.length())
		i += send(fd, message.c_str(), message.length() - i, 0);
}


int Server::findFdClientByNick(std::string receiver, int newSocketFd)
{
	(void)newSocketFd;
    for(std::map<int, Client *>::iterator it = _mapClients.begin(); it != _mapClients.end(); it++)
    {
        if (it->second->getNickName() == receiver)
            return (it->first);
    }
    errorHandler(401, receiver);
	return -1;
}

int Server::findFdClientByNick(std::string receiver)
{
    for(std::map<int, Client *>::iterator it = _mapClients.begin(); it != _mapClients.end(); it++)
    {
        if (it->second->getNickName() == receiver)
            return (it->first);
    }
    return -1;
}

std::string     Server::findNickClientByFd(int sender)
{
    std::map<int, Client *>::iterator it = _mapClients.find(sender);
    if (it != _mapClients.end())
        return it->second->getNickName();
	return "";
}

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
							std::cout << "member at i ==" << tmpChannel.getChannelMembers().at(i) << std::endl;
							std::cout << "sender ==" << it->second->getNickName() << std::endl;
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

void  Server::handleNoticeCmd(Message &msg, int senderFd)
{
    std::string 				sender;
    std::string 				cmd = msg.getCommand();
    std::vector<std::string> 	receivers;
    std::string 				message;
    std::string 				messageFormat;
    std::vector<int>			receiversFd;

	if (!_mapClients[senderFd]->getIsAuthValid())
		errorHandler(451);
	sender = findNickClientByFd(senderFd);
	
	//411
	if (msg.getArguments().empty())
		errorHandler(411, cmd);
	//412
	if (msg.getArguments().size() < 2)
	
	if (msg.getArguments().size())
		errorHandler(412);
	if (msg.getArguments().size())
	{
		receivers.push_back(msg.getArguments()[0]);
		receiversFd.push_back(findFdClientByNick(msg.getArguments()[0], senderFd));
		message = msg.getArguments()[1];
		// if (message.at(0) != ':')
        // 	message.insert(0,1,':');
		messageFormat = ":"+ sender+ " " +cmd + " " + receivers.at(0) + " " + message;
    	sendMessage(receiversFd.at(0), messageFormat);
	}
}

void checkChnlNames(std::vector<std::string> tmpArgs)
{
	for (size_t i = 0; i < tmpArgs.size(); i++)
	{
		if (tmpArgs.at(i).at(0) != '#')
			errorHandler(403, tmpArgs.at(i));
	}
}

std::vector<std::string> splitBySeparator(std::string args, std::string sep)
{
    std::vector<std::string> newArgs;
    size_t pos = 0;
    while ((pos = args.find(sep)) != std::string::npos)
    {
        newArgs.push_back(args.substr(0, pos));
        args.erase(0, pos + 1);
    }
    newArgs.push_back(args.substr(0, pos));
    return newArgs;
}

void checkMultiArgs(Message &msg)
{
	std::vector<std::string> 			tmpArgs;
	
	if (msg.getArguments().at(0).find(',') != std::string::npos)
	{
		tmpArgs = splitBySeparator(msg.getArguments().at(0), ",");
		msg.setMultiArgs(tmpArgs);
		msg.erase(msg.getArguments().begin());
		if (msg.getArguments().size())
		{
			if (msg.getArguments().at(0).find(',') != std::string::npos)
			{
				tmpArgs = splitBySeparator(msg.getArguments().at(0), ",");
				msg.setArguments(tmpArgs);
			}
		}
	}
}

void parseMessageFormat(Message &msg, char **data)
{
	std::vector<std::string> args;
	std::string tmp;
	
	msg.setCommand(data[0]);
	free(data[0]);
	for (int i = 1; data[i]; i++)
	{
		if (data[i][0] == ':')
		{
			for (; data[i]; i++)
			{
				tmp += data[i];
				free(data[i]);
				if (data[i + 1])
					tmp += ' ';
			}
			args.push_back(tmp);
			break;
		}
		else
		{
			args.push_back(data[i]);
			free(data[i]);
		}
	}
	free(data);
	msg.setArguments(args);
}

void Server::backBone(std::string buffer, int newSocketFd)
{
	Message msg;
	char 	**data;
	char	*token;

	char* cstr = const_cast<char*>(buffer.c_str());;
	token = strtok(cstr, "\r\n");
	while (token != NULL)
	{
		data = ft_split(token, ' ');
		try{
			parseMessageFormat(msg, data);
			if (!msg.getCommand().compare("PASS"))
				handlePassCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("NICK"))
				handleNickCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("USER"))
				handleUserCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("QUIT"))
				handleQuitCmd(newSocketFd);
			else if (!msg.getCommand().compare("JOIN"))
				handleJoinCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("PART"))
				handlePartCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("MODE"))
				handleModeCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("TOPIC"))
				handleTopicCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("NAMES"))
				handleNamesCmd(msg,newSocketFd);
			else if (!msg.getCommand().compare("LIST"))
				handleListCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("INVITE"))
				handleInviteCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("KICK"))
				handleKickCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("PRIVMSG"))
				handlePrivmsgCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("NOTICE"))
				handleNoticeCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("WHOIS"))
				handleWhoIsCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("PONG"))
				return;
			else
				std::cout << "invalid command" << std::endl;		
		}
		catch(std::string message){
			size_t i = 0;
			message += "\r\n";
			while (i != message.length())
				i += send(newSocketFd, message.c_str(), message.length() - i, 0);
		}
		token = strtok(NULL, "\r\n");
	}
}