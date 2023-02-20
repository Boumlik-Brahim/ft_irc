/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelCommands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:30:30 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/20 17:46:37 by izail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/Server.hpp"

bool Server::findChannelOperator(std::string sender, Channel chnl)
{
    for (size_t i = 0; i < chnl.getChannelOperators().size(); i++)
        if (chnl.getChannelOperators().at(i) == sender)
            return (true);
    return (false);
}

bool Server::findUserInChannel(std::string sender, Channel &chnl)
{
    for (size_t i = 0; i < chnl.getChannelMembers().size(); i++)
    {
        if (chnl.getChannelMembers().at(i) == sender)
            return true;
    }
    return false;
}

Client&     Server::findClient(std::string nickName)
{
    for (std::map<int, Client *>::iterator it = _mapClients.begin(); it != _mapClients.end() ; it++)
    {
        if (it->second->getNickName() == nickName)
            return *(it->second);  
    }
    throw "client not found";
}

bool Server::checkIfClientIsMember(Channel &chnl, std::string clientName)
{
    for (size_t i = 0; i < chnl.getChannelMembers().size() ; i++)
        if (chnl.getChannelMembers().at(i) == clientName)
            return true;
    return false;
}

bool    Server::checkInvitedChannels(Client &client, std::string channelName)
{
    for(size_t i = 0; i < client.getInvitedChannels().size(); i++)
    {
        if (client.getInvitedChannels().at(i) == channelName)
            return true;
    }
    return false;
}

std::string Server::findClientWithNoChannel()
{
    std::string ChannelClients = "";
    
    for (std::map<int, Client *>::iterator it = _mapClients.begin(); it != _mapClients.end() ; it++)
    {
        if (it->second->getJoinedChannels().size() == 0)
            ChannelClients += it->second->getNickName().append(" ");
    }
    return ChannelClients;
}

void checkMultiArgs2(Message &msg)
{
	std::vector<std::string> 			tmpArgs;

	if (msg.getArguments().at(1).find(',') != std::string::npos)
	{
		tmpArgs = splitBySeparator(msg.getArguments().at(1), ",");
		msg.setMultiArgs(tmpArgs);
		msg.erase(msg.getArguments().begin());
		if (msg.getArguments().size())
		{
			if (msg.getArguments().at(1).find(',') != std::string::npos)
			{
				tmpArgs = splitBySeparator(msg.getArguments().at(1), ",");
				msg.setArguments(tmpArgs);
			}
		}
	}
}

void    Server::handleTopicCmd(Message &msg, int senderFd)
{
    std::string     channelName;
    std::string     topic;
    std::string     sender;
    int             channelExist;
    std::string     cmd = msg.getCommand();
    int             isUserInChannel;

    // check params
    if (msg.getArguments().size() == 0 || msg.getArguments()[0] == ":")
        errorHandler(461, cmd);
        
    // check user is authenticated
    if (!_mapClients[senderFd]->getIsAuthValid())
		errorHandler(451);
    // check if channel exist
    channelName = msg.getArguments()[0];
    channelExist = findChannelByName(msg.getArguments()[0]);
    if (!channelExist)
        errorHandler(401, channelName);
    sender = findNickClientByFd(senderFd);
    
    Channel         &tmpChnl  = findChannel(channelName);
    // check the mode 't' is set
    if (tmpChnl.getIsMode_t())
    {
        // if mode 't' is true then check if the user who wants to change topic is operator
        if (!findChannelOperator(sender, tmpChnl))
            errorHandler(482, sender);
        // check if channel has topic before
        if ((msg.getArguments().size() > 1))
        {
            topic = msg.getArguments()[1];
            if (topic.size() > 1 && topic.at(0) == ':')
            {
                topic = topic.substr(1, topic.size());
                tmpChnl.setChannelTopic(topic);
                cmd_Resp_Handler(senderFd, 332, channelName, tmpChnl.getChannelTopic());   
            }
            // set topic empty
            else if (topic.at(0) == ':' && topic.size() == 1)
                tmpChnl.setChannelTopic("");
        }
        else if (msg.getArguments().size() == 1)
        {
            if (tmpChnl.getChannelTopic().size() == 0)
                cmd_Resp_Handler(senderFd, 331, channelName);
            else
                cmd_Resp_Handler(senderFd, 332, channelName, tmpChnl.getChannelTopic());
        }
    }
    else
    {
        // check if user in channel
        isUserInChannel = findUserInChannel(sender, tmpChnl);
        if (isUserInChannel)
        {
            // check if channel has topic before
            if ((msg.getArguments().size() > 1))
            {
                topic = msg.getArguments()[1];
                if (topic.size() > 1 && topic.at(0) == ':')
                {
                    topic = topic.substr(1, topic.size());
                    tmpChnl.setChannelTopic(topic);
                    cmd_Resp_Handler(senderFd, 332, channelName, tmpChnl.getChannelTopic());   
                }
                else if (topic.at(0) == ':' && topic.size() == 1)
                    tmpChnl.setChannelTopic("");
            }
            else if (msg.getArguments().size() == 1)
            {
                if (tmpChnl.getChannelTopic().size() == 0)
                    cmd_Resp_Handler(senderFd, 331, channelName);
                else
                    cmd_Resp_Handler(senderFd, 332, channelName, tmpChnl.getChannelTopic());
            }
        }
        else
            errorHandler(442, sender);
    }
}

