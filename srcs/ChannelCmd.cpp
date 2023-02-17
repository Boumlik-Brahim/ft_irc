/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:39:29 by bbrahim           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/Server.hpp"

/****************************************************************************************************************************************/

void sendReplay(int fd, std::string message)
{
	size_t i = 0;
	while (i != message.length())
		i += send(fd, message.c_str(), message.length() - i, 0);
}

Channel& Server::findChannel(std::string channelName)
{
	for(size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels.at(i).getChannelName() == channelName)
			return (_channels.at(i));
	}
	throw "there is no channel";
}

int	Server::findChannelByName(std::string channelName)
{
	for(size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels.at(i).getChannelName() == channelName)
			return (1);
	}
	return (0);
}

void	Server::setChannel(Channel &chnl, std::string channelName, std::string channelCreator,  std::string channelkey)
{
	chnl.setChannelName(channelName);
	chnl.setChannelCreator(channelCreator);
	chnl.setChannelMembers(channelCreator);
	chnl.setIsMode_n(true);
	chnl.setChannelOperators(channelCreator);
	chnl.setIsMode_k(true);
	chnl.setChannelkey(channelkey);
	_channels.push_back(chnl);
}

void	Server::joinNewChannelWithKey(int senderFd, std::string channelName, std::string channelkey)
{
	Channel								chnl;
	std::map<int, Client *>::iterator	it;
	std::string							rpl;
	char								hostname[256];

	it = _mapClients.find(senderFd);
	if (it->second->getJoinedChannels().size() >= (size_t)it->second->getClientMaxnumOfChannels())/*ERR_TOOMANYCHANNELS*/
		return (errorHandler(senderFd, 405, channelName));
	setChannel(chnl, channelName, it->second->getNickName(), channelkey);
	it->second->setJoinedChannels(channelName);
	gethostname(hostname, sizeof(hostname));
	rpl = ":" + it->second->getNickName() + "!~" + it->second->getUserName() + "@" + hostname + " JOIN :" + channelName + "\r\n"
		+ ":" + it->second->getNickName() + " MODE " + channelName + " +kn\r\n"
		+ ":irc" + " 353 " + it->second->getNickName() + " = " + channelName + " :@" + it->second->getNickName() + "\r\n" 
		+ ":irc" + " 366 " + it->second->getNickName() + " " + channelName + " :End of /NAMES list\r\n";
	sendReplay(senderFd, rpl);
}

void	Server::setChannel(Channel &chnl, std::string channelName, std::string channelCreator)
{
	chnl.setChannelName(channelName);
	chnl.setChannelCreator(channelCreator);
	chnl.setChannelMembers(channelCreator);
	chnl.setChannelOperators(channelCreator);
	chnl.setIsMode_n(true);
	_channels.push_back(chnl);
}

void	Server::joinNewChannel(int senderFd, std::string channelName)
{
	Channel								chnl;
	std::map<int, Client *>::iterator	it;
	std::string							rpl;
	char								hostname[256];

	it = _mapClients.find(senderFd);
	if (it->second->getJoinedChannels().size() >= (size_t)it->second->getClientMaxnumOfChannels())/*ERR_TOOMANYCHANNELS*/
		return (errorHandler(senderFd, 405, channelName));
	setChannel(chnl, channelName, it->second->getNickName());
	it->second->setJoinedChannels(channelName);
	gethostname(hostname, sizeof(hostname));
	rpl = ":" + it->second->getNickName() + "!~" + it->second->getUserName() + "@" + hostname + " JOIN :" + channelName + "\r\n"
		+ ":" + it->second->getNickName() + " MODE " + channelName + " +n\r\n"
		+ ":irc" + " 353 " + it->second->getNickName() + " = " + channelName + " :@" + it->second->getNickName() + "\r\n" 
		+ ":irc" + " 366 " + it->second->getNickName() + " " + channelName + " :End of /NAMES list\r\n";
	sendReplay(senderFd, rpl);
}

