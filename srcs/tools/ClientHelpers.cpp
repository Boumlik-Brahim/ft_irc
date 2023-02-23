#include "../../headers/Server.hpp"

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
            ChannelClients = ChannelClients.append(" ") + it->second->getNickName();
    }
    return ChannelClients;
}

int Server::findFdClientByNick(std::string receiver, int newSocketFd)
{
	(void)newSocketFd;
    for(std::map<int, Client *>::iterator it = _mapClients.begin(); it != _mapClients.end(); it++)
    {
        if (it->second->getNickName() == receiver)
            return (it->first);
    }
    errorHandler(401, receiver);
	return -1;
}

int Server::findFdClientByNick(std::string receiver)
{
    for(std::map<int, Client *>::iterator it = _mapClients.begin(); it != _mapClients.end(); it++)
    {
        if (it->second->getNickName() == receiver)
            return (it->first);
    }
    return -1;
}

std::string     Server::findNickClientByFd(int sender)
{
    std::map<int, Client *>::iterator it = _mapClients.find(sender);
    if (it != _mapClients.end())
        return it->second->getNickName();
	return "";
}

void Server::checkIfClientExist(int newSocketFd, std::string nickName)
{
    std::map<int, Client*>::iterator clientIt;
    
    clientIt = _mapClients.find(newSocketFd);
    if (clientIt == _mapClients.end())
        errorHandler(401, nickName);
}