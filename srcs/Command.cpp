/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:22:27 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/17 10:28:38 by izail            ###   ########.fr       */
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
    for(std::map<int, Client *>::iterator it = _mapClients.begin(); it != _mapClients.end(); it++)
    {
        if (it->second->getNickName() == receiver)
            return (it->first);
    }
    errorHandler(newSocketFd, 401, receiver);
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

	if (!_mapClients[senderFd]->getIsAuthValid())
		errorHandler(senderFd, 451);
	sender = findNickClientByFd(senderFd);
	
	//411
	if (msg.getArguments().empty())
		errorHandler(senderFd, 411, cmd);
	//412
	if (msg.getArguments().size() < 2)
		errorHandler(senderFd, 412);

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
			Channel &tmpChannel = findChannel(channelName);
			for (size_t i = 0; i < tmpChannel.getChannelMembers().size(); i++)
			{
				std::cout << "kaydkhol l PRIVMSG f #\n";
				receivers.push_back(tmpChannel.getChannelMembers().at(i));
				receiversFd.push_back(findFdClientByNick(tmpChannel.getChannelMembers().at(i), senderFd));
				message = msg.getArguments()[1];
				messageFormat = ":"+ sender+ " " + cmd + " " + receivers.at(i) + " " + message;
				sendMessage(receiversFd.at(i), messageFormat);
			}
		}
		receivers.push_back(msg.getArguments()[0]);
		receiversFd.push_back(findFdClientByNick(msg.getArguments()[0], senderFd));
		message = msg.getArguments()[1];
		if (message.at(0) != ':')
        	message.insert(0,1,':');
		messageFormat = ":"+ sender+ " " +cmd + " " + receivers.at(0) + " " + message;
    	sendMessage(receiversFd.at(0), messageFormat);
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
		errorHandler(senderFd, 451);
	sender = findNickClientByFd(senderFd);
	
	//411
	if (msg.getArguments().empty())
		errorHandler(senderFd, 411, cmd);
	//412
	if (msg.getArguments().size() < 2)
		errorHandler(senderFd, 412);

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
		receivers.push_back(msg.getArguments()[0]);
		receiversFd.push_back(findFdClientByNick(msg.getArguments()[0], senderFd));
		message = msg.getArguments()[1];
		if (message.at(0) != ':')
        	message.insert(0,1,':');
		messageFormat = ":"+ sender+ " " +cmd + " " + receivers.at(0) + " " + message;
    	sendMessage(receiversFd.at(0), messageFormat);
	}
}

void checkChnlNames(std::vector<std::string> tmpArgs, int newSocketFd)
{
	for (size_t i = 0; i < tmpArgs.size(); i++)
	{
		if (tmpArgs.at(i).at(0) != '#')
			errorHandler(newSocketFd, 403, tmpArgs.at(i));
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
	std::cout << "huf hna \n";
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

	data = ft_split(buffer.c_str(), ' ');
	std::cout << "buf ==" << buffer << std::endl;
	try{
		parseMessageFormat(msg, data);
		if (!msg.getCommand().compare("PASS"))
			handlePassCmd(msg, newSocketFd);
		else if (!msg.getCommand().compare("NICK"))
			handleNickCmd(msg, newSocketFd);
		else if (!msg.getCommand().compare("USER"))
			handleUserCmd(msg, newSocketFd);
		else if (!msg.getCommand().compare("OPER"))
			std::cout << "i got the oper" << std::endl;
		else if (!msg.getCommand().compare("SERVICE"))
			std::cout << "i got the service" << std::endl;
		else if (!msg.getCommand().compare("QUIT"))
			std::cout << "i got the quit" << std::endl;
		else if (!msg.getCommand().compare("SQUIT"))
			std::cout << "i got the squit" << std::endl;
		else if (!msg.getCommand().compare("JOIN"))
			handleJoinCmd(msg, newSocketFd);
		else if (!msg.getCommand().compare("PART"))
			handlePartCmd(msg, newSocketFd);
		else if (!msg.getCommand().compare("MODE"))
			std::cout << "i got the mode" << std::endl;
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
		else
			std::cout << "invalid command" << std::endl;		
	}
	catch(std::string message){
		size_t i = 0;
		message += "\r\n";
		while (i != message.length())
			i += send(newSocketFd, message.c_str(), message.length() - i, 0);
	}
}