void	Server::joinExistChannel(Channel &chnl, std::map<int, Client *>::iterator	&it)
{
	int			fd;
	char		hostname[256];
	std::string	rpl;

	chnl.setChannelMembers(it->second->getNickName());
	it->second->setJoinedChannels(chnl.getChannelName());
	gethostname(hostname, sizeof(hostname));
	rpl = ":" + it->second->getNickName() + "!~" + it->second->getUserName() + "@" + hostname + " JOIN :" + chnl.getChannelName() + "\r\n"
		+ ":irc" + " 353 " + it->second->getNickName() + " @ " + chnl.getChannelName() + " :" + it->second->getNickName() + " @" + chnl.getChannelCreator() + "\r\n"
		+ ":irc" + " 366 " + it->second->getNickName() + " " + chnl.getChannelName() + " :End of /NAMES list\r\n";
	for(size_t i = 0; i < chnl.getChannelMembers().size(); i++)
	{
		fd = findFdClientByNick(chnl.getChannelMembers().at(i));
		sendReplay(fd, rpl);
	}
}

void	Server::checkExistChannel(int senderFd, Message &msg, std::string channelName, int i)
{
	std::map<int, Client *>::iterator	it;

	it = _mapClients.find(senderFd);
	Channel &chnl = findChannel(channelName);
	for(size_t i = 0; i < chnl.getChannelMembers().size(); i++)
	{
		if (chnl.getChannelMembers().at(i) == it->second->getNickName())
			return ;
	}
	if (it->second->getJoinedChannels().size() >= (size_t)it->second->getClientMaxnumOfChannels() )/*ERR_TOOMANYCHANNELS*/
		return (errorHandler(senderFd, 405, channelName));
	if (chnl.getIsMode_l())
	{
		if (chnl.getChannelMembers().size() >= (size_t)chnl.getChannelLimit())/*ERR_CHANNELISFULL*/
			return (errorHandler(senderFd, 471, chnl.getChannelName()));
	}
	if (chnl.getIsMode_i())
	{
		std::vector<std::string>::iterator	result = std::find(chnl.getInvitedMembers().begin(), chnl.getInvitedMembers().end(), it->second->getNickName());
		if (result == chnl.getInvitedMembers().end())
			return (errorHandler(senderFd, 473, chnl.getChannelName()));/*ERR_INVITEONLYCHAN*/
	}
	if (chnl.getIsMode_b())
	{
		for(size_t i = 0; i < chnl.getChannelBannedMembers().size(); i++)
		{
			if (chnl.getChannelBannedMembers().at(i) == it->second->getNickName())
				return (errorHandler(senderFd, 474,  chnl.getChannelName()));/*ERR_BANNEDFROMCHAN*/
		}
	}
	if (chnl.getIsMode_k())
	{
		if ((!msg.getMultiArgs().empty() && !msg.getArguments().empty()) || (msg.getMultiArgs().empty() && msg.getArguments().size() > 1))
		{
			if (chnl.getChannelkey() != msg.getArguments().at(i))
				return (errorHandler(senderFd, 475, chnl.getChannelName()));/*ERR_BADCHANNELKEY*/
		}
		else if ((!msg.getMultiArgs().empty() && msg.getArguments().empty()) || (msg.getMultiArgs().empty() && msg.getArguments().size() == 1))
			return (errorHandler(senderFd, 475, chnl.getChannelName()));/*ERR_BADCHANNELKEY*/
	}
	joinExistChannel(chnl, it);
}

void	Server::leaveAllChannels(int senderFd)
{
	std::map<int, Client *>::iterator	it;
	std::string							rpl;
	int									fd;
	char								hostname[256];

	gethostname(hostname, sizeof(hostname));
	it = _mapClients.find(senderFd);
	for(size_t i = 0; i < it->second->getJoinedChannels().size(); i++)
	{
		Channel &chnl = findChannel(it->second->getJoinedChannels().at(i));
		rpl = ":" + it->second->getNickName() + "!~" + it->second->getUserName() + "@" + hostname + " PART :" + chnl.getChannelName() + "\r\n";
		for(size_t i = 0; i < chnl.getChannelMembers().size(); i++)
		{
			fd = findFdClientByNick(chnl.getChannelMembers().at(i));
			sendReplay(fd, rpl);
		}
		std::vector<std::string>::iterator	channelMember = std::find(chnl.getChannelMembers().begin(), chnl.getChannelMembers().end(), it->second->getNickName());
		chnl.getChannelMembers().erase(channelMember);
	}
	it->second->getJoinedChannels().clear();
}

