/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:09:07 by marvin            #+#    #+#             */
/*   Updated: 2024/09/16 18:09:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp"

Pmerge::Pmerge() {

}

Pmerge::Pmerge(const Pmerge &copy) {
  (void)copy;  
}

Pmerge::~Pmerge() {

}

Pmerge& Pmerge::operator=(const Pmerge &copy) {
    if(this != &copy)
    {
        this->listvec = copy.listvec;
    }
    return *this;
}

std::vector<int>    parse(std::string list, std::vector<int> temp)
{
    for (size_t i = 0; i < list.size(); i++)
    {
        if (!std::isdigit(list[i]) )
        {
            std::cerr << "Error: list not numeric" << std::endl;
            return temp;
        }
    }
    int number = atoi(list.c_str());
    if (number < 0 || number > 2147483647)
    {
        std::cerr << "Error: number is not enter" << std::endl;
        return temp;
    }
    temp.push_back(number);
    return temp;
}

void    sort_list(std::vector< std::vector<int> > &pair)
{
    for(size_t i = 0; i < pair.size() - 1; i++)
    {
        if (pair[i + 1].size() > 1 && pair[i][0] > pair[i + 1][0])
            std::swap(pair[i], pair[i + 1]);
    }
    for (size_t i = 0; i < pair.size() - 1; i++)
    {
        if (pair[i + 1].size() > 1 && pair[i][0] > pair[i + 1][0])
            sort_list(pair);
    }
}

void    Pmerge::create_index(std::vector<int> pend, std::vector<double> jacob)
{ 
    double save = 0;
    size_t j = 3;
    size_t  pend_size = pend.size() + 1;

    while(index.size() < pend_size && j < jacob.size())
    {
        save = jacob[j];
        if (std::find(index.begin(), index.end(), save) == index.end())
            index.push_back(save);
        else
            save--;
        while(save > 1 && index.size() < pend_size)
        {
            if (std::find(index.begin(), index.end(), save) == index.end())
                index.push_back(save);
            save--;
        }
        j++;
    }

}

std::vector<int>    Pmerge::make_list(std::vector< std::vector<int> > &pair)
{
    std::vector<int> pend;
    std::vector<double> jacob;

    for(size_t i = 0; i < pair.size(); i++)
        this->listvec.push_back(pair[i][0]);
    for (size_t i = 0; i < pair.size(); i++)
        pend.push_back(pair[i][1]);
    if (pair[0][0] > pair[0][1]) 
        listvec.insert(listvec.begin(), pair[0][1]);
    jacob.push_back(0);
    jacob.push_back(1);
    for (size_t i = 2; i < pend.size() + 4; i++)
        jacob.push_back(jacob[i - 1] + (2 * jacob[i - 2]));
    this->index.push_back(jacob[3]);
    create_index(pend, jacob);
    return pend;
}

void    Pmerge::sort_vec(char **argv)
{
    std::vector< std::vector<int> > pair;
    std::vector<int>    temp;
    size_t index = 0;
    size_t  size = 0;
    std::vector<int> pend;

    for(int i = 1; argv[i]; i++)
        temp = parse(argv[i], temp);

    if ((temp.size() % 2) == 0)
        size = temp.size() / 2;
    else
        size = (temp.size() / 2) + 1;
    pair.resize(size);
    std::cout << "Before: ";
    for (size_t i = 0; i < 5; i++)
        std::cout << temp[i] << " ";
    if (temp.size() > 5)
        std::cout << "[...]" << std::endl;
    for(size_t i = 0; i < size; i++)
    {
        if (index + 1 < temp.size())
        {
            if (temp[index] > temp[index + 1])
            {
                pair[i].push_back(temp[index]);
                pair[i].push_back(temp[index + 1]);
            }
            else
            {
                pair[i].push_back(temp[index + 1]);
                pair[i].push_back(temp[index]);
            }
        }
        else
            pair[i].push_back(temp[index]);
        index += 2;
    }
    sort_list(pair);
    pend = make_list(pair);
    /*for (size_t i = 0; i < size; i++)
       listvec.push_back(pair[i][0]);
    std::sort(listvec.begin(), listvec.end());
    if (pair[0][0] < pair[1][0])
       listvec.insert(listvec.begin(), pair[1][0]);
    for (size_t i = 0; i < pair.size(); i++) {
    std::cout << "pair n°" << i << " = ";
    for (size_t j = 0; j < pair[i].size(); j++) {
        std::cout << pair[i][j] << " ";
    }
    std::cout << std::endl; 
    }*/
   /* for (size_t i = 0; i < listvec.size(); i++)
        std::cout << "listvec = " << listvec[i] << std::endl;
    for (size_t i = 0; i < pend.size(); i++)
        std::cout << "pend = " << pend[i] << std::endl;*/
}
