/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 10:31:45 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/04 10:43:48 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void errorHandler(int err_code, std::string err_arg, char err_arg2)
{
	switch (err_code)
	{
		case  472:
			std::cout << "472 ERR_UNKNOWNMODE <char>" << err_arg2 << " :is unknown mode char to me for <channel>" << err_arg << "" << std::endl;
			break;
		case  478:
			std::cout << "478 ERR_BANLISTFULL <channel>" << err_arg << " <char>" << err_arg2 << " :Channel list is full" << std::endl;
			break;
		default:
			std::cout << "Invalid error code" << std::endl;
	}
}
void errorHandler(int err_code, std::string err_arg, std::string err_arg2)
{
	switch (err_code)
	{
		case  436:
			std::cout << "436 ERR_NICKCOLLISION <nick>" << err_arg << " :Nickname collision KILL from <user>" << err_arg2 << "@<host>" << std::endl;
			break;
		case  437:
			std::cout << "437 ERR_UNAVAILRESOURCE <nick" << err_arg << "/channel" << err_arg2 << "> :Nick/channel is temporarily unavailable" << std::endl;
			break;
		case  441:
			std::cout << "441 ERR_USERNOTINCHANNEL <nick>" << err_arg << " <channel>" << err_arg2 << " :They aren't on that channel" << std::endl;
			break;
		case  443:
			std::cout << "443 ERR_USERONCHANNEL <user>" << err_arg2 << " <channel>" << err_arg << " :is already on channel" << std::endl;
			break;
		case  424:
			std::cout << "424 ERR_FILEERROR:File error doing <file op>" << err_arg2 << " on <file>" << err_arg << std::endl;
			break;
		default:
			std::cout << "Invalid error code" << std::endl;
	}
}
void errorHandler(int err_code, std::string err_arg)
{
	switch (err_code)
	{
		case 401:
			std::cout << "401 ERR_NOSUCHNICK <nickname>" << err_arg << ":No such nick/channel" << std::endl;
			break;
		case  406:
			std::cout << "406 ERR_WASNOSUCHNICK <nickname>" << err_arg << " :There was no such nickname" << std::endl;
			break;
		case  432:
			std::cout << "432 ERR_ERRONEUSNICKNAME <nick>" << err_arg << " :Erroneous nickname" << std::endl;
			break;
		case  433:
			std::cout << "433 ERR_NICKNAMEINUSE <nick>" << err_arg << " :Nickname is already in use" << std::endl;
			break;
		case  407:
			std::cout << "407 ERR_TOOMANYTARGETS <target>" << err_arg << " :Duplicate recipients. No message delivered" << std::endl;
			break;
		case  444:
			std::cout << "444 ERR_NOLOGIN <user>" << err_arg << " :User not logged in" << std::endl;
			break;
		case  411:
			std::cout << "411 ERR_NORECIPIENT :No recipient given (<command>" << err_arg << ")" << std::endl;
			break;
		case  421:
			std::cout << "421 ERR_UNKNOWNCOMMAND <command>" << err_arg << " :Unknown command" << std::endl;
			break;
		case  461:
			std::cout << "461 ERR_NEEDMOREPARAMS<command>" << err_arg << " :Not enough parameters" << std::endl;
			break;
		case  402:
			std::cout << "402 ERR_NOSUCHSERVER <server name>" << err_arg << " :No such server" << std::endl;
			break;
		case  423:
			std::cout << "423 ERR_NOADMININFO <server>" << err_arg << " :No administrative info available" << std::endl;
			break;
		case  408:
			std::cout << "408 ERR_NOSUCHSERVICE <service name>" << err_arg << " :No such service" << std::endl;
			break;
		case  403:
			std::cout << "403 ERR_NOSUCHCHANNEL <channel name>" << err_arg << " :No such channel" << std::endl;
			break;
		case  404:
			std::cout << "404 ERR_CANNOTSENDTOCHAN <channel name>" << err_arg << " :Cannot send to channel" << std::endl;
			break;
		case  405:
			std::cout << "405 ERR_TOOMANYCHANNELS <channel name>" << err_arg << " :You have joined too many channels" << std::endl;
			break;
		case  442:
			std::cout << "442 ERR_NOTONCHANNEL <channel>" << err_arg << " :You're not on that channel" << std::endl;
			break;
		case  467:
			std::cout << "467 ERR_KEYSET <channel>" << err_arg << " :Channel key already set" << std::endl;
			break;
		case  471:
			std::cout << "471 ERR_CHANNELISFULL <channel>" << err_arg << " :Cannot join channel (+l)" << std::endl;
			break;
		case  473:
			std::cout << "473 ERR_INVITEONLYCHAN <channel>" << err_arg << " :Cannot join channel (+i)" << std::endl;
			break;
		case  474:
			std::cout << "474 ERR_BANNEDFROMCHAN <channel>" << err_arg << " :Cannot join channel (+b)" << std::endl;
			break;
		case  475:
			std::cout << "475 ERR_BADCHANNELKEY <channel>" << err_arg << " :Cannot join channel (+k)" << std::endl;
			break;
		case  476:
			std::cout << "476 ERR_BADCHANMASK <channel>" << err_arg << " :Bad Channel Mask" << std::endl;
			break;
		case  477:
			std::cout << "477 ERR_NOCHANMODES <channel>" << err_arg << " :Channel doesn't support modes" << std::endl;
			break;
		case  482:
			std::cout << "482 ERR_CHANOPRIVSNEEDED <channel>" << err_arg << " :You're not channel operator" << std::endl;
			break;
		case  413:
			std::cout << "413 ERR_NOTOPLEVEL <mask>" << err_arg << " :No toplevel domain specified" << std::endl;
			break;
		case  414:
			std::cout << "414 ERR_WILDTOPLEVEL <mask>" << err_arg << " :Wildcard in toplevel domain" << std::endl;
			break;
		case  415:
			std::cout << "415 ERR_BADMASK <mask>" << err_arg << " :Bad Server/host mask" << std::endl;
			break;
		default:
			std::cout << "Invalid error code" << std::endl;
	}
}
void errorHandler(int err_code)
{
	switch (err_code)
	{
		case  409:
			std::cout << "409 ERR_NOORIGIN:No origin specified" << std::endl;
			break;
		case  412:
			std::cout << "412 ERR_NOTEXTTOSEND :No text to send" << std::endl;
			break;
		case  422:
			std::cout << "422 ERR_NOMOTD:MOTD File is missing" << std::endl;
			break;
		case  431:
			std::cout << "431 ERR_NONICKNAMEGIVEN:No nickname given" << std::endl;
			break;
		case  445:
			std::cout << "445 ERR_SUMMONDISABLED:SUMMON has been disabled" << std::endl;
			break;
		case  446:
			std::cout << "446 ERR_USERSDISABLED:USERS has been disabled" << std::endl;
			break;
		case  451:
			std::cout << "451 ERR_NOTREGISTERED:You have not registered" << std::endl;
			break;
		case  462:
			std::cout << "462 ERR_ALREADYREGISTRED:Unauthorized command (already registered)" << std::endl;
			break;
		case  463:
			std::cout << "463 ERR_NOPERMFORHOST:Your host isn't among the privileged" << std::endl;
			break;
		case  464:
			std::cout << "464 ERR_PASSWDMISMATCH:Password incorrect" << std::endl;
			break;
		case  465:
			std::cout << "465 ERR_YOUREBANNEDCREEP:You are banned from this server" << std::endl;
			break;
		case  466:
			std::cout << "466 ERR_YOUWILLBEBANNED" << std::endl;
			break;
		case  479:
			std::cout << "481 ERR_NOPRIVILEGES:Permission Denied- You're not an IRC operator" << std::endl;
			break;
		case  481:
			std::cout << "481 ERR_NOPRIVILEGES:Permission Denied- You're not an IRC operator" << std::endl;
			break;
		case  483:
			std::cout << "483 ERR_CANTKILLSERVER:You can't kill a server!" << std::endl;
			break;
		case  484:
			std::cout << "484 ERR_RESTRICTED:Your connection is restricted!" << std::endl;
			break;
		case  485:
			std::cout << "485 ERR_UNIQOPPRIVSNEEDED:You're not the original channel operator" << std::endl;
			break;
		case  491:
			std::cout << "491 ERR_NOOPERHOST:No O-lines for your host" << std::endl;
			break;
		case  501:
			std::cout << "501 ERR_UMODEUNKNOWNFLAG:Unknown MODE flag" << std::endl;
			break;
		case  502:
			std::cout << "502 ERR_USERSDONTMATCH:Cannot change mode for other users" << std::endl;
			break;
		default:
			std::cout << "Invalid error code" << std::endl;
	}
}