void  Server::handleJoinCmd(Message &msg, int senderFd)
{
	if (!_mapClients[senderFd]->getIsAuthValid())	
		return (errorHandler(senderFd , 451));
	if (msg.getArguments().empty()) /*ERR_NEEDMOREPARAMS*/
		return (errorHandler(senderFd, 461, msg.getCommand()));
	if (msg.getArguments().at(0) == "#0")
	{
		leaveAllChannels(senderFd);
		return ;
	}
	checkMultiArgs(msg);
	checkChnlNames(msg.getMultiArgs(), senderFd);
	if (!msg.getMultiArgs().empty())
	{
		if (msg.getMultiArgs().size() > 2)/*ERR_TOOMANYTARGETS*/
			return (errorHandler(senderFd, 407, msg.getMultiArgs().at(0), "reduce the number of targets and try the request again"));
		for (size_t i = 0; i < msg.getMultiArgs().size(); i++)
		{
			if (findChannelByName(msg.getMultiArgs().at(i)))
				checkExistChannel(senderFd, msg, msg.getMultiArgs().at(i), i);
			else
			{
				if (msg.getArguments().empty())
					joinNewChannel(senderFd, msg.getMultiArgs().at(i));
				else
					joinNewChannelWithKey(senderFd, msg.getMultiArgs().at(i), msg.getArguments().at(i));
			}
		}
	}
	else if (msg.getMultiArgs().empty() && msg.getArguments().at(0) != "0")
	{
		if (findChannelByName(msg.getArguments().at(0)))
			checkExistChannel(senderFd, msg, msg.getArguments().at(0), 1);
		else
		{
			if (msg.getArguments().size() == 1)
				joinNewChannel(senderFd, msg.getArguments().at(0));
			else if (msg.getArguments().size() > 1)
				joinNewChannelWithKey(senderFd, msg.getArguments().at(0), msg.getArguments().at(1));
		}
	}
}

/****************************************************************************************************************************************/

void Server::partFromChannel(int senderFd, std::string channelName)
{
	std::map<int, Client *>::iterator	it;
	std::string							message;
	int									fd;
	char								hostname[256];

	if(!findChannelByName(channelName))
		return (errorHandler(senderFd, 403, channelName)); /*ERR_NOSUCHCHANNEL*/
	it = _mapClients.find(senderFd);
	Channel &chnl = findChannel(channelName);
	gethostname(hostname, sizeof(hostname));
	std::string rpl = ":" + it->second->getNickName() + "!~" + it->second->getUserName() + "@" + hostname + " PART :" + chnl.getChannelName() + "\r\n";
	for(size_t i = 0; i < chnl.getChannelMembers().size(); i++)
	{
		fd = findFdClientByNick(chnl.getChannelMembers().at(i));
		sendReplay(fd, rpl);
	}
	std::vector<std::string>::iterator	channelMember = std::find(chnl.getChannelMembers().begin(), chnl.getChannelMembers().end(), it->second->getNickName());
	if (channelMember == chnl.getChannelMembers().end())
		return (errorHandler(senderFd, 442, "channel")); /*ERR_NOTONCHANNEL*/
	chnl.getChannelMembers().erase(channelMember);
	std::vector<std::string>::iterator	joinedChannel = std::find(it->second->getJoinedChannels().begin(), it->second->getJoinedChannels().end(), channelName);
	it->second->getJoinedChannels().erase(joinedChannel);
}

void  Server::handlePartCmd(Message &msg, int senderFd)
{

	if (!_mapClients[senderFd]->getIsAuthValid())	
		return (errorHandler(senderFd , 451));
	if (msg.getArguments().empty()) /*ERR_NEEDMOREPARAMS*/
		return (errorHandler(senderFd, 461, msg.getCommand()));
	checkMultiArgs(msg);
	checkChnlNames(msg.getMultiArgs(), senderFd);
	if (!msg.getMultiArgs().empty())
	{
		for (size_t i = 0; i < msg.getMultiArgs().size(); i++)
			partFromChannel(senderFd, msg.getMultiArgs().at(i));
	}
	else
		partFromChannel(senderFd, msg.getArguments().at(0));
}

/****************************************************************************************************************************************/