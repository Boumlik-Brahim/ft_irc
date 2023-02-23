#include "../../headers/Server.hpp"

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