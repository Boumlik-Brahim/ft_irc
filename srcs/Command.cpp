/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:22:27 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/03 10:09:01 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void parseMessageFormat(Message &msg, char **data)
{
	std::vector<std::string> args;
	std::string tmp;

	msg.setCommand(data[0]);
	for (int i = 1; data[i]; i++)
	{
		if (data[i][0] == ':')
		{
			for (; data[i]; i++)
			{
				tmp += data[i];
				if (data[i + 1])
					tmp += ' ';
			}
			args.push_back(tmp);
			break;
		}
		else
			args.push_back(data[i]);
	}
	msg.setArguments(args);
}

void Server::backBone(std::string buffer, int new_socket_fd)
{
	(void)new_socket_fd;
	Message msg;
	char **data;

	data = ft_split(buffer.c_str(), ' ');
	parseMessageFormat(msg, data);
	// if (!msg.getCommand().compare("PASS"))
	// {
	//     std::cout << "i got the pass" << std::endl;
	// }
	// if (!msg.getCommand().compare("NICK"))
	// {
	//     std::cout << "i got the nick" << std::endl;
	// }
	// if (!msg.getCommand().compare("USER"))
	// {
	//     std::cout << "i got the user" << std::endl;
	// }
	// if (!msg.getCommand().compare("NOTICE"))
	// {
	// }
	// if (!msg.getCommand().compare("PRIVMSG"))
	// {
	// }
	// else
	// {
	// }
}