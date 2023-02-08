/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:39:29 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/08 18:39:46 by bbrahim          ###   ########.fr       */
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
Channel Server::findChannel(std::string channelName)
{
	for(size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels.at(i).getChannelName() == channelName)
			return (_channels.at(i));
	}
	throw "there is no channel";
}
void	Server::createChannel(Channel &chnl, int senderFd, std::string channelName)
{
    std::map<int, Client *>::iterator	it;
	std::string							creator;

	it = _mapClients.find(senderFd);
	creator = findNickClientByFd(senderFd);
	chnl.setChannelCreator(creator);
	chnl.setChannelName(channelName);
	chnl.setChannelMembers(it->second->getNickName());
	chnl.setChannelOperators(it->second->getNickName());
	chnl.setChannelModes("n");
	it->second->setJoinedChannels(channelName);
	_channels.push_back(chnl);
}
void  Server::handleJoinCmd(Message &msg, int senderFd)
{
    std::string							receiver;
    std::string							channelName;
	std::string							cmd;
	Channel								tmpChannel;
	Channel								tmp;
	int									channelExist;
    std::map<int, Client *>::iterator	it;

	it = _mapClients.find(senderFd);
	cmd = msg.getCommand();
	checkMultiArgs(msg);
	checkChnlNames(msg.getMultiArgs(), senderFd);
	if (msg.getMultiArgs().empty() && msg.getArguments().at(0).empty()) /*ERR_NEEDMOREPARAMS*/
		return (errorHandler(senderFd, 461, cmd));
	if (!msg.getMultiArgs().empty())
	{
		if (msg.getMultiArgs().size() > 2)/*ERR_TOOMANYTARGETS*/
			return (errorHandler(senderFd, 407, msg.getMultiArgs().at(0), "reduce the number of targets and try the request again"));
		for (size_t i = 0; i < msg.getMultiArgs().size(); i++)
		{
			channelName = msg.getMultiArgs().at(i);
			if (!findChannelByName(channelName))/*ERR_NOSUCHCHANNEL*/
				return (errorHandler(senderFd, 403, channelName));
			channelExist = findChannelByName(channelName);
			if (channelExist)
			{
				tmp = findChannel(channelName);
				if (tmp.getChannelMembers().size() > 9)/*ERR_CHANNELISFULL*/
					return (errorHandler(senderFd, 471, tmp.getChannelName()));
				else if (it->second->getJoinedChannels().size() > 2)/*ERR_TOOMANYCHANNELS*/
					return (errorHandler(senderFd, 405, channelName));
				for(size_t i = 0; i < tmp.getChannelModes().size() ; i++)
				{
					if (tmp.getChannelModes().at(i) == "i")
						checkInviteOnlyChanFlag(tmp, it->second->getNickName(), senderFd);
				}
			}
			else
				createChannel(tmpChannel, senderFd, msg.getArguments().at(i));
		}
	}
	else
	{
		channelExist = findChannelByName(msg.getArguments().at(0));
		if (channelExist)
		{
		}
		else
			createChannel(tmpChannel, senderFd, msg.getArguments().at(0));
	}
	// else if ()/*ERR_INVITEONLYCHAN*/
	// 	return (errorHandler(senderFd, 473, channelName));
	// else if ()/*ERR_BANNEDFROMCHAN*/
	// 	return (errorHandler(senderFd, 474, channelName));
	// else if ()/*ERR_BADCHANNELKEY*/
	// 	return (errorHandler(senderFd, 475, channelName));
	// else if ()/*ERR_BADCHANMASK*/
	// 	return (errorHandler(senderFd, 476, channelName));
	// else if ()/*RPL_TOPIC*/
	// 	return (cmd_Resp_Handler(senderFd, 332, channelName, "topic"));
}
