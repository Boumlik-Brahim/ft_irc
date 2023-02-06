/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:20:09 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/06 13:43:22 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>

# include <iostream>
# include <string>
# include <map>
# include "../headers/Client.hpp"
class Channel
{
	private:
		std::string				_channelName;
		std::string				_channelProperties;
		std::string				_channelCreator;
		std::string				_channellifetime;
		std::map<int, Client>	_currentMembers;

	public:
		Channel();
		Channel(const Channel &copy);

		Channel & operator=(const Channel &assign);

		~Channel();
};

#endif