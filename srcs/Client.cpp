/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:23:56 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/06 15:25:08 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Client.hpp"

Client::Client():  buf("")
{}
Client::Client(const Client &copy) : _nickName(copy._nickName), _userName(copy._userName), _clientFd(copy._clientFd), buf("")
{}

Client & Client::operator=(const Client &assign)
{
	if (this != &assign)
	{
		_nickName = assign._nickName;
		_userName = assign._userName;
		_clientFd = assign._clientFd;
	}
	return *this;
}

void Client::setNickName(std::string nickName)
{
	_nickName = nickName;
}
std::string Client::getNickName(void) const
{
	return (_nickName);
}
void Client::setUserName(std::string userName)
{
	_userName = userName;
}
std::string Client::getUserName(void) const
{
	return (_userName);
}
void Client::setRealName(std::string realName)
{
	_realName = realName;
}
std::string Client::getRealName(void) const
{
	return (_realName);
}
bool Client::getIsAuthValid(void) const
{
	return (_isAuthValid);
}
void Client::setAuthValid(bool isValid)
{
	_isAuthValid = isValid;
}

Client::~Client()
{}
