/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:20:06 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/04 17:32:17 by bbrahim          ###   ########.fr       */
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
		Message 	msg;
		std::string	nickName;
		std::string	userName;
		int			clientFd;

	public:
		std::string buf;
		// Constructors
		Client();
		Client(int clientFd);
		Client(const Client &copy);

		std::string	getNickName();
		void		setNickName(std::string nickname);
		std::string	getUserName();
		void		setUserName(std::string nickname);
		int			getClientFd();
		void		setClientFd(int clientFd);
		
		// Operators
		Client & operator=(const Client &assign);

		// Destructor
		~Client();
};

#endif