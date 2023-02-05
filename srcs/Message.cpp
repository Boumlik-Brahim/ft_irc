/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:35:14 by bbrahim           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Message.hpp"

// Constructors
Message::Message()
{}
Message::Message(const Message &copy) : _arguments(copy._arguments), _command(copy._command), _isValidCommad(copy._isValidCommad)
{}

// Operators
Message & Message::operator=(const Message &assign)
{
	if (this != &assign)
	{
		this->_arguments = assign._arguments;
		this->_command = assign._command;
		this->_isValidCommad = assign._isValidCommad;
	}
	return *this;
}

std::string Message::getCommand(void) const
{
	return (this->_command);
}
void Message::setCommand(std::string command)
{
	this->_command = command;
}
std::vector<std::string> Message::getArgument(void) const
{	
	return (this->_arguments);
}
void Message::setArguments(std::vector<std::string> arguments)
{
	this->_arguments = arguments;	
}
bool Message::getIsValidCommand(void) const
{
	return (this->_isValidCommad);
}
void Message::setIsValidCommand(bool isValid)
{
	this->_isValidCommad = isValid;
}

Message::~Message()
{}