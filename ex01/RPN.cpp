/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:02:03 by marvin            #+#    #+#             */
/*   Updated: 2024/09/13 18:02:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {

}

RPN::RPN(const RPN &copy) {
	*this = copy;
}

RPN& RPN::operator=(const RPN &copy) {
	
	if (this != &copy)
		this->nbr = copy.nbr;
	return *this;
}

RPN::~RPN() {

}

int    RPN::parse_input(std::string input)
{
	int status = 0;
	if (input.size() < 3)
	{
		std::cerr << "Error: bad arguments." << std::endl;
		return 1;
	}
	for (unsigned int i = 0; input[i]; ++i)
	{
		if (input[i] == 32 && input[i + 1] == 32 && input[i + 1])
		{
			std::cerr << "Error: bad arguments." << std::endl;
			status = 1;
		}
		if ((isdigit(input[i]) || (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')) && input[i] != 32)
		{
			if (input[i + 1] != 32 && input[i + 1])
			{
				std::cerr << "Error: number is invalid." << std::endl;
				status = 1;
			}
		}
		else if (input[i] != 32)
		{
			status = 1;
		}
			
	}
	return status;
}

void RPN::calculRPN(std::string input)
{
	unsigned int i = 0;
	long long overflow = 0;
	if(parse_input(input) == 0)
	{
		while(input[i] && i < input.size())
		{
			if (isdigit(input[i]))
			{
				nbr.push(input[i] - 48);
			}
			else if (input[i] != 32)
			{
				if(nbr.size() >= 2)
				{
					overflow = nbr.top();
					nbr.pop();
					if (input[i] == '+')
						overflow += nbr.top();
					else if (input[i] == '-')
						overflow = nbr.top() - overflow;
					else if (input[i] == '*')
						overflow *= nbr.top();
					else if (input[i] == '/')
					{
						if (overflow == 0)
						{
							std::cerr << "Error: calculation is not possible." << std::endl;
							exit(1);
						}
						overflow = nbr.top() / overflow;
					}
					nbr.pop();
					nbr.push(overflow);
					if (overflow > INT_MAX || overflow < INT_MIN)
					{
						std::cerr << "Error: displaying the result is impossible" << std::endl;
						exit(1);
					}
				}
				else
					throw std::exception();

			}
			i++;
		}
	}
	else
		return ;
	if (nbr.size() != 1)
		std::cerr << "Error: calculation is not possible" << std::endl;
	else
		std::cout << nbr.top() << std::endl;
}