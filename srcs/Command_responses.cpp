/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command_responses.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:24:53 by bbrahim           #+#    #+#             */
/*   Updated: 2023/02/12 15:32:36 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void cmd_Resp_Handler(int sender_fd, int cmd_resp_code)
{
	std::string message;

	switch (cmd_resp_code)
	{
        case 305 :
            message = "305 RPL_UNAWAY :You are no longer marked as being away\r\n";
            break;
        case 306 :
            message = "306 RPL_NOWAWAY :You have been marked as being away\r\n";
            break;
        case 321 :
            message = "321 RPL_LISTSTART Obsolete. Not used.\r\n";
            break;
        case 323 :
            message = "323 RPL_LISTEND :End of LIST\r\n";
            break;
        case 374 :
            message = "374 RPL_ENDOFINFO :End of INFO list\r\n";
            break;
        case 376 :
            message = "376 RPL_ENDOFMOTD :End of MOTD command\r\n";
            break;
        case 381 :
            message = "381 RPL_YOUREOPER :You are now an IRC operator\r\n";
            break;
        case 392 :
            message = "392 RPL_USERSSTART :UserID Terminal  Host\r\n";
            break;
        case 394 :
            message = "394 RPL_ENDOFUSERS :End of users\r\n";
            break;
        case 395 :
            message = "395 RPL_NOUSERS :Nobody logged in\r\n";
            break;
        case 210 :
            message = "210 RPL_TRACERECONNECT Unused.\r\n";
            break;
		default:
			std::cout << "Invalid command response code" << std::endl;
	}

	sendMessage(sender_fd, message);
}
void cmd_Resp_Handler(int sender_fd, int cmd_resp_code, std::string cmd_resp_arg)
{
	std::string message;

	switch (cmd_resp_code)
	{
        case 003 :
            message = "003 RPL_CREATED This server was created <date>" + cmd_resp_arg + "\r\n";
            break;
        case 313 :
            message = "313 RPL_WHOISOPERATOR <nick>" + cmd_resp_arg + " :is an IRC operator\r\n";
            break;
        case 318 :
            message = "318 RPL_ENDOFWHOIS <nick>" + cmd_resp_arg + " :End of WHOIS list\r\n";
            break;
        case 369 :
            message = "369 RPL_ENDOFWHOWAS <nick>" + cmd_resp_arg + " :End of WHOWAS\r\n";
            break;
        case 331 :
            message = "331 RPL_NOTOPIC <channel>" + cmd_resp_arg + " :No topic is set\r\n";
            break;
        case 342 :
            message = "342 RPL_SUMMONING <user>" + cmd_resp_arg + " :Summoning user to IRC\r\n";
            break;
        case 347 :
            message = "347 RPL_ENDOFINVITELIST <channel>" + cmd_resp_arg + " :End of channel invite list\r\n";
            break;
        case 349 :
            message = "349 RPL_ENDOFEXCEPTLIST <channel>" + cmd_resp_arg + " :End of channel exception list\r\n";
            break;
        case 315 :
            message = "315 RPL_ENDOFWHO <name>" + cmd_resp_arg + " :End of WHO list\r\n";
            break;
        case 366 :
            message = "366 RPL_ENDOFNAMES <channel>" + cmd_resp_arg + " :End of NAMES list\r\n";
            break;
        case 371 :
            message = "371 RPL_INFO :<string>" + cmd_resp_arg + "\r\n";
            break;
        case 372 :
            message = "372 RPL_MOTD :- <text>" + cmd_resp_arg + "\r\n";
            break;
        case 383 :
            message = "383 RPL_YOURESERVICE You are service <servicename>" + cmd_resp_arg + "\r\n";
            break;
        case 375 :
            message = "375 RPL_MOTDSTART :- <server>" + cmd_resp_arg + " Message of the day - \r\n";
            break;
        case 382 :
            message = "382 RPL_REHASHING <config file>" + cmd_resp_arg + " :Rehashing\r\n";
            break;
        case 219 :
            message = "219 RPL_ENDOFSTATS <stats letter>" + cmd_resp_arg + " :End of STATS report\r\n";
            break;
        case 221 :
            message = "221 RPL_UMODEIS <user mode string>" + cmd_resp_arg + "\r\n";
            break;
        case 252 :
            message = "252 RPL_LUSEROP <integer>" + cmd_resp_arg + " :operator(s) online\r\n";
            break;
        case 253 :
            message = "253 RPL_LUSERUNKNOWN <integer>" + cmd_resp_arg + " :unknown connection(s)\r\n";
            break;
        case 254 :
            message = "254 RPL_LUSERCHANNELS <integer>" + cmd_resp_arg + " :channels formed\r\n";
            break;
        case 257 :
            message = "257 RPL_ADMINLOC1 :<admin info>" + cmd_resp_arg + "\r\n";
            break;
        case 258 :
            message = "258 RPL_ADMINLOC2 :<admin info>" + cmd_resp_arg + "\r\n";
            break;
        case 259 :
            message = "259 RPL_ADMINEMAIL :<admin info>" + cmd_resp_arg + "\r\n";
            break;
        case 263 :
            message = "263 RPL_TRYAGAIN <command>" + cmd_resp_arg + " :Please wait a while and try again.\r\n";
            break;
        case 365 :
            message = "365 RPL_ENDOFLINKS <mask>" + cmd_resp_arg + " :End of LINKS list\r\n";
            break;
        case 368 :
            message = "368 RPL_ENDOFBANLIST <channel>" + cmd_resp_arg + " :End of channel ban list\r\n";
            break;
        case 256 :
            message = "256 RPL_ADMINME <server>" + cmd_resp_arg + " :Administrative info\r\n";
            break;
		default:
			std::cout << "Invalid command response code" << std::endl;
	}

	sendMessage(sender_fd, message);
}
void cmd_Resp_Handler(int sender_fd, int cmd_resp_code, std::string cmd_resp_arg, std::string cmd_resp_arg2)
{
	std::string message;

	switch (cmd_resp_code)
	{
        case 005 :
            message = "005 RPL_BOUNCE Try server <server name>" + cmd_resp_arg + ", port <port number>" + cmd_resp_arg2 + "\r\n";
            break;
        case 302 :
            message = "302 RPL_USERHOST :*1<reply>" + cmd_resp_arg + " *( " " <reply>" + cmd_resp_arg + " )\r\n";
            break;
        case 303 :
            message = "303 RPL_ISON :*1<nick>" + cmd_resp_arg + " *( " " <nick>" + cmd_resp_arg + " )\r\n";
            break;
        case 301 :
            message = "301 RPL_AWAY <nick>" + cmd_resp_arg + " :<away message>" + cmd_resp_arg2 + "\r\n";
            break;
        case 317 :
            message = "317 RPL_WHOISIDLE <nick>" + cmd_resp_arg + " <integer>" + cmd_resp_arg2 + " :seconds idle\r\n";
            break;
        case 319 :
            message = "319 RPL_WHOISCHANNELS <nick>" + cmd_resp_arg + " :*( ( @ / + ) <channel>" + cmd_resp_arg2 + " " " )\r\n";
            break;
        case 325 :
            message = "325 RPL_UNIQOPIS <channel>" + cmd_resp_arg + " <nickname>" + cmd_resp_arg2 + "\r\n";
            break;
        case 332 :
            message = "332 RPL_TOPIC <channel>" + cmd_resp_arg + " :<topic>" + cmd_resp_arg2 + "\r\n";
            break;
        case 341 :
            message = "341 RPL_INVITING <channel>" + cmd_resp_arg + " <nick>" + cmd_resp_arg2 + "\r\n";
            break;
        case 346 :
            message = "346 RPL_INVITELIST <channel>" + cmd_resp_arg + " <invitemask>" + cmd_resp_arg2 + "\r\n";
            break;
        case 348 :
            message = "348 RPL_EXCEPTLIST <channel>" + cmd_resp_arg + " <exceptionmask>" + cmd_resp_arg2 + "\r\n";
            break;
        case 367 :
            message = "367 RPL_BANLIST <channel>" + cmd_resp_arg + " <banmask>" + cmd_resp_arg2 + "\r\n";
            break;
        case 201 :
            message = "201 RPL_TRACECONNECTING Try. <class>" + cmd_resp_arg + " <server>" + cmd_resp_arg2 + "\r\n";
            break;
        case 202 :
            message = "202 RPL_TRACEHANDSHAKE H.S. <class>" + cmd_resp_arg + " <server>" + cmd_resp_arg2 + "\r\n";
            break;
        case 203 :
            message = "203 RPL_TRACEUNKNOWN ???? <class>" + cmd_resp_arg + " [<client IP address in dot form>" + cmd_resp_arg2 + "]\r\n";
            break;
        case 204 :
            message = "204 RPL_TRACEOPERATOR Oper <class>" + cmd_resp_arg + " <nick>" + cmd_resp_arg2 + "\r\n";
            break;
        case 205 :
            message = "205 RPL_TRACEUSER User <class>" + cmd_resp_arg + " <nick>" + cmd_resp_arg2 + "\r\n";
            break;
        case 391 :
            message = "391 RPL_TIME <server>" + cmd_resp_arg + " :<string showing server's local time>" + cmd_resp_arg2 + "\r\n";
            break;
        case 208 :
            message = "208 RPL_TRACENEWTYPE <newtype>" + cmd_resp_arg + " 0 <client name>" + cmd_resp_arg2 + "\r\n";
            break;
        case 209 :
            message = "209 RPL_TRACECLASS Class <class>" + cmd_resp_arg + " <count>" + cmd_resp_arg2 + "\r\n";
            break;
        case 261 :
            message = "261 RPL_TRACELOG File <logfile>" + cmd_resp_arg + " <debug level>" + cmd_resp_arg2 + "\r\n";
            break;
        case 262 :
            message = "262 RPL_TRACEEND <server name>" + cmd_resp_arg + " <version & debug level>" + cmd_resp_arg2 + " :End of TRACE\r\n";
            break;
        case 243 :
            message = "243 RPL_STATSOLINE O <hostmask>" + cmd_resp_arg + " * <name>" + cmd_resp_arg2 + "\r\n";
            break;
        case 235 :
            message = "235 RPL_SERVLISTEND <mask>" + cmd_resp_arg + " <type>" + cmd_resp_arg2 + " :End of service listing\r\n";
            break;
        case 255 :
            message = "255 RPL_LUSERME :I have <integer>" + cmd_resp_arg + " clients and <integer>" + cmd_resp_arg2 + "servers\r\n";
            break;
        case 002 :
            message = "002 RPL_YOURHOST Your host is <servername>" + cmd_resp_arg + ", running version <ver>" + cmd_resp_arg2 + "\r\n";
            break;
        case 324 :
            message = "324 RPL_CHANNELMODEIS " + cmd_resp_arg + " " + cmd_resp_arg2 + " +o\r\n";
            break;
		default:
			std::cout << "Invalid command response code" << std::endl;
	}

	sendMessage(sender_fd, message);
}
void cmd_Resp_Handler(int sender_fd, int cmd_resp_code, std::string cmd_resp_arg, std::string cmd_resp_arg2, std::string cmd_resp_arg3)
{
	std::string message;

	switch (cmd_resp_code)
	{
		case 001 :
	        message = "001 RPL_WELCOME Welcome to the Internet Relay Network <nick>" + cmd_resp_arg + "!<user>" + cmd_resp_arg2 + "@<host>" + cmd_resp_arg3 + "\r\n";
            break;
        case 312 :
            message = "312 RPL_WHOISSERVER <nick>" + cmd_resp_arg + " <server>" + cmd_resp_arg2 + " :<server info>" + cmd_resp_arg3 + "\r\n";
            break;
        case 322 :
            message = "322 RPL_LIST <channel>" + cmd_resp_arg + " <# visible>" + cmd_resp_arg2 + " :<topic>" + cmd_resp_arg3 + "\r\n";
            break;
        case 393 :
            message = "393 RPL_USERS :<username>" + cmd_resp_arg + " <ttyline>" + cmd_resp_arg2 + " <hostname>" + cmd_resp_arg3 + "\r\n";
            break;
        case 324 :
            message = "324 RPL_CHANNELMODEIS <channel>" + cmd_resp_arg + " <mode>" + cmd_resp_arg2 + " <mode params>" + cmd_resp_arg3 + "\r\n";
            break;
        case 311 :
            message = "311 RPL_WHOISUSER " + cmd_resp_arg + " " + cmd_resp_arg2 + " @<host> * :" + cmd_resp_arg3 + "\r\n";
            break;
        // case 004 :
        //     message = "004 RPL_MYINFO <servername> <version> <available user modes><available channel modes>\r\n";
        //     break;
        // case 314 :
        //     message = "314 RPL_WHOWASUSER <nick> <user> <host> * :<real name>\r\n";
        //     break;
        // case 351 :
        //     message = "351 RPL_VERSION <version>.<debuglevel> <server> :<comments>\r\n";
        //     break;
        // case 352 :
        //     message = "352 RPL_WHOREPLY <channel> <user> <host> <server> <nick> ( H / G > [*] [ ( @ / + ) ] :<hopcount> <real name>\r\n";
        //     break;
        // case 353 :
        //     message = "353 RPL_NAMREPLY ( = / * / @ ) <channel> :[ @ / + ] <nick> *( " " [ @ / + ] <nick> ) - @ is used for secret channels, * for private channels, and = for others (public channels).\r\n";
        //     break;
        // case 364 :
        //     message = "364 RPL_LINKS <mask> <server> :<hopcount> <server info>\r\n";
        //     break;
        // case 200 :
        //     message = "200 RPL_TRACELINK Link <version & debug level> <destination> <next server> V<protocol version> <link uptime in seconds> <backstream sendq> <upstream sendq>\r\n";
        //     break;
        // case 206 :
        //     message = "206 RPL_TRACESERVER Serv <class> <int>S <int>C <server> <nick!user|*!*>@<host|server> V<protocol version>\r\n";
        //     break;
        // case 207 :
        //     message = "207 RPL_TRACESERVICE Service <class> <name> <type> <active type>\r\n";
        //     break;
        // case 11  :
        //     message = "11 RPL_STATSLINKINFO <linkname> <sendq> <sent messages> <sent Kbytes> <received messages> <received Kbytes> <time open>\r\n";
        //     break;
        // case 212 :
        //     message = "212 RPL_STATSCOMMANDS <command> <count> <byte count> <remote count>\r\n";
        //     break;
        // case 242 :
        //     message = "242 RPL_STATSUPTIME :Server Up %d days %d:%02d:%02d\r\n";
        //     break;
        // case 234 :
        //     message = "234 RPL_SERVLIST <name> <server> <mask> <type> <hopcount> <info>\r\n";
        //     break;
        // case 251 :
        //     message = "251 RPL_LUSERCLIENT :There are <integer> users and <integer>services on <integer> servers\r\n";
        //     break;
		default:
			std::cout << "Invalid command response code" << std::endl;
	}

	sendMessage(sender_fd, message);
}