#include "../../headers/Server.hpp"

Client::Client(): _clientMaxnumOfChannels(2), buf("")
{}

Client::Client(int newSocketFd): _clientFd(newSocketFd), _clientMaxnumOfChannels(2), buf("") 
{}

Client::Client(const Client &copy)
{
	*this = copy;
}

Client & Client::operator=(const Client &assign)
{
	if (this != &assign)
	{
		_nickName = assign._nickName;
		_userName = assign._userName;
		_realName = assign._realName;
		_joinedChannels = assign._joinedChannels;
		_invitedChannels = assign._invitedChannels;
		_clientFd = assign._clientFd;
		_clientMaxnumOfChannels = assign._clientMaxnumOfChannels;
		_isAuthValid = assign._isAuthValid;
	}
	return *this;
}

std::string Client::getNickName(void)
{
	return (_nickName);
}
void Client::setNickName(std::string nickName)
{
	_nickName = nickName;
}
std::string Client::getUserName(void) const
{
	return (_userName);
}
void Client::setUserName(std::string userName)
{
	_userName = userName;
}
std::string Client::getRealName(void) const
{
	return (_realName);
}
void Client::setRealName(std::string realName)
{
	_realName = realName;
}
std::vector<std::string>& Client::getJoinedChannels(void)
{
    return (_joinedChannels);
}
void Client::setJoinedChannels(std::string joinedChannel)
{
	_joinedChannels.push_back(joinedChannel);
}
std::vector<std::string>&	Client::getInvitedChannels(void)
{
	return (_invitedChannels);
}
void Client::setInvitedChannels(std::string invitedChannel)
{
	this->_invitedChannels.push_back(invitedChannel);
}
int Client::getClientFd()
{
	return (_clientFd);
}
void Client::setClientFd(int clientFd)
{
	_clientFd = clientFd;
}
int	Client::getClientMaxnumOfChannels(void) const
{
	return (_clientMaxnumOfChannels);	
}
void Client::setClientMaxnumOfChannels(int clientMaxnumOfChannels)
{
	_clientMaxnumOfChannels = clientMaxnumOfChannels;	
}
bool Client::getIsAuthValid(void) const
{
	return (_isAuthValid);
}
void Client::setAuthValid(bool isValid)
{
	_isAuthValid = isValid;
}

int	Client::getLoginTime(void)
{
	return _loginTime;
}
void Client::setLoginTime(int loginTime)
{
	_loginTime = loginTime;
}

Client::~Client()
{}