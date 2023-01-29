/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:36:23 by bbrahim           #+#    #+#             */
/*   Updated: 2023/01/29 18:25:29 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Server.hpp"
#include "headers/Channel.hpp"
#include "headers/Client.hpp"
#include "headers/Bot.hpp"

int main(int argc, char const *argv[])
{
	(void)argc;
	Server server1(atoi(argv[1]), argv[2]);
	server1.create_socket();
	server1.bind_socket();
	server1.listen_socket();
	server1.accept_socket();
	server1.read_write_socket(server1.getNew_socket_fd());
	server1.close_socket(server1.getSocket_fd());

	return (0);
}