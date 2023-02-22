/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:56:38 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/22 16:29:26 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>

#include "Message.hpp"

class Client
{
	private:
		std::string					_nickName;
		std::string					_userName;
		std::string					_realName;
		std::vector<std::string>	_joinedChannels;
		std::vector<std::string>	_invitedChannels;
		int 						_loginTime;	
		int							_clientFd;
		int							_clientMaxnumOfChannels;
		bool						_isAuthValid;

	public:
		std::string	buf;

		Client();
		Client(int newSocketFd);
		Client(const Client &copy);
		Client & operator=(const Client &assign);

		std::string					getNickName(void);
		void						setNickName(std::string nickName);
		std::string					getUserName(void) const;
		void						setUserName(std::string userName);
		std::string					getRealName(void) const;
		void						setRealName(std::string realName);
		std::vector<std::string>&	getJoinedChannels(void);
        void						setJoinedChannels(std::string joinedChannel);
		std::vector<std::string>&	getInvitedChannels(void);
        void						setInvitedChannels(std::string invitedChannel);
		int							getClientFd();
		void						setClientFd(int clientFd);
		int							getClientMaxnumOfChannels(void) const;
		void						setClientMaxnumOfChannels(int clientMaxnumOfChannels);
		bool						getIsAuthValid(void) const;
		void						setAuthValid(bool isValid);
		int							getLoginTime(void);
		void						setLoginTime(int LoginTime);

		~Client();
};

#endif