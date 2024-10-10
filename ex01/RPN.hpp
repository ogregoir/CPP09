/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:35:32 by marvin            #+#    #+#             */
/*   Updated: 2024/09/13 13:35:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <limits.h>
#include <stack>
#include <cctype>
#include <cstdlib>
#include <string>
#include <cfloat>

class RPN
{
    private :
        std::stack<double> nbr;
    public :

        RPN();
        RPN(const RPN &copy);
        RPN& operator=(const RPN &copy);
        ~RPN();
        void calculRPN(std::string input);
        void parse_input(std::string input);
};