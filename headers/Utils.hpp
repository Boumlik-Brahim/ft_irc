/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:20:15 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/20 16:22:57 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "Server.hpp"

char	                    **ft_split(char *s, char c);
void                        checkMultiArgs(Message &msg);
void                        checkChnlNames(std::vector<std::string> tmpArgs, int newSocketFd);
std::vector<std::string>    splitBySeparator(std::string args, std::string sep);
void sendReplay(int fd, std::string message);


#endif