/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:09:36 by marvin            #+#    #+#             */
/*   Updated: 2024/09/16 18:09:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cctype>
#include <limits>
#include <cstdlib>

class Pmerge
{
    private :
        std::vector<int>    listvec;

    public :
        Pmerge();
        Pmerge(const Pmerge &copy);
        Pmerge& operator=(const Pmerge &copy);
        ~Pmerge();
        void    sort_vec(char **argv);
        void    sort_list(std::vector< std::vector<int> > &pair);
};