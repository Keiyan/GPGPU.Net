#include "stdafx.h"
#include "MinCutProblem.h"
#include <amp.h>
#include <ppl.h>

using namespace concurrency;

const size_t amountOfNodes = 200;

int _tmain(int argc, _TCHAR* argv [])
{
	int iteractionCount = amountOfNodes * amountOfNodes * 3;
    auto start = GetTimeMs64();
   
    std::vector<int> results;
    parallel_for(0, iteractionCount, 1, [&results](int i){
        auto graph = ReadFile("kargerMinCut.txt", amountOfNodes);
        results.push_back(Contract(graph, amountOfNodes));
        delete [] graph;
    });

    int result = INT_MAX;
    std::for_each(results.begin(), results.end(), [&result](int val)
    {
        if (val < result) result = val;
    });

    auto stop = GetTimeMs64();

    std::cout << "Edge count is " << result << std::endl;
    std::cout << "Time is " << (stop - start) / 10000 << " milliseconds" << std::endl;

    return results[0];
}

