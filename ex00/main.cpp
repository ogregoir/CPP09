/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <ogregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:57:22 by ogregoir          #+#    #+#             */
/*   Updated: 2024/09/16 15:11:54 by ogregoir         ###   ########.fr       */
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
			std::cerr << e.what() << '\n';
		}
    }  
    else
        std::cerr << "Error: could not open file." << std::endl;
    return 0;
}   
