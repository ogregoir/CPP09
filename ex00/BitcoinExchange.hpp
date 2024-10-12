/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:56:01 by ogregoir          #+#    #+#             */
/*   Updated: 2024/10/12 13:40:21 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <cmath>
#include <stdio.h>

class BitcoinExchange
{
    private :
    
        std::map<std::string, double> data;
        
    public :
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &copy);
        BitcoinExchange& operator=(const BitcoinExchange &copy);
        ~BitcoinExchange();
        int    parse_input(char **argv);
        void    convert_btc(std::string date, std::string value, BitcoinExchange *acc);
        std::map<std::string, double> init_data();
};

