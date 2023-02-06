/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:20:09 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/06 15:19:39 by bbrahim          ###   ########.fr       */
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

		std::string	getChannelName(void) const;
		void		setChannelName(std::string channelName);
		std::string	getChannelProperties(void) const;
		void		setChannelProperties(std::string channelProperties);
		std::string	getChannelCreator(void) const;
		void		setChannelCreator(std::string channelCreator);
		std::string	getChannellifetime(void) const;
		void		setChannellifetime(std::string channellifetime);

		~Channel();
};

#endif