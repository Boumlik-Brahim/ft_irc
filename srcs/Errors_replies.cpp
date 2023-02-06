/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors_replies.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 10:31:45 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/06 10:54:10 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void errorHandler(int sender_fd, int err_code, std::string err_arg, std::string err_arg2)
{
	std::string message;

	switch (err_code)
	{
		case 437:
			message = "437 ERR_UNAVAILRESOURCE <" + err_arg + "/" + err_arg2 + "> :Nick/channel is temporarily unavailable\r\n";
			break;
		case 441:
			message = "441 ERR_USERNOTINCHANNEL " + err_arg + err_arg2 + " :They aren't on that channel\r\n";
			break;
		case 443:
			message = "443 ERR_USERONCHANNEL " + err_arg2 + err_arg + " :is already on channel\r\n";
			break;
		case 424:
			message = "424 ERR_FILEERROR:File error doing " + err_arg2 + " on " + err_arg+"\r\n";
			break;
		case 472:
			message = "472 ERR_UNKNOWNMODE " + err_arg + " :is unknown mode char to me for " + err_arg2+"\r\n";
			break;
		case 478:
			message = "478 ERR_BANLISTFULL " + err_arg + err_arg2 + " :Channel list is full\r\n";
			break;
		default:
			std::cout << "Invalid error code" << std::endl;
	}

	sendMessage(sender_fd, message);
}
void errorHandler(int sender_fd, int err_code, std::string err_arg)
{
	std::string message;

	switch (err_code)
	{
		case 401:
			message = "401 ERR_NOSUCHNICK "+err_arg+":No such nick/channel\r\n";
			break;
		case 406:
			message = "406 ERR_WASNOSUCHNICK "+err_arg+" :There was no such nickname\r\n";
			break;
		case 432:
			message = "432 ERR_ERRONEUSNICKNAME "+err_arg+" :Erroneous nickname\r\n";
			break;
		case 433:
			message = "433 ERR_NICKNAMEINUSE "+err_arg+" :Nickname is already in use\r\n";
			break;
		case 407:
			message = "407 ERR_TOOMANYTARGETS "+err_arg+" :Duplicate recipients. No message delivered\r\n";
			break;
		case 444:
			message = "444 ERR_NOLOGIN "+err_arg+" :User not logged in\r\n";
			break;
		case 411:
			message = "411 ERR_NORECIPIENT :No recipient given ("+err_arg+")\r\n";
			break;
		case 421:
			message = "421 ERR_UNKNOWNCOMMAND "+err_arg+" :Unknown command\r\n";
			break;
		case 461:
			message = "461 ERR_NEEDMOREPARAMS "+err_arg+" :Not enough parameters\r\n";
			break;
		case 402:
			message = "402 ERR_NOSUCHSERVER "+err_arg+" :No such server\r\n";
			break;
		case 423:
			message = "423 ERR_NOADMININFO "+err_arg+" :No administrative info available\r\n";
			break;
		case 408:
			message = "408 ERR_NOSUCHSERVICE "+err_arg+" :No such service\r\n";
			break;
		case 403:
			message = "403 ERR_NOSUCHCHANNEL "+err_arg+" :No such channel\r\n";
			break;
		case 404:
			message = "404 ERR_CANNOTSENDTOCHAN "+err_arg+" :Cannot send to channel\r\n";
			break;
		case 405:
			message = "405 ERR_TOOMANYCHANNELS "+err_arg+" :You have joined too many channels\r\n";
			break;
		case 436:
			message = "436 ERR_NICKCOLLISION " + err_arg + " :Nickname collision KILL\r\n";
			break;
		case 442:
			message = "442 ERR_NOTONCHANNEL "+err_arg+" :You're not on that channel\r\n";
			break;
		case 467:
			message = "467 ERR_KEYSET "+err_arg+" :Channel key already set\r\n";
			break;
		case 471:
			message = "471 ERR_CHANNELISFULL "+err_arg+" :Cannot join channel (+l)\r\n";
			break;
		case 473:
			message = "473 ERR_INVITEONLYCHAN "+err_arg+" :Cannot join channel (+i)\r\n";
			break;
		case 474:
			message = "474 ERR_BANNEDFROMCHAN "+err_arg+" :Cannot join channel (+b)\r\n";
			break;
		case 475:
			message = "475 ERR_BADCHANNELKEY "+err_arg+" :Cannot join channel (+k)\r\n";
			break;
		case 476:
			message = "476 ERR_BADCHANMASK "+err_arg+" :Bad Channel Mask\r\n";
			break;
		case 477:
			message = "477 ERR_NOCHANMODES "+err_arg+" :Channel doesn't support modes\r\n";
			break;
		case 482:
			message = "482 ERR_CHANOPRIVSNEEDED "+err_arg+" :You're not channel operator\r\n";
			break;
		case 413:
			message = "413 ERR_NOTOPLEVEL "+err_arg+" :No toplevel domain specified\r\n";
			break;
		case 414:
			message = "414 ERR_WILDTOPLEVEL "+err_arg+" :Wildcard in toplevel domain\r\n";
			break;
		case 415:
			message = "415 ERR_BADMASK "+err_arg+" :Bad Server/host mask\r\n";
			break;
		default:
			std::cout << "Invalid error code" << std::endl;
	}

	sendMessage(sender_fd, message);
}
void errorHandler(int sender_fd, int err_code)
{
	std::string message;

	switch (err_code)
	{
		case 409:
			message = "409 ERR_NOORIGIN:No origin specified\r\n";
			break;
		case 412:
			message = "412 ERR_NOTEXTTOSEND :No text to send\r\n";
			break;
		case 422:
			message = "422 ERR_NOMOTD:MOTD File is missing\r\n";
			break;
		case 431:
			message = "431 ERR_NONICKNAMEGIVEN:No nickname given\r\n";
			break;
		case 445:
			message = "445 ERR_SUMMONDISABLED:SUMMON has been disabled\r\n";
			break;
		case 446:
			message = "445 ERR_SUMMONDISABLED:SUMMON has been disabled\r\n";
			break;
		case 451:
			message = "451 ERR_NOTREGISTERED:You have not registered\r\n";
			break;
		case 462:
			message = "462 ERR_ALREADYREGISTRED:Unauthorized command (already registered)\r\n";
			break;
		case 463:
			message = "463 ERR_NOPERMFORHOST:Your host isn't among the privileged\r\n";
			break;
		case 464:
			message = "464 ERR_PASSWDMISMATCH:Password incorrect\r\n";
			break;
		case 465:
			message = "465 ERR_YOUREBANNEDCREEP:You are banned from this server\r\n";
			break;
		case 466:
			message = "466 ERR_YOUWILLBEBANNED\r\n";
			break;
		case 479:
			message = "481 ERR_NOPRIVILEGES:Permission Denied- You're not an IRC operator\r\n";
			break;
		case 481:
			message = "481 ERR_NOPRIVILEGES:Permission Denied- You're not an IRC operator\r\n";
			break;
		case 483:
			message = "483 ERR_CANTKILLSERVER:You can't kill a server!\r\n";
			break;
		case 484:
			message = "484 ERR_RESTRICTED:Your connection is restricted!\r\n";
			break;
		case 485:
			message = "485 ERR_UNIQOPPRIVSNEEDED:You're not the original channel operator\r\n";
			break;
		case 491:
			message = "491 ERR_NOOPERHOST:No O-lines for your host\r\n";
			break;
		case 501:
			message = "501 ERR_UMODEUNKNOWNFLAG:Unknown MODE flag\r\n";
			break;
		case 502:
			message = "502 ERR_USERSDONTMATCH:Cannot change mode for other users\r\n";
			break;
		default:
			std::cout << "Invalid error code" << std::endl;
	}

	sendMessage(sender_fd, message);
}