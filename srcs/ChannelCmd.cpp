/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:39:29 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/11 18:45:36 by bbrahim          ###   ########.fr       */
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

void	Server::setChannel(Channel &chnl, std::string channelName, std::string channelCreator)
{
	chnl.setChannelName(channelName);
	chnl.setChannelCreator(channelCreator);
	chnl.setChannelMembers(channelCreator);
	chnl.setChannelOperators(channelCreator);
	chnl.setIsMode_o(true);
	_channels.push_back(chnl);
}

void	Server::joinNewChannel(int senderFd, std::string channelName)
{
	Channel								chnl;
	std::map<int, Client *>::iterator	it;

	it = _mapClients.find(senderFd);
	if (it->second->getJoinedChannels().size() >= (size_t)it->second->getClientMaxnumOfChannels())/*ERR_TOOMANYCHANNELS*/
		return (errorHandler(senderFd, 405, channelName));
	setChannel(chnl, channelName, it->second->getNickName());
	it->second->setJoinedChannels(channelName);
	cmd_Resp_Handler(senderFd, 353, "=", channelName, it->second->getNickName());
	cmd_Resp_Handler(senderFd, 332, channelName, "...");
}

void	Server::joinExistChannel(int senderFd, Channel &chnl, std::map<int, Client *>::iterator	&it)
{
	chnl.setChannelMembers(it->second->getNickName());
	it->second->setJoinedChannels(chnl.getChannelName());
	if (chnl.getIsMode_s())
		cmd_Resp_Handler(senderFd, 353, "@", chnl.getChannelName(), it->second->getNickName());
	else if (chnl.getIsMode_p())
		cmd_Resp_Handler(senderFd, 353, "*", chnl.getChannelName(), it->second->getNickName());
	else
		cmd_Resp_Handler(senderFd, 353, "=", chnl.getChannelName(), it->second->getNickName());
	cmd_Resp_Handler(senderFd, 332, chnl.getChannelName(), "...");
}

// void	Server::checkChannelModes(int senderFd, Channel &chnl, Message &msg, std::map<int, Client *>::iterator	&it, std::string channelkey)
// {
// 	(void)msg;
// 	if (chnl.getIsMode_l())
// 	{
// 		if (chnl.getChannelMembers().size() >= (size_t)chnl.getChannelLimit())/*ERR_CHANNELISFULL*/
// 			return (errorHandler(senderFd, 471, chnl.getChannelName()));
// 	}
// 	else if (chnl.getIsMode_i())
// 	{
// 		for(size_t i = 0; i < chnl.getInvitedMembers().size(); i++)
// 		{
// 			if (chnl.getInvitedMembers().at(i) == it->second->getNickName())
// 				return ;
// 		}
// 		return (errorHandler(senderFd, 473, chnl.getChannelName()));/*ERR_INVITEONLYCHAN*/
// 	}
// 	else if (chnl.getIsMode_b())
// 	{
// 		for(size_t i = 0; i < chnl.getChannelBannedMembers().size(); i++)
// 		{
// 			if (chnl.getChannelBannedMembers().at(i) == it->second->getNickName())
// 				return (errorHandler(senderFd, 474,  chnl.getChannelName()));/*ERR_BANNEDFROMCHAN*/
// 			/*banned with IP*/
// 		}
// 	}
// 	else if (chnl.getIsMode_s() || chnl.getIsMode_p())
// 	{
// 		std::cout << "|channelis===> |" << chnl.getChannelName() << "|channelkeyis===> |" << chnl.getChannelkey() << "|channelkeylidkhlnais===> |" << channelkey << std::endl;
// 		if (chnl.getChannelkey() == channelkey)
// 			return (errorHandler(senderFd, 475, chnl.getChannelName()));/*ERR_BADCHANNELKEY*/
// 	}
// }

void	Server::checkExistChannel(int senderFd, Message &msg, std::string channelName, std::string channelkey)
{
	(void)msg;
	std::map<int, Client *>::iterator	it;
	Channel &chnl = findChannel(channelName);

	chnl.setIsMode_s(true);
	chnl.setChannelkey("key");
	it = _mapClients.find(senderFd);
	for(size_t i = 0; i < chnl.getChannelMembers().size(); i++)
	{
		if (chnl.getChannelMembers().at(i) == it->second->getNickName())
			return ;
	}
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
				return (errorHandler(senderFd, 474,  chnl.getChannelName()));/*ERR_BANNEDFROMCHAN*/
			/*banned with IP*/
		}
	}
	else if (chnl.getIsMode_s() || chnl.getIsMode_p())
	{
		if (chnl.getChannelkey() == channelkey)
			return (errorHandler(senderFd, 475, chnl.getChannelName()));/*ERR_BADCHANNELKEY*/
	}
	// checkChannelModes(senderFd, chnl, msg, it, channelkey);
	if (it->second->getJoinedChannels().size() >= (size_t)it->second->getClientMaxnumOfChannels() )/*ERR_TOOMANYCHANNELS*/
		return (errorHandler(senderFd, 405, channelName));
	joinExistChannel(senderFd, chnl, it);
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
				if (!msg.getArguments().empty())
				{
					std::cout << msg.getMultiArgs().at(i) << msg.getArguments().at(i) << std::endl;
					checkExistChannel(senderFd, msg, msg.getMultiArgs().at(i), msg.getArguments().at(i));
				}
				else
					checkExistChannel(senderFd, msg, msg.getMultiArgs().at(i), "");
			}
			else
				joinNewChannel(senderFd, msg.getMultiArgs().at(i));
		}
	}
	else
	{
		if (findChannelByName(msg.getArguments().at(0)))
		{
			if (msg.getArguments().size() > 1)
				checkExistChannel(senderFd, msg, msg.getArguments().at(0), msg.getArguments().at(1));
			else
				checkExistChannel(senderFd, msg, msg.getArguments().at(0), "");
		}
		else
			joinNewChannel(senderFd, msg.getArguments().at(0));
	}
}

