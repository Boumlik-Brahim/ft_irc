/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:35:14 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/02 15:11:29 by bbrahim          ###   ########.fr       */
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

Message::~Message()
{}

void Message::setArguments(char **data)
{
	std::string tmp;
    for (int i = 1; data[i]; i++)
    {
        tmp = data[i];
        _arguments.push_back(tmp);
    }
}

void Message::setCommand(char *cmd)
{
	this->_command = cmd;
	std::cout << "here : " << this->_command << std::endl;
}

void Message::setIsValidCommand(bool isValid)
{
	this->_isValidCommad = isValid;
}

void Message::setAppendMsg(std::string toAppend)
{
	this->_appendMsg = toAppend;
}

std::string Message::getAppendMsg() const
{
	return this->_appendMsg;
}


std::string Message::getCommand(void) const
{
	return this->_command;
}
bool Message::getIsValidCommand(void) const
{
	return this->_isValidCommad;
}
std::vector<std::string> Message::getArgument(void) const
{	
	return this->_arguments;
}