/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:57:22 by ogregoir          #+#    #+#             */
/*   Updated: 2024/09/11 22:50:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) 
{
    BitcoinExchange  btc;
    if (argc == 2)
    {
        if(btc.parse_input(argv) != 0)
            std::cerr << "PASS" << std::endl;
    }
}   