// Channel &chnl = findChannel(msg.getMultiArgs().at(i));
// it = _mapClients.find(senderFd);
// for(size_t i = 0; i < chnl.getChannelMembers().size(); i++)
// {
// 	if (chnl.getChannelMembers().at(i) == it->second->getNickName())
// 		return ;
// }
// checkChannelModes(senderFd, chnl, msg, it);
// if (it->second->getJoinedChannels().size() >= (size_t)it->second->getClientMaxnumOfChannels() )/*ERR_TOOMANYCHANNELS*/
// 	return (errorHandler(senderFd, 405, msg.getMultiArgs().at(i)));
// joinExistChannel(senderFd, chnl, it);


// Channel &chnl = findChannel(msg.getArguments().at(0));
// it = _mapClients.find(senderFd);
// for(size_t i = 0; i < chnl.getChannelMembers().size(); i++)
// {
// 	if (chnl.getChannelMembers().at(i) == it->second->getNickName())
// 		return ;
// }
// checkChannelModes(senderFd, chnl, msg, it);
// if (it->second->getJoinedChannels().size() >= (size_t)it->second->getClientMaxnumOfChannels() )/*ERR_TOOMANYCHANNELS*/
// 	return (errorHandler(senderFd, 405, chnl.getChannelName()));
// joinExistChannel(senderFd, chnl, it);


// if (chnl.getIsMode_l())
// {
// 	if (chnl.getChannelMembers().size() >= (size_t)chnl.getChannelLimit())/*ERR_CHANNELISFULL*/
// 		return (errorHandler(senderFd, 471, chnl.getChannelName()));
// }
// else if (chnl.getIsMode_i())
// {
// 	for(size_t i = 0; i < chnl.getInvitedMembers().size(); i++)
// 	{
// 		if (chnl.getInvitedMembers().at(i) == it->second->getNickName())
// 			return ;
// 	}
// 	return (errorHandler(senderFd, 473, chnl.getChannelName()));/*ERR_INVITEONLYCHAN*/
// }
// else if (chnl.getIsMode_b())
// {
// 	for(size_t i = 0; i < chnl.getChannelBannedMembers().size(); i++)
// 	{
// 		if (chnl.getChannelBannedMembers().at(i) == it->second->getNickName())
// 			return (errorHandler(senderFd, 474,  msg.getArguments().at(0)));/*ERR_BANNEDFROMCHAN*/
// 		/*banned with IP*/
// 	}
// }
// else if (chnl.getIsMode_s() || chnl.getIsMode_p())
// {
// 	if (chnl.getChannelkey() != msg.getArguments().at(1))
// 		return (errorHandler(senderFd, 475, msg.getArguments().at(0)));/*ERR_BADCHANNELKEY*/
// }
// else if (it->second->getJoinedChannels().size() >= (size_t)it->second->getClientMaxnumOfChannels() )/*ERR_TOOMANYCHANNELS*/
// 	return (errorHandler(senderFd, 405, msg.getArguments().at(0)));
// chnl.setChannelMembers(it->second->getNickName());
// it->second->setJoinedChannels(chnl.getChannelName());
// if (chnl.getIsMode_s())
// 	cmd_Resp_Handler(senderFd, 353, "@", chnl.getChannelName(), it->second->getNickName());
// else if (chnl.getIsMode_p())
// 	cmd_Resp_Handler(senderFd, 353, "*", chnl.getChannelName(), it->second->getNickName());
// else
// 	cmd_Resp_Handler(senderFd, 353, "=", chnl.getChannelName(), it->second->getNickName());
// cmd_Resp_Handler(senderFd, 332, chnl.getChannelName(), "...");


// if (!msg.getMultiArgs().empty() && msg.getArguments().size() > 1)
// {
// 	if (chnl.getChannelkey() != channelkey)
// 		return (errorHandler(senderFd, 475, chnl.getChannelName()));/*ERR_BADCHANNELKEY*/
// }
// if (!msg.getMultiArgs().empty() && msg.getArguments().empty())
// 	return (errorHandler(senderFd, 475, chnl.getChannelName()));/*ERR_BADCHANNELKEY*/
// else if (msg.getMultiArgs().empty() && msg.getArguments().size() > 1)
// {
// 	if (chnl.getChannelkey() != msg.getArguments().at(1))
// 		return (errorHandler(senderFd, 475, chnl.getChannelName()));/*ERR_BADCHANNELKEY*/
// }
// else if ((msg.getMultiArgs().empty() && msg.getArguments().size() == 1))
// 	return (errorHandler(senderFd, 475, chnl.getChannelName()));/*ERR_BADCHANNELKEY*/