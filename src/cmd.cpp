/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:05:17 by dravaono          #+#    #+#             */
/*   Updated: 2025/02/05 13:23:18 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.hpp"

void    checkCmd(Client *cli, std::vector<std::string> cmd, Server *server)
{
	size_t size;

	size = cmd.size(); 	                    // protection segfault
	if (size >= 1)
	{
		if (cmd[0] == "PASS")
		{
			verifyPassword(cmd, server, cli);
		}
	}
	if (size >= 2)
	{
		if ((cmd[0] == "NICK" || cmd[0] == "USER") && !cli->_isRegistered)
		{
			cli->sendMessage(":server 464 " + cli->_nickname + " :Password required\r\n");
			close(cli->_fd);
			server->removeClient(cli->_fd);
		}
		else if (cmd[0] == "NICK")
		{
			if (nickExists(cmd[1], server))
			{
				cli->sendMessage(":server 433 " + cmd[1] + " :Nickname already taken\r\n");
			}
			else if (cli->_nickname != "Unknown")
			{
				//changement de nickname
				// sendNickChangeNotification(cli, cmd[1], server);
				cli->sendMessage(":" + cli->_nickname + "!" + cli->_username + "@" + cli->_ip + " NICK :" + cmd[1] + "\r\n");
				cli->_nickname = cmd[1];
			}
			else
			{
				cli->_nickname = cmd[1];
			}
		}
		else if (cmd[0] == "USER")
		{
			cli->_username = cmd[1];
		}
		else if (cmd[0] == "QUIT" && cmd[1] == ":Leaving")
		{
			std::cout << "Client " << cli->_nickname << " disconnected" << std::endl;
			close(cli->_fd);
			server->removeClient(cli->_fd);
		}
		else if (cmd[0] == "JOIN" && cmd[1][0] != '#')
		{
			std::string mess = cmd[1] + " :No such channel" + "\r\n";
			send(cli->_fd, mess.c_str(), mess.length(), 0);
		}
		else if (cmd[0] == "JOIN" && cmd[1][0] == '#')
		{
			cmdJoin(cli, cmd[1], server);
		}
	}
}

void cmdJoin(Client *cli, std::string channel, Server *serv)
{
	// static Channel channelManager;
	std::string joinMessage = ":" + cli->_nickname + "!" + cli->_username + "@" + cli->_ip + " JOIN " + channel + "\r\n";

	if (serv->_channelManager.channelExists(channel))
		cli->sendMessageToChannel(joinMessage, serv->_channelManager.getChannelClients(channel));

	serv->_channelManager.createChannel(channel, *cli);

	cli->sendMessage(joinMessage);
	cli->sendMessage(":server 332 " + cli->_nickname + " " + channel + " :\r\n");
	cli->sendMessage(":server 353 " + cli->_nickname + " = " + channel + " :" + serv->_channelManager.getChannelUsers(channel) + "\r\n");
	cli->sendMessage(":server 366 " + cli->_nickname + " " + channel + " :End of NAMES list\r\n");
}

void	verifyPassword(std::vector<std::string> cmd, Server *serv, Client *cli)
{
	if (cli->_isRegistered)
		cli->sendMessage(":server 462 " + cli->_nickname + " :You may not reregister\r\n");
	else if (cmd.size() != 2)
	{
		cli->sendMessage(":server 461 " + cli->_nickname + " PASS :Not enough parameters\r\n");
		close(cli->_fd);
		serv->removeClient(cli->_fd);
	}
	else if (cmd[1] != serv->_password)
	{
		cli->sendMessage(":server 464 " + cli->_nickname + " :Password incorrect\r\n");
		close(cli->_fd);
		serv->removeClient(cli->_fd);
	}
	else
	{
		cli->_isRegistered = true;
	}
}
