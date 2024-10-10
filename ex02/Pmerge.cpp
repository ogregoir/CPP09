/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <ogregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:58:04 by ogregoir          #+#    #+#             */
/*   Updated: 2024/10/07 18:58:04 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp"

Pmerge::Pmerge() {

}

Pmerge::Pmerge(const Pmerge &copy) {
    if(this != &copy)
    {
        this->listvec = copy.listvec;
        this->listdeq = copy.listdeq;
    }
}

Pmerge::~Pmerge() {

}

Pmerge& Pmerge::operator=(const Pmerge &copy) {
    if(this != &copy)
    {
        this->listvec = copy.listvec;
        this->listdeq = copy.listdeq;
    }
    return *this;
}

//---------------- VECTOR ------------------

std::vector<int>    parse_vec(std::string list, std::vector<int> temp)
{
    std::stringstream ss(list);
    int number;

    if (ss >> number)
    {
        if (number < 0)
        {
            std::cerr << "Error: number is not positive" << std::endl;
            exit(1);
        }
        temp.push_back(number);
    } 
    else
    {
        std::cerr << "Error: list not numeric" << std::endl;
        exit(1);
    }
    return temp;
}

void    sort_list_vec(std::vector< std::vector<int> > &pair)
{
    for(size_t i = 0; i < pair.size() - 1; i++)
    {
        if (pair[i + 1].size() > 1 && pair[i][0] > pair[i + 1][0])
            std::swap(pair[i], pair[i + 1]);
    }
    for (size_t i = 0; i < pair.size() - 1; i++)
    {
        if (pair[i + 1].size() > 1 && pair[i][0] > pair[i + 1][0])
            sort_list_vec(pair);
    }
}

void    Pmerge::create_index_vec(std::vector<int> pend, std::vector<double> jacob)
{
    size_t j = 2;
    size_t ind;
    for (size_t i = 0; i < pend.size(); i++)
    {
        ind = jacob[j];
        if (ind > 1)
            this->index.push_back(ind);
        ind--;
        while (jacob[j - 1] && ind != jacob[j - 1] && ind > 1)
        {
            this->index.push_back(ind);
            ind--;
        }
        j++;

    }
}

std::vector<int>    Pmerge::make_list_vec(std::vector< std::vector<int> > &pair)
{
    std::vector<int> pend;
    size_t size = pair.size();
    std::vector<double> jacob;

    for(size_t i = 0; i < pair.size(); i++)
    {
        this->listvec.push_back(pair[i][0]);
        pend.push_back(pair[i][1]);
    }
    if (size > 0 && pair[0][0] > pair[0][1]) 
        listvec.insert(listvec.begin(), pair[0][1]);
    jacob.push_back(0);
    jacob.push_back(1);
    for (size_t i = 2; i < pend.size() + 4; i++)
        jacob.push_back(jacob[i - 1] + (2 * jacob[i - 2]));
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
        temp = parse_vec(argv[i], temp);

    if ((temp.size() % 2) == 0)
        size = temp.size() / 2;
    else
    {
        size = (temp.size() / 2);
        struggler = temp[temp.size() - 1];
    }
    std::cout << "Before: ";
    for (size_t i = 0; i < temp.size(); i++)
    {
        if (i == 5)
            break;
        std::cout << temp[i] << " ";
    }
    if (temp.size() > 5)
        std::cout << "[...]";
    std::cout << std::endl;
    std::clock_t start = std::clock();
    if (temp.size() >= 2)
    {
        pair.resize(size);
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
        sort_list_vec(pair);
        pend = make_list_vec(pair);
        std::vector<int>::iterator it;
        size_t ind = 0;
        for (size_t i = 0; i < this->index.size(); i++)
        {
            ind = this->index[i];
            if ((ind - 1) < pend.size())
            {
                it = std::lower_bound(listvec.begin(), listvec.end(), pend[ind - 1]);
                listvec.insert(it, pend[ind - 1]);
            }
        }
        if (struggler != -1)
        {
            it = std::lower_bound(listvec.begin(), listvec.end(), struggler);
            listvec.insert(it, struggler);
        }   
    }
    else
        listvec.push_back(temp[0]);
    std::cout << "After : ";
    for (size_t i = 0; i < listvec.size(); i++)
    {
        if (i == 5)
            break;
        std::cout << listvec[i] << " ";
    }
    if (listvec.size() > 5)
        std::cout << "[...]";
    std::cout << std::endl;
    std::clock_t end = std::clock();
    std::cout << "Time to process a range of " << temp.size() << " elements with std::vector : " << (static_cast<double>(end - start) * 1000) / CLOCKS_PER_SEC << " us" << std::endl;
}
