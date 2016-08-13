#pragma once

#include "stdafx.h"


std::vector<int>* ReadFile(const char * fileName);

long long GetTimeMs64();

int Contract(std::vector<int>* toContract);

void Merge(std::vector<int>* data, int a, int b);

void FindEdge(std::vector<int>* data, int & a, int & b);