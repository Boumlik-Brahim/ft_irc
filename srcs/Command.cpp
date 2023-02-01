/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:22:27 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/01 16:28:54 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/Server.hpp"

void setAttributeMsg(Message &msg, char **data)
{
    msg.setCommand(data[0]);
    msg.setArguments(data);
    msg.setIsValidCommand(false);
}

void Server::backBone(char *buffer, int new_socket_fd)
{
    (void)new_socket_fd;
    Message msg;
    char **data;

    data = ft_split(buffer, ' ');
    setAttributeMsg(msg, data);
    if (!msg.getCommand().compare("PASS"))
    {
        std::cout << "i got the pass" << std::endl;
    }
    if (!msg.getCommand().compare("NICK"))
    {
        std::cout << "i got the nick" << std::endl;
    }
    if (!msg.getCommand().compare("USER"))
    {
        std::cout << "i got the user" << std::endl;
    }
    if (!msg.getCommand().compare("NOTICE"))
    {
    }
    if (!msg.getCommand().compare("PRIVMSG"))
    {
    }
    else
    {
    }
    
}