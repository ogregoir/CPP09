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
/*
void print_stack()
{
	while (!stack.empty())
	{
		std::cout << stack.top() << " ";
		stack.pop();
	}
}*/

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
			std::cout << input[i] << std::endl;
			if (input[i + 1] != 32 && input[i + 1])
				status = 1;
		}
		else if (input[i] != 32)
			status = 1;
	}
	return status;
}

void RPN::calculRPN(std::string input)
{
	//std::cout << "input = " << input << std::endl;
	unsigned int i = 0;
	int res;
	if(parse_input(input) == 0)
	{
		//std::cout << "PASS" << std::endl;
		while(input[i] && i < input.size())
		{
			res = 0;
			std::cout << "PASS" << std::endl;
			if (isdigit(input[i]))
			{
				nbr.push(input[i] - 48);
			}
			else if (input[i] != 32)
			{
				while (!nbr.empty())
				{
					std::cout << "stack = " << nbr.top() << " ";
					nbr.pop();
				}
				/*res = stack.top();
				std::cout << "res = " << res << std::endl;
				stack.pop();
				if (input[i] == '+')
				{
					while (stack.top())
					{
						res += stack.top();
						stack.pop();
					}
				}*/
			}
			i++;
		}
	}
	else
	{
		std::cerr << "Error: bad arguments." << std::endl;
		return ;
	}
		
}