#pragma once

#include "stdafx.h"


std::vector<int>* ReadFile(const char * fileName, size_t amountOfNodes, size_t & width);

long long GetTimeMs64();

int Contract(std::vector<int>* toContract, size_t amountOfNodes);
int Contract(std::vector<int>* toContract, size_t amountOfNodes, size_t width);

void Merge(std::vector<int>* data, int a, int b, size_t amountOfNodes);

void FindEdge(std::vector<int>* data, int & a, int & b, size_t amountOfNodes);