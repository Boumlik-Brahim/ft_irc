/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:10:19 by iomayr            #+#    #+#             */
/*   Updated: 2023/02/10 11:56:10 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.hpp"

void splitModes(Message &msg, std::string modes, int newSocketFd)
{
    std::string modeList = "OovaimnqpsrtklbeI";
    
    if (modes.at(0) == '+')
    {
        for (size_t i = 1; i < modes.size(); i++)
        {
            if (modeList.find(modeList, modes.at(i)) != std::string::npos)
                msg.setVecAddMode(modes.at(i), newSocketFd);      
        }    
    }
    else if (modes.at(0) == '-')
    {
        for (size_t i = 1; i < modes.size(); i++)
        {
            if (modeList.find(modeList, modes.at(i)) != std::string::npos)
                msg.setVecRmMode(modes.at(i), newSocketFd);      
        }    
    }
}

void checkModes(Message &msg, int newSocketFd)
{
    size_t argSize = msg.getArguments().size();
    
    if (argSize >= 4)
    {
        if (msg.getArguments().at(1).at(0) != '+' || msg.getArguments().at(1).at(0) != '-')
        {
            splitModes(msg, msg.getArguments().at(1), newSocketFd);
            if (msg.getArguments().at(2).at(0) != '+' || msg.getArguments().at(2).at(0) != '-')
                splitModes(msg, msg.getArguments().at(2), newSocketFd);    
            else
                errorHandler(newSocketFd, 472); //Unkown Mode 
        }
        else
            errorHandler(newSocketFd, 472); //Unkown Mode 
    }
    else if (argSize >= 3)
    {

    }
    else if (argSize == 2)
    {

    }
    else
        //Need More Arguments
}

void Server::handleModeCmd(Message &msg, int newSocketFd)
{
    std::vector<std::string> tmpArgs;

    if (msg.getArguments().empty())
        errorHandler(newSocketFd, 461, msg.getCommand());
    if (msg.getArguments().at(0).at(0) == '#')
    {
        if (findChannelByName(msg.getArguments().at(0)))
        {
           // Split modes
           checkModes(msg, newSocketFd);
           // checkAllModes
        }
        else
        {
            //No channel found
        }
    }
    else
    {
        //Search by Nick
    }
}