/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Guest.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:09:44 by iomayr            #+#    #+#             */
/*   Updated: 2023/02/06 15:26:14 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Guest.hpp"

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
		_nick = assign._nick;
		_user = assign._user;
		_realName = assign._realName;
		_passValid = assign._passValid;
		_nickValid = assign._nickValid;
	}
	return *this;
}

bool Guest::getPassValid() const
{
	return (_passValid);
}
void Guest::setPassValid(bool isValid)
{
	_passValid = isValid;
}
bool Guest::getNickValid(void) const
{
	return (_nickValid);
}
void Guest::setNickValid(bool isValid)
{
	_nickValid = isValid;
}
std::string Guest::getGuestNick(void) const
{
	return (_nick);
}
void Guest::setGuestNick(std::string nick)
{
	_nick = nick;
}
std::string Guest::getGuestUser(void) const
{
	return (_user);
}
void Guest::setGuestUser(std::string user)
{
	_user = user;
}
std::string Guest::getGuestRealName(void) const
{
	return (_realName);
}
void Guest::setGuestRealName(std::string realName)
{
	_realName = realName;
}
int Guest::getGuestFd(void) const
{
	return (_guestFd);
}
void Guest::setGuestFd(int guestFd)
{
	_guestFd = guestFd;
}

bool Guest::getUserValid(void) const
{
	return	_userValid;
}
void Guest::setUserValid(bool isValid)
{
	_userValid = isValid;	
}

Guest::~Guest()
{}