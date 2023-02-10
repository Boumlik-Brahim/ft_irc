/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelCommands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:32:47 by izail             #+#    #+#             */
/*   Updated: 2023/02/10 11:34:28 by izail            ###   ########.fr       */
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

int Server::findUserInChannel(std::string sender, Channel chnl)
{
    for (size_t i = 0; i < chnl.getChannelMembers().size(); i++)
    {
        if (chnl.getChannelMembers().at(i) == sender)
            return 1;
    }
    return 0;
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
    Channel         &tmpChnl  = findChannel(channelName);
    sender = findNickClientByFd(senderFd);
    
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

    std::cout << "Hello from NAMES\n";
    // check if user is authenticated
    if (!_mapClients[senderFd]->getIsAuthValid())
		errorHandler(senderFd, 451);
    
    sender = findNickClientByFd(senderFd);
    
    if (msg.getArguments().size() != 0)
        checkMultiArgs(msg);
    else if (msg.getArguments().size() == 0 && msg.getMultiArgs().size() == 0)
    {
        std::cout << "khass ytprintaw ga3 channels bl users dialhom\n";
        // if (_channels.size() == 0)
            errorHandler(senderFd, 451);
            // cmd_Resp_Handler(senderFd, 366, "irc" ,sender, "*");
        // else
        //     std::cout << "kayna chi channel\n";
    }
    // list a channel and it users
    if (!msg.getMultiArgs().empty())
    {
        for (size_t i = 0; i < msg.getMultiArgs().size(); i++)
        {
            channelName = msg.getMultiArgs().at(i);
            channelExist = findChannelByName(channelName);
            if (!channelExist)
                errorHandler(senderFd, 401, channelName);
            Channel &tmpChnl  = findChannel(channelName);
            // messageForm = "Channel Name ==" + tmpChnl.getChannelName();
            sendMessage(senderFd, messageForm);
            // std::cout << "channel member size ==" << tmpChnl.getChannelMembers().size() << std::endl;
            for (size_t i = 0; i < tmpChnl.getChannelMembers().size(); i++)
            {
                messageForm = "Member :" + tmpChnl.getChannelMembers().at(i);
                sendMessage(senderFd, messageForm);
            }
            // cmd_Resp_Handlers(senderFd, 366, channelName);
            
        }
    }
    // list all channels and their users
    else if (msg.getArguments().size() > 0)
    {
        std::cout << "dkhel hna\n";
        channelName = msg.getArguments()[0];
        // check if channel exist
        channelExist = findChannelByName(channelName);
        if (!channelExist)
            errorHandler(senderFd, 401, channelName);
        Channel &tmpChnl  = findChannel(channelName);
        // std::cout << "Channel Name ==" << tmpChnl.getChannelName() << std::endl;
        // messageForm = "Channel Name ==" + tmpChnl.getChannelName();
        sendMessage(senderFd, messageForm);
        for (size_t i = 0; i < tmpChnl.getChannelMembers().size(); i++)
        {
            messageForm = "Member :" + tmpChnl.getChannelMembers().at(i);
            sendMessage(senderFd, messageForm);
        }
        cmd_Resp_Handler(senderFd, 366, channelName);
    }
    // list all visible users
}