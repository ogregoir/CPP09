/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:57:22 by ogregoir          #+#    #+#             */
/*   Updated: 2024/09/13 13:51:10 by marvin           ###   ########.fr       */
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
        catch
        {
            
        }
    }  
    else
        std::cerr << "Error: could not open file." << std::endl;
}   
