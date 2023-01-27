/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:36:31 by bbrahim           #+#    #+#             */
/*   Updated: 2023/01/27 17:39:40 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.hpp"

// Constructors
server::server()
{
	std::cout << "\e[0;33mDefault Constructor called of server\e[0m" << std::endl;
}

server::server(const server &copy)
{
	(void) copy;
	std::cout << "\e[0;33mCopy Constructor called of server\e[0m" << std::endl;
}

// Operators
server & server::operator=(const server &assign)
{
	(void) assign;
	return *this;
}

// Destructor
server::~server()
{
	std::cout << "\e[0;31mDestructor called of server\e[0m" << std::endl;
}