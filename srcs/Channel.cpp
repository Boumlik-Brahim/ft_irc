/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:23:31 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/06 15:20:25 by bbrahim          ###   ########.fr       */
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

std::string	Channel::getChannelName(void) const
{
	return(_channelName);
}
void	Channel::setChannelName(std::string channelName)
{
	_channelName = channelName;

}
std::string	Channel::getChannelProperties(void) const
{
	return(_channelProperties);
}
void	Channel::setChannelProperties(std::string channelProperties)
{
	_channelProperties = channelProperties;	
}
std::string	Channel::getChannelCreator(void) const
{
	return(_channelCreator);
}
void	Channel::setChannelCreator(std::string channelCreator)
{
	_channelCreator = channelCreator;
}
std::string	Channel::getChannellifetime(void) const
{
	return(_channellifetime);
}
void	Channel::setChannellifetime(std::string channellifetime)
{
	_channellifetime = channellifetime;
}

Channel::~Channel()
{}