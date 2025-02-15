/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:59:58 by afont             #+#    #+#             */
/*   Updated: 2025/02/07 14:36:35 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "all.hpp"

int							nickExists(std::string nickname, Server *server);
int							parserCmd(Client *cli, std::string buf);
int							initCliValue(Client *cli, Server *serv);
void						parse_argv(Server *server, int ac, char **av);
void						tryWelcome(Client *cli);
void						printvector(std::vector<std::string> vec);
std::vector<std::string>	split(const std::string& str, char delimiter);