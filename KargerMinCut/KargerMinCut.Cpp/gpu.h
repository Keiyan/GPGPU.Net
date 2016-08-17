#pragma once

#include "stdafx.h"
#include "utils.h"
#include "rnd\amp_tinymt_rng.h"

using namespace concurrency;

const int amountOfNodes = 200;

int Contract(const array_view<int, 2> & data, int height, int  width, tinymt random) restrict(amp)
{
	int redirections[amountOfNodes];
	int validDestinations[amountOfNodes];
	for (int  i = 0; i < height; i++)
	{
		redirections[i] = i;
		validDestinations[i] = -1;
	}


	for (int  loop = 0; loop < height - 2; loop++)
	{
		unsigned int source, destination;

		do
		{
			source = (random.next_uint() - 1) % height;
		} while (redirections[source] != source);

		int rank = 0;
		for (int  i = 0; i < height; i++)
		{
			if (redirections[i] == source)
			{
				for (int  j = 0; j < width; j++)
				{
					auto local = data[i][j];
					if (local == -1) break;

					auto mappedLocal = redirections[local];
					if (mappedLocal != source
						&& validDestinations[mappedLocal] == -1)
					{
						validDestinations[mappedLocal] = 1;
						rank++;
					}
				}
			}
		}

		int destIndex = (random.next_uint() - 1) % rank;
		for (int i = 0; i < height; i++)
		{
			if (validDestinations[i] > -1)
			{
				if (destIndex == 0) destination = i;
				--destIndex;
				validDestinations[i] = -1;
			}
		}

		for (int  i = 0; i < height; i++)
		{
			if (redirections[i] == source)
			{
				redirections[i] = destination;
			}
		}
	}

	int result = 0;
	int nodeValue = redirections[0];
	for (int  i = 0; i < height; i++)
	{
		if (redirections[i] == nodeValue)
			for (int  j = 0; j < width; j++)
			{
				auto local = data[i][j];
				if (local != -1 && redirections[local] != nodeValue) ++result;
			}
	}
	return result;
}

void GpuMinCut(std::vector<std::vector<int>> graph, size_t iterationCount, size_t height, size_t width, std::vector<int> & results)
{
	auto data = FlattenGraph(graph, width);

	array_view<int, 2> gpuData(height, width, data);

	results.resize(iterationCount);
	array_view<int> gpuResults(iterationCount, results);

	extent<1> e_size(65535);
	tinymt_collection<1> random(e_size);
	extent<1> seedSize(1);
	tinymt_collection<1> seed(seedSize, 0);
	index<1> seedIndex(0);

	parallel_for_each(gpuResults.extent,
		[=](index<1> i) restrict(amp) {
		auto t = random[i % e_size.size()];

		t.initialize(seed[seedIndex].next_uint());

		gpuResults[i] = Contract(gpuData, (int)height, (int)width, t);
	});

	gpuResults.synchronize();
}
