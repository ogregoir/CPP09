/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <ogregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:57:22 by ogregoir          #+#    #+#             */
/*   Updated: 2024/09/11 16:41:25 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) 
{
    BitcoinExchange  btc;
    if (argc == 2)
    {
        if(btc.stock_data(argv) != 0)
            throw std::exception();
    }
}   
