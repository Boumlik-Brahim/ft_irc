#include "../../headers/Server.hpp"

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

    // only if the channel exists
    if (channelExist)
    {
        Channel &tmpChannel  = findChannel(channelName);
        // check if the sender is operator to perform the KICK command 'only operators who can KICK clients from channels'
        if (findChannelOperator(sender, tmpChannel))
        {    
            // if we have multiple cients separated by Comma then we'll execute the instructions on each one of them.
            for (size_t i = 0; i < _users.size(); i++)
            {
                // if client exists
                if (findFdClientByNick(_users.at(i)) != -1)
                {
                    Client &target = findClient(_users.at(i));
                    // check if client is memeber of the #Channel 
                    if (findUserInChannel(target.getNickName(), tmpChannel))
                    {
                        // iterate over the #Channel member and if the target client is one of the #channel target member then he will be kicked from the #channel
                        std::vector<std::string>::iterator it = tmpChannel.getChannelMembers().begin();
                        for (; it != tmpChannel.getChannelMembers().end(); ++it)
                        {
                            if (*it == target.getNickName())
                            {
                                if (findChannelOperator(target.getNickName(), tmpChannel))
                                {
                                    std::cout << "cant kick operator" << std::endl;
                                    return ;
                                }
                                // if there is a third argument is the command then it will be the reason of the kick
                                if (msg.getArguments().size() == 3)
                                {
                                    reason = msg.getArguments()[2];
                                    reason = reason.substr(1, reason.size());
                                }              
                                // reply for kick
                                std::string rpl = ":" + sender + "!~" + sender + "@" + hostname + " KICK " + tmpChannel.getChannelName() + " " + target.getNickName() + " " + reason +"\r\n";
                                for (size_t j = 0; j < tmpChannel.getChannelMembers().size() ; j++)
                                {
                                    fd = findFdClientByNick(tmpChannel.getChannelMembers().at(j));
                                    sendReplay(fd, rpl);
                                }
                                // erase the client target from the #channel target members & also erase the #channel target from his joinedChannels 
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
}