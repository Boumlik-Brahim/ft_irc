/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Guest.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:09:44 by iomayr            #+#    #+#             */
/*   Updated: 2023/02/04 16:01:32 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

Guest::Guest()
{}

Guest::Guest(int newSocketFd) : _guestFd(newSocketFd)
{}

// Guest::Guest(const Guest &copy)
// {}

// Guest &Guest::operator=(const Guest &assign)
// {}

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
bool Guest::getAuthValid( void ) const
{
    return _authValid;
}
void Guest::setAuthValid(bool isValid)
{
    _authValid = isValid;
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