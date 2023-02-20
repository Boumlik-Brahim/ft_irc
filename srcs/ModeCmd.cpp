/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:10:19 by iomayr            #+#    #+#             */
/*   Updated: 2023/02/20 16:32:11 by iomayr           ###   ########.fr       */
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
        std::cout << "set in AddVec" << std::endl;
        for (size_t i = 1; i < modes.size(); i++)
        {
            std::cout << modes.at(i) << std::endl;
            if (modeList.find(modes.at(i)) != std::string::npos)
                msg.setVecAddMode(modes.at(i));      
		    else
                errorHandler(newSocketFd, 472, std::string(1, modes.at(i)));//Unkown Mode 
        }    
    }
    else if (modes.at(0) == '-')
    {
        std::cout << "set in RmVec" << std::endl;
        for (size_t i = 1; i < modes.size(); i++)
        {
            std::cout << modes.at(i) << std::endl;
            if (modeList.find(modes.at(i)) != std::string::npos){
                msg.setVecRmMode(modes.at(i));      
            }
            else{
		        errorHandler(newSocketFd, 472, std::string(1, modes.at(i)));//Unkown Mode 
            }
                
        }    
    }
}

void Server::checkModes(Message &msg, int newSocketFd)
{
    size_t argSize = msg.getArguments().size();
    
    if (argSize >= 4)
    {
        if (msg.getArguments().at(1).at(0) == '+' || msg.getArguments().at(1).at(0) == '-')
        {
            splitModes(msg, msg.getArguments().at(1), newSocketFd);
            msg.setIsAddOrRm(msg.getArguments().at(1).at(0) == '+' ? true : false);
            msg.getArguments().erase(msg.getArguments().begin() + 1);
            if (msg.getArguments().at(1).at(0) == '+' || msg.getArguments().at(1).at(0) == '-')
            {
                splitModes(msg, msg.getArguments().at(1), newSocketFd);    
                msg.getArguments().erase(msg.getArguments().begin() + 1);
            }
        }
        else
            errorHandler(newSocketFd, 472, std::string(1, msg.getArguments().at(1).at(0)));//Unkown Mode
    }
    else if (argSize >= 3)
    {
        if (msg.getArguments().at(1).at(0) != '+' || msg.getArguments().at(1).at(0) != '-'){
            msg.setIsAddOrRm(msg.getArguments().at(1).at(0) == '+' ? true : false);
            splitModes(msg, msg.getArguments().at(1), newSocketFd);
        }
        else
            errorHandler(newSocketFd, 472, std::string(1, msg.getArguments().at(1).at(0)));//Unkown Mode
        msg.getArguments().erase(msg.getArguments().begin() + 1);
    }
    else if (argSize == 2)
    {
        if (msg.getArguments().at(1).at(0) != '+' || msg.getArguments().at(1).at(0) != '-'){
            msg.setIsAddOrRm(msg.getArguments().at(1).at(0) == '+' ? true : false);
            splitModes(msg, msg.getArguments().at(1), newSocketFd);
            msg.getArguments().erase(msg.getArguments().begin() + 1);
        }
        else
            errorHandler(newSocketFd, 472, std::string(1, msg.getArguments().at(1).at(0)));//Unkown Mode
    }
    else
        errorHandler(newSocketFd, 461, msg.getCommand()); //Need More Arguments
}

