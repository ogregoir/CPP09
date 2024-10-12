/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <ogregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:57:22 by ogregoir          #+#    #+#             */
/*   Updated: 2024/10/10 15:00:30 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) 
{
    BitcoinExchange  btc;
    if (argc == 2)
    {
        try 
        {
            btc.parse_input(argv);
        }
		catch(const std::exception& e)
		{
			std::cerr << "Error: bad arguments" << '\n';
		}
    }  
    else
        std::cerr << "Error: could not open file." << std::endl;
    return 0;
}   
