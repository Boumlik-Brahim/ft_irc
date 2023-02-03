/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:35:17 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/03 09:47:13 by bbrahim          ###   ########.fr       */
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

		std::vector<std::string>	getArgument(void) const;
		void						setArguments(std::vector<std::string> arguments);
		std::string					getCommand(void) const;
		void						setCommand(std::string command);
		bool						getIsValidCommand(void) const;
		void						setIsValidCommand(bool isValid);

		~Message();
};

#endif