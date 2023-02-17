/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:20:15 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/16 13:42:26 by izail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "Server.hpp"


char	                    **ft_split(const char *s, char c);
void                        checkMultiArgs(Message &msg);
void                        checkChnlNames(std::vector<std::string> tmpArgs, int newSocketFd);
std::vector<std::string>    splitBySeparator(std::string args, std::string sep);

#endif