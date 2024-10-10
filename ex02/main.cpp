/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:08:19 by marvin            #+#    #+#             */
/*   Updated: 2024/09/16 18:08:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp"

int main(int argc, char **argv)
{
    Pmerge bob;
    if(argc > 1)
    {
        bob.sort_vec(argv);
        //bob.sort_deq(argv);
    }
    else
        std::cout << "Error: bad arguments" << std::endl;
    return 0;
}