/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Guest.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:09:44 by iomayr            #+#    #+#             */
/*   Updated: 2023/02/21 08:12:37 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Guest.hpp"

Guest::Guest()
{}
Guest::Guest(int newSocketFd) : _guestFd(newSocketFd), _passValid(false), _nickValid(false), _userValid(false)
{}
Guest::Guest(const Guest &copy)
{
	*this = copy;
}
Guest &Guest::operator=(const Guest &assign)
{
	if (this != &assign)
	{
		_guestFd= assign._guestFd;
		_nick = assign._nick;
		_user = assign._user;
		_realName = assign._realName;
		_passValid = assign._passValid;
		_nickValid = assign._nickValid;
		_userValid = assign._userValid;
	}
	return *this;
}

int Guest::getGuestFd(void) const
{
	return (_guestFd);
}
void Guest::setGuestFd(int guestFd)
{
	_guestFd = guestFd;
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