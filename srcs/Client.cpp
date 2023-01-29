/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:23:56 by bbrahim           #+#    #+#             */
/*   Updated: 2023/01/29 18:25:01 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Client.hpp"

// Constructors
Client::Client()
{
	std::cout << "\e[0;33mDefault Constructor called of Client\e[0m" << std::endl;
}

Client::Client(const Client &copy)
{
	(void) copy;
	std::cout << "\e[0;33mCopy Constructor called of Client\e[0m" << std::endl;
}

// Operators
Client & Client::operator=(const Client &assign)
{
	(void) assign;
	return *this;
}

// Destructor
Client::~Client()
{
	std::cout << "\e[0;31mDestructor called of Client\e[0m" << std::endl;
}