/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Guest.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:09:44 by iomayr            #+#    #+#             */
/*   Updated: 2023/02/05 11:46:24 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

Guest::Guest()
{}

Guest::Guest(int newSocketFd) : _guestFd(newSocketFd)
{}

Guest::Guest(const Guest &copy)
{
    *this = copy;
}

Guest &Guest::operator=(const Guest &assign)
{
    if (this != &assign)
	{
		this->_nick = assign._nick ;
		this->_user = assign._user ;
		this->_realName = assign._realName ;
        this->_passValid = assign._passValid ;
        this->_nickValid = assign._nickValid ;
	}
	return *this;
}

Guest::~Guest()
{}

bool Guest::getPassValid() const
{
    return _passValid;
}

void Guest::setPassValid(bool isValid)
{
    this->_passValid = isValid;
}

bool Guest::getNickValid( void ) const
{
    return _nickValid;
}
void Guest::setNickValid(bool isValid)
{
    _nickValid = isValid;
}

std::string Guest::getGuestNick( void ) const
{
    return _nick;
}

void Guest::setGuestNick(std::string nick)
{
    _nick = nick;
}

void Guest::setGuestUser(std::string user)
{
    _user = user;
}
void Guest::setGuestRealName(std::string realName)
{
    _realName = realName;
}

int Guest::getGuestFd( void ) const
{
    return _guestFd;
} 

std::string Guest::getGuestUser( void ) const
{
    return _user;
}
std::string Guest::getGuestRealName( void ) const
{
    return _realName;
}