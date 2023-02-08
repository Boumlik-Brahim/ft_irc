/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:23:31 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/08 11:38:15 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Channel.hpp"

Channel::Channel()
{}
Channel::Channel(const Channel &copy): _channelName(copy._channelName), _channelCreator(copy._channelCreator), _channelMembers(copy._channelMembers), _channelOperators(copy._channelOperators), _channelBannedMembers(copy._channelBannedMembers), _channelModes(copy._channelModes)
{}
Channel & Channel::operator=(const Channel &assign)
{
	if (this != &assign)
	{
		_channelName = assign._channelName;
		_channelCreator = assign._channelCreator;
		_channelMembers = assign._channelMembers;
		_channelOperators = assign._channelOperators;
		_channelBannedMembers = assign._channelBannedMembers;
		_channelModes = assign._channelModes;
	}
	return *this;
}

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