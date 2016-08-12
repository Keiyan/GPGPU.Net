#pragma once

#include "stdafx.h"

std::multiset<int>* ReadFile(const char * fileName, size_t amountOfNodes);

int * FlattenGraph(std::multiset<int>* graph, size_t amountOfNodes, size_t & width);

long long GetTimeMs64();
