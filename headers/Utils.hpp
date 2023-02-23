/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:54:13 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/20 17:54:17 by bbrahim          ###   ########.fr       */
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
void                        checkChnlNames(std::vector<std::string> tmpArgs);
std::vector<std::string>    splitBySeparator(std::string args, std::string sep);
void                        sendReplay(int fd, std::string message);

#endif