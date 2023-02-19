/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:02:45 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/19 19:02:47 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <string>
#include <vector>

class Message
{
	private:
		std::vector<std::string>	_arguments;
		std::vector<std::string>	_multiArgs;
		std::string					_command;
		std::vector<char>			_vecAddMode;
		std::vector<char>			_vecRmMode;
		bool						_isAddOrRm;
		bool						_isValidCommad;

	public:
		Message();
		Message(const Message &copy);
		Message &operator=(const Message &assign);

		std::string					getCommand(void) const;
		void						setCommand(std::string command);
		std::vector<std::string>&	getArguments(void);
		void						setArguments(std::vector<std::string> arguments);
		std::vector<std::string>	getMultiArgs(void) const;
		void						setMultiArgs(std::vector<std::string> multiArgs);
		bool						getIsValidCommand(void) const;
		void						setIsValidCommand(bool isValid);
		std::vector<char>&			getVecAddMode(void);
		void						setVecAddMode(char m);
		std::vector<char>&			getVecRmMode(void);
		void						setVecRmMode(char m);
		void						setIsAddOrRm(bool trueOrFalse);
		bool						getIsAddOrRm(void) const;

		void erase(std::vector<std::string>::iterator it);
		~Message();
};

void sendMessage(int sender_fd, std::string message);
void errorHandler(int sender_fd, int err_code, std::string err_arg, std::string err_arg2);
void errorHandler(int sender_fd, int err_code, std::string err_arg);
void errorHandler(int sender_fd, int err_code);

void cmd_Resp_Handler(int sender_fd, int cmd_resp_code, std::string cmd_resp_arg1, std::string cmd_resp_arg2, std::string cmd_resp_arg3, std::string cmd_resp_arg4);
void cmd_Resp_Handler(int sender_fd, int cmd_resp_code, std::string cmd_resp_arg, std::string cmd_resp_arg2, std::string cmd_resp_arg3);
void cmd_Resp_Handler(int sender_fd, int cmd_resp_code, std::string cmd_resp_arg, std::string cmd_resp_arg2);
void cmd_Resp_Handler(int sender_fd, int cmd_resp_code, std::string cmd_resp_arg);

// ishak
void cmd_Resp_Handler1(int sender_fd, int cmd_resp_code, std::string serverName, std::string nickName);
void cmd_Resp_Handler1(int sender_fd, int cmd_resp_code, std::string serverName, std::string nickName, std::string arg1, std::string arg2);
void cmd_Resp_Handler1(int sender_fd, int cmd_resp_code, std::string serverName, std::string nickName, std::string channelName, std::string arg2, std::string arg3);

void cmd_Resp_Handler(int sender_fd, int cmd_resp_code);

#endif
