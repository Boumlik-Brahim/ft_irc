/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:22:09 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/23 15:50:31 by izail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Bot.hpp"

Bot::Bot()
{}

Bot::Bot(const Bot &copy)
{
	(void) copy;
}

Bot & Bot::operator=(const Bot &assign)
{
	(void) assign;
	return *this;
}

Bot::~Bot()
{}

