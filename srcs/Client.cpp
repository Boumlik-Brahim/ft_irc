/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:23:56 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/04 14:33:14 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Client.hpp"

// Constructors
Client::Client(): buf("")
{}
Client::Client(const Client &copy) : nickName(copy.nickName), userName(copy.userName), clientFd(copy.clientFd), buf("")
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
		this->nickName = assign.nickName;
		this->userName = assign.userName;
		this->clientFd = assign.clientFd;
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