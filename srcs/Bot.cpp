/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:22:09 by bbrahim           #+#    #+#             */
/*   Updated: 2023/01/29 18:23:15 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Bot.hpp"

// Constructors
Bot::Bot()
{
	std::cout << "\e[0;33mDefault Constructor called of Bot\e[0m" << std::endl;
}

Bot::Bot(const Bot &copy)
{
	(void) copy;
	std::cout << "\e[0;33mCopy Constructor called of Bot\e[0m" << std::endl;
}

// Operators
Bot & Bot::operator=(const Bot &assign)
{
	(void) assign;
	return *this;
}

// Destructor
Bot::~Bot()
{
	std::cout << "\e[0;31mDestructor called of Bot\e[0m" << std::endl;
}
