/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <ogregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:55:41 by ogregoir          #+#    #+#             */
/*   Updated: 2024/09/11 19:40:17 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


int search(std::string str, int start, char c)
{
    while(str[start])
    {
        if(str[start] != c) 
            break ;
        start++;
    }
       
    return start;
}

int verif_files(std::string date, std::string value)
{
    std::string year;
    std::string month;
    std::string day;
    int i = 0;
    
    (void)value;
  
    if (!date.compare("date "))
        return 0;

    year = date.substr(0, search(date, i, '-'));
    i = search(date, i, '-') + 1;
    std::cout << i << std::endl;
    month = date.substr(i, search(date, i, '-'));
    i = search(date, i, '-') + 1;
    day = date.substr(i, date.size());
    
    std::cout << "year = " << year << std::endl;
    std::cout << "month = " << month << std::endl;
    std::cout << "day = " << day << std::endl;
    
    return 0;
}

int    BitcoinExchange::stock_data(char **argv)
{
    std::string     save;
    std::ifstream   inputFile(argv[1]);
    std::string     date;
    std::string     value;
    
    if (!inputFile.is_open())
    {
        std::cerr << "Error: unable to open file" << std::endl;
        throw std::exception();
    }
    while(std::getline(inputFile, save))
    {
        int i = 0;
        while (save[i] != '|')
            i++;
        date = save.substr(0, i);
        value = save.substr(i + 1, save.size());
        std::cout << "date = " << date << std::endl;
        std::cout << "value = " << value << std::endl;
        if (verif_files(date, value) != 0)
            std::cerr << "err : " << std::endl;
    }
    return 0;
}