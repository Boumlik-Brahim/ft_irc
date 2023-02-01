/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:37:22 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/01 11:28:27 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <poll.h>
# include <map>
# include "../headers/Client.hpp"
# include "../headers/Utils.hpp"
# include "../headers/Message.hpp"

# define MAX_CONNECTIONS 10
class Server
{
	private:
		std::string				password;
		int						port_number;
		int						socket_fd;
		int						new_socket_fd;
		struct sockaddr_in 		serv_addr, cli_addr;
		struct pollfd			fds[MAX_CONNECTIONS];
		std::map<int, Client*>	mapClients;

	public:
		// Constructors
		Server();
		Server(int port_number, std::string password);
		Server(const Server &copy);

		// Operators
		Server &operator=(const Server &assign);

		// Getters and setters
		int			getPort_number(void) const;
		void		setPort_number(int port_number);
		std::string	getPassword(void) const;
		void		setPassword(std::string password);
		int			getSocket_fd( void ) const;
		void		setSocket_fd( int socket_fd );
		int			getNew_socket_fd( void ) const;
		void		setNew_socket_fd( int new_socket_fd );

		// Functions
		void create_socket();
		void bind_socket();
		void listen_socket();
		void accept_socket();
		void read_write_socket(int new_socket_fd, int *count);
		void close_socket(int socket_fd);

		// Destructor
		~Server();
};

#endif