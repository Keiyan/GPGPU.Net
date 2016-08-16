// MinCutProblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MinCutProblem.h"

using namespace std;

int Contract(std::vector<int>* data, size_t amountOfNodes, size_t width)
{
    static random_device dev;
    static default_random_engine e{ dev() };
    static uniform_int_distribution<int> d{ 0, (int)amountOfNodes - 1 };

    int* redirections = new int[amountOfNodes];
    for (size_t i = 0; i < amountOfNodes; i++)
    {
        redirections[i] = i;
    }

    int* validDestinations = new int[amountOfNodes];

    for (size_t loop = 0; loop < amountOfNodes - 2; loop++)
    {
        unsigned int source, destination;

        do
        {
            source = d(e);
        } while (redirections[source] != source);

        int rank = 0;
        for (size_t i = 0; i < amountOfNodes; i++)
        {
            if (redirections[i] == source)
            {
                for (size_t j = 0; j < width; j++)
                {
                    auto local = data[i][j];
                    if (local == -1) break;
                    if (redirections[local] != source)
                    {
                        validDestinations[rank] = redirections[local];
                        rank++;
                    }
                }
            }
        }

        uniform_int_distribution<int> d2{ 0, rank - 1 };

        destination = validDestinations[d2(e)];

        for (size_t i = 0; i < amountOfNodes; i++)
        {
            if (redirections[i] == source)
            {
                redirections[i] = destination;
            }
        }
    }

    int result = 0;
    int nodeValue = redirections[0];
    for (size_t i = 0; i < amountOfNodes; i++)
    {
        if (redirections[i] == nodeValue)
            for (size_t j = 0; j < width; j++)
            {
                auto local = data[i][j];
                auto redirected = redirections[local];
                if (data[i][j] != -1 && redirections[data[i][j]] != nodeValue) ++result;
            }
    }
    return result;
}

int Contract(std::vector<int>* toContract, size_t amountOfNodes)
{
    int a = 0, b = 0, count = amountOfNodes;
    while (count > 2)
    {
        FindEdge(toContract, a, b, amountOfNodes);
        Merge(toContract, a, b, amountOfNodes);
        --count;
    }

    return toContract[a].size();
}

void Merge(std::vector<int>* data, int a, int b, size_t amountOfNodes)
{
    data[a].erase(std::remove(data[a].begin(), data[a].end(), b), data[a].end());
    for (auto i = data[b].begin(); i < data[b].end(); i++)
    {
        if (*i != a)
        {
            data[a].push_back(*i);
        }
    }
    data[b].clear();

    for (size_t i = 0; i < amountOfNodes; i++)
    {
        int amount = 0;
        for (auto iter = data[i].begin(); iter != data[i].end(); iter++)
        {
            if (*iter == b)
            {
                *iter = a;
            }
        }
    }
}

void FindEdge(std::vector<int>* data, int & a, int & b, size_t amountOfNodes)
{
    static random_device dev;
    static default_random_engine e{ dev() };
    static uniform_int_distribution<int> d{ 0, (int)amountOfNodes - 1 };
    do
    {
        a = d(e);
    } while (data[a].size() == 0);

    uniform_int_distribution<int> d2{ 0, (int) data[a].size() - 1 };

    int index = d2(e);
    auto value = data[a].begin();
    while (index-- > 0) value++;
    b = *value;
}