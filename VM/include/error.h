/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 12:25:41 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/07 12:25:43 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*
******************************************************************************
***************************** Virtual Machine ********************************
******************************************************************************
*/

# define ERR_101 "\e[91mError: \e[93mmemory was not allocated\e[0m\n"
# define ERR_102 "\e[91mError: \e[93mexecutable doesn't exist\e[0m\n"
# define ERR_103 "\e[91mError: \e[93msomething after executable\e[0m\n"
# define ERR_104 "\e[91mError: \e[93mthere isn't NULL after comment\e[0m\n"
# define ERR_105 "\e[91mError: \e[93mthere isn't comment\e[0m\n"
# define ERR_106 "\e[91mError: \e[93mchampion's size is too big\e[0m\n"
# define ERR_107 "\e[91mError: \e[93mthere isn't NULL after name\e[0m\n"
# define ERR_108 "\e[91mError: \e[93mthere isn't name\e[0m\n"
# define ERR_109 "\e[91mError: \e[93mthere isn't magic header\e[0m\n"
# define ERR_110 "\e[91mError: \e[93mmagic header isn't right\e[0m\n"
# define ERR_111 "\e[91mError: \e[93mtoo many players\e[0m\n"
# define ERR_112 "\e[91mError: \e[93mcan't open file\e[0m\n"
# define ERR_113 "\e[91mError: \e[93mrepeats number of bot\e[0m\n"
# define ERR_114 "\e[91mError: \e[93mcan be only one of 1-4 numbers\e[0m\n"
# define ERR_115 "\e[91mError: \e[93mchampion's size doesn't exist\e[0m\n"

/*
******************************************************************************
**************************** Network Game Mode *******************************
******************************************************************************
*/

# define ERR_301 "\e[91mError: \e[93mfailed connect to the server\e[0m\n"
# define ERR_302 "\e[91mError: \e[93mthere isn't player\e[0m\n"
# define ERR_303 "\e[91mError: \e[93mfailed accept client\e[0m\n"
# define ERR_304 "\e[91mError: \e[93mthere aren't players for game\e[0m\n"
# define ERR_305 "\e[91mError: \e[93mserver socket doesn't active\e[0m\n"
# define ERR_306 "\e[91mError: \e[93mfailed create socket\e[0m\n"
# define ERR_307 "\e[91mError: \e[93minvalid IP\e[0m\n"
# define ERR_308 "\e[91mError: \e[93mthis IP address is busy\e[0m\n"

#endif
