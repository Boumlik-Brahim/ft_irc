/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:39:29 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/13 09:34:06 by iomayr           ###   ########.fr       */
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
Channel &Server::findChannel(std::string channelName)
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
	_channels.push_back(chnl);
}
void  Server::handleJoinCmd(Message &msg, int senderFd)
{
    std::string	receiver;
    std::string	channelName;
	std::string	cmd;
	Channel		tmpChannel;
	Channel		tmp;
	int			channelExist;

	// check if JOIN command have multiple channels
	checkMultiArgs(msg);
	checkChnlNames(msg.getMultiArgs(), senderFd);
	if (!msg.getMultiArgs().empty())
	{
		if (msg.getMultiArgs().size() > 2)/*ERR_TOOMANYTARGETS*/
			return (errorHandler(senderFd, 407, msg.getMultiArgs().at(0), "reduce the number of targets and try the request again"));
		for (size_t i = 0; i < msg.getMultiArgs().size(); i++)
		{
			channelName = msg.getMultiArgs().at(i);
			// if (!findChannelByName(channelName))/*ERR_NOSUCHCHANNEL*/
			// 	return (errorHandler(senderFd, 403, channelName));
			channelExist = findChannelByName(channelName);
			if (channelExist)
			{
				tmp = findChannel(channelName);
				if (tmp.getChannelMembers().size() > 9)/*ERR_CHANNELISFULL*/
					return (errorHandler(senderFd, 471, tmp.getChannelName()));
				// for(size_t i = 0; i < tmp.getChannelModes().size() ; i++)
				// {
				// 	if (tmp.getChannelModes().at(i) == "a")
				// 		void checkAnonymousChanFlag();
				// 	else if (tmp.getChannelModes().at(i) == "i")
				// 		void checkInviteOnlyChanFlag();
				// 	else if (tmp.getChannelModes().at(i) == "m")
				// 		void checkModeratedChan();
				// 	else if (tmp.getChannelModes().at(i) == "n")
				// 		void checkNoMsgToChannel();
				// 	else if (tmp.getChannelModes().at(i) == "q")
				// 		void checkQuietChanFlag();
				// 	else if (tmp.getChannelModes().at(i) == "p")
				// 		void PrivateChanFlag();
				// 	else if (tmp.getChannelModes().at(i) == "s")
				// 		void checkSecretChanFlag();
				// 	else if (tmp.getChannelModes().at(i) == "r")
				// 		void checkServerReopChanFlag();
				// 	else if (tmp.getChannelModes().at(i) == "t")
				// 		void checkTopic();
				// }
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
			// check mode
			// join user to channel
		}
		else
			createChannel(tmpChannel, senderFd, msg.getArguments().at(0));
	}
	if (msg.getMultiArgs().empty() && msg.getArguments().at(0).empty()) /*ERR_NEEDMOREPARAMS*/
		return (errorHandler(senderFd, 461, cmd));
	// else if ()/*ERR_INVITEONLYCHAN*/
	// 	return (errorHandler(senderFd, 473, channelName));
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
