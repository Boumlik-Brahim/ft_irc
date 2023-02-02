/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:22:27 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/02 19:19:31 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/Server.hpp"

void setAttributeMsg(Message &msg, char **data)
{
    msg.setCommand(data[0]);
    msg.setArguments(data);
    msg.setIsValidCommand(false);
}

void parseArg(Message &msg, char **data)
{
	(void)msg;
	std::vector<std::string> args;
	std::string tmp;

	for (int i = 1; data[i]; i++)
	{
		if (data[i][0] == ':')
		{
			for ( int j = i; data[j]; j++)
			{
				std::cout << tmp << std::endl;
				tmp += data[j];
				if (data[j + 1])
					tmp += ' ';
			}
			args.push_back(tmp);
			break;
		}
		else
			args.push_back(data[i]);
	}
}

void Server::backBone(std::string buffer, int new_socket_fd)
{
    (void)new_socket_fd;
    Message msg;
    char **data;

    data = ft_split(buffer.c_str(), ' ');
	parseArg(msg, data);
    setAttributeMsg(msg, data);
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