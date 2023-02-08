/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:20:15 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/08 10:13:19 by izail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "Server.hpp"


char	**ft_split(const char *s, char c);
void    checkMultiArgs(Message &msg);
void    checkChnlNames(std::vector<std::string> tmpArgs, int newSocketFd);


#endif