/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:23:56 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/05 11:46:06 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Client.hpp"

// Constructors
Client::Client(): buf("")
{}
Client::Client(const Client &copy) : _nickName(copy._nickName), _userName(copy._userName), _clientFd(copy._clientFd), buf("")
{}

// Operators
Client & Client::operator=(const Client &assign)
{
	if (this != &assign)
	{
		this->_nickName = assign._nickName;
		this->_userName = assign._userName;
		this->_clientFd = assign._clientFd;
	}
	return *this;
}

// Destructor
Client::~Client()
{
	std::cout << "\e[0;31mDestructor called of Client\e[0m" << std::endl;
}

void Client::setNickName(std::string nickName)
{
	_nickName = nickName;
}
void Client::setUserName(std::string userName)
{
	_userName = userName;
}
void Client::setRealName(std::string realName)
{
	_realName = realName;
}

void Client::setAuthValid(bool isValid)
{
	_isAuthValid = isValid;
}

std::string Client::getNickName(void) const
{
	return _nickName;
}
std::string Client::getUserName(void) const
{
	return _userName;
}
std::string Client::getRealName(void) const
{
	return _realName;
}

bool Client::getIsAuthValid(void) const
{
	return _isAuthValid;
}
