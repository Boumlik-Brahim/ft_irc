/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:23:56 by bbrahim           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Client.hpp"

// Constructors
Client::Client(): buf("")
{}
Client::Client(const Client &copy) : _nickName(copy._nickName), _userName(copy._userName), _clientFd(copy._clientFd), buf("")
{}

Client::Client(int clientFd) : nickName("brahim")
{
	this->clientFd = clientFd;
}

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

std::string Client::getNickName()
{
	return (this->nickName);
}
void	Client::setNickName(std::string nickname)
{
	this->nickName = nickname;
}
std::string	Client::getUserName()
{
	return (this->userName);
}
void Client::setUserName(std::string userName)
{
	this->userName = userName;
}
int Client::getClientFd()
{
	return (this->clientFd);
}
void	Client::setClientFd(int clientFd)
{
	this->clientFd = clientFd;
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
