/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <ogregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:55:41 by ogregoir          #+#    #+#             */
/*   Updated: 2024/10/09 15:49:02 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iomanip>  


int verif_files(std::string date, std::string value)
{
	std::string year;
	std::string month;
	std::string day;
	
	date.erase(std::remove(date.begin(), date.end(), ' '), date.end());
	
	int i = date.find('-');
	year = date.substr(0, i);
	month = date.substr(i + 1, (date.find('-', i + 1) - (i + 1)));
	i = date.find('-', i + 1) + 1;
	day = date.substr(i, date.find('-', i) - 1);

	if (year.size() != 4 || month.size() != 2 || day.size() != 2)
	{
		std::cerr << "Error : date : is incorrect" << std::endl;
		return 1;
	}
	
	int y = atoi(year.c_str()); 
	int m = atoi(month.c_str());
	int d = atoi(day.c_str());
	
	if (y < 0 || m < 0 || m > 12 || d < 0 || d > 31)
	{
		std::cerr << "Error: bad input => " << date << std::endl;
		return 1;
	}

	value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
	double val = atof(value.c_str());
	if (val < 0 || value == "-0")
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return 1;
	}
	if (val > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return 1;
	}
	return 0;
}

std::map<std::string, double> BitcoinExchange::init_data()
{
	std::string     save;
	std::fstream    data_og;
	std::string     date;
	double          value;

	std::map<std::string, double> map;
	data_og.open("data.csv",  std::ios::in);

	while(std::getline(data_og, save))
	{
		date = save.substr(0, save.find(','));
		value = atof(save.substr(save.find(','), save.size()).c_str() + 1);
		map.insert(std::make_pair(date, value));
	}
	data_og.close();
	return map;
}

BitcoinExchange::BitcoinExchange()
{
	data = init_data();
}

BitcoinExchange::~BitcoinExchange(){
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	this->data.insert(copy.data.begin(), copy.data.end());
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	this->data.insert(copy.data.begin(), copy.data.end());
	return *this;
}

void    BitcoinExchange::convert_btc(std::string date, std::string value, BitcoinExchange *acc)
{
	double  val = atof(value.c_str());
	double  op = 0;
	
	date.erase(std::remove(date.begin(), date.end(), ' '), date.end());
	std::map<std::string, double>::iterator it = acc->data.find(date);
	if (it == acc->data.end())
	{
		it = acc->data.lower_bound(date);
		if (it == acc->data.begin())
		{
			std::cerr << "Error: Date is earlier than the earliest available record." << std::endl;
			return;
		}
		else
			--it;
	}
	op = it->second * val;
	value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
	std::cout << date << " => " << value << " = " << op << std::endl;
}

int    BitcoinExchange::parse_input(char **argv)
{
	std::string     save;
	std::ifstream   inputFile(argv[1]);
	std::string     date;
	std::string     value;
	BitcoinExchange *acc(this);

	if (!inputFile.is_open())
	{
		std::cerr << "Error: unable to open file" << std::endl;
		return 1;
	}
	std::getline(inputFile, save);
	if (save.find("date ") && save.find("value"))
	{
		std::cerr << "Error: miss \"date | value\" in inputfile." << std::endl;
		return 0;
	}
	while(std::getline(inputFile, save))
	{
		date = save.substr(0, save.find('|'));
		value = save.substr(save.find('|') + 1, save.size());
		if (verif_files(date, value) != 0)
			std::exception();
		else 
			convert_btc(date, value, acc);
	}
	return 0;
}