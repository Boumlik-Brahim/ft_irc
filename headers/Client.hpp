/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:20:06 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/08 16:26:37 by bbrahim          ###   ########.fr       */
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
		std::vector<std::string>	_joinedChannels;

	public:
		std::string	buf;

		Client();
		Client(const Client &copy);
		Client & operator=(const Client &assign);

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
		std::vector<std::string>&	getJoinedChannels(void);
        void						setJoinedChannels(std::string joinedChannel);

		~Client();
};

#endif