/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:39:29 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/07 10:09:17 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void  Server::handleJoinCmd(Message &msg, Channel &chnl, int senderFd)
{
    std::string	receiver;
    std::string	channelName;
	std::string	cmd;

	(void)senderFd;
	receiver = msg.getArguments()[0];
	channelName = chnl.getChannelName();
	cmd = msg.getCommand();

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