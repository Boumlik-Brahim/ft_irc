/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:23:31 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/07 18:53:55 by izail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Channel.hpp"

Channel::Channel()
{}
Channel::Channel(const Channel &copy)
{
	*this = copy;
}
// Channel & Channel::operator=(const Channel &assign)
// {
// 	(void) assign;
// 	return *this;
// }

std::string&	Channel::getChannelName(void)
{
	return(_channelName);
}
void	Channel::setChannelName(std::string channelName)
{
	_channelName = channelName;
}
std::string&	Channel::getChannelCreator(void)
{
	return(_channelCreator);
}
void	Channel::setChannelCreator(std::string channelCreator)
{
	_channelCreator = channelCreator;
}

std::vector<std::string>& Channel::getChannelMembers(void)
{
    return (_channelMembers);
}
void Channel::setChannelMembers(std::string channelMember)
{
    _channelMembers.push_back(channelMember);
}
std::vector<std::string>& Channel::getChannelOperators(void)
{
    return (_channelOperators);
}
void Channel::setChannelOperators(std::string channelOperator)
{
    _channelOperators.push_back(channelOperator);
}
std::vector<std::string>& Channel::getChannelBannedMembers(void)
{
    return (_channelBannedMembers);
}
void Channel::setChannelBannedMembers(std::string channelBannedMember)
{
    _channelBannedMembers.push_back(channelBannedMember);
}
std::vector<std::string>& Channel::getChannelModes(void)
{
    return (_channelModes);
}
void Channel::setChannelModes(std::string channelMode)
{
    _channelModes.push_back(channelMode);
}

Channel::~Channel()
{}