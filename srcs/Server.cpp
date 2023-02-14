/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:41:32 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/14 15:18:17 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

Server::Server()
{}
Server::Server(std::string server_name, int port_number, std::string password) : _server_name(server_name),  _password(password), _port_number(port_number)
{}
Server::Server(int port_number, std::string password) : _password(password), _port_number(port_number)
{}
Server::Server(const Server &copy) : _password(copy._password), _port_number(copy._port_number)
{}

Server &Server::operator=(const Server &assign)
{
	if (this != &assign)
	{
		_password = assign._password;
		_port_number = assign._port_number;
	}
	return *this;
}

int Server::getPort_number(void) const
{
	return (_port_number);
}
void Server::setPort_number(int port_number)
{
	_port_number = port_number;
}
std::string Server::getPassword(void) const
{
	return (_password);
}
void Server::setPassword(std::string password)
{
	_password = password;
}
int Server::getSocket_fd(void) const
{
	return (_socket_fd);
}
void Server::setSocket_fd(int socket_fd)
{
	_socket_fd = socket_fd;
}
int Server::getNew_socket_fd(void) const
{
	return (_new_socket_fd);
}
void Server::setNew_socket_fd(int new_socket_fd)
{
	_new_socket_fd = new_socket_fd;
}

void Server::create_socket()
{
	int opt;

	opt = 1;
	_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket_fd < 0)
	{
		std::cout << "ERROR OPENING SOCKET" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0)
	{
		std::cout << "ERROR OPENING SETSOCKETOPT" << std::endl;
		exit(EXIT_FAILURE);
	}
	memset((char *)&_serv_addr, 0, sizeof(_serv_addr));
	_serv_addr.sin_family = AF_INET;
	_serv_addr.sin_addr.s_addr = INADDR_ANY;
	_serv_addr.sin_port = htons(_port_number);
}
void Server::bind_socket()
{
	if (bind(_socket_fd, (struct sockaddr *)&_serv_addr, sizeof(_serv_addr)) < 0)
	{
		std::cout << "ERROR ON BINDING" << std::endl;
		exit(EXIT_FAILURE);
	}
}
void Server::listen_socket()
{
	if (listen(_socket_fd, 5) < 0)
	{
		std::cout << "ERROR ON LISTEN" << std::endl;
		exit(EXIT_FAILURE);
	}
}
void Server::accept_socket()
{
	int numfds;
	int ret;
	int sock;
	int i;
	int	client_lenght;
	int	count;
	

	client_lenght = sizeof(_cli_addr);
	memset(_fds, 0, MAX_CONNECTIONS * sizeof(struct pollfd));
	numfds = 1;
	_fds[0].fd = _socket_fd;
	_fds[0].events = POLLIN;
	while (1)
	{
		ret = poll(_fds, numfds, -1);
		if (ret < 0)
		{
			std::cout << "ERROR ON POLL" << std::endl;
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < numfds; i++)
		{
			if (_fds[i].revents & POLLIN)
			{
				if (_fds[i].fd == _socket_fd)
				{
					_new_socket_fd = accept(_socket_fd, (struct sockaddr *)&_cli_addr, (socklen_t *)&client_lenght);
					if (_new_socket_fd < 0)
					{
						std::cout << "ERROR ON ACCEPT" << std::endl;
						exit(EXIT_FAILURE);
					}
					_fds[numfds].fd = _new_socket_fd;
					_fds[numfds].events = POLLIN;
					numfds++;
					count = numfds;
					_mapGuest.insert(std::pair<int, Guest*>(_new_socket_fd, new Guest()));
					_mapClients.insert(std::pair<int, Client*>(_new_socket_fd, new Client()));
				}
				else
				{
					sock = _fds[i].fd;
					read_write_socket(sock, &count);
				}
			}
		}
	}
}
void Server::read_write_socket(int newSocketFd, int *count)
{
	int		n;
	char	buffer[256];

	bzero(buffer, 256);
	Client *client = _mapClients[newSocketFd];
	n = recv(newSocketFd, buffer, 255, 0);
	if (n < 0)
	{
		std::cout << "ERROR READING FROM SOCKET" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (n == 0)
	{
		std::cout << "CLIENT IS DISCONNECTED." << std::endl;
		(*count)--;
		_mapClients.erase(newSocketFd);
		close(newSocketFd);
		if ((*count) == 1)
			exit(EXIT_SUCCESS);
		return ;
	}
	if (n > 1)
	{
		client->buf += buffer;
		size_t size = client->buf.size();
		if(size > 2 && client->buf[size - 1] == '\n' && client->buf[size - 2] == '\r')
		{
			std::string tmp = client->buf;
			client->buf.erase();
			tmp.erase(size - 2, 2);
			backBone(tmp, newSocketFd);
		}
	}
	// n = write(new_socket_fd, "I GOT YOUR MESSAGE.\n", 20);
	// if (n < 0)
	// {
	// 	std::cout << "ERROR WRITNG ON SOCKET" << std::endl;
	// 	exit(EXIT_FAILURE);
	// }	
}
void Server::close_socket(int socket_fd)
{
	close(socket_fd);
}

void Server::WelcomeMsg(int fd)
{
	std::string sender = findNickClientByFd(fd);
	cmd_Resp_Handler1(fd, 1, _server_name, sender);
	cmd_Resp_Handler1(fd, 2, _server_name, sender);
	cmd_Resp_Handler1(fd, 3, _server_name, sender);
}

// Destructor
Server::~Server()
{}
