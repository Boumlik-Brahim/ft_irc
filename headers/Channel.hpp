/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:53:00 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/20 17:53:17 by bbrahim          ###   ########.fr       */
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
		std::string								_channelTopic;
		std::string								_channelkey;
    	int										_channelLimit;
		std::vector<std::string>				_channelMemberAndOperators;
		std::vector<std::string>				_channelMembers;
		std::vector<std::string>				_channelOperators;
		std::vector<std::string>				_channelBannedMembers;
		std::vector<std::string>				_invitedMembers;

		bool 									_isMode_O;
        bool 									_isMode_o;
        bool 									_isMode_v;
        bool 									_isMode_a;
        bool 									_isMode_i;
        bool 									_isMode_m;
        bool 									_isMode_n;
        bool 									_isMode_q;
        bool 									_isMode_p;
        bool 									_isMode_s;
        bool 									_isMode_r;
        bool 									_isMode_t;
        bool 									_isMode_k;
        bool 									_isMode_l;
        bool 									_isMode_b;
        bool 									_isMode_e;
        bool 									_isMode_I;

	public:
		Channel();
		Channel(const Channel &copy);
		Channel & operator=(const Channel &assign);

		std::string&				getChannelName(void) ;
		void						setChannelName(std::string channelName);
		std::string&				getChannelCreator(void);
		void						setChannelCreator(std::string channelCreator);
		std::string&				getChannelkey(void);
		void						setChannelkey(std::string channelkey);
		std::string&				getChannelTopic(void);
		void						setChannelTopic(std::string channelTopic);
		std::vector<std::string>& 	getChannelMembers(void);
		void 						setChannelMembers(std::string channelMember);
		std::vector<std::string>& 	getChannelOperators(void);
		void						setChannelOperators(std::string channelOperator);
		std::vector<std::string>&	getChannelBannedMembers(void);
		void						setChannelBannedMembers(std::string channelBannedMember);
		std::vector<std::string>& 	getInvitedMembers(void);
		void 						setInvitedMembers(std::string channelMember);
		int							getChannelLimit(void) const;
		void						setChannelLimit(int channelLimit);
		bool						getIsMode_O(void) const;
		void						setIsMode_O(bool isMode_O);
		bool						getIsMode_o(void) const;
		void						setIsMode_o(bool isMode_o);
		bool						getIsMode_v(void) const;
		void						setIsMode_v(bool isMode_v);
		bool						getIsMode_a(void) const;
		void						setIsMode_a(bool isMode_a);
		bool						getIsMode_i(void) const;
		void						setIsMode_i(bool isMode_i);
		bool						getIsMode_m(void) const;
		void						setIsMode_m(bool isMode_m);
		bool						getIsMode_n(void) const;
		void						setIsMode_n(bool isMode_n);
		bool						getIsMode_q(void) const;
		void						setIsMode_q(bool isMode_q);
		bool						getIsMode_p(void) const;
		void						setIsMode_p(bool isMode_p);
		bool						getIsMode_s(void) const;
		void						setIsMode_s(bool isMode_s);
		bool						getIsMode_r(void) const;
		void						setIsMode_r(bool isMode_r);
		bool						getIsMode_t(void) const;
		void						setIsMode_t(bool isMode_t);
		bool						getIsMode_k(void) const;
		void						setIsMode_k(bool isMode_k);
		bool						getIsMode_l(void) const;
		void						setIsMode_l(bool isMode_l);
		bool						getIsMode_b(void) const;
		void						setIsMode_b(bool isMode_b);
		bool						getIsMode_e(void) const;
		void						setIsMode_e(bool isMode_e);
		bool						getIsMode_I(void) const;
		void						setIsMode_I(bool isMode_I);

		~Channel();
};

#endif