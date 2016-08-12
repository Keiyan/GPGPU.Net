#pragma once

#include "stdafx.h"


std::multiset<int>* ReadFile(const char * fileName);

long long GetTimeMs64();

int Contract(std::multiset<int>* toContract);

void Merge(std::multiset<int>* data, int a, int b);

void FindEdge(std::multiset<int>* data, int & a, int & b);