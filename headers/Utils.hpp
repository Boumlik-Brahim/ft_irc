/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
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