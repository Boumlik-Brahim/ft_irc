/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:35:17 by bbrahim           #+#    #+#             */
/*   Updated: 2023/01/31 17:40:34 by bbrahim          ###   ########.fr       */
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
		std::vector<std::string>	arguments;
		std::string					command;
		bool						isValidCommad;

	public:
		// Constructors
		Message();
		Message(const Message &copy);

		// Operators
		Message &operator=(const Message &assign);

		// Destructor
		~Message();
};

#endif