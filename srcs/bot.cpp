/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:36:54 by bbrahim           #+#    #+#             */
/*   Updated: 2023/01/27 17:40:03 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/bot.hpp"

// Constructors
bot::bot()
{
	std::cout << "\e[0;33mDefault Constructor called of bot\e[0m" << std::endl;
}

bot::bot(const bot &copy)
{
	(void) copy;
	std::cout << "\e[0;33mCopy Constructor called of bot\e[0m" << std::endl;
}

// Operators
bot & bot::operator=(const bot &assign)
{
	(void) assign;
	return *this;
}

// Destructor
bot::~bot()
{
	std::cout << "\e[0;31mDestructor called of bot\e[0m" << std::endl;
}