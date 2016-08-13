#include "stdafx.h"
#include "MinCutProblem.h"

std::vector<int>* ReadFile(const char * fileName, size_t amountOfNodes)
{
    FILE * file = NULL;
    fopen_s(&file, fileName, "r");
    if (!file) return NULL;

	std::vector<int>* result = new std::vector<int>[amountOfNodes];

    char c = fgetc(file);
    int readInt = 0;
    bool startOfLine = true;
    int VerticeId = 0;
    while (c != EOF)
    {
        if (c == '\n')
        {
            readInt = 0;
            VerticeId = 0;
            startOfLine = true;
        }
        else if (c == '\t')
        {
            if (startOfLine)
            {
                VerticeId = readInt - 1;
            }
            else
            {
                result[VerticeId].push_back(readInt - 1);
            }
            readInt = 0;
            startOfLine = false;
        }
        else
        {
            readInt *= 10;
            readInt += c - '0';
        }
        c = fgetc(file);
    }

    fclose(file);
    file = NULL;

    return result;
}