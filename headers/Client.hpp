/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:20:06 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/05 11:46:01 by iomayr           ###   ########.fr       */
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

	public:
		std::string buf;

		Client();
		Client(const Client &copy);
		Client & operator=(const Client &assign);
		~Client();

		void setNickName(std::string nickName);
		void setUserName(std::string userName);
		void setRealName(std::string realName);
		void setAuthValid(bool isValid);
		std::string getNickName(void) const;
		std::string getUserName(void) const;
		std::string getRealName(void) const;
		bool 		getIsAuthValid(void) const;
};

#endif