
#include "../../headers/Server.hpp"

void Server::handleQuitCmd(int newSocketFd)
{
	std::map<int, Client*>::iterator	itClient = _mapClients.find(newSocketFd);
	std::string 						clientNick = itClient->second->getNickName();
	std::vector<std::string> 			chnlVec = itClient->second->getJoinedChannels();
	
	for (std::vector<std::string>::iterator	it = chnlVec.begin(); it != chnlVec.end(); it++)
	{
		Channel &tmpChnl = findChannel(*it);
		for (std::vector<std::string>::iterator	it = tmpChnl.getChannelMembers().begin(); it != tmpChnl.getChannelMembers().end(); it++){
			if (*it == clientNick){
				tmpChnl.getChannelMembers().erase(it);
				break;
			}
		}
		for (std::vector<std::string>::iterator	it = tmpChnl.getChannelOperators().begin(); it != tmpChnl.getChannelOperators().end(); it++){
			if (*it == clientNick){
				tmpChnl.getChannelOperators().erase(it);
				break;
			}
		}
		for (std::vector<std::string>::iterator	it = tmpChnl.getInvitedMembers().begin(); it != tmpChnl.getInvitedMembers().end(); it++){
			if (*it == clientNick){
				tmpChnl.getInvitedMembers().erase(it);
				break;
			}
		}
	}
	if (itClient != _mapClients.end()){
		delete itClient->second;
		_mapClients.erase(itClient);
	}
	close(newSocketFd);
}