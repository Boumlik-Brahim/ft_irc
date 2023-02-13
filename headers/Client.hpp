/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:20:06 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/13 09:51:01 by izail            ###   ########.fr       */
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
		Message 	_msg;
		std::string	_nickName;
		std::string	_userName;
		std::string	_realName;
		int			_clientFd;
		bool		_isAuthValid;
		bool		_hasChannel;

	public:
		std::string	buf;

		Client();
		Client(const Client &copy);
		Client & operator=(const Client &assign);

		int			getClientFd();
		void		setClientFd(int clientFd);
		std::string	getNickName(void);
		void		setNickName(std::string nickName);
		std::string	getUserName(void) const;
		void		setUserName(std::string userName);
		std::string	getRealName(void) const;
		void		setRealName(std::string realName);
		bool		getIsAuthValid(void) const;
		void		setAuthValid(bool isValid);
		bool		getHasChannel(void);
		void		setHasChannel(bool hasChannel);

		~Client();
};

#endif