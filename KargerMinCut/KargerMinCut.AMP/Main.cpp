#include "stdafx.h"
#include "MinCutProblem.h"
#include "rnd/amp_tinymt_rng.h"

using namespace concurrency;

const size_t amountOfNodes = 200;


int Contract(const array_view<int, 2> & data, size_t height, size_t width, tinymt random) restrict(amp)
{
	int redirections[amountOfNodes];
	for (size_t i = 0; i < height; i++)
	{
		redirections[i] = i;
	}

	int validDestinations[amountOfNodes];

	for (size_t loop = 0; loop < height - 2; loop++)
	{
		unsigned int source, destination;

		do
		{
			source = (random.next_uint() - 1) % height;
		} while (redirections[source] != source);

		int rank = 0;
		for (size_t i = 0; i < height; i++)
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

		destination = validDestinations[(random.next_uint()-1) % rank];

		for (size_t i = 0; i < height; i++)
		{
			if (redirections[i] == source)
			{
				redirections[i] = destination;
			}
		}
	}

	int result = 0;
	int nodeValue = redirections[0];
	for (size_t i = 0; i < height; i++)
	{
		if(redirections[i] == nodeValue)
		for (size_t j = 0; j < width; j++)
		{
			auto local = data[i][j];
			auto redirected = redirections[local];
			if (data[i][j] != -1 && redirections[data[i][j]] != nodeValue) ++result;
		}
	}
	return result;
}

int _tmain(int argc, _TCHAR* argv [])
{
	int iterationCount = 65535;//amountOfNodes * amountOfNodes * 3;

    auto start = GetTimeMs64();

	auto graph = ReadFile("kargerMinCut.txt", amountOfNodes);
	
	size_t width = 0;
	auto data = FlattenGraph(graph, amountOfNodes, width);

	array_view<int, 2> gpuData(amountOfNodes, width, data);

	int* results = new int[iterationCount]();
	array_view<int> gpuResults(iterationCount,results);

	tinymt_collection<1> random(gpuResults.extent, 54841);

	parallel_for_each(gpuResults.extent, 
		[=](index<1> i) restrict(amp){
			auto t = random[i];

			gpuResults[i] = Contract(gpuData, amountOfNodes, width, t);
    });

	gpuResults.synchronize();

    int result = INT_MAX;
	for (int i = 0; i < iterationCount; i++)
	{
		if (results[i] < result) result = results[i];
	}

    auto stop = GetTimeMs64();

    std::cout << "Edge count is " << result << std::endl;
    std::cout << "Time is " << (stop - start) / 10000 << " milliseconds" << std::endl;

    return result;
}

