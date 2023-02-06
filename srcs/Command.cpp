/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:22:27 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/06 11:25:00 by izail            ###   ########.fr       */
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

int Server::findFdClientByNick(std::string receiver)
{
    for(std::map<int, Client *>::iterator it = _mapClients.begin(); it != _mapClients.end(); it++)
    {
        if (it->second->getNickName() == receiver)
            return (it->first);
    }
    return (-1);
}

std::string     Server::findNickClientByFd(int sender)
{
    std::map<int, Client *>::iterator it = _mapClients.find(sender);
    if (it != _mapClients.end())
        return it->second->getNickName();
    else
        return "Client not found";
}

void  Server::handlePrivmsgCmd(Message &msg, int senderFd)
{
    std::string receiver;
    std::string sender;
    std::string cmd;
    std::string message;
    std::string messageFormat;
    int receiverFd;

    cmd = msg.getCommand();
	if (msg.getArgument().empty())
        return (errorHandler(senderFd , 411, cmd));
	receiver = msg.getArgument()[0];
	message = msg.getArgument()[1];
    sender = findNickClientByFd(senderFd);
    receiverFd = findFdClientByNick(receiver);
	
	if (!_mapClients[senderFd]->getIsAuthValid())
		return (errorHandler(senderFd, 451));
    else if (msg.getArgument().size() < 2)
		return (errorHandler(senderFd , 412));
	// else if(receiverFd == -1)
	// 	return (errorHandler(senderFd , 401, receiver));
	// else if(ERR_TOOMANYTARGETS)
    //     return (errorHandler(senderFd , 407, "target"));
	// else if(ERR_CANNOTSENDTOCHAN)
    //     return (errorHandler(senderFd , 404, "channel name"));
	// else if(ERR_WILDTOPLEVEL)
    //     return (errorHandler(senderFd , 414, "mask"));
	// else if(ERR_NOTOPLEVEL)
    //     return (errorHandler(senderFd , 413, "mask"));
    if (message.at(0) != ':')
        message.insert(0,1,':');

    messageFormat = ":"+ sender+ " " +cmd + " " + receiver + " " + message;
    sendMessage(receiverFd, messageFormat);
}

void  Server::handleNoticeCmd(Message &msg, int senderFd)
{
    std::string receiver;
    std::string sender;
    std::string cmd;
    std::string message;
    std::string messageFormat;
    int receiverFd;

    cmd = msg.getCommand();
	if (msg.getArgument().empty())
        return (errorHandler(senderFd , 411, cmd));	
	receiver = msg.getArgument()[0];
	message = msg.getArgument()[1];
    sender = findNickClientByFd(senderFd);
    receiverFd = findFdClientByNick(receiver);
	
	if (!_mapClients[senderFd]->getIsAuthValid())
		return (errorHandler(senderFd, 451));
    else if (msg.getArgument().size() < 2)
		return (errorHandler(senderFd , 412));
    if (message.at(0) != ':')
        message.insert(0,1,':');

    messageFormat = ":"+ sender+ " " +cmd + " " + receiver + " " + message;
    sendMessage(receiverFd, messageFormat);
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
	// if (args[1].back() - 1 != '\r' && args[1].back() != '\n')
    //     args[1] += "\r\n";
	free(data);
	msg.setArguments(args);
}

void Server::backBone(std::string buffer, int newSocketFd)
{
	Message msg;
	char 	**data;

	data = ft_split(buffer.c_str(), ' ');
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
	    std::cout << "i got the join" << std::endl;
	else if (!msg.getCommand().compare("PART"))
	    std::cout << "i got the part" << std::endl;
	else if (!msg.getCommand().compare("MODE"))
	    std::cout << "i got the mode" << std::endl;
	else if (!msg.getCommand().compare("TOPIC"))
	    std::cout << "i got the topic" << std::endl;
	else if (!msg.getCommand().compare("NAMES"))
	    std::cout << "i got the names" << std::endl;
	else if (!msg.getCommand().compare("LIST"))
	    std::cout << "i got the names" << std::endl;
	else if (!msg.getCommand().compare("INVITE"))
	    std::cout << "i got the names" << std::endl;
	else if (!msg.getCommand().compare("KICK"))
	    std::cout << "i got the kick" << std::endl;
	else if (!msg.getCommand().compare("PRIVMSG"))
	    handlePrivmsgCmd(msg, newSocketFd);
	else if (!msg.getCommand().compare("NOTICE"))
		handleNoticeCmd(msg, newSocketFd);
  	else if (!msg.getCommand().compare("WHOIS"))
		handleWhoIsCmd(msg, newSocketFd);
	else
	    std::cout << "invalid command" << std::endl;
}