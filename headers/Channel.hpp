/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <izail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:20:09 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/07 18:54:27 by izail            ###   ########.fr       */
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
		std::string								_channelName;
		std::string								_channelCreator;
		std::vector<std::string>				_channelMembers;
		std::vector<std::string>				_channelOperators;
		std::vector<std::string>				_channelBannedMembers;
		std::vector<std::string>				_channelModes;

	public:
		Channel();
		Channel(const Channel &copy);
		// Channel & operator=(const Channel &assign);

		std::string&				getChannelName(void) ;
		void						setChannelName(std::string channelName);
		std::string&				getChannelCreator(void);
		void						setChannelCreator(std::string channelCreator);
		std::vector<std::string>& 	getChannelMembers(void);
        void 						setChannelMembers(std::string channelMember);
        std::vector<std::string>& 	getChannelOperators(void);
        void        				setChannelOperators(std::string channelOperator);
        std::vector<std::string>&	getChannelBannedMembers(void);
        void        				setChannelBannedMembers(std::string channelBannedMember);
        std::vector<std::string>& 	getChannelModes(void);
        void        				setChannelModes(std::string channelModes);
		
		~Channel();
};

#endif