void    Server::handleNamesCmd(Message &msg, int senderFd)
{
    std::string     channelName;
    std::string     topic;
    std::string     sender;
    int             channelExist;
    std::string     cmd = msg.getCommand();
    std::string     messageForm;
    std::string     ChannelClients = "";
	std::string		creator;

    // check if user is authenticated
    if (!_mapClients[senderFd]->getIsAuthValid())
		errorHandler(451);
    
    sender = findNickClientByFd(senderFd);
    
    if (msg.getArguments().size() != 0)
        checkMultiArgs(msg);
    // if only Command NAMES typed , then it prints the list of channels and the users who are not in any channel and visible
    else if (msg.getArguments().size() == 0 && msg.getMultiArgs().size() == 0)
    {        
        if (_channels.size() > 0)
        {    
            for (size_t i = 0; i < _channels.size(); i++)
            {
                Channel &tmpChnl = findChannel(_channels.at(i).getChannelName());
                if (!tmpChnl.getIsMode_p() && !tmpChnl.getIsMode_s())
                {
                    ChannelClients = "";
                    for (size_t i = 0; i < tmpChnl.getChannelMembers().size(); i++)
                        ChannelClients = ChannelClients.append(" ") + tmpChnl.getChannelMembers().at(i);
                    cmd_Resp_Handler1(senderFd, 353, _server_name, sender, tmpChnl.getChannelName(), ChannelClients , std::string(""));
                }
            }
        }
        ChannelClients = findClientWithNoChannel();
        if (ChannelClients.size() > 0)
            cmd_Resp_Handler1(senderFd, 353, _server_name, sender, std::string("*") , ChannelClients, std::string(""));    
    }
    // list all channels and their users
    if (!msg.getMultiArgs().empty())
    {
        for (size_t i = 0; i < msg.getMultiArgs().size(); i++)
        {
            channelName = msg.getMultiArgs().at(i);
            channelExist = findChannelByName(channelName);
            if (channelExist)
            {
                ChannelClients = "";
                Channel tmpChnl  = findChannel(channelName);
                if (tmpChnl.getIsMode_p() == false && tmpChnl.getIsMode_s() == false)
                {
                    for (size_t i = 0; i < tmpChnl.getChannelMembers().size(); i++)
                        ChannelClients += tmpChnl.getChannelMembers().at(i);
                    cmd_Resp_Handler1(senderFd, 353, _server_name, sender, tmpChnl.getChannelName(), ChannelClients , std::string(""));
                }
            }
        }
    }
    // list a single channel and their users
    else if (msg.getArguments().size() > 0)
    {
        channelName = msg.getArguments()[0];
        // check if channel exist
        channelExist = findChannelByName(channelName);
        if (channelExist)
        {
            Channel tmpChnl  = findChannel(channelName);
            if (tmpChnl.getIsMode_p() == false && tmpChnl.getIsMode_s() == false)
            {
                for (size_t i = 0; i < tmpChnl.getChannelMembers().size(); i++)
                    ChannelClients += tmpChnl.getChannelMembers().at(i).append(" ");
                cmd_Resp_Handler1(senderFd, 353, _server_name, sender, tmpChnl.getChannelName(), ChannelClients, "");
            }  
        }
    }
    cmd_Resp_Handler1(senderFd, 366, _server_name, sender, std::string("*") , std::string("") , std::string(""));
}

