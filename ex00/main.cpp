/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <ogregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:57:22 by ogregoir          #+#    #+#             */
/*   Updated: 2024/09/06 16:31:09 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) 
{
    if (argc == 2)
    {
        std::ifstream inputFile(argv[1]);
        if (!inputFile.is_open())
        {
            std::cerr << "Error: unable to open file" << std::endl;
            return 1;
        }
    }
}   
