/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:20:09 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/06 17:29:34 by bbrahim          ###   ########.fr       */
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
		std::string					_channelName;
		std::string					_channelCreator;
		std::vector<Client>			_channelMembers;
		std::vector<Client>			_channelOperators;
		std::vector<Client>			_channelBannedMembers;
		std::vector<std::string>	_channelModes;

	public:
		Channel();
		Channel(const Channel &copy);
		Channel & operator=(const Channel &assign);

		std::string	getChannelName(void) const;
		void		setChannelName(std::string channelName);
		std::string	getChannelCreator(void) const;
		void		setChannelCreator(std::string channelCreator);

		~Channel();
};

#endif