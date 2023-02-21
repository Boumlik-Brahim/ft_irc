/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:36:23 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/21 11:05:09 by izail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Server.hpp"
#include "headers/Channel.hpp"
#include "headers/Client.hpp"
#include "headers/Bot.hpp"

int main(int argc, char const *argv[])
{
	(void)argc;
	Server server1("localhost",atoi(argv[1]), argv[2]);
	server1.create_socket();
	server1.bind_socket();
	server1.listen_socket();
	server1.accept_socket();
	server1.close_socket(server1.getSocket_fd());

	return (0);
}