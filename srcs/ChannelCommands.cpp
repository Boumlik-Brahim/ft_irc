/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelCommands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:32:47 by izail             #+#    #+#             */
/*   Updated: 2023/02/14 18:24:00 by izail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

int Server::findChannelOperator(std::string sender, Channel chnl)
{
    for (size_t i = 0; i < chnl.getChannelOperators().size(); i++)
        if (chnl.getChannelOperators().at(i) == sender)
            return (1);
    return (0);
}

int Server::findUserInChannel(std::string sender, Channel &chnl)
{
    for (size_t i = 0; i < chnl.getChannelMembers().size(); i++)
    {
        if (chnl.getChannelMembers().at(i) == sender)
            return 1;
    }
    return 0;
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

// Client& Server::findClient(std::string nickName)
// {
//     for (std::map<int, Client *>::iterator it = _mapClients.begin(); it != _mapClients.end() ; it++)
//     {
//         if (it->second->getNickName() == nickName)
//             return it->second;
//     }
//     throw "client not found";
// }

void    Server::handleTopicCmd(Message &msg, int senderFd)
{
    std::string     channelName;
    std::string     topic;
    std::string     sender;
    int             channelExist;
    std::string     cmd = msg.getCommand();
    int             isUserInChannel;

    // check params
    if (!msg.getArguments().size())
        errorHandler(senderFd, 461, cmd);
    // check user is authenticated
    if (!_mapClients[senderFd]->getIsAuthValid())
		errorHandler(senderFd, 451);
    // check if channel exist
    channelName = msg.getArguments()[0];
    channelExist = findChannelByName(msg.getArguments()[0]);
    if (!channelExist)
        errorHandler(senderFd, 401, channelName);
    sender = findNickClientByFd(senderFd);
    
    Channel         &tmpChnl  = findChannel(channelName);
    // check the mode 't' is set
    if (tmpChnl.getIsMode_t())
    {
        // if mode 't' is true then check if the user who wants to change topic is operator
        if (!findChannelOperator(sender, tmpChnl))
            errorHandler(senderFd, 482, sender);
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
            errorHandler(senderFd, 442, sender);
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
		errorHandler(senderFd, 451);
    
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
                Channel tmpChnl = _channels.at(i);
                if (tmpChnl.getIsMode_p() == false && tmpChnl.getIsMode_s() == false)
                {
                    ChannelClients = "";
                    for (size_t i = 0; i < tmpChnl.getChannelMembers().size(); i++)
                        ChannelClients += tmpChnl.getChannelMembers().at(i).append(" ");
                    cmd_Resp_Handler1(senderFd, 353, _server_name, sender, tmpChnl.getChannelName(), ChannelClients , std::string(""));
                }
            }
        }
        ChannelClients = findClientWithNoChannel();
        std::cout << "channel Clients ==" << ChannelClients << std::endl;
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
                        ChannelClients += tmpChnl.getChannelMembers().at(i).append(" ");
                    cmd_Resp_Handler1(senderFd, 353, _server_name, sender, tmpChnl.getChannelName(), ChannelClients , std::string(""));
                }
            }
        }
    }
    // list a single channel and their users
    else if (msg.getArguments().size() > 0)
    {
        std::cout << "dkhel hna\n";
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
		errorHandler(senderFd, 451);
    
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
            std::cout << "dkhel l mulitargs\n";
            channelName = msg.getMultiArgs().at(i);
            channelExist = findChannelByName(channelName);
            std::cout << "chan exist ==" << channelExist << std::endl;
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
    int             channelExist = 0;
    std::string     cmd = msg.getCommand();

    // check if user is authenticated
    if (!_mapClients[senderFd]->getIsAuthValid())
		errorHandler(senderFd, 451);
    
    sender = findNickClientByFd(senderFd);
    receiver = msg.getArguments()[0];
    channelName = msg.getArguments()[1];
    channelExist = findChannelByName(channelName);
    // check if the channel exist to perform the INVITE command
    if (channelExist)
    {
        Channel &tmpChannel = findChannel(channelName);
        // check if channel has invite-only flag set
        if (tmpChannel.getIsMode_i())
        {
            // check if the inviter is operator or not
            if (findChannelOperator(sender, tmpChannel) == 1)
            {
                // check if the channel the receiver being invited to is exist in his invitedChannels
                // else the invitation will be sent and the channel will be added to his _invitedChannels
            }
            else
                errorHandler(senderFd, 482, sender);
        }
        else
        {
            std::cout << "channel without flag i" << std::endl;
            // check if inviter is member of the channel
            if (findUserInChannel(sender, tmpChannel) == 1)
            {
                std::cout << "channel without flag i" << std::endl;
                Client &target = findClient(receiver);
                if (findUserInChannel(target.getNickName(), tmpChannel))
                    errorHandler(senderFd, 443, target.getNickName(), tmpChannel.getChannelName());
                else
                {
                    std::cout << "dkhel hna\n";
                    target.setInvitedChannels(tmpChannel.getChannelName());
                    cmd_Resp_Handler1(senderFd, 341, _server_name, sender, tmpChannel.getChannelName(), target.getNickName(), std::string(""));
                    std::cout << "fd dial l client" << target.getClientFd() <<std::endl;
                    sendMessage(target.getClientFd(), "SENDER invited you to #channel");
                }
            }
            else
                errorHandler(senderFd, 442, sender);
            // else he needs to be a member to perform te INVITE command
        }
    }
}