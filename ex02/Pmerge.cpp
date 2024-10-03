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

std::deque<int>    parse_deq(std::string list, std::deque<int> temp)
{
    for (size_t i = 0; i < list.size(); i++)
    {
        if (!std::isdigit(list[i]) )
        {
            std::cerr << "Error: list not numeric" << std::endl;
            exit(1);
        }
    }
    int number = atoi(list.c_str());
    if (number < 0 || number > 2147483647)
    {
        std::cerr << "Error: number is not enter" << std::endl;
        exit(1);
    }
    temp.push_back(number);
    return temp;
}

void    sort_list_deq(std::deque< std::deque<int> > &pair)
{
    for(size_t i = 0; i < pair.size() - 1; i++)
    {
        if (pair[i + 1].size() > 1 && pair[i][0] > pair[i + 1][0])
            std::swap(pair[i], pair[i + 1]);
    }
    for (size_t i = 0; i < pair.size() - 1; i++)
    {
        if (pair[i + 1].size() > 1 && pair[i][0] > pair[i + 1][0])
            sort_list_deq(pair);
    }
}

void    Pmerge::create_index_deq(std::deque<int> pend, std::deque<double> jacob)
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

std::deque<int>    Pmerge::make_list_deq(std::deque< std::deque<int> > &pair)
{
    std::deque<int> pend;
    std::deque<double> jacob;

    for(size_t i = 0; i < pair.size(); i++)
        this->listdeq.push_back(pair[i][0]);
    for (size_t i = 0; i < pair.size(); i++)
        pend.push_back(pair[i][1]);
    if (pair[0][0] > pair[0][1]) 
        listdeq.insert(listdeq.begin(), pair[0][1]);
    jacob.push_back(0);
    jacob.push_back(1);
    for (size_t i = 2; i < pend.size() + 4; i++)
        jacob.push_back(jacob[i - 1] + (2 * jacob[i - 2]));
    this->index.push_back(jacob[3]);
    create_index_deq(pend, jacob);
    return pend;
}

void    Pmerge::sort_deq(char **argv)
{
    std::deque< std::deque<int> > pair;
    std::deque<int>    temp;
    size_t index = 0;
    size_t  size = 0;
    std::deque<int> pend;
    int struggler = -1;

    for(int i = 1; argv[i]; i++)
        temp = parse_deq(argv[i], temp);
    std::cout << temp.size() << std::endl;
    if ((temp.size() % 2) == 0)
        size = temp.size() / 2;
    else
    {
        size = (temp.size() / 2);
        struggler = temp[temp.size() - 1];
    }
    std::cout << "struggler =  " << struggler << std::endl;  
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
    sort_list_deq(pair);
    pend = make_list_deq(pair);
    std::vector<int>::iterator it;
    size_t ind = 0;
    size_t ind_max = 0;
    ind_max = this->index[0];
    for (size_t i = 0; i < pend.size() - 1; i++)
    {
        ind = this->index[i];
        if (ind < pend.size())
        {
            if (ind_max < ind)
                ind_max = ind;
        }
        else
        {
            ind_max++;
            ind = ind_max; 
        }
        it = std::lower_bound(listvec.begin(), listvec.end(), pend[ind - 1]);
        listvec.insert(it, pend[ind - 1]);
    }
    if (struggler != -1)
    {
        it = std::lower_bound(listvec.begin(), listvec.end(), struggler);
        listvec.insert(it, struggler);
    }
    std::cout << "After : ";
    for (size_t i = 0; i < 5; i++)
        std::cout << listvec[i] << " ";
    if (listvec.size() > 5)
        std::cout << " [...]";
    std::cout << std::endl;
}


std::vector<int>    parse(std::string list, std::vector<int> temp)
{
    for (size_t i = 0; i < list.size(); i++)
    {
        if (!std::isdigit(list[i]) )
        {
            std::cerr << "Error: list not numeric" << std::endl;
            exit(1);
        }
    }
    int number = atoi(list.c_str());
    if (number < 0 || number > 2147483647)
    {
        std::cerr << "Error: number is not enter" << std::endl;
        exit(1);
    }
    temp.push_back(number);
    return temp;
}

void    sort_list_veq(std::vector< std::vector<int> > &pair)
{
    for(size_t i = 0; i < pair.size() - 1; i++)
    {
        if (pair[i + 1].size() > 1 && pair[i][0] > pair[i + 1][0])
            std::swap(pair[i], pair[i + 1]);
    }
    for (size_t i = 0; i < pair.size() - 1; i++)
    {
        if (pair[i + 1].size() > 1 && pair[i][0] > pair[i + 1][0])
            sort_list_veq(pair);
    }
}

void    Pmerge::create_index_vec(std::vector<int> pend, std::vector<double> jacob)
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

std::vector<int>    Pmerge::make_list_vec(std::vector< std::vector<int> > &pair)
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
    create_index_vec(pend, jacob);
    return pend;
}

void    Pmerge::sort_vec(char **argv)
{
    std::vector< std::vector<int> > pair;
    std::vector<int>    temp;
    size_t index = 0;
    size_t  size = 0;
    std::vector<int> pend;
    int struggler = -1;

    for(int i = 1; argv[i]; i++)
        temp = parse(argv[i], temp);
    std::cout << temp.size() << std::endl;
    if ((temp.size() % 2) == 0)
        size = temp.size() / 2;
    else
    {
        size = (temp.size() / 2);
        struggler = temp[temp.size() - 1];
    }
    std::cout << "struggler =  " << struggler << std::endl;  
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
    sort_list_veq(pair);
    pend = make_list_vec(pair);
    std::vector<int>::iterator it;
    size_t ind = 0;
    size_t ind_max = 0;
    ind_max = this->index[0];
    for (size_t i = 0; i < pend.size() - 1; i++)
    {
        ind = this->index[i];
        if (ind < pend.size())
        {
            if (ind_max < ind)
                ind_max = ind;
        }
        else
        {
            ind_max++;
            ind = ind_max; 
        }
        it = std::lower_bound(listvec.begin(), listvec.end(), pend[ind - 1]);
        listvec.insert(it, pend[ind - 1]);
    }
    if (struggler != -1)
    {
        it = std::lower_bound(listvec.begin(), listvec.end(), struggler);
        listvec.insert(it, struggler);
    }
    std::cout << "After : ";
    for (size_t i = 0; i < 5; i++)
        std::cout << listvec[i] << " ";
    if (listvec.size() > 5)
        std::cout << " [...]";
    std::cout << std::endl;
}
