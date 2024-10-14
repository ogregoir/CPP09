/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:55:41 by ogregoir          #+#    #+#             */
/*   Updated: 2024/10/14 16:23:14 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iomanip>  

void ft_error(std::string error)
{
	std::cerr << error << std::endl;
	exit(1);
}

int verif_files(std::string date, std::string value)
{
	std::string year;
	std::string month;
	std::string day;
	
	for (size_t i = 0; i < date.size(); i++)
	{
		if (!isdigit(date[i]) && date[i] != '-')
		{
			std::cerr << "Error: format is invalid" << std::endl;
			return 1;
		}	
	}
	if (std::count(date.begin(), date.end(), '-') != 2)
	{
		std::cerr << "Error: format is invalid" << std::endl;
		return 1;
	}

	int i = date.find('-');
	year = date.substr(0, i);
	month = date.substr(i + 1, (date.find('-', i + 1) - (i + 1)));
	i = date.find('-', i + 1) + 1;
	day = date.substr(i, date.find('-', i) - 1);
	
	if (year.size() != 4 || month.size() != 2 || day.size() != 2)
	{
		std::cerr << "Error: date : is incorrect" << std::endl;
		return 1;
	}
	int y = atoi(year.c_str()); 
	int m = atoi(month.c_str());
	int d = atoi(day.c_str());
	
	if (y < 2009 || y > 2024 || m <= 0 || m > 12 || d <= 0 || d > 31)
	{
		std::cerr << "Error: bad input => " << date << std::endl;
		return 1;
	}
	if (m % 2 == 0 && d > 30)
	{
		std::cerr << "Error: bad input => " << date << std::endl;
		return 1;
	}
	if(m == 2)
	{
		if (y % 4 == 0)
		{
			if (((y % 100 != 0) || (y % 100 == 0 && y % 400 == 0)) && d > 29)
			{
				std::cerr << "Error: bad input => " << date << std::endl;
				return 1;
			}
		}
		else if (d > 28)
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			return 1;
		}
	}
	for (size_t i = 0; i < value.size(); i++)
	{
		if (!isdigit(value[i]) && value[i] != '.' && value[i] != 32 && value[i] != '\r')
		{
			if (value[i] == '-')
				std::cerr << "Error: not a positive number." << std::endl;
			else
				std::cerr << "Error: format is invalid" << std::endl;
			return 1;
		}	
	}
	if (value.find('.') == 0)
	{
		if (std::count(value.begin(), value.end(), '.') != 1)
		{
			std::cerr << "Error: format is invalid"<< std::endl;
			return 1;
		}
	}
	double val = atof(value.c_str());
	if (val < 0)
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
	std::string 	val;
	double          value = -1;

	std::map<std::string, double> map;
	data_og.open("data.csv",  std::ios::in);
	if (!data_og.is_open())
		ft_error("Error: \"data.csv\" : Unable to open");
	std::getline(data_og, save);
	if (save != "date,exchange_rate")
		ft_error("Error: \"data.csv\" : format incorrect");
	while(std::getline(data_og, save))
	{
		if (save.empty())
			ft_error("Error: \"data.csv\" : empty line");
		date = save.substr(0, save.find(','));
		val = save.substr(save.find(',') + 1, save.size());
		if (date.empty() || val.empty())
			ft_error("Error: \"data.csv\" : missing date or value");
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
	std::cout << date << " => " << val << " = " << op << std::endl;
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
		ft_error("Error: \"input\" : miss \"date | value\" in inputfile.");
	while(std::getline(inputFile, save))
	{
		if (std::count(save.begin(), save.end(), '|') != 1 || (!save.find('|') - 1 == ' ' && !save.find('|') + 1 != ' ') || std::count(save.begin(), save.end(), ' ') != 2)
			std::cerr << "Error: bad input => " << save.substr(0) << std::endl;
		else
		{
			date = save.substr(0, save.find('|') - 1);
			value = save.substr(save.find('|') + 2, save.size());
			if(date.empty() || value.empty())
				std::cerr << "Error: format is invalid" << std::endl;
			else if (verif_files(date, value) != 0)
				std::exception();
			else
				convert_btc(date, value, acc);

		}
	}
	return 0;
}