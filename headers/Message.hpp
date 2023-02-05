/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:35:17 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/05 16:39:42 by bbrahim          ###   ########.fr       */
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
		std::string					_command;
		bool						_isValidCommad;

	public:
		Message();
		Message(const Message &copy);
		Message &operator=(const Message &assign);

		std::string					getCommand(void) const;
		void						setCommand(std::string command);
		std::vector<std::string>	getArgument(void) const;
		void						setArguments(std::vector<std::string> arguments);
		bool						getIsValidCommand(void) const;
		void						setIsValidCommand(bool isValid);

		~Message();
};

void sendMessage(int sender_fd, std::string message);
void errorHandler(int sender_fd, int err_code, std::string err_arg, std::string err_arg2);
void errorHandler(int sender_fd, int err_code, std::string err_arg);
void errorHandler(int sender_fd, int err_code);

void cmd_Resp_Handler(int sender_fd, int cmd_resp_code, std::string cmd_resp_arg, std::string cmd_resp_arg2, std::string cmd_resp_arg3);
void cmd_Resp_Handler(int sender_fd, int cmd_resp_code, std::string cmd_resp_arg, std::string cmd_resp_arg2);
void cmd_Resp_Handler(int sender_fd, int cmd_resp_code, std::string cmd_resp_arg);
void cmd_Resp_Handler(int sender_fd, int cmd_resp_code);

#endif
