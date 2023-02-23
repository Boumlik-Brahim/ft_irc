#include "../../headers/Server.hpp"

void    Server::handleTopicCmd(Message &msg, int senderFd)
{
    std::string     channelName;
    std::string     topic;
    std::string     sender;
    int             channelExist;
    std::string     cmd = msg.getCommand();
    int             isUserInChannel;

    // check params
    if (msg.getArguments().size() == 0 || msg.getArguments()[0] == ":")
        errorHandler(461, cmd);
        
    // check user is authenticated
    if (!_mapClients[senderFd]->getIsAuthValid())
		errorHandler(451);
    // check if channel exist
    channelName = msg.getArguments()[0];
    channelExist = findChannelByName(msg.getArguments()[0]);
    if (!channelExist)
        errorHandler(401, channelName);
    sender = findNickClientByFd(senderFd);
    
    Channel         &tmpChnl  = findChannel(channelName);
    
    isUserInChannel = findUserInChannel(sender, tmpChnl);
    if (isUserInChannel)
    {
        // check if channel has topic before
        if ((msg.getArguments().size() > 1))
        {
            if (tmpChnl.getIsMode_t())
            {
                if (findChannelOperator(sender, tmpChnl))
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
                else
                    errorHandler(482, sender);
            }
            else
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
        }
        else if (msg.getArguments().size() == 1)
        {
            if (tmpChnl.getChannelTopic().size() == 0){
                cmd_Resp_Handler(senderFd, 331, channelName);
            }
            else{
                cmd_Resp_Handler(senderFd, 332, channelName, tmpChnl.getChannelTopic());
            }
        }
    }
    else
        errorHandler(442, sender);
}