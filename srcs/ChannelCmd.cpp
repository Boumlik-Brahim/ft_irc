/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:39:29 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/10 13:20:52 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

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
void	Server::createChannel(Channel &chnl, std::string channelName, std::string channelCreator)
{
	chnl.setChannelName(channelName);
	chnl.setChannelCreator(channelCreator);
	chnl.setChannelMembers(channelCreator);
	chnl.setChannelOperators(channelCreator);
	chnl.setIsMode_o(true);
	_channels.push_back(chnl);
}
void  Server::handleJoinCmd(Message &msg, int senderFd)
{
	if (msg.getArguments().empty()) /*ERR_NEEDMOREPARAMS*/
		return (errorHandler(senderFd, 461, msg.getCommand()));
	checkMultiArgs(msg);
	checkChnlNames(msg.getMultiArgs(), senderFd);
	if (!msg.getMultiArgs().empty())
	{
		if (msg.getMultiArgs().size() > 2)/*ERR_TOOMANYTARGETS*/
			return (errorHandler(senderFd, 407, msg.getMultiArgs().at(0), "reduce the number of targets and try the request again"));
		for (size_t i = 0; i < msg.getMultiArgs().size(); i++)
		{
			if (findChannelByName(msg.getMultiArgs().at(i)))
			{
				Channel &chnl = findChannel(msg.getMultiArgs().at(i));

				if (chnl.getChannelMembers().size() > 1)/*ERR_CHANNELISFULL*/
					return (errorHandler(senderFd, 471, chnl.getChannelName()));
			}
			else
			{
				Channel								chnl;
				std::map<int, Client *>::iterator	it;

				it = _mapClients.find(senderFd);
				createChannel(chnl, msg.getMultiArgs().at(i), it->second->getNickName());
				it->second->setJoinedChannels(msg.getMultiArgs().at(i));
				cmd_Resp_Handler(senderFd, 332, msg.getMultiArgs().at(i), "...");
			}
		}
	}
	else
	{
		if (findChannelByName(msg.getArguments().at(0)))
		{
			std::map<int, Client *>::iterator	it;
			Channel &chnl = findChannel(msg.getArguments().at(0));

			it = _mapClients.find(senderFd);
			if (chnl.getIsMode_l())
			{
				if (chnl.getChannelMembers().size() >= (size_t)chnl.getChannelLimit())/*ERR_CHANNELISFULL*/
					return (errorHandler(senderFd, 471, chnl.getChannelName()));
			}
			else if (chnl.getIsMode_i())
			{
				for(size_t i = 0; i < chnl.getInvitedMembers().size(); i++)
				{
					if (chnl.getInvitedMembers().at(i) == it->second->getNickName())
						return ;
				}
				return (errorHandler(senderFd, 473, chnl.getChannelName()));/*ERR_INVITEONLYCHAN*/
			}
			else if (chnl.getIsMode_b())
			{
				for(size_t i = 0; i < chnl.getChannelBannedMembers().size(); i++)
				{
					if (chnl.getChannelBannedMembers().at(i) == it->second->getNickName())
						return (errorHandler(senderFd, 474,  msg.getArguments().at(0)));/*ERR_BANNEDFROMCHAN*/
					/*banned with IP*/
				}
			}
			else if (chnl.getIsMode_k())
			{
				if (chnl.getChannelkey() != msg.getArguments().at(1))
					return (errorHandler(senderFd, 475, msg.getArguments().at(0)));/*ERR_BADCHANNELKEY*/
			}
			else if (it->second->getJoinedChannels().size() > (size_t)it->second->getClientMaxnumOfChannels() )/*ERR_TOOMANYCHANNELS*/
				return (errorHandler(senderFd, 405, msg.getArguments().at(0)));
			chnl.setChannelMembers(it->second->getNickName());
			cmd_Resp_Handler(senderFd, 332, msg.getArguments().at(0), "...");
		}
		else
		{
			Channel								chnl;
			std::map<int, Client *>::iterator	it;

			it = _mapClients.find(senderFd);
			createChannel(chnl, msg.getArguments().at(0), it->second->getNickName());
			it->second->setJoinedChannels(msg.getArguments().at(0));
			cmd_Resp_Handler(senderFd, 332, msg.getArguments().at(0), "...");
		}	
	}
}