void    Server::handleListCmd(Message &msg, int senderFd)
{
    std::string     channelName;
    std::string     topic;
    std::string     sender;
    int             channelExist;
    std::string     cmd = msg.getCommand();
    std::string     messageForm;

    // check if user is authenticated
    if (!_mapClients[senderFd]->getIsAuthValid())
		errorHandler(451);

    sender = findNickClientByFd(senderFd);
    
    cmd_Resp_Handler1(senderFd, 321, _server_name, sender);
    
    if (msg.getArguments().size() != 0)
        checkMultiArgs(msg);
    // if no Args nor Multiargs , then it will print the channels and the number of users in it with their topic. 
    else if (msg.getArguments().size() == 0 && msg.getMultiArgs().size() == 0)
    {   
        for (size_t i = 0; i < _channels.size(); i++)
        {
            channelName = _channels.at(i).getChannelName();
            channelExist = findChannelByName(channelName);
            if (channelExist)
            {
                Channel &tmpChnl  = findChannel(channelName);
                // check if the channel is not private nor secret and also if the user requesting is member of that channel
                if (tmpChnl.getIsMode_s() == false && tmpChnl.getIsMode_p() == false 
                    && checkIfClientIsMember(tmpChnl, sender) == true)
                        cmd_Resp_Handler1(senderFd, 322, _server_name , sender , tmpChnl.getChannelName(), std::to_string(tmpChnl.getChannelMembers().size()), tmpChnl.getChannelTopic());
            }
        }
    }
    // list a channel and it users
    if (!msg.getMultiArgs().empty())
    {
        for (size_t i = 0; i < msg.getMultiArgs().size(); i++)
        {
            channelName = msg.getMultiArgs().at(i);
            channelExist = findChannelByName(channelName);
            if (channelExist)
            {
                Channel &tmpChnl  = findChannel(channelName);
                if (tmpChnl.getIsMode_s() == false && checkIfClientIsMember(tmpChnl, sender) == true)
                    cmd_Resp_Handler1(senderFd, 322, _server_name ,  sender ,tmpChnl.getChannelName(), std::to_string(tmpChnl.getChannelMembers().size()), tmpChnl.getChannelTopic());
            }
        }
    }
    // list single channel, it's number of users and topic 
    else if (msg.getArguments().size() > 0)
    {
        channelName = msg.getArguments()[0];
        channelExist = findChannelByName(channelName);
        if (channelExist)
        {
            Channel &tmpChnl  = findChannel(channelName);
            if (tmpChnl.getIsMode_s() == false && checkIfClientIsMember(tmpChnl, sender) == true)
                cmd_Resp_Handler1(senderFd, 322, _server_name ,  sender ,tmpChnl.getChannelName(), std::to_string(tmpChnl.getChannelMembers().size()), tmpChnl.getChannelTopic());
        }
    }
    cmd_Resp_Handler1(senderFd, 323, _server_name, sender);
}


