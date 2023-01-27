/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:36:46 by bbrahim           #+#    #+#             */
/*   Updated: 2023/01/27 17:39:53 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/channel.hpp"

// Constructors
channel::channel()
{
	std::cout << "\e[0;33mDefault Constructor called of channel\e[0m" << std::endl;
}

channel::channel(const channel &copy)
{
	(void) copy;
	std::cout << "\e[0;33mCopy Constructor called of channel\e[0m" << std::endl;
}

// Operators
channel & channel::operator=(const channel &assign)
{
	(void) assign;
	return *this;
}

// Destructor
channel::~channel()
{
	std::cout << "\e[0;31mDestructor called of channel\e[0m" << std::endl;
}