/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:10:19 by iomayr            #+#    #+#             */
/*   Updated: 2023/02/13 16:50:39 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void Server::checkIfClientExist(int newSocketFd, std::string nickName)
{
    std::map<int, Client*>::iterator clientIt;
    
    clientIt = _mapClients.find(newSocketFd);
    if (clientIt == _mapClients.end())
        errorHandler(newSocketFd, 401, nickName);
}

void splitModes(Message &msg, std::string modes, int newSocketFd)
{
    std::string modeList = "OovaimnqpsrtklbeI";
    
    if (modes.at(0) == '+')
    {
        for (size_t i = 1; i < modes.size(); i++)
        {
            if (modeList.find(modes.at(i)) != std::string::npos)
                msg.setVecAddMode(modes.at(i));      
		    else
                errorHandler(newSocketFd, 472);//Unkown Mode 
        }    
    }
    else if (modes.at(0) == '-')
    {
        for (size_t i = 1; i < modes.size(); i++)
        {
            if (modeList.find(modes.at(i)) != std::string::npos)
                msg.setVecRmMode(modes.at(i));      
            else
		        errorHandler(newSocketFd, 472);//Unkown Mode 
                
        }    
    }
}

void Server::checkModes(Message &msg, int newSocketFd)
{
    size_t argSize = msg.getArguments().size();
    
    if (argSize >= 4)
    {
        if (msg.getArguments().at(1).at(0) != '+' || msg.getArguments().at(1).at(0) != '-')
        {
            splitModes(msg, msg.getArguments().at(1), newSocketFd);
            msg.setIsAddOrRm(msg.getArguments().at(1).at(0) == '+' ? true : false);
            if (msg.getArguments().at(2).at(0) != '+' || msg.getArguments().at(2).at(0) != '-')
                splitModes(msg, msg.getArguments().at(2), newSocketFd);    
            else
                errorHandler(newSocketFd, 472); //Unknown Mode
            for (int i = 0; i < 2; i++)
                msg.getArguments().erase(msg.getArguments().begin() + 1);
        }
        else
            errorHandler(newSocketFd, 472); //Unknown Mode 
    }
    else if (argSize >= 3)
    {
        if (msg.getArguments().at(1).at(0) != '+' || msg.getArguments().at(1).at(0) != '-'){
            msg.setIsAddOrRm(msg.getArguments().at(1).at(0) == '+' ? true : false);
            splitModes(msg, msg.getArguments().at(1), newSocketFd);
        }
        else
            errorHandler(newSocketFd, 472); //Unknown Mode
        msg.getArguments().erase(msg.getArguments().begin() + 1);
    }
    else if (argSize == 2)
    {
        if (msg.getArguments().at(1).at(0) != '+' || msg.getArguments().at(1).at(0) != '-'){
            msg.setIsAddOrRm(msg.getArguments().at(1).at(0) == '+' ? true : false);
            splitModes(msg, msg.getArguments().at(1), newSocketFd);
        }
        else
            errorHandler(newSocketFd, 472); //Unknown Mode
    }
    else
        errorHandler(newSocketFd, 461, msg.getCommand()); //Need More Arguments
}

void Server::exec_o(Message &msg, int newSocketFd, bool addOrRm)
{
    Channel     &tmpChannel = findChannel(msg.getArguments().at(0));
    std::string senderNick = findNickClientByFd(newSocketFd);
    std::string receiver = msg.getArguments().at(1);
    std::vector<std::string>::iterator itSender = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), senderNick);
    std::vector<std::string>::iterator itReceiver;
    
    if (addOrRm == true){
        itReceiver = std::find(tmpChannel.getChannelMembers().begin(), tmpChannel.getChannelMembers().end(), receiver);
        if (itSender != tmpChannel.getChannelOperators().end()){
            if (itReceiver != tmpChannel.getChannelMembers().end()){
                tmpChannel.getChannelOperators().push_back(receiver);
                tmpChannel.getChannelMembers().erase(itReceiver);
                msg.getArguments().erase(msg.getArguments().begin() + 1);
            }
            else{
                errorHandler(newSocketFd, 441, msg.getArguments().at(1), msg.getArguments().at(0)); //User is NOt in this channel  
            }
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
    else{
        itReceiver = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), receiver);
        if (itSender != tmpChannel.getChannelOperators().end()){
            if (itReceiver != tmpChannel.getChannelOperators().end()){
                tmpChannel.getChannelMembers().push_back(receiver);
                tmpChannel.getChannelOperators().erase(itReceiver);
                msg.getArguments().erase(msg.getArguments().begin() + 1);
            }
            else{
                errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
            }
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }   
    } 
}

void Server::exec_k(Message &msg, int newSocketFd, bool addOrRm)
{
    Channel     &tmpChannel = findChannel(msg.getArguments().at(0));
    std::string senderNick = findNickClientByFd(newSocketFd);
    std::string key = msg.getArguments().at(1);
    std::vector<std::string>::iterator itSender = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), senderNick);

    if (addOrRm == true){
        if (itSender != tmpChannel.getChannelOperators().end()){
            tmpChannel.setChannelkey(key);
            msg.getArguments().erase(msg.getArguments().begin() + 1);
            tmpChannel.setIsMode_k(true);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
    else{
        if (itSender != tmpChannel.getChannelOperators().end()){
            tmpChannel.setChannelkey("");
            tmpChannel.setIsMode_k(false);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
}

void Server::exec_l(Message &msg, int newSocketFd, bool addOrRm)
{
    Channel     &tmpChannel = findChannel(msg.getArguments().at(0));
    std::string senderNick = findNickClientByFd(newSocketFd);
    int         limit = atoi(msg.getArguments().at(1).c_str());
    std::vector<std::string>::iterator itSender = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), senderNick);

    // if (limit == 0)
        //Enter a Number Please
    if (addOrRm == true){
        if (itSender != tmpChannel.getChannelOperators().end()){
            tmpChannel.setChannelLimit(limit);
            msg.getArguments().erase(msg.getArguments().begin() + 1);
            tmpChannel.setIsMode_l(true);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
    else{
        if (itSender != tmpChannel.getChannelOperators().end()){
            tmpChannel.setChannelLimit(0);
            tmpChannel.setIsMode_l(false);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
}

void Server::exec_i(Message &msg, int newSocketFd, bool addOrRm)
{
    Channel     &tmpChannel = findChannel(msg.getArguments().at(0));
    std::string senderNick = findNickClientByFd(newSocketFd);
    std::vector<std::string>::iterator itSender = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), senderNick);

    if (addOrRm == true){
        if (itSender != tmpChannel.getChannelOperators().end()){
            tmpChannel.setIsMode_l(true);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
    else{
        if (itSender != tmpChannel.getChannelOperators().end()){
            tmpChannel.setIsMode_l(false);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
}


void Server::exec_p(Message &msg, int newSocketFd, bool addOrRm)
{
    Channel     &tmpChannel = findChannel(msg.getArguments().at(0));
    std::string senderNick = findNickClientByFd(newSocketFd);
    std::vector<std::string>::iterator itSender = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), senderNick);

    if (addOrRm == true){
        if (itSender != tmpChannel.getChannelOperators().end()){
            tmpChannel.setIsMode_p(true);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
    else{
        if (itSender != tmpChannel.getChannelOperators().end()){
            tmpChannel.setIsMode_p(false);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
}

void Server::exec_s(Message &msg, int newSocketFd, bool addOrRm)
{
    Channel     &tmpChannel = findChannel(msg.getArguments().at(0));
    std::string senderNick = findNickClientByFd(newSocketFd);
    std::vector<std::string>::iterator itSender = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), senderNick);

    if (addOrRm == true){
        if (itSender != tmpChannel.getChannelOperators().end()){
            tmpChannel.setIsMode_s(true);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
    else{
        if (itSender != tmpChannel.getChannelOperators().end()){
            tmpChannel.setIsMode_s(false);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
}

void Server::exec_t(Message &msg, int newSocketFd, bool addOrRm)
{
    Channel     &tmpChannel = findChannel(msg.getArguments().at(0));
    std::string senderNick = findNickClientByFd(newSocketFd);
    std::string topic = msg.getArguments().at(1);
    std::vector<std::string>::iterator itSender = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), senderNick);

    if (addOrRm == true){
        if (tmpChannel.getIsMode_t()){
            if (itSender != tmpChannel.getChannelOperators().end()){
                tmpChannel.setChannelTopic(topic);
                tmpChannel.setIsMode_t(true);
            }
            else{
                errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
            }
        }
        else{
            tmpChannel.setChannelTopic(topic);
            tmpChannel.setIsMode_t(true);
        }
    }
    else{
        if (itSender != tmpChannel.getChannelOperators().end()){
            tmpChannel.setIsMode_t(false);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
}

void Server::execMode(Message &msg, char mode, int newSocketFd, bool addOrRm)
{
    if (mode == 'o')
        exec_o(msg, newSocketFd, addOrRm);
    if (mode == 'k')
        exec_k(msg, newSocketFd, addOrRm);
    if (mode == 'l')
        exec_l(msg, newSocketFd, addOrRm);
    if (mode == 'i')
        exec_i(msg, newSocketFd, addOrRm);
    if (mode == 'p')
        exec_p(msg, newSocketFd, addOrRm);   
    if (mode == 's')
        exec_s(msg, newSocketFd, addOrRm);  
    if (mode == 't')
        exec_t(msg, newSocketFd, addOrRm);  
    // if (mode == 'n')
    // {
        
    // }
}

void Server::executeModes(Message &msg, int newSocketFd)
{
    if (msg.getIsAddOrRm() == true){
        for (size_t i = 0; i < msg.getVecAddMode().size(); i++)
            execMode(msg, msg.getVecAddMode().at(i), newSocketFd, true);
        for (size_t i = 0; i < msg.getVecRmMode().size(); i++)
            execMode(msg, msg.getVecAddMode().at(i), newSocketFd, true);
    }
    else{
        for (size_t i = 0; i < msg.getVecRmMode().size(); i++)
            execMode(msg, msg.getVecAddMode().at(i), newSocketFd, false);
        for (size_t i = 0; i < msg.getVecAddMode().size(); i++)
            execMode(msg, msg.getVecAddMode().at(i), newSocketFd, false);
    }
}


void Server::handleModeCmd(Message &msg, int newSocketFd)
{
    std::vector<std::string> tmpArgs;

    if (msg.getArguments().empty())
        errorHandler(newSocketFd, 461, msg.getCommand());
    if (msg.getArguments().at(0).at(0) == '#')
    {
        if (findChannelByName(msg.getArguments().at(0))){
            checkModes(msg, newSocketFd);
            executeModes(msg, newSocketFd);
        }
        else
            errorHandler(newSocketFd, 401, msg.getArguments().at(0)); //No channel found
    }
    else{
        //Invalid arg
    }
}