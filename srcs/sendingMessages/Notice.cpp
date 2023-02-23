#include "../../headers/Server.hpp"

void  Server::handleNoticeCmd(Message &msg, int senderFd)
{
    std::string 				sender;
    std::string 				cmd = msg.getCommand();
    std::vector<std::string> 	receivers;
    std::string 				message;
    std::string 				messageFormat;
    std::vector<int>			receiversFd;

	if (!_mapClients[senderFd]->getIsAuthValid())
		errorHandler(451);
	sender = findNickClientByFd(senderFd);
	
	//411
	if (msg.getArguments().empty())
		errorHandler(411, cmd);
	//412
	if (msg.getArguments().size() < 2)
	
	if (msg.getArguments().size())
		errorHandler(412);
	if (msg.getArguments().size())
	{
		receivers.push_back(msg.getArguments()[0]);
		receiversFd.push_back(findFdClientByNick(msg.getArguments()[0], senderFd));
		message = msg.getArguments()[1];
		// if (message.at(0) != ':')
        // 	message.insert(0,1,':');
		messageFormat = ":"+ sender+ " " +cmd + " " + receivers.at(0) + " " + message;
    	sendMessage(receiversFd.at(0), messageFormat);
	}
}