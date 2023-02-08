/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Modes.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:40:30 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/08 18:43:12 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void checkInviteOnlyChanFlag(Channel chnl, std::string nickname, int senderFd)
{
    for(size_t i = 0; i < chnl.getInvitedMembers().size() ; i++)
    {
        if (chnl.getInvitedMembers().at(i) == nickname)
            return ;
    }
    return (errorHandler(senderFd, 473, chnl.getChannelName()));/*ERR_INVITEONLYCHAN*/
}



// if (tmp.getChannelModes().at(i) == "a")
//     void checkAnonymousChanFlag();
// else if (tmp.getChannelModes().at(i) == "i")
//     checkInviteOnlyChanFlag(tmp, );
// else if (tmp.getChannelModes().at(i) == "m")
//     void checkModeratedChan();
// else if (tmp.getChannelModes().at(i) == "n")
//     void checkNoMsgToChannel();
// else if (tmp.getChannelModes().at(i) == "q")
//     void checkQuietChanFlag();
// else if (tmp.getChannelModes().at(i) == "p")
//     void PrivateChanFlag();
// else if (tmp.getChannelModes().at(i) == "s")
//     void checkSecretChanFlag();
// else if (tmp.getChannelModes().at(i) == "r")
//     void checkServerReopChanFlag();
// else if (tmp.getChannelModes().at(i) == "t")
//     void checkTopic();