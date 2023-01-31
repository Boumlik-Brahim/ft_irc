/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:36:31 by bbrahim           #+#    #+#             */
/*   Updated: 2023/01/31 18:42:14 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

// Constructors
Server::Server()
{}
Server::Server(int port_number, std::string password) : password(password), port_number(port_number)
{}
Server::Server(const Server &copy) : password(copy.password), port_number(copy.port_number)
{}

// Operators
Server &Server::operator=(const Server &assign)
{
	if (this != &assign)
	{
		this->password = assign.password;
		this->port_number = assign.port_number;
	}
	return *this;
}

// Getters and setters
int Server::getPort_number(void) const
{
	return (this->port_number);
}
void Server::setPort_number(int port_number)
{
	this->port_number = port_number;
}
std::string Server::getPassword(void) const
{
	return (this->password);
}
void Server::setPassword(std::string password)
{
	this->password = password;
}
int Server::getSocket_fd(void) const
{
	return (this->socket_fd);
}
void Server::setSocket_fd(int socket_fd)
{
	this->socket_fd = socket_fd;
}
int Server::getNew_socket_fd(void) const
{
	return (this->new_socket_fd);
}
void Server::setNew_socket_fd(int new_socket_fd)
{
	this->new_socket_fd = new_socket_fd;
}

// Functions
void Server::create_socket()
{
	int opt;

	opt = 1;
	this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socket_fd < 0)
	{
		std::cout << "ERROR OPENING SOCKET" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0)
	{
		std::cout << "ERROR OPENING SETSOCKETOPT" << std::endl;
		exit(EXIT_FAILURE);
	}
	memset((char *)&this->serv_addr, 0, sizeof(this->serv_addr));
	this->serv_addr.sin_family = AF_INET;
	this->serv_addr.sin_addr.s_addr = INADDR_ANY;
	this->serv_addr.sin_port = htons(this->port_number);
}
void Server::bind_socket()
{
	if (bind(this->socket_fd, (struct sockaddr *)&this->serv_addr, sizeof(this->serv_addr)) < 0)
	{
		std::cout << "ERROR ON BINDING" << std::endl;
		exit(EXIT_FAILURE);
	}
}
void Server::listen_socket()
{
	if (listen(this->socket_fd, 5) < 0)
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
	

	client_lenght = sizeof(this->cli_addr);
	numfds = 1;
	this->fds[0].fd = this->socket_fd;
	this->fds[0].events = POLLIN;
	while (1)
	{
		ret = poll(this->fds, numfds, -1);
		if (ret < 0)
		{
			std::cout << "ERROR ON POLL" << std::endl;
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < numfds; i++)
		{
			if (this->fds[i].revents & POLLIN)
			{
				if (this->fds[i].fd == this->socket_fd)
				{
					this->new_socket_fd = accept(this->socket_fd, (struct sockaddr *)&this->cli_addr, (socklen_t *)&client_lenght);
					if (this->new_socket_fd < 0)
					{
						std::cout << "ERROR ON ACCEPT" << std::endl;
						exit(EXIT_FAILURE);
					}
					this->fds[numfds].fd = this->new_socket_fd;
					this->fds[numfds].events = POLLIN;
					numfds++;
					count = numfds;
					mapClients.insert(std::pair<int, Client*>(numfds, new Client()));
				}
				else
				{
					sock = this->fds[i].fd;
					read_write_socket(sock, &count);
				}
			}
		}
	}
}
void Server::read_write_socket(int new_socket_fd, int *count)
{
	int		n;
	char	buffer[256];

	bzero(buffer, 256);
	n = read(new_socket_fd, buffer, 255);
	if (n < 0)
	{
		std::cout << "ERROR READING FROM SOCKET" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (n == 0)
	{
		std::cout << "CLIENT IS DISCONNECTED." << std::endl;
		(*count)--;
		close(new_socket_fd);
		if ((*count) == 1)
			exit(EXIT_SUCCESS);
		return ;
	}
	std::cout << "HERE IS THE MESSAGE: " << buffer << std::endl;
	n = write(new_socket_fd, "I GOT YOUR MESSAGE.\n", 20);
	if (n < 0)
	{
		std::cout << "ERROR WRITNG ON SOCKET" << std::endl;
		exit(EXIT_FAILURE);
	}	
}
void Server::close_socket(int socket_fd)
{
	close(socket_fd);
}

// Destructor
Server::~Server()
{
}