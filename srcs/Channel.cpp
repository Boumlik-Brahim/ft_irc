/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:23:31 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/05 16:53:30 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Channel.hpp"

Channel::Channel()
{}

Channel::Channel(const Channel &copy)
{
	(void) copy;
	std::cout << "\e[0;33mCopy Constructor called of Channel\e[0m" << std::endl;
}

Channel & Channel::operator=(const Channel &assign)
{
	(void) assign;
	return *this;
}

Channel::~Channel()
{}