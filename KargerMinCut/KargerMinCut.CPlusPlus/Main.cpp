#include "stdafx.h"
#include "MinCutProblem.h"
#include <amp.h>
#include <ppl.h>

using namespace concurrency;

const size_t amountOfNodes = 200;

int _tmain(int argc, _TCHAR* argv [])
{
    int iterationCount = 1;//amountOfNodes * amountOfNodes * 3;
    auto start = GetTimeMs64();
   
    size_t width = 0;
    auto graph = ReadFile("kargerMinCut.txt", amountOfNodes, width);

    std::vector<int> results(iterationCount);
    parallel_for(0, iterationCount, 1, [&results, &graph, width](int i){
        results.push_back(Contract(graph, amountOfNodes, width));
    });

    delete[] graph;

    int result = INT_MAX;
    std::for_each(results.begin(), results.end(), [&result](int val)
    {
        if (val < result) result = val;
    });

    auto stop = GetTimeMs64();

    std::cout << "Performed " << iterationCount << " iterations" << std::endl;
    std::cout << "Edge count is " << result << std::endl;
    std::cout << "Time is " << (stop - start) / 10000 << " milliseconds" << std::endl;

    return results[0];
}

