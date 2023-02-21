/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:35:14 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/21 08:26:07 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Message.hpp"

Message::Message()
{}
Message::Message(const Message &copy)
{
	*this = copy;
}

Message & Message::operator=(const Message &assign)
{
	if (this != &assign)
	{
		_arguments = assign._arguments;
		_multiArgs = assign._multiArgs;
		_command = assign._command;
		_vecAddMode = assign._vecAddMode;
		_vecRmMode = assign._vecRmMode;
		_isAddOrRm = assign._isAddOrRm;
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
std::vector<char>& Message::getVecAddMode(void)
{
	return _vecAddMode;
}
void Message::setVecAddMode(char m)
{
	_vecAddMode.push_back(m);
}
std::vector<char>& Message::getVecRmMode(void)
{
	return _vecRmMode;
}
void Message::setVecRmMode(char m)
{
	_vecRmMode.push_back(m);
}
bool Message::getIsAddOrRm(void) const
{
	return _isAddOrRm;
}
void Message::setIsAddOrRm(bool trueOrFalse)
{
	_isAddOrRm = trueOrFalse;
}

void Message::erase(std::vector<std::string>::iterator it)
{
	_arguments.erase(it);
}

Message::~Message()
{}