void    Server::handleInviteCmd(Message &msg, int senderFd)
{
    std::string     channelName = "";
    std::string     sender = "";
    std::string     receiver = "";
    int             channelExist = -1;
    int             clientExist = -1;
    std::string     cmd = msg.getCommand();
    std::string     messageForm = "";
    char			hostname[256];

    // check if user is authenticated
    if (!_mapClients[senderFd]->getIsAuthValid())
		errorHandler(451);
    
    if (msg.getArguments().empty())
		errorHandler(461, msg.getCommand());

    sender = findNickClientByFd(senderFd);
    receiver = msg.getArguments()[0];
    channelName = msg.getArguments()[1];
    channelExist = findChannelByName(channelName);
    clientExist = findFdClientByNick(receiver, senderFd);
    gethostname(hostname, sizeof(hostname));
    
    // check if the channel exist to perform the INVITE command
    if (channelExist && clientExist)
    {
        Client &target = findClient(receiver);
        Channel &tmpChannel = findChannel(channelName);
        // check if channel has invite-only flag set
        if (tmpChannel.getIsMode_i())
        {
            // check if the inviter is operator or not
            if (findChannelOperator(sender, tmpChannel))
            {
                // check if the channel the receiver being invited to is exist in his invitedChannels
                if (checkInvitedChannels(target, tmpChannel.getChannelName()))
                {
                    std::cout << "Client is already invited to this channel\n";
                }
                // else the invitation will be sent and the channel will be added to his _invitedChannels
                else
                {
                    target.setInvitedChannels(tmpChannel.getChannelName());
                    cmd_Resp_Handler1(senderFd, 341, _server_name, sender, tmpChannel.getChannelName(), target.getNickName(), std::string(""));
                    std::string rpl = ":" + sender + "!~" + sender + "@" + hostname + " INVITE " + " " + "  to  " + tmpChannel.getChannelName() +  "\r\n";
                    sendReplay(target.getClientFd(), rpl);
                }
            }
            else
                errorHandler(482, sender);
        }
        else
        {
            // check if inviter is member of the channel
            if (findUserInChannel(sender, tmpChannel) == 1)
            {
                if (findUserInChannel(target.getNickName(), tmpChannel))
                    errorHandler(443, target.getNickName(), tmpChannel.getChannelName());
                else
                {
                    target.setInvitedChannels(tmpChannel.getChannelName());
                    cmd_Resp_Handler1(senderFd, 341, _server_name, sender, tmpChannel.getChannelName(), target.getNickName(), std::string(""));
                    std::string rpl = ":" + sender + "!~" + sender + "@" + hostname + " INVITE " + " " + "  to  " + tmpChannel.getChannelName() +  "\r\n";
                    sendReplay(target.getClientFd(), rpl);
                }
            }
            else
                errorHandler(442, sender);
            // else he needs to be a member to perform te INVITE command
        }
    }
    else
        errorHandler(403, channelName);
}

void    Server::handleKickCmd(Message &msg, int senderFd)
{
    std::string     channelName = "";
    std::string     reason = "";
    std::string     sender = "";
    int             channelExist = 0;
    std::string     cmd = msg.getCommand();
    std::string     messageForm = "";
    std::string     ChannelClients = "";
    std::string     receiver;
    char			hostname[256];
    int             fd;
    
    // check if user is authenticated
    if (!_mapClients[senderFd]->getIsAuthValid())
		errorHandler(451);
        
    sender = findNickClientByFd(senderFd);
    if (msg.getArguments().size() < 2)
        errorHandler(461, "KICK");
    
    channelName = msg.getArguments()[0];
    channelExist = findChannelByName(channelName);
    std::vector<std::string> _users = splitBySeparator(msg.getArguments()[1], ",");
    gethostname(hostname, sizeof(hostname));

    if (channelExist)
    {
        Channel &tmpChannel  = findChannel(channelName);
        if (findChannelOperator(sender, tmpChannel))
        {    
            for (size_t i = 0; i < _users.size(); i++)
            {
                if (findFdClientByNick(_users.at(i)) != -1)
                {
                    Client &target = findClient(_users.at(i));
                    if (findUserInChannel(target.getNickName(), tmpChannel))
                    {
                        std::vector<std::string>::iterator it = tmpChannel.getChannelMembers().begin();
                        for (; it != tmpChannel.getChannelMembers().end(); ++it)
                        {
                            if (*it == target.getNickName())
                            {
                                if (msg.getArguments().size() == 3)
                                {
                                    reason = msg.getArguments()[2];
                                    reason = reason.substr(1, reason.size());
                                }              
                                std::string rpl = ":" + sender + "!~" + sender + "@" + hostname + " KICK " + tmpChannel.getChannelName() + " " + target.getNickName() + " " + reason +"\r\n";
                                for (size_t j = 0; j < tmpChannel.getChannelMembers().size() ; j++)
                                {
                                    fd = findFdClientByNick(tmpChannel.getChannelMembers().at(j));
                                    sendReplay(fd, rpl);
                                }
                                tmpChannel.getChannelMembers().erase(it);
                                std::vector<std::string>::iterator it1 = std::find(target.getJoinedChannels().begin(), target.getJoinedChannels().end(), tmpChannel.getChannelName());
                                target.getJoinedChannels().erase(it1);
                                break;
                            }
                        }
                    }
                    else
                        errorHandler(441, _users.at(i)); // ERR_USERNOTINCHANNE
                }
                else
                    errorHandler(401, _users.at(i));
            }
        }
        else
            errorHandler(482, sender);
    }
    else
        errorHandler(403, channelName);
    
    // check if channel exists
    // check if user exist
    // check if user exists in that channel
    // check if the kicker is operator on that channel  
}