/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:22:09 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/22 18:52:20 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Bot.hpp"

Bot::Bot()
{}

Bot::Bot(const Bot &copy)
{
	(void) copy;
	std::cout << "\e[0;33mCopy Constructor called of Bot\e[0m" << std::endl;
}

Bot & Bot::operator=(const Bot &assign)
{
	(void) assign;
	return *this;
}

Bot::~Bot()
{}

