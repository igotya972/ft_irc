/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:04:06 by afont             #+#    #+#             */
/*   Updated: 2025/01/30 16:20:57 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <sstream>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <algorithm>
#include <iostream>
#include <csignal>
#include <poll.h>
// #include <sys/socket.h>
#include <vector>
#include <cstdlib>
#include <map>

#include "client.hpp"
#include "server.hpp"
#include "cmd.hpp"
#include "utils.hpp"
#include "channel.hpp"