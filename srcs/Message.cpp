/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:35:14 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/10 11:04:22 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Message.hpp"

Message::Message()
{}
Message::Message(const Message &copy) : _arguments(copy._arguments), _command(copy._command), _isValidCommad(copy._isValidCommad)
{}

Message & Message::operator=(const Message &assign)
{
	if (this != &assign)
	{
		_arguments = assign._arguments;
		_command = assign._command;
		_isValidCommad = assign._isValidCommad;
	}
	return *this;
}

std::string Message::getCommand(void) const
{
	return (_command);
}
void Message::setCommand(std::string command)
{
	_command = command;
}
std::vector<std::string>& Message::getArguments(void)
{	
	return (_arguments);
}
void Message::setArguments(std::vector<std::string> arguments)
{
	_arguments = arguments;	
}
std::vector<std::string> Message::getMultiArgs(void) const
{	
	return (_multiArgs);
}
void Message::setMultiArgs(std::vector<std::string> multiArgs)
{
	_multiArgs = multiArgs;	
}
bool Message::getIsValidCommand(void) const
{
	return (_isValidCommad);
}
void Message::setIsValidCommand(bool isValid)
{
	_isValidCommad = isValid;
}

void Message::erase(std::vector<std::string>::iterator it)
{
	_arguments.erase(it);
}

std::vector<char>& Message::getVecAddMode(void)
{
	return _vecAddMode;
}
void Message::setVecAddMode(char m, int newSocketFd)
{
	std::string modeList = "OovaimnqpsrtklbeI";
	
	if (modeList.find(m) != std::string::npos)
		errorHandler(newSocketFd, 472);
	_vecAddMode.push_back(m);
}
std::vector<char>& Message::getVecRmMode(void)
{
	return _vecRmMode;
}
void Message::setVecRmMode(char m, int newSocketFd)
{
	std::string modeList = "OovaimnqpsrtklbeI";
	
	if (modeList.find(m) != std::string::npos)
		errorHandler(newSocketFd, 472);
	_vecAddMode.push_back(m);
}

Message::~Message()
{}