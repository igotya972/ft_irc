/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:21:51 by afont             #+#    #+#             */
/*   Updated: 2025/01/10 11:21:51 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "all.hpp"

class	Server
{
	private:
	public:
		int							_port;
		int							_socketFd;
		static bool					_signal;
		std::string					_password;
		std::vector<struct pollfd>	_pfds;
		std::vector<Client>			_clients;
		Channel						_channelManager;
		
		Server();
		~Server();
		int			getClientIndex(int fd);
		void		initServer();
		void		initSocket();
		void		closeFd();
		void		newClient();
		void		processData(int fd);
		void		removeClient(int fd);
		static void	signalHandler(int signum);
};