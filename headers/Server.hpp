/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <poll.h>
# include <map>
# include "../headers/Client.hpp"
# include "../headers/Utils.hpp"
# include "../headers/Message.hpp"
# include "../headers/Guest.hpp"
# include "../headers/Channel.hpp"

# define MAX_CONNECTIONS 10
class Server
{
	private:
		std::string				_server_name;
		std::string				_password;
		int						_port_number;
		int						_socket_fd;
		int						_new_socket_fd;
		struct sockaddr_in 		_serv_addr, _cli_addr;
		struct pollfd			_fds[MAX_CONNECTIONS];
		std::map<int, Client*>	_mapClients;
		std::map<int, Guest*>	_mapGuest;
		std::vector<Channel >	_channels;

	public:
		Server();
		Server(int port_number, std::string password);
		Server(std::string server_name, int port_number, std::string password);
		Server &operator=(const Server &assign);
		Server(const Server &copy);

		int			getPort_number(void) const;
		void		setPort_number(int port_number);
		std::string	getPassword(void) const;
		void		setPassword(std::string password);
		int			getSocket_fd(void) const;
		void		setSocket_fd(int socket_fd);
		int			getNew_socket_fd(void) const;
		void		setNew_socket_fd(int new_socket_fd);
		
		void create_socket();
		void bind_socket();
		void listen_socket();
		void accept_socket();
		void backBone(std::string buffer, int new_socket_fd);
		void read_write_socket(int new_socket_fd, int *count);
		void close_socket(int socket_fd);

		std::string	findNickClientByFd(int sender);
		int			findFdClientByNick(std::string receiver, int senderFd);
		int			findFdClientByNick(std::string receiver);
		void		handleNoticeCmd(Message &msg, int senderFd);
		void		handlePrivmsgCmd(Message &msg, int senderFd);

		void guestToClient(Guest *tmpGuest, int newSocketFd);
		void handlePassCmd(Message &msg, int newSocketFd);
		void handleNickCmd(Message &msg, int newSocketFd);
		void handleUserCmd(Message &msg, int newSocketFd);
		void handleWhoIsCmd(Message &msg, int newSocketFd);

		int		findChannelByName(std::string channelName);
		Channel& findChannel(std::string channelName);
		void setChannel(Channel &chnl, std::string channelName, std::string channelCreator,  std::string channelkey);
		void joinNewChannelWithKey(int senderFd, std::string channelName, std::string channelkey);
		void setChannel(Channel &chnl, std::string channelName, std::string channelCreator);
		void joinNewChannel(int senderFd, std::string channelName);
		void joinExistChannel(Channel &chnl, std::map<int, Client *>::iterator	&it);
		void checkExistChannel(int senderFd, Message &msg, std::string channelName, int i);
		void leaveAllChannels(int senderFd);
		void handleJoinCmd(Message &msg, int senderFd);

		void partFromChannel(int senderFd, std::string channelName);
		void handlePartCmd(Message &msg, int senderFd);

		// Ishak
		void			handleTopicCmd(Message &msg, int senderFd);
		void    		handleNamesCmd(Message &msg, int senderFd);
		void    		handleListCmd(Message &msg, int senderFd);
		void    		handleInviteCmd(Message &msg, int senderFd);
		void    		handleKickCmd(Message &msg, int senderFd);
		bool			findChannelOperator(std::string sender, Channel chnl);
		bool 			findUserInChannel(std::string sender, Channel &chnl);
		bool 			checkIfClientIsMember(Channel &chnl, std::string clientName);
		bool   			checkInvitedChannels(Client &client, std::string channelName);
		std::string 	findClientWithNoChannel();
		Client& 		findClient(std::string nickName);
		int 			findClientByNick(std::string nickName);
		void 	WelcomeMsg(int fd);
		~Server();
};

#endif