void Server::exec_o(Message &msg, int newSocketFd, bool addOrRm)
{
    Channel     &tmpChannel = findChannel(msg.getArguments().at(0));
    std::string senderNick = findNickClientByFd(newSocketFd);
    std::vector<std::string>::iterator itSender = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), senderNick);
    std::vector<std::string>::iterator itReceiver;
    
    if (msg.getArguments().size() == 1)
        errorHandler(newSocketFd, 461, msg.getCommand()); //Need More Arguments
    if (addOrRm == true){
        itReceiver = std::find(tmpChannel.getChannelMembers().begin(), tmpChannel.getChannelMembers().end(), msg.getArguments().at(1));
        if (itSender != tmpChannel.getChannelOperators().end()){
            if (itReceiver != tmpChannel.getChannelMembers().end()){
                tmpChannel.getChannelOperators().push_back(msg.getArguments().at(1));
                tmpChannel.getChannelMembers().erase(itReceiver);
                msg.getArguments().erase(msg.getArguments().begin() + 1);
            }
            else{
                errorHandler(newSocketFd, 441, msg.getArguments().at(1), msg.getArguments().at(0)); //User is Not in this channel  
            }
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
    else{
        itReceiver = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), msg.getArguments().at(1));
        if (itSender != tmpChannel.getChannelOperators().end()){
            if (itReceiver != tmpChannel.getChannelOperators().end()){
                tmpChannel.getChannelMembers().push_back(msg.getArguments().at(1));
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
    std::vector<std::string>::iterator itSender = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), senderNick);

    if (addOrRm == true){
        if (msg.getArguments().size() == 1)
            errorHandler(newSocketFd, 461, msg.getCommand()); //Need More Arguments
        if (!tmpChannel.getIsMode_k()){
            if (itSender != tmpChannel.getChannelOperators().end()){
                tmpChannel.setChannelkey(msg.getArguments().at(1));
                msg.getArguments().erase(msg.getArguments().begin() + 1);
                std::cout << "key setted Successfully" << std::endl;
                tmpChannel.setIsMode_k(true);
            }
            else{
                errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
            }
        }
        else{
            errorHandler(newSocketFd, 467, msg.getArguments().at(0));
        }
    }
    else{
        if (itSender != tmpChannel.getChannelOperators().end()){
            std::cout << "key removed Successfully" << std::endl;
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
    std::vector<std::string>::iterator itSender = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), senderNick);

    if (addOrRm == true){
        if (msg.getArguments().size() == 1)
            errorHandler(newSocketFd, 461, msg.getCommand()); //Need More Arguments
        int limit = atoi(msg.getArguments().at(1).c_str());
        if (limit == 0){
            errorHandler(newSocketFd, 472, "Limit");//Unkown Mode
        }
        if (itSender != tmpChannel.getChannelOperators().end()){
            tmpChannel.setChannelLimit(limit);
            msg.getArguments().erase(msg.getArguments().begin() + 1);
            std::cout << "limit setted Successfully" << std::endl;
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
            std::cout << "limit removed Successfully" << std::endl;
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
}

void Server::exec_b(Message &msg, int newSocketFd, bool addOrRm)
{
    Channel     &tmpChannel = findChannel(msg.getArguments().at(0));
    std::string senderNick = findNickClientByFd(newSocketFd);
    std::vector<std::string>::iterator itSender = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), senderNick);

    if (msg.getArguments().size() == 1)
        errorHandler(newSocketFd, 461, msg.getCommand()); //Need More Arguments
    std::vector<std::string>::iterator itReceiver = std::find(tmpChannel.getChannelBannedMembers().begin(), tmpChannel.getChannelBannedMembers().end(), msg.getArguments().at(1));
    std::vector<std::string>::iterator itReceiver1 = std::find(tmpChannel.getChannelMembers().begin(), tmpChannel.getChannelMembers().end(), msg.getArguments().at(1));
    std::vector<std::string>::iterator itReceiver2 = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), msg.getArguments().at(1));
    
    if (addOrRm == true){
        if (itSender != tmpChannel.getChannelOperators().end()){
            if (itReceiver1 != tmpChannel.getChannelMembers().end())
            {
                tmpChannel.setChannelBannedMembers(msg.getArguments().at(1));
                tmpChannel.getChannelMembers().erase(itReceiver1);
                if (itReceiver2 != tmpChannel.getChannelOperators().end())
                    tmpChannel.getChannelOperators().erase(itReceiver2);
            }
            msg.getArguments().erase(msg.getArguments().begin() + 1);
            std::cout << "ban setted Successfully" << std::endl;
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
    else{
        if (itSender != tmpChannel.getChannelOperators().end()){
            if (itReceiver != tmpChannel.getChannelBannedMembers().end()){
                tmpChannel.getChannelBannedMembers().erase(itReceiver);
                std::cout << "ban removed Successfully" << std::endl;
            }
            else
                errorHandler(newSocketFd, 401, msg.getArguments().at(0)); //NO such NICK
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
            std::cout << "invite setted Successfully" << std::endl;
            tmpChannel.setIsMode_i(true);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
    else{
        if (itSender != tmpChannel.getChannelOperators().end()){
            std::cout << "invite removed Successfully" << std::endl;
            tmpChannel.setIsMode_i(false);
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
            std::cout << "private setted Successfully" << std::endl;
            tmpChannel.setIsMode_p(true);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
    else{
        if (itSender != tmpChannel.getChannelOperators().end()){
            std::cout << "private removed Successfully" << std::endl;
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
            std::cout << "secret setted Successfully" << std::endl;
            tmpChannel.setIsMode_s(true);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
    else{
        if (itSender != tmpChannel.getChannelOperators().end()){
            std::cout << "secret removed Successfully" << std::endl;
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
    std::vector<std::string>::iterator itSenderOp = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), senderNick);
    std::vector<std::string>::iterator itSenderMem = std::find(tmpChannel.getChannelMembers().begin(), tmpChannel.getChannelMembers().end(), senderNick);

    if (addOrRm == true){
        if (msg.getArguments().size() == 1)
            errorHandler(newSocketFd, 461, msg.getCommand()); // Check if there's a Topic
        std::string topic = msg.getArguments().at(1);
        if (tmpChannel.getIsMode_t()){
            if (itSenderOp != tmpChannel.getChannelOperators().end()){
                std::cout << "Topic setted by Operator Successfully" << std::endl;
                tmpChannel.setChannelTopic(topic);
                tmpChannel.setIsMode_t(true);
            }
            else{
                errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
            }
        }
        else{
            if (itSenderMem != tmpChannel.getChannelMembers().end()){
                tmpChannel.setChannelTopic(topic);
                tmpChannel.setIsMode_t(true);
                std::cout << "Topic setted by Member Successfully" << std::endl;
            }
            else
                errorHandler(newSocketFd, 441, msg.getArguments().at(1), msg.getArguments().at(0)); //User is Not in this channel  
        }
    }
    else{
        if (itSenderOp != tmpChannel.getChannelOperators().end()){
            std::cout << "Topic removed Successfully" << std::endl;
            tmpChannel.setIsMode_t(false);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
}

void Server::exec_n(Message &msg, int newSocketFd, bool addOrRm)
{
    Channel     &tmpChannel = findChannel(msg.getArguments().at(0));
    std::string senderNick = findNickClientByFd(newSocketFd);
    std::vector<std::string>::iterator itSender = std::find(tmpChannel.getChannelOperators().begin(), tmpChannel.getChannelOperators().end(), senderNick);

    if (addOrRm == true){
        if (itSender != tmpChannel.getChannelOperators().end()){
            std::cout << "NO message from Outside setted Successfully" << std::endl;
            tmpChannel.setIsMode_n(true);
        }
        else{
            errorHandler(newSocketFd, 482, msg.getArguments().at(0)); //Need Chanop priveleges
        }
    }
    else{
        if (itSender != tmpChannel.getChannelOperators().end()){
            std::cout << "No message from Outside removed Successfully" << std::endl;
            tmpChannel.setIsMode_n(false);
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
    if (mode == 'n')
        exec_n(msg, newSocketFd, addOrRm);
    if (mode == 'b')
        exec_b(msg, newSocketFd, addOrRm);
}

void Server::executeModes(Message &msg, int newSocketFd)
{
    if (msg.getIsAddOrRm() == true){
        for (size_t i = 0; i < msg.getVecAddMode().size(); i++)
            execMode(msg, msg.getVecAddMode().at(i), newSocketFd, true);
        for (size_t i = 0; i < msg.getVecRmMode().size(); i++)
            execMode(msg, msg.getVecRmMode().at(i), newSocketFd, false);
    }
    else{
        for (size_t i = 0; i < msg.getVecRmMode().size(); i++)
            execMode(msg, msg.getVecRmMode().at(i), newSocketFd, false);
        for (size_t i = 0; i < msg.getVecAddMode().size(); i++)
            execMode(msg, msg.getVecAddMode().at(i), newSocketFd, true);
    }
}

void Server::treatReplay(Message &msgCopy, int newSocketFd)
{
    std::string rpl;
    std::string modes;
    char        hostname[256];
    Channel     &tmpChannel = findChannel(msgCopy.getArguments().at(0));
    std::map<int, Client*>::iterator itClient = _mapClients.find(newSocketFd);
    
    gethostname(hostname, sizeof(hostname));
    for (size_t i = 0; i < msgCopy.getArguments().size(); i++){
        modes += " ";
        modes += msgCopy.getArguments().at(i);
    }
    rpl = ":" + itClient->second->getNickName() + "!~" + itClient->second->getUserName() + "@" + hostname + " MODE " + tmpChannel.getChannelName() +  modes + "\r\n";
	sendReplay(newSocketFd, rpl);
}

void Server::handleModeCmd(Message &msg, int newSocketFd)
{
    std::vector<std::string> tmpArgs;
    Message msgCopy = msg;
    
    if (msg.getArguments().empty())
        errorHandler(newSocketFd, 461, msg.getCommand());
    if (msg.getArguments().at(0).at(0) == '#')
    {
        if (findChannelByName(msg.getArguments().at(0))){
            checkModes(msg, newSocketFd);
            executeModes(msg, newSocketFd);
            treatReplay(msgCopy, newSocketFd);
        }
        else
            errorHandler(newSocketFd, 403, msg.getArguments().at(0)); //NO such channel
    }
    else{
        errorHandler(newSocketFd, 403, msg.getArguments().at(0)); //NO such channel
    }
    
}