/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:35:14 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/05 16:54:49 by bbrahim          ###   ########.fr       */
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
std::vector<std::string> Message::getArgument(void) const
{	
	return (_arguments);
}
void Message::setArguments(std::vector<std::string> arguments)
{
	_arguments = arguments;	
}
bool Message::getIsValidCommand(void) const
{
	return (_isValidCommad);
}
void Message::setIsValidCommand(bool isValid)
{
	_isValidCommad = isValid;
}

Message::~Message()
{}