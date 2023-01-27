/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:36:39 by bbrahim           #+#    #+#             */
/*   Updated: 2023/01/27 17:39:31 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/client.hpp"

// Constructors
client::client()
{
	std::cout << "\e[0;33mDefault Constructor called of client\e[0m" << std::endl;
}

client::client(const client &copy)
{
	(void) copy;
	std::cout << "\e[0;33mCopy Constructor called of client\e[0m" << std::endl;
}

// Operators
client & client::operator=(const client &assign)
{
	(void) assign;
	return *this;
}

// Destructor
client::~client()
{
	std::cout << "\e[0;31mDestructor called of client\e[0m" << std::endl;
}