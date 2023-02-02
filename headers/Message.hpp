/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:35:17 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/02 15:08:52 by bbrahim          ###   ########.fr       */
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
		std::string					_appendMsg;
		bool						_isValidCommad;

	public:
		Message();
		Message(const Message &copy);
		Message &operator=(const Message &assign);
		~Message();

		void setArguments(char **data);
		void setCommand(char *cmd);
		void setIsValidCommand(bool isValid);
		void setAppendMsg(std::string toAppend);

		std::string getAppendMsg() const;
		std::string getCommand(void) const;
		bool 		getIsValidCommand(void) const;
		std::vector<std::string> getArgument(void) const;

		
};

#endif