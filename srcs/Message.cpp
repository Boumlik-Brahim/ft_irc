/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:35:14 by bbrahim           #+#    #+#             */
/*   Updated: 2023/01/31 17:43:04 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Message.hpp"

// Constructors
Message::Message()
{}
Message::Message(const Message &copy) : arguments(copy.arguments), command(copy.command), isValidCommad(copy.isValidCommad)
{}

// Operators
Message & Message::operator=(const Message &assign)
{
	if (this != &assign)
	{
		this->arguments = assign.arguments;
		this->command = assign.command;
		this->isValidCommad = assign.isValidCommad;
	}
	return *this;
}

// Destructor
Message::~Message()
{
	std::cout << "\e[0;31mDestructor called of Message\e[0m" << std::endl;
}