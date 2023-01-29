/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:36:31 by bbrahim           #+#    #+#             */
/*   Updated: 2023/01/29 18:22:33 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

// Constructors
Server::Server()
{
	std::cout << "\e[0;33mDefault Constructor called of Server\e[0m" << std::endl;
}
Server::Server(int port_number, std::string	password): password(password), port_number(port_number)
{
	std::cout << "\e[0;33mParametrized Constructor called of Server\e[0m" << std::endl;
}
Server::Server(const Server &copy): password(copy.password), port_number(copy.port_number)
{
	std::cout << "\e[0;33mCopy Constructor called of Server\e[0m" << std::endl;	
}

// Operators
Server & Server::operator=(const Server &assign)
{
	if(this != &assign)
	{
		this->password = assign.password;
		this->port_number = assign.port_number;
	}
	return *this;
}

// Getters and setters
int Server::getPort_number( void ) const
{
	return (this->port_number);
}
void Server::setPort_number( int port_number )
{
	this->port_number = port_number;
}
std::string	Server::getPassword(void) const
{
	return (this->password);
}
void Server::setPassword(std::string password)
{
	this->password = password;
}
int Server::getSocket_fd( void ) const
{
	return (this->socket_fd);
}
void Server::setSocket_fd( int socket_fd )
{
	this->socket_fd = socket_fd;
}
int Server::getNew_socket_fd( void ) const
{
	return (this->new_socket_fd);
}
void Server::setNew_socket_fd( int new_socket_fd )
{
	this->new_socket_fd = new_socket_fd;
}

// Functions
void Server::create_socket()
{
	this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socket_fd < 0)
	{
		std::cout << "ERROR OPENING SOCKET" << std::endl;
		exit (EXIT_FAILURE);
	}
	int opt = 1;
	setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
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
		exit (EXIT_FAILURE);
	}
}
void Server::listen_socket()
{
	if (listen(this->socket_fd, 5) < 0)
	{
		std::cout << "ERROR ON LISTEN" << std::endl;
		exit (EXIT_FAILURE);
	}
	this->client_lenght = sizeof(this->cli_addr);
}
void Server::accept_socket()
{
	struct pollfd fds[10];
	int numfds = 1;
	fds[0].fd = this->socket_fd;
	fds[0].events = POLLIN;
	while (1)
	{
		int ret = poll(fds, numfds, -1);
		if (ret < 0)
		{
			std::cout << "ERROR ON POLL" << std::endl;
			exit (EXIT_FAILURE);
		}
		if (fds[0].revents & POLLIN)
		{
			this->new_socket_fd = accept(this->socket_fd, (struct sockaddr *)&this->cli_addr, (socklen_t *)&this->client_lenght);
			if (this->new_socket_fd < 0)
			{
				std::cout << "ERROR ON ACCEPT" << std::endl;
				exit (EXIT_FAILURE);
			}
			fds[numfds].fd = this->new_socket_fd;
			fds[numfds].events = POLLIN;
			numfds++;
		}
		for (int i = 1; i < numfds; i++)
		{
			if (fds[i].revents & POLLIN)
			{
				int sock = fds[i].fd;
				read_write_socket(sock);
			}
		}
	}
}
void Server::read_write_socket(int new_socket_fd)
{
	int		n;
	char	buffer[256];

	bzero(buffer, 256);
	n = read(new_socket_fd, buffer, 255);
	if (n < 0)
	{
		std::cout << "ERROR READING FROM SOCKET" << std::endl;
		exit (EXIT_FAILURE);
	}
	// if (n == 0)
	// 	;// client is desconected
	// if (n > 0)
	// {
		
	// }
	std::cout << "here is the measage: " << buffer << std::endl;

	n = write(new_socket_fd, "Igot your meassage\n", 20);
	if (n < 0)
	{
		std::cout << "ERROR WRITNG ON SOCKET" << std::endl;
		exit (EXIT_FAILURE);
	}
}
void Server::close_socket(int socket_fd)
{
	close(socket_fd);
}

// Destructor
Server::~Server()
{
	std::cout << "\e[0;31mDestructor called of Server\e[0m" << std::endl;
}