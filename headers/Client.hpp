/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:20:06 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/05 15:37:48 by bbrahim          ###   ########.fr       */
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
		Client(int clientFd);
		Client(const Client &copy);
   
		int			getClientFd();
		void		setClientFd(int clientFd);
		
		// Operators
		Client & operator=(const Client &assign);

		// Destructor
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