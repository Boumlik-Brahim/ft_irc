# ft_irc

## IRC Server:

This is an implementation of an IRC (Internet Relay Chat) server in C++.

## Getting Started:

## Prerequisites:
To compile and run this project, you will need a C++ compiler that supports C++ 98 standard, as well as the make utility.

## Building:
To build the server, simply run the make command in the root directory of the project. This will generate an executable file called ircserv.

## Running:
To start the server, run the ircserv executable file. The server will listen for incoming connections. You can specify a different port number(6660...6669) as a command-line argument, like so:
- ./ircserv 6661

This will start the server on port 6661 instead.

## Features:
The IRC server supports the following commands:

- PASS: Used to set a 'connection password'.
- NICK: Used to give user a nickname or change the existing one.
- USER: Used at the beginning of connection to specify the username, hostname and realname of a new user.
- QUIT: A client session is terminated with a quit message.
- JOIN: Used by a user to request to start listening to the specific channel.
- PART: Causes the user sending the message to be removed from the list of active members for all given channels.
- MODE: Is provided so that users may query and change the characteristics of a channel.
- TOPIC: Used to change or view the topic of a channel.
- NAMES: Used to list all nicknames that are visible to user.
- LIST: Used to list channels and their topics.
- INVITE: Used to invite a user to a channel.
- KICK: Used to request the forced removal of a user from a channel.
- PRIVMSG: Used to send private messages between users, as well as to send messages to channels.
- NOTICE: Used similarly to PRIVMSG.
- WHOIS: Used to query information about particular user.
- BOT: Used to interpret and execute commands given by users.

## Architecture:
The server uses the TCP/IP protocol to communicate with clients. It uses the poll system call to handle multiple connections simultaneously.

The server is implemented as a single-threaded event loop. Incoming connections are accepted and added to a list of connected clients. Whenever data is received from a client, the server parses the data and performs the appropriate action (e.g. join a channel, send a message, etc.).

## Contributors:

- Ishak Zail (ishakzail).

    ![Ishak Zail](https://github.com/ishakzail)
- Ibrahim Omayr (B-omayr).

    ![Ibrahim Omayr](https://github.com/B-omayr)
- Brahim Boumlik (Boumlik-Brahim).

    ![Brahim Boumlik](https://github.com/Boumlik-Brahim)