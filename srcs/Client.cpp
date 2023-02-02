/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:23:56 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/02 18:00:11 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Client.hpp"

// Constructors
Client::Client(): buf("")
{}
Client::Client(const Client &copy) : nickName(copy.nickName), userName(copy.userName), clientFd(copy.clientFd), buf("")
{}

// Operators
Client & Client::operator=(const Client &assign)
{
	if (this != &assign)
	{
		this->nickName = assign.nickName;
		this->userName = assign.userName;
		this->clientFd = assign.clientFd;
	}
	return *this;
}

// Destructor
Client::~Client()
{
	std::cout << "\e[0;31mDestructor called of Client\e[0m" << std::endl;
}