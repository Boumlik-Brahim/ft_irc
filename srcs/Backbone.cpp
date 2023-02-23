#include "../headers/Server.hpp"

void Server::backBone(std::string buffer, int newSocketFd)
{
	Message msg;
	char 	**data;
	char	*token;

	char* cstr = const_cast<char*>(buffer.c_str());;
	token = strtok(cstr, "\r\n");
	while (token != NULL)
	{
		data = ft_split(token, ' ');
		try{
			parseMessageFormat(msg, data);
			if (!msg.getCommand().compare("PASS"))
				handlePassCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("NICK"))
				handleNickCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("USER"))
				handleUserCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("QUIT"))
				handleQuitCmd(newSocketFd);
			else if (!msg.getCommand().compare("JOIN"))
				handleJoinCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("PART"))
				handlePartCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("MODE"))
				handleModeCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("TOPIC"))
				handleTopicCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("NAMES"))
				handleNamesCmd(msg,newSocketFd);
			else if (!msg.getCommand().compare("LIST"))
				handleListCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("INVITE"))
				handleInviteCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("KICK"))
				handleKickCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("PRIVMSG"))
				handlePrivmsgCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("NOTICE"))
				handleNoticeCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("WHOIS"))
				handleWhoIsCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("BOT"))
				handleBotCmd(msg, newSocketFd);
			else if (!msg.getCommand().compare("PONG"))
				return;
			else
				std::cout << "invalid command" << std::endl;		
		}
		catch(std::string message){
			size_t i = 0;
			message += "\r\n";
			while (i != message.length())
				i += send(newSocketFd, message.c_str(), message.length() - i, 0);
		}
		token = strtok(NULL, "\r\n");
	}
}