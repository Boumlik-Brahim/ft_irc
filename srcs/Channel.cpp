/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:23:31 by bbrahim           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Channel.hpp"

Channel::Channel(): _channelName(""), _channelCreator(""), _channelkey(""), _channelLimit(2), _isMode_O(false), _isMode_o(false), _isMode_v(false), _isMode_a(false), _isMode_i(false), _isMode_m(false), _isMode_n(false), _isMode_q(false), _isMode_p(false), _isMode_s(false), _isMode_r(false), _isMode_t(false), _isMode_k(false), _isMode_l(false), _isMode_b(false), _isMode_e(false), _isMode_I(false)
{}
Channel::Channel(const Channel &copy)
{
	*this = copy;
}
Channel & Channel::operator=(const Channel &assign)
{
	std::cout << "Copy= Constructor" << std::endl;
	if (this != &assign)
	{
		_channelName = assign._channelName;
		_channelCreator = assign._channelCreator;
		_channelkey = assign._channelkey;
		_channelLimit = assign._channelLimit;
		_channelMembers = assign._channelMembers;
		_channelOperators = assign._channelOperators;
		_channelBannedMembers = assign._channelBannedMembers;
		_invitedMembers = assign._invitedMembers;
		_isMode_O = assign._isMode_O;
        _isMode_o = assign._isMode_o;
        _isMode_v = assign._isMode_v;
        _isMode_a = assign._isMode_a;
        _isMode_i = assign._isMode_i;
        _isMode_m = assign._isMode_m;
        _isMode_n = assign._isMode_n;
        _isMode_q = assign._isMode_q;
        _isMode_p = assign._isMode_p;
        _isMode_s = assign._isMode_s;
        _isMode_r = assign._isMode_r;
        _isMode_t = assign._isMode_t;
        _isMode_k = assign._isMode_k;
        _isMode_l = assign._isMode_l;
        _isMode_b = assign._isMode_b;
        _isMode_e = assign._isMode_e;
        _isMode_I = assign._isMode_I;
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
std::string& Channel::getChannelkey(void)
{
	return(_channelkey);
}
void Channel::setChannelkey(std::string channelkey)
{
	_channelkey = channelkey;
}

int	Channel::getChannelLimit(void) const
{
	return(_channelLimit);	
}
void Channel::setChannelLimit(int channelLimit)
{
	_channelLimit = channelLimit;
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
std::vector<std::string>& Channel::getInvitedMembers(void)
{
	return (_invitedMembers);
}
void Channel::setInvitedMembers(std::string invitedMember)
{
	_invitedMembers.push_back(invitedMember);	
}


std::string&	Channel::getChannelTopic(void)
{
	return _channelTopic;
}

void	Channel::setChannelTopic(std::string channelTopic)
{
	_channelTopic = channelTopic;
}

bool Channel::getIsMode_O(void) const
{
	return (_isMode_O);
}
void Channel::setIsMode_O(bool isMode_O)
{
	_isMode_O = isMode_O;
}
bool Channel::getIsMode_o(void) const
{
	return (_isMode_o);
}
void Channel::setIsMode_o(bool isMode_o)
{
	_isMode_o = isMode_o;
}
bool Channel::getIsMode_v(void) const
{
	return (_isMode_v);
}
void Channel::setIsMode_v(bool isMode_v)
{
	_isMode_v = isMode_v;
}
bool Channel::getIsMode_a(void) const
{
	return (_isMode_a);
}
void Channel::setIsMode_a(bool isMode_a)
{
	_isMode_a = isMode_a;
}
bool Channel::getIsMode_i(void) const
{
	return (_isMode_i);
}
void Channel::setIsMode_i(bool isMode_i)
{
	_isMode_i = isMode_i;
}
bool Channel::getIsMode_m(void) const
{
	return (_isMode_m);
}
void Channel::setIsMode_m(bool isMode_m)
{
	_isMode_m = isMode_m;
}
bool Channel::getIsMode_n(void) const
{
	return (_isMode_n);
}
void Channel::setIsMode_n(bool isMode_n)
{
	_isMode_n = isMode_n;
}
bool Channel::getIsMode_q(void) const
{
	return (_isMode_q);
}
void Channel::setIsMode_q(bool isMode_q)
{
	_isMode_q = isMode_q;
}
bool Channel::getIsMode_p(void) const
{
	return (_isMode_p);
}
void Channel::setIsMode_p(bool isMode_p)
{
	_isMode_p = isMode_p;
}
bool Channel::getIsMode_s(void) const
{
	return (_isMode_s);
}
void Channel::setIsMode_s(bool isMode_s)
{
	_isMode_s = isMode_s;
}
bool Channel::getIsMode_r(void) const
{
	return (_isMode_r);
}
void Channel::setIsMode_r(bool isMode_r)
{
	_isMode_r = isMode_r;
}
bool Channel::getIsMode_t(void) const
{
	return (_isMode_t);
}
void Channel::setIsMode_t(bool isMode_t)
{
	_isMode_t = isMode_t;
}
bool Channel::getIsMode_k(void) const
{
	return (_isMode_k);
}
void Channel::setIsMode_k(bool isMode_k)
{
	_isMode_k = isMode_k;
}
bool Channel::getIsMode_l(void) const
{
	return (_isMode_l);
}
void Channel::setIsMode_l(bool isMode_l)
{
	_isMode_l = isMode_l;
}
bool Channel::getIsMode_b(void) const
{
	return (_isMode_b);
}
void Channel::setIsMode_b(bool isMode_b)
{
	_isMode_b = isMode_b;
}
bool Channel::getIsMode_e(void) const
{
	return (_isMode_e);
}
void Channel::setIsMode_e(bool isMode_e)
{
	_isMode_e = isMode_e;
}
bool Channel::getIsMode_I(void) const
{
	return (_isMode_I);
}
void Channel::setIsMode_I(bool isMode_I)
{
	_isMode_I = isMode_I;
}

Channel::~Channel()
{}