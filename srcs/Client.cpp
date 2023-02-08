/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:23:56 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/08 16:32:10 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Client.hpp"

Client::Client():  buf("")
{}
Client::Client(const Client &copy) : _nickName(copy._nickName), _userName(copy._userName), _realName(copy._realName), _clientFd(copy._clientFd), _isAuthValid(copy._isAuthValid), _joinedChannels(copy._joinedChannels), buf("")
{}

Client & Client::operator=(const Client &assign)
{
	if (this != &assign)
	{
		_nickName = assign._nickName;
		_userName = assign._userName;
		_realName = assign._realName;
		_clientFd = assign._clientFd;
		_isAuthValid = assign._isAuthValid;
		_joinedChannels = assign._joinedChannels;
	}
	return *this;
}

void Client::setNickName(std::string nickName)
{
	_nickName = nickName;
}
std::string Client::getNickName(void)
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
std::vector<std::string>& Client::getJoinedChannels(void)
{
    return (_joinedChannels);
}
void Client::setJoinedChannels(std::string joinedChannel)
{
	_joinedChannels.push_back(joinedChannel);
}

Client::~Client()
{}
