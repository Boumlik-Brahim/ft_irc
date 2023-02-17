/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:20:06 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/17 15:31:38 by izail            ###   ########.fr       */
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
		Message 					_msg;
		std::string					_nickName;
		std::string					_userName;
		std::string					_realName;
		int							_clientFd;
		bool						_isAuthValid;
		int							_clientMaxnumOfChannels;
		std::vector<std::string>	_joinedChannels;
		std::vector<std::string>	_invitedChannels;
	public:
		std::string	buf;

		Client();
		Client(int newSocketFd);
		Client(const Client &copy);
		Client & operator=(const Client &assign);

		// bool		getHasChannel(void);
		// void		setHasChannel(bool hasChannel);
		std::string					getNickName(void);
		void						setNickName(std::string nickName);
		std::string					getUserName(void) const;
		void						setUserName(std::string userName);
		std::string					getRealName(void) const;
		void						setRealName(std::string realName);
		int							getClientFd();
		void						setClientFd(int clientFd);
		bool						getIsAuthValid(void) const;
		void						setAuthValid(bool isValid);
		int							getClientMaxnumOfChannels(void) const;
		void						setClientMaxnumOfChannels(int clientMaxnumOfChannels);
		std::vector<std::string>&	getJoinedChannels(void);
		std::vector<std::string>&	getInvitedChannels(void);
        void						setJoinedChannels(std::string joinedChannel);
        void						setInvitedChannels(std::string invitedChannel);

		~Client();
};

#endif