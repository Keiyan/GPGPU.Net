#pragma once

#include "stdafx.h"


std::vector<int>* ReadFile(const char * fileName, size_t amountOfNodes);

long long GetTimeMs64();

int Contract(std::vector<int>* toContract, size_t amountOfNodes);

void Merge(std::vector<int>* data, int a, int b, size_t amountOfNodes);

void FindEdge(std::vector<int>* data, int & a, int & b, size_t amountOfNodes);