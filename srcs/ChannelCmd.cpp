/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:39:29 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/07 18:58:08 by izail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

int	Server::findChannelByName(std::string channelName)
{
	for(size_t i = 0; i < _channels.size(); i++)
	{
		if (channelName == _channels.at(i).getChannelName())
			return (1);
	}
	return (0);
}

void	Server::createChannel(Channel &chnl, int senderFd, std::string channelName)
{
    std::map<int, Client *>::iterator it = _mapClients.find(senderFd);
	std::string creator = findNickClientByFd(senderFd);
	chnl.setChannelCreator(creator);
	chnl.setChannelName(channelName);

	chnl.setChannelMembers(it->second->getNickName());
	chnl.setChannelOperators(it->second->getNickName());
	chnl.setChannelModes("n");
	_channels.push_back(chnl);
}

void  Server::handleJoinCmd(Message &msg, int senderFd)
{
    std::string	receiver;
	Channel 	tmpChannel;
	std::string	cmd;
	int	channelExist;

	// check if JOIN command have multiple channels
	if (!msg.getMultiArgs().empty())
	{
		for (size_t i = 0; i < msg.getMultiArgs().size(); i++)
		{
			channelExist = findChannelByName(msg.getMultiArgs().at(i));
			if (channelExist)
			{
				// check mode;
				// Join user to channel
			}
			else
			{
				// create new Channel
				// set user as the operator of this channel
			}
		}
	}
	else
	{
		channelExist = findChannelByName(msg.getArguments().at(0));
		if (channelExist)
		{
			// check mode
			// join user to channel
		}
		else
		{
			createChannel(tmpChannel, senderFd, msg.getArguments().at(0));
			// create new channel
			/* 
				createChannel(chnl, senderFd, msg.getArguments()[0]);
				string user = getUserByFd(senderFd);
				user.getJoinedChannel().push_back("channelName");
				setMode();
				
			*/
			// set user as the operator of this channel
		}
	}
	// if ()/*ERR_NEEDMOREPARAMS*/
	// 	return (errorHandler(senderFd, 461, cmd));
	// else if ()/*ERR_INVITEONLYCHAN*/
	// 	return (errorHandler(senderFd, 473, channelName));
	// else if ()/*ERR_CHANNELISFULL*/
	// 	return (errorHandler(senderFd, 471, channelName));
	// else if ()/*ERR_NOSUCHCHANNEL*/
	// 	return (errorHandler(senderFd, 403, channelName));
	// else if ()/*ERR_TOOMANYTARGETS*/
	// 	return (errorHandler(senderFd, 407, receiver, "abort message"));
	// else if ()/*ERR_BANNEDFROMCHAN*/
	// 	return (errorHandler(senderFd, 474, channelName));
	// else if ()/*ERR_BADCHANNELKEY*/
	// 	return (errorHandler(senderFd, 475, channelName));
	// else if ()/*ERR_BADCHANMASK*/
	// 	return (errorHandler(senderFd, 476, channelName));
	// else if ()/*ERR_TOOMANYCHANNELS*/
	// 	return (errorHandler(senderFd, 405, channelName));
	// else if ()/*ERR_UNAVAILRESOURCE*/
	// 	return (errorHandler(senderFd, 437, receiver, channelName));
	// else if ()/*RPL_TOPIC*/
	// 	return (cmd_Resp_Handler(senderFd, 332, channelName, "topic"));
}
