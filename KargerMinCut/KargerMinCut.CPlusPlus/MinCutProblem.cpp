// MinCutProblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MinCutProblem.h"

using namespace std;

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
    static uniform_int_distribution<int> d{ 0, (int)amountOfNodes };
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