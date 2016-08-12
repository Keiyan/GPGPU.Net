// MinCutProblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MinCutProblem.h"

using namespace concurrency;

int * FlattenGraph(std::multiset<int>* graph, size_t amountOfNodes, size_t & width)
{
	for (size_t i = 0; i < amountOfNodes; i++)
	{
		if (graph[i].size() > width) width = graph[i].size();
	}

	auto result = new int[amountOfNodes * width];
	for (size_t i = 0; i < amountOfNodes; i++)
	{
		size_t j = 0;
		std::for_each(graph[i].begin(), graph[i].end(), [=, &result, &j](int elem)
		{
			result[i * width + j] = elem;
			j++;
		});
		for (; j < width; j++)
		{
			result[i * width + j] = -1;
		}
	}
	
	return result;
}
