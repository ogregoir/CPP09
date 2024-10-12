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
#include <deque>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cctype>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <sstream>

class Pmerge
{
    private :
        std::vector<int>    listvec;
        std::vector<double>    index;
        std::deque<double>    indeq;
        std::deque<int>    listdeq;

    public :
        Pmerge();
        Pmerge(const Pmerge &copy);
        Pmerge& operator=(const Pmerge &copy);
        ~Pmerge();

        void    sort_vec(char **argv);
        void    sort_deq(char **argv);

        void    create_index_deq(std::deque<int> pend, std::deque<double> jacob);
        void    create_index_vec(std::vector<int> pend, std::vector<double> jacob);

        std::vector<int>    make_list_vec(std::vector< std::vector<int> > &pair);
        std::deque<int>     make_list_deq(std::deque< std::deque<int> > &pair);
};