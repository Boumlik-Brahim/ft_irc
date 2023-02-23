#include "../../headers/Server.hpp"

void  Server::handlePartCmd(Message &msg, int senderFd)
{
	if (!_mapClients[senderFd]->getIsAuthValid())	
		errorHandler(451);
	if (msg.getArguments().empty()) /*ERR_NEEDMOREPARAMS*/
		errorHandler(461, msg.getCommand());
	checkMultiArgs(msg);
	checkChnlNames(msg.getMultiArgs());
	if (!msg.getMultiArgs().empty())
	{
		for (size_t i = 0; i < msg.getMultiArgs().size(); i++)
			partFromChannel(senderFd, msg.getMultiArgs().at(i));
	}
	else
		partFromChannel(senderFd, msg.getArguments().at(0));
}

void Server::partFromChannel(int senderFd, std::string channelName)
{
	std::map<int, Client *>::iterator	it;
	std::string							message;
	int									fd;
	char								hostname[256];

	if(!findChannelByName(channelName))
		errorHandler(403, channelName); /*ERR_NOSUCHCHANNEL*/
	it = _mapClients.find(senderFd);
	Channel &chnl = findChannel(channelName);
	gethostname(hostname, sizeof(hostname));
	std::vector<std::string>::iterator	channelMember = std::find(chnl.getChannelMembers().begin(), chnl.getChannelMembers().end(), it->second->getNickName());
	if (channelMember == chnl.getChannelMembers().end())
		errorHandler(442, "channel"); /*ERR_NOTONCHANNEL*/
	std::string rpl = ":" + it->second->getNickName() + "!~" + it->second->getUserName() + "@" + hostname + " PART :" + chnl.getChannelName() + "\r\n";
	for(size_t i = 0; i < chnl.getChannelMembers().size(); i++)
	{
		fd = findFdClientByNick(chnl.getChannelMembers().at(i));
		sendReplay(fd, rpl);
	}
	chnl.getChannelMembers().erase(channelMember);
	std::vector<std::string>::iterator	joinedChannel = std::find(it->second->getJoinedChannels().begin(), it->second->getJoinedChannels().end(), channelName);
	it->second->getJoinedChannels().erase(joinedChannel);
}
